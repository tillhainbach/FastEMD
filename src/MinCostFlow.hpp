#ifndef MIN_COST_FLOW_HXX
#define MIN_COST_FLOW_HXX

#include <vector>
#include <limits>
#include <array>
#include <cassert>
#include <math.h>
#include <numeric>
#include <iostream>
#include "utils/EMD_DEFS.hpp"
#include "utils/tictocChrono.hpp"
#include "Container.hpp"
namespace FastEMD
{

//------------------------------------------------------------------------------
template<typename CONVERT_TO_T, typename INTERFACE_T, int size>
class MinCostFlow {

    //NODE_T _num_nodes;
    
    Distance<CONVERT_TO_T, INTERFACE_T, size> Q;
    Counter<CONVERT_TO_T, INTERFACE_T, size> d;
    Counter<CONVERT_TO_T, INTERFACE_T, size> prev;
    Counter<NODE_T, INTERFACE_T, size> _nodes_to_Q;
    Counter<bool, INTERFACE_T, size> finalNodesFlg;
    Counter<NODE_T, INTERFACE_T, size> counters;
    ReducedCostsForwardEdgesNetwork<CONVERT_TO_T, INTERFACE_T, size> forwardCost;
    ReducedCostsAndCapacityBackwardEdgesNetwork<CONVERT_TO_T, INTERFACE_T, size> backwardCost;

public:
    MinCostFlow(NODE_T _N)
    : Q(_N)
//    , _num_nodes(_N)
    , d(_N)
    , prev(_N)
    , _nodes_to_Q(_N)
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
        VertexWeights<CONVERT_TO_T, INTERFACE_T, size>& weights,
        const CostNetwork< CONVERT_TO_T, INTERFACE_T, size>& cost,
        FlowNetwork< CONVERT_TO_T, INTERFACE_T, size>& flow);
    
    void resize(NODE_T _newSize)
    {
//        _num_nodes = _newSize;
        Q.resize(_newSize);
        d.resize(_newSize);
        prev.resize(_newSize);
        _nodes_to_Q.resize(_newSize);
        finalNodesFlg.resize(_newSize);
        counters.resize(_newSize);
        forwardCost.resize(_newSize);
        backwardCost.resize(_newSize);
    }

private:
   
    NODE_T compute_shortest_path(
        const VertexWeights<CONVERT_TO_T, INTERFACE_T, size>& weights,
        NODE_T from);
    
    void heap_decrease_key(NODE_T v, CONVERT_TO_T alt);
            
    void heap_remove_first();
        
    void heapify(NODE_T i);
        
    void swap_heap(NODE_T i, NODE_T j);
    
    inline NODE_T LEFT(NODE_T i) {return 2 * (i + 1) - 1;}

    inline NODE_T RIGHT(NODE_T i) {return 2 * (i + 1);}

    inline NODE_T PARENT(NODE_T i) {return (i - 1) / 2;}
    
}; // end min_cost_flow
} //FastEMD
#include "MinCostFlow.cpp"
#endif

// Copyright (c) 2009-2012, Ofir Pele
// Copyright (c) 2019, Till Hainbach
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met: 
//    * Redistributions of source code must retain the above copyright
//    notice, this vector of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright
//    notice, this vector of conditions and the following disclaimer in the
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





