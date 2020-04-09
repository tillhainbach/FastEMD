//
//  MinCostFlow.cpp
//  arrayFastEMD
//
//  Created by Till Hainbach on 08.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//
#ifndef MIN_COST_FLOW_CPP
#define MIN_COST_FLOW_CPP

#include <stdio.h>
#include "MinCostFlow.hpp"
namespace FastEMD
{
//MARK: Operator()
template<typename CONVERT_TO_T, typename INTERFACE_T, NODE_T SIZE>
CONVERT_TO_T MinCostFlow<CONVERT_TO_T, INTERFACE_T, SIZE>::operator()(
            VertexWeights<CONVERT_TO_T, INTERFACE_T, SIZE>& weights,
            const CostNetwork< CONVERT_TO_T, INTERFACE_T, SIZE>& cost,
            FlowNetwork< CONVERT_TO_T, INTERFACE_T, SIZE>& flow)
{
    // zero the counters:
    std::fill(counters.begin(), counters.end(), 0);
    flow.fill(cost, counters);

#if PRINT && DEBUG
    std::cout << flow << std::endl;
#endif
    
    // reduced costs for forward edges (c[i,j]-pi[i]+pi[j])
    // Note that for forward edges the residual capacity is
    // infinity
    forwardCost.fill(cost);
    
#if PRINT && DEBUG
    std::cout << forwardCost << std::endl;
#endif
        
    // reduced costs and capacity for backward edges
    // (c[j,i]-pi[j]+pi[i])
    // Since the flow at the beginning is 0, the residual
    // capacity is also zero
    std::fill(counters.begin(), counters.end(), 0);
    backwardCost.fill(cost, counters);
    
#if PRINT && DEBUG
    std::cout << backwardCost << std::endl;
#endif
    
    // Max supply TODO:demand?, given U?,
    // optimization-> min out of demand, supply
//    CONVERT_TO_T U = *(std::max_element(weigths.begin(),
//                       weigths.begin() + _num_nodes));
    
//    CONVERT_TO_T delta =
//        static_cast<CONVERT_TO_T>(pow(2.0l,
//        ceil(log(static_cast<long double>(U))/log(2.0))));
    
    CONVERT_TO_T delta = 1;
    while (true)
    { //until we break when S or T is empty
        NODE_T k = static_cast<NODE_T>(std::distance(weights.begin(),
                std::max_element(weights.begin(), weights.end())));
        
        CONVERT_TO_T maxSupply = weights[k];
        if (maxSupply == 0) break;
        delta = maxSupply;
    
        NODE_T l = compute_shortest_path(weights, k);
        //---------------------------------------------------------
        // find delta (minimum on the path from k to l)
        // delta = weigths[k];
        // if (-weigths[l] < delta) delta = weigths[k];
        NODE_T to = l;
        do
        {
            NODE_T from = prev[to];
            assert(from != to);
                                
            // residual
            auto it = backwardCost.findIndex(from, to);
            auto end = backwardCost.fromNode(from)->end();
            if (!utils::isEnd(it, end))
            {
                if (it[2] < delta) delta = it[2];
            }
            to = from;
        } while (to!=k);
    
        //---------------------------------------------------------
        // augment delta flow from k to l (backwards actually...)
    
        to = l;
        do
        {
            NODE_T from = prev[to];
            assert(from != to);

                                
            // TODO: might do here O(n) can be done in O(1)
            flow.findIndex(from, to)[2] += delta;
            
            // update residual for backward edges
            auto it = backwardCost.findIndex(to, from);
            auto end = backwardCost.fromNode(to)->end();
            if (!utils::isEnd(it, end)) it [2] += delta;

            it = backwardCost.findIndex(from, to);
            end = backwardCost.fromNode(from)->end();
            if (!utils::isEnd(it, end)) it [2] -= delta;

            // update weigths
            weights[to] += delta;
            weights[from] -= delta;
            to = from;
        } while (to != k);
        
    } // while true (until we break when S or T is empty)
    
    CONVERT_TO_T dist = flow.calcDist();
    return dist;
}// operator()


    
//MARK: Compute Shortest Path
template<typename CONVERT_TO_T, typename INTERFACE_T, NODE_T SIZE>
NODE_T MinCostFlow<CONVERT_TO_T, INTERFACE_T, SIZE>::compute_shortest_path(
                const VertexWeights<CONVERT_TO_T, INTERFACE_T, SIZE>& weights,
                NODE_T from)
{
    NODE_T l = 0;
    Q.fill(from, weights.size());

    //-------------------------------------------------------------
    // main loop
    //-------------------------------------------------------------
    std::fill(finalNodesFlg.begin(), finalNodesFlg.end(), false);
    
    do
    {
        NODE_T u = static_cast<NODE_T>(Q[0]);
        d[u] = Q[1]; // final distance
        finalNodesFlg[u] = true;
        if (weights[u] < 0)
        {
            l = u;
            break;
        }
        
        Q.heapRemoveFirst();
        // neighbors of u
        for (auto it = forwardCost.fromNode(u)->begin(), end = forwardCost.fromNode(u)->end();
             it != end; it += forwardCost.fields())
        {
            assert (it[1] >= 0);
            CONVERT_TO_T alt = d[u] + it[1];
            NODE_T v = static_cast<NODE_T>(*it);
            if ( Q.check(v, alt) )
            {
                Q.heapDecreaseKey(v, alt);
                prev[v] = u;
            }
            if (forwardCost.breakCondition(u, v)) break;
        } //it
          
        for (auto it = backwardCost.fromNode(u)->begin(), end = backwardCost.fromNode(u)->end();
        it != end; it += backwardCost.fields())
        {
            NODE_T v = static_cast<NODE_T>(*it);
            if (it[2] > 0)
            {
                 assert (it[1] >= 0);
                CONVERT_TO_T alt = d[u] + it[1];
                if ( Q.check(v, alt)  )
                {
                    Q.heapDecreaseKey(v, alt);
                    prev[v] = u;
                }
            }
            if (backwardCost.breakCondition(u, v)) break;
        }
    } while (!(Q.size() == 0));
    //-------------------------------------------------------------

    if(std::any_of(d.begin(), d.end(), [](CONVERT_TO_T& n) {return n != 0;}))
    {
        // reduced costs for forward edges (c[i,j] - pi[i] + pi[j])
        forwardCost.reduceCost(d, finalNodesFlg, l);
    
        // reduced costs and capacity for backward edges
        // (c[j,i]-pi[j]+pi[i])
        backwardCost.reduceCost(d, finalNodesFlg, l);
    } // if...

    return l;
} // compute_shortest_path
 
} //FastEMD
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
