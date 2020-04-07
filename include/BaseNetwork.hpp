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
#include "Counter.hpp"

namespace FastEMD
{
using namespace types;

//MARK: Vertex Base Class
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE, uchar FIELDS>
class BaseNetwork : public VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, FIELDS, 2>
{
public:
    
    BaseNetwork(NODE_T numberOfNodes,
                std::string containerName,
                std::vector<std::string> dataNames)
    : VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, FIELDS, 2>(numberOfNodes,
                                                               containerName,
                                                               dataNames) {};
    
    BaseNetwork(vector2d<NUM_T> _data,
                std::string containerName,
                std::vector<std::string> dataNames)
    : VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, FIELDS, 2>(_data,
                                                               containerName,
                                                               dataNames) {};
    
    //MARK: Iterators
    inline auto fromNode(NODE_T nodeIndex) {return this->begin() + nodeIndex;}
    inline auto fromNode(NODE_T nodeIndex) const
        {return this->begin() + nodeIndex;}
    
    // MARK: public member functions
    // break condition for inner loop
    inline bool breakCondition(NODE_T fromIndex, NODE_T toIndex) const
        {return ((fromIndex < this->artificialNodeIndex()
                  && toIndex == this->artificialNodeIndex()) ||
                (fromIndex == this->artificialNodeIndex() && toIndex == this->thresholdNodeIndex()));}
    
    // returns an iterator to "value" in row "node"
    inline auto findIndex(NODE_T node, NODE_T value);

   
    //MARK: operator overloading
    template<typename _T, typename _I, NODE_T _S, uchar _F>
    friend std::ostream& operator<<(std::ostream& os,
                                   const BaseNetwork<_T, _I, _S, _F>& network);

    
//private:
//    inline virtual void fillCore(
//                    typeSelector1d<NUM_T, INTERFACE_T, SIZE, 2> const & costFrom,
//                                 NODE_T from, NODE_T i,
//                    Counter<NODE_T, INTERFACE_T, SIZE>& counters) = 0;

};

//MARK: Implentations
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE, uchar FIELDS>
inline auto BaseNetwork<NUM_T, INTERFACE_T, SIZE, FIELDS>::findIndex(NODE_T node, NODE_T value)
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
    
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE, uchar FIELDS>
std::ostream& operator<<(std::ostream& os,
                               const BaseNetwork<NUM_T, INTERFACE_T, SIZE, FIELDS>& network)
{
    // Print the network name.
    os << network._containerName << ":" << std::endl;
    
    // Print one line describing the containing data.
    os << "vertex: [";
    for (auto& dataName : network._dataNames)
    {
        os << dataName;
        if (&dataName != &network._dataNames.back()) os << " : ";
    }
    os << "]" << std::endl;
    
    bool isFlowNetwork = network._containerName == "Flow Network";
    // Now, print the actual data.
    NODE_T vertexIndex = 0;
    for (auto const& row : network)
    {
        bool costSignHasChanged = false;
        NODE_T counter = 0;
        os << vertexIndex << ": [";
        for(auto const& element : row)
        {
            counter++;
            os << element;
            if (counter % network.fields() == 0) os << "] [";
            else os << " : ";
            if (network.breakCondition(vertexIndex, element))
            {
                if(!(costSignHasChanged ^ isFlowNetwork)) break;
                else costSignHasChanged = true;
            }
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
