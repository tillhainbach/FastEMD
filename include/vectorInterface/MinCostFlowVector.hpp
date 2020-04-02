#ifndef MIN_COST_FLOW_HXX
#define MIN_COST_FLOW_HXX
#define USE_ARRAY 1
#define USE_EDGE 0
#define USE_ARR 1
#define MAX_SIG_SIZE 80

#include <vector>
#include <limits>
#include <vector>
#include <cassert>
#include <math.h>
#include <numeric>
#include <iostream>
#include "utils/EMD_DEFS.hpp"
#include "utils/tictocChrono.hpp"
#include "utils/utils.h"

//------------------------------------------------------------------------------
template<typename CONVERT_TO_T>
class min_cost_flow {

    NODE_T _num_nodes;
    std::vector< NODE_T > _nodes_to_Qq;
    std::vector< CONVERT_TO_T > Qq;
    std::vector< NODE_T > finalNodesFlg;
    std::vector< CONVERT_TO_T > d;
    std::vector< NODE_T > prev;
    std::vector< NODE_T > counters_arr;
    std::vector< std::vector< CONVERT_TO_T>> r_cost_forward_arr;
    std::vector< std::vector< CONVERT_TO_T>> r_cost_cap_backward_arr;

public:
    min_cost_flow(NODE_T _N)
    : _num_nodes(_N)
    , _nodes_to_Qq(_N)
    , Qq(_N)
    , finalNodesFlg(_N)
    , d(_N)
    , prev(_N)
    , counters_arr(_N)
    , r_cost_forward_arr(_N, std::vector< CONVERT_TO_T>(2 * _N))
    , r_cost_cap_backward_arr(_N, std::vector< CONVERT_TO_T>(3 * _N))
    {};

