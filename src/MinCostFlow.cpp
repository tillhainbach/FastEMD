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

template<typename CONVERT_TO_T, typename INTERFACE_T, int size>
CONVERT_TO_T MinCostFlow<CONVERT_TO_T, INTERFACE_T, size>::operator()(
            VertexWeights<CONVERT_TO_T, INTERFACE_T, size>& weights,
            const Cost< CONVERT_TO_T, INTERFACE_T, size>& cost,
            Flow< CONVERT_TO_T, INTERFACE_T, size>& flow)
{
    this->resize(cost.rows());

    // zero the counters:
    std::fill(counters.begin(), counters.end(), 0);
    flow.fill(cost, counters);

#if PRINT
    std::cout << flow << std::endl;
#endif
        
    // reduced costs for forward edges (c[i,j]-pi[i]+pi[j])
    // Note that for forward edges the residual capacity is
    // infinity
    forwardCost.fill(cost, counters);
            
#if PRINT
    std::cout << forwardCost << std::endl;
#endif
        
    // reduced costs and capacity for backward edges
    // (c[j,i]-pi[j]+pi[i])
    // Since the flow at the beginning is 0, the residual
    // capacity is also zero
    std::fill(counters.begin(), counters.end(), 0);
    backwardCost.fill(cost, counters);

#if PRINT
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
            if (it != backwardCost[from].end())
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
            if (it != backwardCost[to].end()) it [2] += delta;

            it = backwardCost.findIndex(from, to);
            if (it != backwardCost[from].end()) it [2] -= delta;

            // update weigths
            weights[to] += delta;
            weights[from] -= delta;
            to = from;
        } while (to != k);
    } // while true (until we break when S or T is empty)
    
    CONVERT_TO_T dist = flow.calcDist();
    return dist;
} // operator()

template<typename CONVERT_TO_T, typename INTERFACE_T, int size>
NODE_T MinCostFlow<CONVERT_TO_T, INTERFACE_T, size>::compute_shortest_path(
                const VertexWeights<CONVERT_TO_T, INTERFACE_T, size>& weights,
                NODE_T from)
{
    // Making heap (all inf except 0, so we are saving
    // comparisons...)
    NODE_T l = 0;
    Q[0] = from;
    Q[1] = 0;
    NODE_T j = 2;
    _nodes_to_Q[from] = 0;
    

    // TODO: both of these into a function?
    for (NODE_T i = 0; i < from; ++i)
    {
        _nodes_to_Q[i] = j;
        Q[j] = i;
        Q[j + 1] = std::numeric_limits<CONVERT_TO_T>::max();
        j += 2;
    }

    for (NODE_T i = from + 1; i < _num_nodes; ++i)
    {
        _nodes_to_Q[i] = j;
        Q[j] = i;
        Q[j + 1] = std::numeric_limits<CONVERT_TO_T>::max();
        j += 2;
    }

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

        heap_remove_first();
        
        // neighbors of u
        for (auto it = forwardCost[u].begin(), end = forwardCost[u].end();
             it != end; it += forwardCost.getFields())
        {
            assert (it[1] >= 0);
            CONVERT_TO_T alt = d[u] + it[1];
            NODE_T v = static_cast<NODE_T>(*it);
            NODE_T i = _nodes_to_Q[v];
            if ( (i < Q.size()) && (alt < Q[i + 1]) )
            {
                heap_decrease_key(i, alt);
                prev[v] = u;
            }
            if (forwardCost.breakCondition(u, v)) break;
        } //it
                
        for (auto it = backwardCost[u].begin(), end = backwardCost[u].end();
        it != end; it += backwardCost.getFields())
        {
            NODE_T v = static_cast<NODE_T>(*it);
            if (it[2] > 0)
            {
                assert (it[1] >= 0);
                CONVERT_TO_T alt = d[u] + it[1];
                NODE_T i = _nodes_to_Q[v];
                if ( (i < Q.size()) && (alt < Q[i + 1]) )
                {
                    heap_decrease_key(i, alt);
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
    
template<typename CONVERT_TO_T, typename INTERFACE_T, int size>
void MinCostFlow<CONVERT_TO_T, INTERFACE_T, size>::heap_decrease_key(
                                        NODE_T i, CONVERT_TO_T alt)
{
    Q[i + 1] = alt;
    while (i > 0 && Q[PARENT(i / 2) * 2 + 1] > Q[i + 1])
    {
        swap_heap(i, PARENT(i / 2) * 2);
        i = PARENT(i / 2) * 2;
    }
} // heap_decrease_key

template<typename CONVERT_TO_T, typename INTERFACE_T, int size>
void MinCostFlow<CONVERT_TO_T, INTERFACE_T, size>::heap_remove_first()
{
    Q.resize(Q.size() - 2);
    swap_heap(0, Q.size());
    heapify(0);
} // heap_remove_first
        
template<typename CONVERT_TO_T, typename INTERFACE_T, int size>
void MinCostFlow<CONVERT_TO_T, INTERFACE_T, size>::heapify(NODE_T i)
{
    assert(i % 2 == 0);
    NODE_T Qsize = Q.size();
    do {
        // TODO: change to loop
        NODE_T l = LEFT(i / 2) * 2;
        NODE_T r = RIGHT(i / 2) * 2;
        NODE_T smallest;
        if ( (l < Qsize) && (Q[l + 1] < Q[i + 1]) )
        {
            smallest = l;
        }
        else
        {
            smallest = i;
        }
        if ( (r < Qsize) && (Q[r + 1] < Q[smallest + 1]) )
        {
            smallest = r;
        }
        if (smallest == i) return;
        swap_heap(i, smallest);
        i = smallest;
        
    } while (true);
    
} // end heapify
        
template<typename CONVERT_TO_T, typename INTERFACE_T, int size>
void MinCostFlow<CONVERT_TO_T, INTERFACE_T, size>::swap_heap(NODE_T i,
                                                             NODE_T j)
{
    std::swap(Q[i], Q[j]);
    std::swap(Q[i + 1], Q[j + 1]);
    _nodes_to_Q[ Q[j] ] = j;
    _nodes_to_Q[ Q[i] ] = i;
} // swap_heapify

#endif
