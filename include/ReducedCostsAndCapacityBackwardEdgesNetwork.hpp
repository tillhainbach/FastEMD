//
//  ReducedCostsAndCapacityBackwardEdgesNetwork.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef ReducedCostsAndCapacityBackwardEdgesNetwork_h
#define ReducedCostsAndCapacityBackwardEdgesNetwork_h
#include "ReducedCostsNetwork.hpp"

namespace FastEMD
{
using namespace types;

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0>
class ReducedCostsAndCapacityBackwardEdgesNetwork :
    public ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE, 3>
{
public:
    ReducedCostsAndCapacityBackwardEdgesNetwork(NODE_T num_nodes)
    : ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE, 3>(num_nodes,
                            "Reduced Costs And Capacity For Backward Edges Network",
                            {"to", "reduced cost", "residual capacity"})
    {};
    
    ReducedCostsAndCapacityBackwardEdgesNetwork(vector2d<NUM_T> _data)
    : ReducedCostsNetwork<NUM_T, INTERFACE_T, SIZE, 3>(_data,
                            "Reduced Costs And Capacity For Backward Edges Network",
                            {"to", "reduced cost", "residual capacity"})
    {};

    inline
    void fill(CostNetwork<NUM_T, INTERFACE_T, SIZE> const& cost,
              Counter<NUM_T, INTERFACE_T, SIZE>& counters);
};

//MARK: Implementations
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
inline
void ReducedCostsAndCapacityBackwardEdgesNetwork<NUM_T, INTERFACE_T, SIZE>::fill(
                            CostNetwork<NUM_T, INTERFACE_T, SIZE> const& cost,
                            Counter<NUM_T, INTERFACE_T, SIZE>& counters)
{
    NODE_T from = 0;
    for (auto const & row : cost)
    {
        for (NODE_T i = 0; i < cost.cols(); i += cost.fields())
        {
            NODE_T to = static_cast<NODE_T>(row[i]);
            (*this)[to][counters[to]] = from;
            (*this)[to][counters[to] + 1] = -row[i + 1];;
            (*this)[to][counters[to] + 2] = 0;
            counters[to] += this->fields();
            if (this->breakCondition(from, to)) break;
        }
        ++from;
    }
}

} // namespace FastEMD

#endif /* ReducedCostsAndCapacityBackwardEdgesNetwork_h */
