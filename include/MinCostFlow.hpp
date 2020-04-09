#ifndef MinCostFlow_hpp
#define MinCostFlow_hpp

#include <vector>
#include <limits>
#include <array>
#include <cassert>
#include <math.h>
#include <numeric>
#include <iostream>
#include "utils/EMD_DEFS.hpp"
#include "utils/tictocChrono.hpp"
#include "utils/utils.h"
#include "Container.hpp"
namespace FastEMD
{

//------------------------------------------------------------------------------
template<typename CONVERT_TO_T, typename INTERFACE_T, NODE_T SIZE>
class MinCostFlow {

    //NODE_T _num_nodes;
    
    Distance<CONVERT_TO_T, INTERFACE_T, SIZE> Q;
    Counter<CONVERT_TO_T, INTERFACE_T, SIZE> d;
    Counter<CONVERT_TO_T, INTERFACE_T, SIZE> prev;
    Counter<bool, INTERFACE_T, SIZE> finalNodesFlg;
    Counter<NODE_T, INTERFACE_T, SIZE> counters;
    ReducedCostsForwardEdgesNetwork<CONVERT_TO_T, INTERFACE_T, SIZE> forwardCost;
    ReducedCostsAndCapacityBackwardEdgesNetwork<CONVERT_TO_T, INTERFACE_T, SIZE> backwardCost;

public:
    MinCostFlow(NODE_T _N)
    : Q(_N)
//    , _num_nodes(_N)
    , d(_N, "d")
    , prev(_N, "prev")
    , finalNodesFlg(_N)
    , counters(_N)
    , forwardCost(_N)
    , backwardCost(_N)
    {};

    // weights - supply(positive) and demand(negative).
    // cost[i] - edges that goes from node i.
    // first is the second node
    // flow - the flow is returned in it
    CONVERT_TO_T operator()(
        VertexWeights<CONVERT_TO_T, INTERFACE_T, SIZE>& weights,
        const CostNetwork< CONVERT_TO_T, INTERFACE_T, SIZE>& cost,
        FlowNetwork< CONVERT_TO_T, INTERFACE_T, SIZE>& flow);
    
    void resize(NODE_T _newSize)
    {
//        _num_nodes = _newSize;
        Q.resize(_newSize);
        d.resize(_newSize);
        prev.resize(_newSize);
        finalNodesFlg.resize(_newSize);
        counters.resize(_newSize);
        forwardCost.resize(_newSize);
        backwardCost.resize(_newSize);
    }

private:
   
    NODE_T compute_shortest_path(
        const VertexWeights<CONVERT_TO_T, INTERFACE_T, SIZE>& weights,
        NODE_T from);
    
}; // end min_cost_flow
} //FastEMD
#include "MinCostFlow.cpp"
#endif

// Copyright (c) 2009-2012, Ofir Pele
// Copyright (c) 2019-2020, Till Hainbach
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//    * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//    * Neither the name of the The Hebrew University of Jerusalem nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.





