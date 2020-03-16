//
//  Vertex.hpp
//  FastEMD
//
//  Created by Till Hainbach on 09.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include "utils/utils.h"
#include "utils/types.h"
#include <type_traits>

template<typename NUM_T, typename INTERFACE_T, int arrSize = 0>
class Base1dContainer
{
constexpr static InterfaceRequirement<INTERFACE_T, arrSize> check{};
    
public:
    Base1dContainer(NODE_T _N) : _num_nodes(_N) {};

    //TODO: check if ptr() is really necessary.
    virtual inline NUM_T * ptr() = 0;
    virtual inline NUM_T const * ptr() const = 0;
    
    inline auto begin(){return data.begin();}
    inline auto end(){return data.begin() + data.size();}
    
    inline auto size(){return _num_nodes;}
    inline auto resize(NODE_T _newSize){_num_nodes = _newSize;}
    
    inline auto& operator[](NODE_T idx){return ptr()[idx];}
    inline const auto& operator[](NODE_T idx) const
        {return ptr()[idx];}
            
protected:

    NODE_T _num_nodes;
    typeSelector1d<NUM_T, INTERFACE_T, arrSize> data;
};
// ------------------- VertexWeights Class ----------------------
template<typename NUM_T, typename INTERFACE_T, int size = 0>
class Base1dContainerImpl : public Base1dContainer<NUM_T, INTERFACE_T, size>
{
public:
    Base1dContainerImpl(NODE_T _N) : Base1dContainer<NUM_T, INTERFACE_T, size>(_N) {};
    
    inline NUM_T * ptr()
        {return static_cast<NUM_T*>(this->data.data());}
    inline NUM_T const * ptr() const
        {return static_cast<NUM_T const *>(this->data.data());}
};

template<typename NUM_T>
class Base1dContainerImpl<NUM_T, OPENCV>: public Base1dContainer<NUM_T, OPENCV>
{
public:
    Base1dContainerImpl(NODE_T _N) : Base1dContainer<NUM_T, OPENCV>(_N){};
    
    inline NUM_T * ptr()
        {return this->data.template ptr<NUM_T>(0);}
    inline NUM_T const * ptr() const
        {return this->data.template ptr<const NUM_T>(0);}
};
// ---------------------- Counter Class --------------------------



template<typename NUM_T, typename INTERFACE_T, int size>
class Counter : public Base1dContainerImpl<NUM_T, INTERFACE_T, size>
{
public:
    Counter(NODE_T _N)
    : Base1dContainerImpl<NUM_T, INTERFACE_T, size>(_N){};
};

template<typename NUM_T, typename INTERFACE_T, int size>
class Dist : public Base1dContainerImpl<NUM_T, INTERFACE_T, size>
{
    unsigned char fields;
    std::vector<std::string> datanames;
public:
    Dist(NODE_T _N)
    : fields(2)
    , datanames({"to", "dist"})
    , Base1dContainerImpl<NUM_T, INTERFACE_T, size>(_N * 2){};
};


// --------------- Vertex Weights Base Class ----------------------
template<typename NUM_T, typename INTERFACE_T, int size = 0>
class VertexWeights : public Base1dContainerImpl<NUM_T, INTERFACE_T, size>
{
    constexpr static InterfaceRequirement<INTERFACE_T, size> check{};
    
public:
    
    VertexWeights(NODE_T _N)
    : Base1dContainerImpl<NUM_T, INTERFACE_T, size>(_N) {};
    
    template<typename _T>
    std::tuple<NUM_T, NUM_T, NODE_T, NODE_T>
        fillWeights(const _T& P, const _T& Q,  const NODE_T N,
            Counter<NUM_T, INTERFACE_T, size/2>& nonZeroSourceNodes,
            Counter<NUM_T, INTERFACE_T, size/2>& nonZeroSinkNodes);
    
    template<typename _T>
    void preFlowWeights(const _T& P, const _T& Q);
    
    NUM_T calcPreFlowCost(
            Counter<NUM_T, INTERFACE_T, size/2>& sinkNodes,
            Counter<NUM_T, INTERFACE_T, size/2>& uniqueJs,
            NUM_T sourcesCounter, NUM_T maxC, NODE_T costSize);
    
    void swapWeights();
    
    NODE_T THRESHOLD_NODE;
    NODE_T ARTIFICIAL_NODE;
            
protected:

    NODE_T _num_nodes;
    typeSelector1d<INTERFACE_T, NUM_T, size> data;
};

// ----------------- Vertex Base Class ---------------------------
template<typename NUM_T, typename INTERFACE_T, int size = 0>
class Vertex_Base
{
    constexpr static InterfaceRequirement<INTERFACE_T, size> check{};
    
    std::vector<std::string> datanames;
    
protected:
    NODE_T _num_nodes;
    NODE_T THRESHOLD_NODE;
    NODE_T ARTIFICIAL_NODE;
    
