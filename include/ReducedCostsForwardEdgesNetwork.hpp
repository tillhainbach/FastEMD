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
class ReducedCostsForwardEdgesNetwork : public ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE, 2>
{
public:
    ReducedCostsForwardEdgesNetwork(NODE_T num_nodes)
    : ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE, 2>(num_nodes,
                                                       "Reduced Costs For Forward Edges Network",
                                                       {"to", "reduced cost"})
    {};
    
    ReducedCostsForwardEdgesNetwork(vector2d<NUM_T> _data)
    : ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE, 2>(_data,
                                                       "Reduced Costs For Forward Edges Network",
                                                       {"to", "reduced cost"})
    {};
    
    inline
    void fill(CostNetwork<NUM_T, INTERFACE_T, SIZE> const& cost);
    
};

//MARK: Implementation
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
inline
void ReducedCostsForwardEdgesNetwork<NUM_T, INTERFACE_T, SIZE>::fill(
                        CostNetwork<NUM_T, INTERFACE_T, SIZE> const& cost)
{
    NODE_T from = 0;
    for (auto const & row : cost)
    {
        for (NODE_T i = 0; i < cost.cols(); i += cost.fields())
        {
            NODE_T to = row[i];
            (*this)[from][i] = row[i];
            (*this)[from][i + 1] = row[i + 1];
            if (this->breakCondition(from, to)) break;
        }
        ++from;
    }
}
} // namespace FastEMD

#endif /* ReducedCostsForwardEdgesNetwork_h */