    // e - supply(positive) and demand(negative).
    // c[i] - edges that goes from node i. first is the second nod
    // x - the flow is returned in it
    CONVERT_TO_T operator()(
                     std::vector<CONVERT_TO_T>& e,
                     const std::vector< std::vector< CONVERT_TO_T > >& cc,
                     std::vector< std::vector< CONVERT_TO_T > >& xx,
                     const NODE_T eSize)
    {
        _num_nodes = eSize;

        // zero the counter:
        std::fill(counters_arr.begin(), counters_arr.begin() + _num_nodes, 0);
        // init flow
        for (NODE_T from = 0; from < _num_nodes; ++from)
        {
            for (int i = 0; i < _num_nodes * 2; i += 2)
            {
                NODE_T to = cc[from][i];
                CONVERT_TO_T cost = cc[from][i + 1];
                xx[from][counters_arr[from]] = to;
                xx[from][counters_arr[from] + 1] = cost;
                xx[from][counters_arr[from] + 2] = 0;
                xx[to][counters_arr[to]] = from;
                xx[to][counters_arr[to] + 1] = -cost;
                xx[to][counters_arr[to] + 2] = 0;
                counters_arr[from] += 3;
                counters_arr[to] += 3;
                if (to == _num_nodes - 1 || (from == _num_nodes - 1 && to == _num_nodes - 2)) break;
            } // node
        } // from

//        printFlow<CONVERT_TO_T, NODE_T>(x, _num_nodes);
            
        
        // reduced costs for forward edges (c[i,j]-pi[i]+pi[j])
        // Note that for forward edges the residual capacity is infinity

        for (NODE_T from = 0; from < _num_nodes; ++from)
        {
            for (int i = 0; i < _num_nodes * 2; i += 2)
            {
                NODE_T to = cc[from][i];
                CONVERT_TO_T cost = cc[from][i + 1];
                r_cost_forward_arr[from][i] = to;
                r_cost_forward_arr[from][i + 1] = cost;
                if (to == _num_nodes - 1 || (from == _num_nodes - 1 && to == _num_nodes - 2)) break;
            } // node
        } // from
            
//        printCostForward<CONVERT_TO_T, NODE_T>(r_cost_forward, _num_nodes);
        
        // reduced costs and capacity for backward edges (c[j,i]-pi[j]+pi[i])
        // Since the flow at the beginning is 0, the residual capacity is also zero
        std::fill(counters_arr.begin(), counters_arr.begin() + _num_nodes, 0);
        for (NODE_T from = 0; from < _num_nodes; ++from)
        {
            for (int i = 0; i < _num_nodes * 2; i += 2)
            {
                NODE_T to = cc[from][i];
                CONVERT_TO_T cost = cc[from][i + 1];

                r_cost_cap_backward_arr[to][counters_arr[to]] = from;
                r_cost_cap_backward_arr[to][counters_arr[to] + 1] = -cost;
                r_cost_cap_backward_arr[to][counters_arr[to] + 2] = 0;
                counters_arr[to] += 3;
                if (to == _num_nodes - 1 || (from == _num_nodes - 1 && to == _num_nodes - 2)) break;
            } // node
        } // from
//                printCostBackward<CONVERT_TO_T, NODE_T>(r_cost_cap_backward, _num_nodes);

            
        // Max supply TODO:demand?, given U?, optimization-> min out of demand, supply
//        CONVERT_TO_T U = *(std::max_element(e.begin(), e.begin() + _num_nodes));
    
        //CONVERT_TO_T delta = static_cast<CONVERT_TO_T>(pow(2.0l,ceil(log(static_cast<long double>(U))/log(2.0))));

        CONVERT_TO_T deltaq = 1;
        while (true)
        { //until we break when S or T is empty
            NODE_T k = static_cast<NODE_T>(std::distance(e.begin(),
                                    std::max_element(e.begin(), e.begin() + _num_nodes)));
            CONVERT_TO_T maxSupply = e[k];
            if (maxSupply == 0) break;
            deltaq = maxSupply;
            NODE_T l;
            compute_shortest_path(d, prev, k, r_cost_forward_arr,
                                  r_cost_cap_backward_arr, e, l);
            
            //---------------------------------------------------------------
            // find delta (minimum on the path from k to l)
            //delta= e[k];
            //if (-e[l]<delta) delta= e[k];
            NODE_T to = l;
            do
            {
                NODE_T from = prev[to];
                assert(from != to);
                                    
                // residual
                auto it_arr = findIndex < std::vector< std::vector<CONVERT_TO_T> > >
                        (r_cost_cap_backward_arr, _num_nodes, from, to);
                if (it_arr != r_cost_cap_backward_arr[from].end())
                {
                    if (it_arr[2] < deltaq) deltaq = it_arr[2];
                }
                to = from;
            } while (to!=k);
            //---------------------------------------------------------------
            
            //---------------------------------------------------------------
            // augment delta flow from k to l (backwards actually...)

            to = l;
            do
            {
                NODE_T from = prev[to];
                assert(from != to);
                                    
                // TODO: might do here O(n) can be done in O(1)
                findIndex <std::vector<std::vector<CONVERT_TO_T>>> (xx, _num_nodes, from, to)[2] += deltaq;
                
                // update residual for backward edges
                auto it_arr = findIndex <std::vector<std::vector<CONVERT_TO_T>>>
                (r_cost_cap_backward_arr, _num_nodes, to, from);
                if (it_arr != r_cost_cap_backward_arr[to].end()) it_arr [2] += deltaq;

                it_arr = findIndex <std::vector<std::vector<CONVERT_TO_T>>>
                        (r_cost_cap_backward_arr, _num_nodes, from, to);
                if (it_arr != r_cost_cap_backward_arr[from].end()) it_arr [2] -= deltaq;

                // update e
                e[to] += deltaq;
                e[from] -= deltaq;
                to = from;
            } while (to != k);
            //---------------------------------------------------------------------------------
        }// while true (until we break when S or T is empty)
        
        CONVERT_TO_T dist = 0;
        for (NODE_T from = 0; from < _num_nodes; ++from)
        {
            for (int j = 0;  j < _num_nodes * 3; j += 3)
            {
                NODE_T to = xx[from][j];
                CONVERT_TO_T cost = xx[from][j + 1];
                CONVERT_TO_T flow = xx[from][j + 2];
                dist += cost * flow;
                if ((from < _num_nodes - 1 && to == _num_nodes - 1) ||
                    (from == _num_nodes - 1 && to == _num_nodes - 2))
                    break;
            } // it
        } // from
        return dist;
    } // operator()




private:

    void compute_shortest_path(std::vector< CONVERT_TO_T >& d,
                               std::vector< NODE_T >& prev,
                               NODE_T from,
                               std::vector< std::vector< CONVERT_TO_T > >& cost_forward_arr,
                               std::vector< std::vector< CONVERT_TO_T > >& cost_backward_arr,
                               const std::vector<CONVERT_TO_T>& e,
                               NODE_T& l)
        {
            //----------------------------------------------------------------
            // Making heap (all inf except 0, so we are saving comparisons...)
            //----------------------------------------------------------------
            Qq[0] = from;
            Qq[1] = 0;
            NODE_T jq = 2;
            _nodes_to_Qq[from] = 0;
            

            // TODO: both of these into a function?
            for (NODE_T i = 0; i < from; ++i)
            {
                _nodes_to_Qq[i] = jq;
                Qq[jq] = i;
                Qq[jq + 1] = std::numeric_limits<CONVERT_TO_T>::max();
                jq += 2;
            }

            for (NODE_T i = from + 1; i < _num_nodes; ++i)
            {
                _nodes_to_Qq[i] = jq;
                Qq[jq] = i;
                Qq[jq + 1] = std::numeric_limits<CONVERT_TO_T>::max();
                jq += 2;
            }

            //----------------------------------------------------------------
            // main loop
            //----------------------------------------------------------------
            std::fill(finalNodesFlg.begin(), finalNodesFlg.begin() + _num_nodes, false);
            int Qsize = _num_nodes;
            int Qqsize = _num_nodes * 2;
            
            do
            {
                NODE_T u = 0;
                u = Qq[0];
                d[u] = Qq[1]; // final distance
                
                finalNodesFlg[u] = true;
                if (e[u] < 0)
                {
                    l = u;
                    break;
                }

                heap_remove_first_arr(Qq, _nodes_to_Qq, Qqsize);
                
                // neighbors of u
                for (NODE_T i = 0; i < _num_nodes; ++i)
                {
                    auto itq = &cost_forward_arr[u][2 * i];
                    assert (itq[1] >= 0);
                    CONVERT_TO_T altq = d[u] + itq[1];
                    NODE_T vq = *itq;
//                  std::cout << it._to << ": " << _nodes_to_Q[v] << " < " << Qsize << std::endl;
            
                    if ( (_nodes_to_Qq[vq] < Qqsize) && (altq < Qq[_nodes_to_Qq[vq] + 1]) )
                    {
                        heap_decrease_key_arr(Qq, _nodes_to_Qq, vq, altq);
                        prev[vq]= u;
                    }
                    if (*itq == _num_nodes - 1 || (from == _num_nodes - 1 && *itq == _num_nodes - 2)) break;
                } //it
                        
                for (NODE_T i = 0; i < _num_nodes; ++i)
                {
                    auto itq = &cost_backward_arr[u][3 * i];
                    if (itq[2] > 0)
                    {
                        assert (itq[1] >= 0);
                        CONVERT_TO_T altq = d[u] + itq[1];
                        NODE_T vq = *itq;
                        if ( (_nodes_to_Qq[vq] < Qqsize) && (altq < Qq[_nodes_to_Qq[vq] + 1]) )
                        {
                            heap_decrease_key_arr(Qq, _nodes_to_Qq, vq, altq);
                            prev[vq] = u;
                        }
                    }
                    if (*itq == _num_nodes - 1 || (from == _num_nodes - 1 && *itq == _num_nodes - 2)) break;
                }
                
            } while (!(Qsize == 0));

//            std::cout << std::endl;
            //tmp_tic_toc.tic();
            //---------------------------------------------------------------------------------
            // reduced costs for forward edges (c[i,j]-pi[i]+pi[j])
            if(std::any_of(d.begin(), d.begin() + _num_nodes, [](CONVERT_TO_T n) {return n != 0;}))
            {
                for (NODE_T from = 0; from < _num_nodes; ++from)
                {
                    for (NODE_T i = 0; i < _num_nodes; ++i)
                    {
                        auto itq = &cost_forward_arr[from][2 * i];
                        if (finalNodesFlg[from])
                        {
                            itq[1] += d[from] - d[l];
                        }
                        if (finalNodesFlg[*itq])
                        {
                            itq[1] -= d[*itq] - d[l];
                        }
                        if (*itq == _num_nodes - 1 || (from == _num_nodes - 1 && *itq == _num_nodes - 2)) break;
                    }
                }
                
                // reduced costs and capacity for backward edges (c[j,i]-pi[j]+pi[i])
                for (NODE_T from = 0; from < _num_nodes; ++from)
                {
                    for (NODE_T i = 0; i < _num_nodes; ++i)
                    {
                        auto itq = &cost_backward_arr[from][3 * i];
                        if (finalNodesFlg[from])
                        {
                            itq[1] += d[from] - d[l];
                        }
                        if (finalNodesFlg[*itq])
                        {
                            itq[1] -= d[*itq] - d[l];
                        }
                        if (*itq == _num_nodes - 1 || (from == _num_nodes - 1 && *itq == _num_nodes - 2)) break;
                    }
                }
            } // if...
        } // compute_shortest_path

