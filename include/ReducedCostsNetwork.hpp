//
//  ReducedCostsNetwork.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef ReducedCostsNetwork_h
#define ReducedCostsNetwork_h

#include "BaseNetwork.hpp"
namespace FastEMD
{
using namespace types;

//MARK: Declaration
///@brief Parent class for ReducedCostFrowardEdgesNetwork and
/// ReducedCostAndCapacityBackwardEdgesNetwork
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE, uchar FIELDS>
class ReducedCostsNetwork : public BaseNetwork<NUM_T, INTERFACE_T, SIZE, FIELDS>
{
    
public:
    ReducedCostsNetwork(NODE_T numberOfNodes,
                        std::string containerName,
                        std::vector<std::string> dataNames)
    : BaseNetwork<NUM_T, INTERFACE_T, SIZE, FIELDS>(numberOfNodes,
                                                    containerName,
                                                    dataNames)
    {};
    
    ReducedCostsNetwork(vector2d<NUM_T> _data,
                        std::string containerName,
                        std::vector<std::string> dataNames)
    : BaseNetwork<NUM_T, INTERFACE_T, SIZE, FIELDS>(_data,
                                                    containerName,
                                                    dataNames)
    {};

    
    ///@brief Calculates the residual costs for all edges in the Network.
    /// Calls "forEach" with "reduceCostCore"
    inline
    void reduceCost(const Counter<NUM_T, INTERFACE_T, SIZE>& d,
                    const Counter<bool, INTERFACE_T, SIZE>& finalNodesFlg,
                    const NODE_T l);
};

//MARK: Implementations
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE, uchar FIELDS>
inline
void ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE, FIELDS>::reduceCost(
                            const Counter<NUM_T, INTERFACE_T, SIZE>& d,
                            const Counter<bool, INTERFACE_T, SIZE>& finalNodesFlg,
                            const NODE_T l)
{
    NODE_T from = 0;
    for (auto& row : *this)
    {
        for (NODE_T i = 0; i < this->cols(); i += this->fields())
        {
            NODE_T to = row[i];
            auto it = &row[i];
            if (finalNodesFlg[from]) it[1] += d[from] - d[l];
            if (finalNodesFlg[*it]) it[1] -= d[*it] - d[l];
            if (this->breakCondition(from, to)) break;
        }
        ++from;
    }
}


} // namespace FastEMD
#endif /* ReducedCostsNetwork_h */
