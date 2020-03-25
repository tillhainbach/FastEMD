//
//  FlowNetwork.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef FlowNetwork_h
#define FlowNetwork_h
namespace FastEMD
{
using namespace types;

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0>
class FlowNetwork : public BaseNetwork<NUM_T, INTERFACE_T, SIZE >
{
public:
    FlowNetwork(NODE_T num_nodes)
    : BaseNetwork<NUM_T, INTERFACE_T, SIZE>(num_nodes, 3, {"to", "cost", "flow"}) {};
    
    NUM_T calcDist();
    
private:
    inline void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                         Counter<NUM_T, INTERFACE_T, SIZE>& counters) override;
};

//MARK: FlowNetwork implementation
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
inline void FlowNetwork<NUM_T, INTERFACE_T, SIZE>::fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, SIZE>& counters)
{
    NODE_T to = static_cast<NODE_T>(costFrom[i]);
    NUM_T cost = costFrom[i + 1];
    (*this)[from][counters[from]] = to;
    (*this)[from][counters[from] + 1] = cost;
    (*this)[from][counters[from] + 2] = 0;
    (*this)[to][counters[to]] = from;
    (*this)[to][counters[to] + 1] = -cost;
    (*this)[to][counters[to] + 2] = 0;
    counters[from] += this->fields;
    counters[to] += this->fields;
}

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
NUM_T FlowNetwork<NUM_T, INTERFACE_T, SIZE>::calcDist()
{
    NUM_T dist = 0;
//    auto calc = [] (auto thisfrom, NODE_T from, NODE_T i) {return ;}
    unsigned char step = this->fields;
    NODE_T rows = this->rows();
    NODE_T cols = this->cols();
    for (NODE_T from = 0; from < rows; ++from)
    {
        auto thisFrom = this->row(from);
        for (int j = 0;  j < cols; j += step)
        {
            NODE_T to = static_cast<NODE_T>(thisFrom[j]);
            auto cost = thisFrom[j + 1];
            auto flow = thisFrom[j + 2];
            dist += cost * flow;
            if (this->breakCondition(from, to)) break; //lastNode = true;
        } // it
    } // from
    return dist;
}

} // namespace FastEMD
#endif /* FlowNetwork_h */
