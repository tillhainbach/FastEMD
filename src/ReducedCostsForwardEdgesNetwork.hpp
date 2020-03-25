//
//  ReducedCostsForwardEdgesNetwork.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef ReducedCostsForwardEdgesNetwork_h
#define ReducedCostsForwardEdgesNetwork_h
#include "ReducedCostsNetwork.hpp"

namespace FastEMD
{
using namespace types;

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0>
class ReducedCostsForwardEdgesNetwork : public ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE>
{
public:
    ReducedCostsForwardEdgesNetwork(NODE_T num_nodes)
    : ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE >(num_nodes, 2, {"to", "reduced cost"}) {};
    
private:
    inline void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                         Counter<NUM_T, INTERFACE_T, SIZE>& counters) override;
    
};

//MARK: Implementation
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
inline void ReducedCostsForwardEdgesNetwork<NUM_T, INTERFACE_T, SIZE>::fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, SIZE>& counters)
{
    (*this)[from][i] = costFrom[i];
    (*this)[from][i + 1] = costFrom[i + 1];
}
} // namespace FastEMD

#endif /* ReducedCostsForwardEdgesNetwork_h */