    inline void reduceCostCore(
            NUM_T* thisFrom,
            const NODE_T from,
            const NODE_T i,
            const Counter<NUM_T, INTERFACE_T, size>& d,
            const Counter<bool, INTERFACE_T, size>& finalNodesFlg,
            const NODE_T l);
    
public:
    typeSelector2d<NUM_T, INTERFACE_T, size> matrix;

    template< class T = INTERFACE_T, std::enable_if_t<isARRAY<T>, int> = 0>
    Vertex_Base(NODE_T num_nodes, unsigned char _fields,
           std::vector<std::string>& names)
    : _num_nodes (num_nodes)
    , THRESHOLD_NODE(num_nodes - 2)
    , ARTIFICIAL_NODE(num_nodes - 1)
    , fields(_fields)
    , datanames(names) {};
    
    template< class T = INTERFACE_T, std::enable_if_t<isVECTOR<T>, int> = 0>
    Vertex_Base(NODE_T num_nodes, unsigned char _fields,
           std::vector<std::string>& names)
    : _num_nodes (num_nodes)
    , THRESHOLD_NODE(num_nodes - 2)
    , ARTIFICIAL_NODE(num_nodes - 1)
    , fields(_fields)
    , datanames(names)
    , matrix(num_nodes, std::vector<NUM_T>(num_nodes)) {};
    
    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    Vertex_Base(NODE_T num_nodes, unsigned char _fields,
           std::vector<std::string>& names)
    : _num_nodes (num_nodes)
    , THRESHOLD_NODE(num_nodes - 2)
    , ARTIFICIAL_NODE(num_nodes - 1)
    , fields(_fields)
    , datanames(names)
    , matrix(num_nodes, num_nodes * _fields, 0) {};
    
    template<typename _T, typename _F, int _s>
    friend std::ostream& operator<<(std::ostream& os,
                            const Vertex_Base<_T, _F, _s>& vertex);
    
    inline virtual NUM_T const * row(NODE_T _row) const = 0;
    inline virtual NUM_T * row(NODE_T _row) = 0;
    
    inline auto const rows() const {return _num_nodes;}
    inline auto const cols() const {return _num_nodes * fields;}

    inline auto resize(NODE_T _newSize){_num_nodes = _newSize;}
    
    template<typename... Args>
    void fill(const Vertex_Base& input, Args&&... args);
    
    template <class F>
    void forEach(F&& func);
    
    template <class F>
    void forEach(F&& func) const;
    
    inline auto begin(){return matrix.begin();}
    inline auto end(){return matrix.begin() + _num_nodes;}
    
    // std::array + std::vector need be return as reference.
    template< class T = INTERFACE_T, std::enable_if_t<!isOPENCV<T>, int> = 0>
    inline auto& operator[](NODE_T idx) {return matrix[idx]; }
    
    // opencv operator[] returns NUM_T * !!
    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    inline auto operator[](NODE_T idx) {return matrix[idx]; }
    
    // break condition for inner loop
    inline bool breakCondition(NODE_T rowIt, NODE_T colIt) const
        {return ((rowIt < ARTIFICIAL_NODE && colIt == ARTIFICIAL_NODE) ||
                (rowIt == ARTIFICIAL_NODE && colIt == THRESHOLD_NODE));}
    
    // returns an iterator to "value" in row "node"
    inline auto findIndex(NODE_T& node, NODE_T& value);

    // calculates the residual cost in matrix
    template<typename... Args>
    void reduceCost(Args&&... args);
    
    Vertex_Base& operator=(const Vertex_Base& vertex)
    {
        matrix = vertex.matrix;
        _num_nodes = vertex._num_nodes;
        datanames = vertex.datanames;
        return *this;
    }
    
    unsigned char fields;
    
private:
    inline virtual void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, size>& counters) = 0;
};

// -------------Vertex partial specialization ----------------------
template<typename NUM_T, typename INTERFACE_T, int size = 0>
class Vertex : public Vertex_Base<NUM_T, INTERFACE_T, size>
{
public:
    Vertex(NODE_T num_nodes, unsigned char channels,
            std::vector<std::string> names)
    : Vertex_Base<NUM_T, INTERFACE_T, size >(num_nodes, channels, names){};
    
    inline NUM_T const * row(const NODE_T _row) const override
        {return this->matrix.at(_row).begin();}
    inline NUM_T * row(const NODE_T _row) override
        {return this->matrix.at(_row).begin();}
};
    
template<typename NUM_T>
class Vertex <NUM_T, OPENCV>: public Vertex_Base<NUM_T, OPENCV>
{
public:
    Vertex (NODE_T num_nodes, unsigned char channels,
            std::vector<std::string> names)
    : Vertex_Base<NUM_T, OPENCV>(num_nodes, channels, names){};

    NODE_T _num_nodes;
    inline NUM_T const * row(const NODE_T _row) const override
        {return this->matrix.template ptr<const NUM_T>(_row);}
    inline NUM_T *  row(const NODE_T _row) override
        {return this->matrix.template ptr<NUM_T>(_row);}
};

// ------------------- Vertex Subclasses -------------------------
template<typename NUM_T, typename INTERFACE_T, int size = 0>
class Cost : public Vertex<NUM_T, INTERFACE_T, size>
{
public:
    Cost(NODE_T num_nodes)
    : Vertex<NUM_T, INTERFACE_T, size >(num_nodes, 2, {"to", "cost"}) {};
    
