//
//  FlowNetwork.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef FlowNetwork_h
#define FlowNetwork_h
#include "BaseNetwork.hpp"

namespace FastEMD
{
using namespace types;

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0>
class FlowNetwork : public BaseNetwork<NUM_T, INTERFACE_T, SIZE, 3>
{
public:
    FlowNetwork(NODE_T num_nodes)
    : BaseNetwork<NUM_T, INTERFACE_T, SIZE, 3>(num_nodes,
                                               "Flow Network",
                                               {"to", "cost", "flow"})
    {};
    
    FlowNetwork(vector2d<NUM_T> _data)
    : BaseNetwork<NUM_T, INTERFACE_T, SIZE, 3>(_data,
                                               "Flow Network",
                                               {"to", "cost", "flow"})
    {};
    
    NUM_T calcDist() const;
    
    inline
    void fill(CostNetwork<NUM_T, INTERFACE_T, SIZE> const& cost,
              Counter<NUM_T, INTERFACE_T, SIZE>& counters);
    
};

//MARK: FlowNetwork implementation
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
inline
void FlowNetwork<NUM_T, INTERFACE_T, SIZE>::fill(
                                CostNetwork<NUM_T, INTERFACE_T, SIZE> const& cost,
                                Counter<NUM_T, INTERFACE_T, SIZE>& counters)
{
    NODE_T from = 0;
    for (auto const & fromNode : cost)
    {
        for (NODE_T i = 0; i < cost.cols(); i += cost.fields())
        {
            NODE_T const to = static_cast<NODE_T const>(fromNode[i]);
            NUM_T const cost = fromNode[i + 1];
            (*this)[from][counters[from]] = to;
            (*this)[from][counters[from] + 1] = cost;
            (*this)[from][counters[from] + 2] = 0;
            (*this)[to][counters[to]] = from;
            (*this)[to][counters[to] + 1] = -cost;
            (*this)[to][counters[to] + 2] = 0;
            counters[from] += this->fields();
            counters[to] += this->fields();
            if (this->breakCondition(from, to)) break;
        }
        ++from;
    }
    
}

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
NUM_T FlowNetwork<NUM_T, INTERFACE_T, SIZE>::calcDist() const
{
    NUM_T dist = 0;
//    auto calc = [] (auto thisfrom, NODE_T from, NODE_T i) {return ;}
    NODE_T from = 0;
    for (auto const & row : *this)
    {
        for (int j = 0;  j < this->cols(); j += this->fields())
        {
            NODE_T to = static_cast<NODE_T>(row[j]);
            auto cost = row[j + 1];
            auto flow = row[j + 2];
            dist += cost * flow;
            if (this->breakCondition(from, to)) break; //lastNode = true;
        } // it
        ++from;
    } // from
    return dist;
}

} // namespace FastEMD
#endif /* FlowNetwork_h */
