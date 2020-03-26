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
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
class ReducedCostsNetwork : public BaseNetwork<NUM_T, INTERFACE_T, SIZE>
{
    
protected:
    ///@brief Core logic for reducing the cost along one edge.
    inline void reduceCostCore(
        typeSelector1d<NUM_T, INTERFACE_T, SIZE> & thisFrom,
        const NODE_T from,
        const NODE_T i,
        const Counter<NUM_T, INTERFACE_T, SIZE>& d,
        const Counter<bool, INTERFACE_T, SIZE>& finalNodesFlg,
        const NODE_T l);
    
public:
    ReducedCostsNetwork(NODE_T numberOfNodes, std::string containerName,
                        std::vector<std::string> dataNames, uchar fields)
    : BaseNetwork<NUM_T, INTERFACE_T, SIZE>(numberOfNodes, containerName,
                                               dataNames, fields) {};
    
    ///@brief Calculates the residual costs for all edges in the Network.
    /// Calls "forEach" with "reduceCostCore"
    template<typename... Args>
    void reduceCost(Args&&... args);
};

//MARK: Implementations
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
inline void ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE>::reduceCostCore(
            typeSelector1d<NUM_T, INTERFACE_T, SIZE> & thisFrom,
            const NODE_T from,
            const NODE_T i,
            const Counter<NUM_T, INTERFACE_T, SIZE>& d,
            const Counter<bool, INTERFACE_T, SIZE>& finalNodesFlg,
            const NODE_T l)
{
    auto it = &thisFrom[2 * i];
    if (finalNodesFlg[*it]) it[1] -= d[*it] - d[l];
    if (finalNodesFlg[from]) it[1] += d[from] - d[l];
    
}

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
template<typename... Args>
void ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE>::reduceCost(Args&&... args)
{
    auto f = std::bind(
            &ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE>::reduceCostCore,
            this,
            std::placeholders::_1, std::placeholders::_2,
            std::placeholders::_3, std::forward<Args>(args)...);
    return this->forEach(f);
}


} // namespace FastEMD
#endif /* ReducedCostsNetwork_h */