    template <typename T>
    auto findIndex(T &input, NODE_T _num_nodes, NODE_T node, NODE_T value)
    {
        auto it_arr = input[node].end();
        for (NODE_T i = 0; i < _num_nodes; ++i)
        {
            it_arr = input[node].begin() + 3 * i;
            if (*it_arr == value) break;
            if (*it_arr == _num_nodes - 1 || (node == _num_nodes - 1 && *it_arr == _num_nodes - 2))
            {
                it_arr = input[node].end();
                break;
            }
        }
        return it_arr;
    }
    
    void heap_decrease_key_arr(std::vector< CONVERT_TO_T >& Q,
                           std::vector< NODE_T> & nodes_to_Q,
                           NODE_T v, CONVERT_TO_T alt)
    {
        NODE_T i = nodes_to_Q[v];
        Q[i + 1] = alt;
        while (i > 0 && Q[PARENT(i / 2) * 2 + 1] > Q[i + 1])
        {
            swap_heap_arr(Q, nodes_to_Q, i, PARENT(i / 2) * 2);
            i = PARENT(i / 2) * 2;
        }
    } // heap_decrease_key
            
    void heap_remove_first_arr(std::vector< CONVERT_TO_T >& Q,
                           std::vector< NODE_T >& nodes_to_Q,
                           int &Qsize)
    {
        Qsize -= 2;
        swap_heap_arr(Q, nodes_to_Q, 0, Qsize);
        heapify_arr(Q, nodes_to_Q, 0, Qsize);
    } // heap_remove_first
        
    void heapify_arr(std::vector< CONVERT_TO_T >& Q,
                 std::vector< NODE_T >& nodes_to_Q,
                 NODE_T i, int Qsize)
    {
        assert(i % 2 == 0);
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
            swap_heap_arr(Q, nodes_to_Q, i, smallest);
            i = smallest;
            
        } while (true);
        
    } // end heapify
        
    void swap_heap_arr(std::vector< CONVERT_TO_T  >& Q,
                   std::vector< NODE_T> & nodes_to_Q, NODE_T i, NODE_T j)
    {
        std::swap(Q[i], Q[j]);
        std::swap(Q[i + 1], Q[j + 1]);
        nodes_to_Q[ Q[j] ] = j;
        nodes_to_Q[ Q[i] ] = i;
    } // swap_heapify

    
    NODE_T LEFT(NODE_T i)
    {
        return 2 * (i + 1) - 1;
    } 

    NODE_T RIGHT(NODE_T i)
    {
        return 2 * (i + 1); // 2*(i+1)+1-1
    }

    NODE_T PARENT(NODE_T i)
    {
        return (i - 1) / 2;
    }
    
}; // end min_cost_flow


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





