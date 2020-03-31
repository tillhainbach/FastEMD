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
    
protected:
    ///@brief Core logic for reducing the cost along one edge.
    inline void reduceCostCore(
        typeSelector1d<NUM_T, INTERFACE_T, SIZE, FIELDS> & thisFrom,
        const NODE_T from,
        const NODE_T i,
        const Counter<NUM_T, INTERFACE_T, SIZE>& d,
        const Counter<bool, INTERFACE_T, SIZE>& finalNodesFlg,
        const NODE_T l);
    
public:
    ReducedCostsNetwork(NODE_T numberOfNodes,
                        std::string containerName,
                        std::vector<std::string> dataNames)
    : BaseNetwork<NUM_T, INTERFACE_T, SIZE, FIELDS>(numberOfNodes,
                                                    containerName,
                                                    dataNames)
    {};
    
    ReducedCostsNetwork(typeSelector2d<NUM_T, INTERFACE_T, SIZE, FIELDS> _data,
                        std::string containerName,
                        std::vector<std::string> dataNames)
    : BaseNetwork<NUM_T, INTERFACE_T, SIZE, FIELDS>(_data,
                                                    containerName,
                                                    dataNames)
    {};

    
    ///@brief Calculates the residual costs for all edges in the Network.
    /// Calls "forEach" with "reduceCostCore"
    template<typename... Args>
    void reduceCost(Args&&... args);
};

//MARK: Implementations
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE, uchar FIELDS>
inline void ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE, FIELDS>::reduceCostCore(
            typeSelector1d<NUM_T, INTERFACE_T, SIZE, FIELDS> & thisFrom,
            const NODE_T from,
            const NODE_T i,
            const Counter<NUM_T, INTERFACE_T, SIZE>& d,
            const Counter<bool, INTERFACE_T, SIZE>& finalNodesFlg,
            const NODE_T l)
{
    auto it = &thisFrom[this->fields() * i];
    if (finalNodesFlg[from]) it[1] += d[from] - d[l];
    if (finalNodesFlg[*it]) it[1] -= d[*it] - d[l];
}

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE, uchar FIELDS>
template<typename... Args>
void ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE, FIELDS>::reduceCost(Args&&... args)
{
    auto f = std::bind(
            &ReducedCostsNetwork::reduceCostCore,
            this,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3,
            std::forward<Args>(args)...);
    return this->forEach(f);
}


} // namespace FastEMD
#endif /* ReducedCostsNetwork_h */
