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

///@brief Parent class for ReducedCostFrowardEdgesNetwork and
/// ReducedCostAndCapacityBackwardEdgesNetwork
template<typename... _Types>
class ReducedCostsNetwork : public BaseNetwork<_Types...>
{
    
protected:
    ///@brief Core logic for reducing the cost along one edge.
    inline void reduceCostCore(
        NUM_T* thisFrom,
        const NODE_T from,
        const NODE_T i,
        const Counter<NUM_T, INTERFACE_T, _size>& d,
        const Counter<bool, INTERFACE_T, _size>& finalNodesFlg,
        const NODE_T l);
    
public:
    ///@brief Calculates the residual costs for all edges in the Network.
    /// Calls "forEach" with "reduceCostCore"
    template<typename... Args>
    void reduceCost(Args&&... args);
}

#endif /* ReducedCostsNetwork_h */
