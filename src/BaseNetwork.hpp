//
//  BaseNetwork.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef BaseNetwork_h
#define BaseNetwork_h
#include "VertexBaseContainer.hpp"

namespace FastEMD
{
using namespace types;

//MARK: Vertex Base Class
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
class BaseNetwork : public VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, 2>
{
public:
    
    BaseNetwork(NODE_T numberOfNodes, std::string containerName,
                std::vector<std::string> dataNames, uchar fields)
    : VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, 2>(numberOfNodes, containerName,
                                                       dataNames, fields) {};
    
    //MARK: Iterators
    inline auto fromNode(NODE_T nodeIndex) {return this->begin() + nodeIndex;}
    inline auto fromNode(NODE_T nodeIndex) const
        {return this->begin() + nodeIndex;}
    
//    template<typename T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
//    inline auto& fromNode(NODE_T nodeIndex)
//        {return *CVMatRowIterator(this->data, nodeIndex);}
//    template<typename T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
//    inline auto& fromNode(NODE_T nodeIndex) const
//        {return *CVMatRowIterator(this->data, nodeIndex);}
    
    // MARK: public member functions
    template<typename... Args>
    void fill(const BaseNetwork<NUM_T, INTERFACE_T, SIZE>& input, Args&&... args);
    
    template <class F>
    void forEach(F&& func);
    
    template <class F>
    void forEach(F&& func) const;
   
    // break condition for inner loop
    inline bool breakCondition(NODE_T fromIndex, NODE_T toIndex) const
        {return ((fromIndex < this->artificialNodeIndex()
                  && toIndex == this->artificialNodeIndex()) ||
                (fromIndex == this->artificialNodeIndex() && toIndex == this->thresholdNodeIndex()));}
    
    // returns an iterator to "value" in row "node"
    inline auto findIndex(NODE_T node, NODE_T value);

   
    //MARK: operator overloading
    template<typename _T, typename _I, NODE_T _S>
    friend std::ostream& operator<<(std::ostream& os,
                                   const BaseNetwork<_T, _I, _S>& network);

    
private:
    inline virtual void fillCore(
                    typeSelector1d<NUM_T, INTERFACE_T, SIZE> const & costFrom,
                                 NODE_T from, NODE_T i,
                    Counter<NODE_T, INTERFACE_T, SIZE>& counters) = 0;

};

//MARK: Implentations
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
template<class F>
void BaseNetwork<NUM_T, INTERFACE_T, SIZE>::forEach(F&& func)
{
    // init flow
    NODE_T from = 0;
    for (auto& row : *this)
    {
        for (NODE_T i = 0; i < this->cols(); i += this->fields())
        {
            NODE_T to = row[i];
            func(row, from, i);
            if (this->breakCondition(from, to)) break;
        }
        ++from;
    }
}
    
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
template<class F>
void BaseNetwork<NUM_T, INTERFACE_T, SIZE>::forEach(F&& func) const
{
    // init flow
    NODE_T from = 0;
    for (auto const & row : *this)
    {
        for (NODE_T i = 0; i < this->cols(); i += this->fields())
        {
            NODE_T to = row[i];
            func(row, from, i);
            if (this->breakCondition(from, to)) break;
        }
        ++from;
    }
}
 
        
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
template<typename... Args>
void BaseNetwork<NUM_T, INTERFACE_T, SIZE>::fill(
                                        const BaseNetwork& input,
                                        Args&&... args)
{
    auto f = std::bind(&BaseNetwork::fillCore,
                       this, std::placeholders::_1,
                       std::placeholders::_2,
                       std::placeholders::_3,
                       std::forward<Args>(args)...);
    return input.forEach(f);
};
        

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
inline auto BaseNetwork<NUM_T, INTERFACE_T, SIZE>::findIndex(NODE_T node, NODE_T value)
{
    auto row = this->fromNode(node);
    auto it = row->begin();
    auto end = row->begin() + this->size() * this->fields();
    for ( ; it != end; it += this->fields())
    {
        if (*it == value) break;
        if (breakCondition(node, *it)) {it = row->end(); break;}
    }
    return it;
}
    
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
std::ostream& operator<<(std::ostream& os,
                               const BaseNetwork<NUM_T, INTERFACE_T, SIZE>& network)
{
    // Print the network name.
    os << network._containerName << ": " << std::endl;
    
    // Print one line describing the containing data.
    os << "vertex: [";
    for (auto& dataName : network._dataNames)
    {
        os << dataName;
        if (&dataName != &network._dataNames.back()) os << " : ";
    }
    os << "]" << std::endl;
    
    // Now, print the actual data.
    NODE_T vertexIndex = 0;
    for (auto const& row : network)
    {
        NODE_T counter = 0;
        os << vertexIndex << ": [";
        for(auto const& element : row)
        {
            counter++;
            os << element;
            if (counter % network.fields() == 0) os << "] [";
            else os << " : ";
            if (network.breakCondition(vertexIndex, element)) break;
        }
        for(NODE_T idx = 0; idx < network.fields() - 1; ++idx)
        {
            if (idx == 1) os << " : ";
            os << row[counter + idx];
        }
        os << "]" << std::endl;
        ++vertexIndex;
    }
    return os;
}
} // namespace FastEMD
#endif /* BaseNetwork_h */
