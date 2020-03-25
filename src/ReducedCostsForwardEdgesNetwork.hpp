//
//  ReducedCostsForwardEdgesNetwork.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef ReducedCostsForwardEdgesNetwork_h
#define ReducedCostsForwardEdgesNetwork_h
namespace FastEMD
{
using namespace types;

template<typename NUM_T, typename INTERFACE_T, int size = 0>
class ReducedCostsForwardEdgesNetwork : public Vertex<NUM_T, INTERFACE_T, size >
{
public:
    ReducedCostsForwardEdgesNetwork(NODE_T num_nodes)
    : Vertex<NUM_T, INTERFACE_T, size >(num_nodes, 2, {"to", "reduced cost"}) {};
    
private:
    inline void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                         Counter<NUM_T, INTERFACE_T, size>& counters) override;
    
};

//MARK: Implementation
template<typename NUM_T, typename INTERFACE_T, int size>
inline void ReducedCostsForwardEdgesNetwork<NUM_T, INTERFACE_T, size>::fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, size>& counters)
{
    (*this)[from][i] = costFrom[i];
    (*this)[from][i + 1] = costFrom[i + 1];
}
} // namespace FastEMD

#endif /* ReducedCostsForwardEdgesNetwork_h */