    void fillCostOPENCV(cv::InputArray _VertexWeights, cv::InputArray _costMatrix, int N, int maxC)
    {
        CV_Assert(_VertexWeights.rows() == 1); // must be flat.
        
        cv::Mat1i VertexWeights;
        cv::Mat costMatrix;
        if (!_VertexWeights.empty())
        {
            VertexWeights = _VertexWeights.getMat();
        }
        if (!_costMatrix.empty())
        {
            costMatrix = _costMatrix.getMat();
        }
        
        cv::Mat data = this->matrix;
    
        cv::Rect sources(0, 0, N, 1);
        cv::Rect sinks(N, 0, N, 1);
        std::vector<cv::Point2i> nonZeroSinkNode;
        std::vector<cv::Point2i> nonZeroSourceNode;
        cv::findNonZero(VertexWeights(sources), nonZeroSourceNode);
        cv::findNonZero(VertexWeights(sinks), nonZeroSinkNode);
        
        std::vector<cv::Point> vertexNotFlowingToThreshold;
        vertexNotFlowingToThreshold.reserve(nonZeroSinkNode.size() * nonZeroSourceNode.size());
        for (auto& point : nonZeroSourceNode)
        {
            for (auto& p : nonZeroSinkNode)
            {
                cv::Point k(point.x, p.x);
                if (costMatrix.at<int>(k) != maxC) vertexNotFlowingToThreshold.push_back(k);
            }
        }
        
        int* dataPtr = data.ptr<int>(0);
        int i = -1;
        int j = 0;
        int prevX = -1;
        int prevY = -1;
        
        for (auto& point : vertexNotFlowingToThreshold)
        {
            
            if(prevX != point.x) ++i;
            std::cout << point << " " << i << " ";
            j = (prevX == point.x && prevY != point.y) ? j + 2 : 0;
            dataPtr[i * (data.cols * data.channels()) + j] = j/data.channels();
            dataPtr[i * (data.cols * data.channels()) + j + 1] = costMatrix.at<int>(point);
            prevX = point.x;
            prevY = point.y;
        }
        
       
//        int j;
//        i = 0;
//        for (auto& point : nonZeroSourceNode)
//        {
//            j = 0;
//            for (auto& p : nonZeroSinkNode)
//            {
//                cv::Point k(point.x, p.x);
//                if (costMatrix.at<int>(k) == maxC) continue;
//                dataPtr[i * (data.cols * data.channels()) + j] = j/data.channels();
//                dataPtr[i * (data.cols * data.channels()) + j + 1] = costMatrix.at<int>(k);
//                std::cout << dataPtr[i * data.rows + j + 1] << " ";
//                j += data.channels();
//            }
//            if (j != 0)
//            {
//                dataPtr[i * (data.cols * data.channels()) + j] = -1;
//                ++i;
//            }
//        }
        this->_num_nodes = i + 1;
    }
    
    template<class _T2d>
    void fill(
        VertexWeights<NUM_T, INTERFACE_T, size>& weights,
        Counter<NUM_T, INTERFACE_T, size/2>& sourceNodes,
        Counter<NUM_T, INTERFACE_T, size/2>& sinkNodes,
        Counter<NUM_T, INTERFACE_T, size/2>& uniqueJs,
        const _T2d& costMatrix, const NUM_T maxC,
        const int REMOVE_NODE_FLAG);
    
private:
    inline void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, size>& counters)
    override {std::cout << "not in use!" << std::endl;};
};

template<typename NUM_T, typename INTERFACE_T, int size = 0>
class ForwardCost : public Vertex<NUM_T, INTERFACE_T, size >
{
public:
    ForwardCost(NODE_T num_nodes)
    : Vertex<NUM_T, INTERFACE_T, size >(num_nodes, 2, {"to", "reduced cost"}) {};
    
private:
    inline void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                         Counter<NUM_T, INTERFACE_T, size>& counters) override;
    
};

template<typename NUM_T, typename INTERFACE_T, int size = 0>
class Flow : public Vertex<NUM_T, INTERFACE_T, size >
{
public:
    Flow(NODE_T num_nodes)
    : Vertex<NUM_T, INTERFACE_T, size>(num_nodes, 3, {"to", "cost", "flow"}) {};
    
    NUM_T calcDist();
    
private:
    inline void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                         Counter<NUM_T, INTERFACE_T, size>& counters) override;
};

template<typename NUM_T, typename INTERFACE_T, int size = 0>
class BackwardCost : public Vertex<NUM_T, INTERFACE_T, size >
{
public:
    BackwardCost(NODE_T num_nodes)
    : Vertex<NUM_T, INTERFACE_T, size >(num_nodes, 3,
            {"to", "reduced cost", "residual capacity"})
    {};

private:
    inline void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                         Counter<NUM_T, INTERFACE_T, size>& counters) override;
};


#include "Vertex.cpp"
#endif /* Vertex_hpp */
