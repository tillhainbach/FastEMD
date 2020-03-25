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
    : VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, 2>(numberOfNodes, containerName
                                                       dataNames, fields) {};
    
    // MARK: public member functions
    template<typename... Args>
    void fill(const BaseNetwork<NUM_T, INTERFACE_T, SIZE>& input, Args&&... args);
    
    template <class F>
    void forEach(F&& func);
    
    template <class F>
    void forEach(F&& func) const;
   
    // break condition for inner loop
    inline bool breakCondition(NODE_T fromIndex, NODE_T toIndex) const
        {return ((fromIndex < this->_artificialNodeIndex && toIndex == this->_artificialNodeIndex) ||
                (fromIndex == this->_artificialNodeIndex && toIndex == this->_thresholdNodeIndex));}
    
    // returns an iterator to "value" in row "node"
    inline auto findIndex(NODE_T node, NODE_T value);

   
    //MARK: operator overloading
    template<typename _T, typename _I, NODE_T _S>
    friend std::ostream& operator<<(std::ostream& os,
                                   const BaseNetwork<_T, _I, _S>& network);

    
private:
    inline virtual void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, SIZE>& counters) = 0;

};

//MARK: Implentations
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
template<class F>
void BaseNetwork<NUM_T, INTERFACE_T, SIZE>::forEach(F&& func)
{
    // init flow
    NUM_T step = this->fields;
    NODE_T rows = this->rows();
    NODE_T cols = this->cols();
    for (NODE_T from = 0; from < rows; ++from)
    {
        auto thisFrom = this->row(from);
        for (NODE_T i = 0; i < cols; i += step)
        {
            NODE_T to = thisFrom[i];
            func(thisFrom, from, i);
            if (this->breakCondition(from, to)) break;
        }
    }
}
    
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
template<class F>
void BaseNetwork<NUM_T, INTERFACE_T, SIZE>::forEach(F&& func) const
{
    // init flow
    NUM_T step = this->fields;
    NODE_T rows = this->rows();
    NODE_T cols = this->cols();
    for (NODE_T from = 0; from < rows; ++from)
    {
        const auto thisFrom = this->row(from);
        for (NODE_T i = 0; i < cols; i += step)
        {
            NODE_T to = thisFrom[i];
            func(thisFrom, from, i);
            if (this->breakCondition(from, to)) break;
        }
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
    auto row = (*this)[node];
    auto it = row.begin();
    auto end = row.begin() + this->_num_nodes * this->fields;
    for ( ; it != end; it += this->fields )
    {
        if (*it == value) break;
        if (breakCondition(node, *it)) {it = row.end(); break;}
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
    NODE_T counter = 0;
    for (auto const& row : network)
    {
        os << vertexIndex;
        for(auto const& element : row)
        {
            counter++;
            os << "[" << element;
            if (counter % network._fields == 0) os << "]";
            else os << " : ";
            if (network.breakCondition(vertexIndex, element)) break;
        }
        os << std::endl;
        ++vertexIndex;
    }
    return os;
}
} // namespace FastEMD
#endif /* BaseNetwork_h */
