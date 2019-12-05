#ifndef MIN_COST_FLOW_HXX
#define MIN_COST_FLOW_HXX
#define USE_ARRAY 1
#define MAX_SIG_SIZE 80

#include <vector>
#include <limits>
#include <array>
#include <cassert>
#include <math.h>
#include <numeric>
#include "EMD_DEFS.hpp"
#include <iostream>
#include "tictoc.hpp"

//------------------------------------------------------------------------------
template<typename NUM_T>
struct edge {
    edge(NODE_T to = -1, NUM_T cost = -1) : _to(to), _cost(cost) {}
    NODE_T _to;
    NUM_T _cost;
    edge& operator=(const edge& e)
    {
        _to = e._to;
        _cost = e._cost;
        return *this;
    };
};

template<typename NUM_T>
struct edgeCompareByCost {
    bool operator()(const edge<NUM_T>& a, const edge<NUM_T>& b) {
        return a._cost<b._cost;
    }
};

template<typename NUM_T>
struct edge0 {
    edge0(NODE_T to = -1, NUM_T cost = -1, NUM_T flow = -1) : _to(to), _cost(cost), _flow(flow) {}
    NODE_T _to;
    NUM_T _cost;
    NUM_T _flow;
    edge0& operator=(const edge0& e)
    {
        _to = e._to;
        _cost = e._cost;
        _flow = e._flow;
        return *this;
    };
};

template<typename NUM_T>
struct edge1 {
    edge1(NODE_T to = -1, NUM_T reduced_cost = -1) : _to(to), _reduced_cost(reduced_cost) {}
    NODE_T _to;
    NUM_T _reduced_cost;
    edge1& operator=(const edge1& e)
    {
        _to = e._to;
        _reduced_cost = e._reduced_cost;
        return *this;
    };
};

template<typename NUM_T>
struct edge2 {
    edge2(NODE_T to = -1, NUM_T reduced_cost = -1, NUM_T residual_capacity = -1) : _to(to), _reduced_cost(reduced_cost), _residual_capacity(residual_capacity) {}
    NODE_T _to;
    NUM_T _reduced_cost;
    NUM_T _residual_capacity;
    edge2& operator=(const edge2& e)
    {
        _to = e._to;
        _reduced_cost = e._reduced_cost;
        _residual_capacity = e._residual_capacity;
        return *this;
    };
};

template<typename NUM_T>
struct edge3 {
    edge3(NODE_T to = 0, NUM_T dist = 0) : _to(to), _dist(dist) {}
    NODE_T _to;
    NUM_T _dist;
    edge3& operator=(const edge3& e)
    {
        _to = e._to;
        _dist = e._dist;
        return *this;
    };
};
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
template<typename NUM_T>
class min_cost_flow {

    NODE_T _num_nodes;
    std::vector<NODE_T> _nodes_to_Q;

//    tictoc tictoc_shortest_path;
//    tictoc tictoc_while_true;
//    tictoc tmp_tic_toc;
//    tictoc tictoc_all_function;

public:

    // e - supply(positive) and demand(negative).
    // c[i] - edges that goes from node i. first is the second nod
    // x - the flow is returned in it
    NUM_T operator()(
                     std::array<NUM_T, MAX_SIG_SIZE>& e, const size_t eSize,
                     const std::array< std::array< edge<NUM_T>, MAX_SIG_SIZE >,MAX_SIG_SIZE >& c,
                     std::array< std::array< edge0<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE >& x
                     )
    {
        //for (NODE_T i = 0; i < e.size(); ++i) cout << e[i]<< " ";
        //cout << endl;
//        tictoc_all_function.tic();
        
        _num_nodes = static_cast<NODE_T>(eSize);
        _nodes_to_Q.resize(_num_nodes);
        std::array<int, MAX_SIG_SIZE > counters;
        std::fill(counters.begin(), counters.begin() + _num_nodes, 0);
        // init flow
        for (NODE_T from = 0; from < _num_nodes; ++from)
        {
            for (auto node : c[from])
            {
                if (node._to == -1 && node._cost == -1) break;
                x[from][counters[from]] = edge0<NUM_T> (node._to, node._cost, 0);
                x[node._to][counters[node._to]] = edge0<NUM_T>(from, -node._cost, 0);
                counters[from]++;
                counters[node._to]++;
            } // node
        } // from
        
        // reduced costs for forward edges (c[i,j]-pi[i]+pi[j])
        // Note that for forward edges the residual capacity is infinity
        std::array< std::array< edge1<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE> r_cost_forward;
        for (NODE_T from = 0; from < _num_nodes; ++from)
        {
            int i = 0;
            for (auto node : c[from])
            {
                if (node._to == -1 && node._cost == -1) break;
                r_cost_forward[from][i] = edge1<NUM_T>(node._to, node._cost);
                i++;
            } // node
        } // from
        
        // reduced costs and capacity for backward edges (c[j,i]-pi[j]+pi[i])
        // Since the flow at the beginning is 0, the residual capacity is also zero
        std::array< std::array< edge2<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE > r_cost_cap_backward;
        std::fill(counters.begin(), counters.begin() + _num_nodes, 0);
        for (NODE_T from = 0; from < _num_nodes; ++from)
        {
            for (auto &node : c[from])
            {
                if (node._to == -1 && node._cost == -1) break;
                r_cost_cap_backward[node._to][counters[node._to]] = edge2<NUM_T>(from, -node._cost, 0);
                counters[node._to]++;
            } // node
        } // from
        
        // Max supply TODO:demand?, given U?, optimization-> min out of demand, supply
        NUM_T U = *(std::max_element(e.begin(), e.begin() + _num_nodes));
    
        //NUM_T delta = static_cast<NUM_T>(pow(2.0l,ceil(log(static_cast<long double>(U))/log(2.0))));

        std::array< NUM_T, MAX_SIG_SIZE > d;
        std::array< NODE_T, MAX_SIG_SIZE > prev;
        NUM_T delta = 1;

        while (true)
        { //until we break when S or T is empty
            NODE_T k = static_cast<NODE_T>(std::distance(e.begin(),
                                    std::max_element(e.begin(), e.begin() + _num_nodes)));
            NUM_T maxSupply = e[k];
            if (maxSupply == 0) break;
            delta = maxSupply;

//        std::cout << "comput shortest path" << std::endl;
            NODE_T l;
            //tictoc_shortest_path.tic();
            compute_shortest_path(d, prev, k,r_cost_forward,r_cost_cap_backward , e, l);
            //tictoc_shortest_path.toc();
            
//        std::cout << "l = " << l << std::endl;

            
            //---------------------------------------------------------------
            // find delta (minimum on the path from k to l)
            //delta= e[k];
            //if (-e[l]<delta) delta= e[k];
            NODE_T to= l;
            do
            {
                NODE_T from = prev[to];
                assert(from != to);
                                    
                // residual
                auto it = std::find_if(r_cost_cap_backward[from].begin(),
                                       r_cost_cap_backward[from].begin() + _num_nodes,
                                       [&](auto &e) {return e._to == to;});
                if (it != r_cost_cap_backward[from].begin() + _num_nodes)
                {
                    if (it->_residual_capacity < delta) delta = it->_residual_capacity;
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
                std::find_if(x[from].begin(), x[from].begin() + _num_nodes, [&](auto &e) {return e._to == to;})->_flow += delta;
   
                // update residual for backward edges
                auto it = std::find_if(r_cost_cap_backward[to].begin(),
                                       r_cost_cap_backward[to].begin() + _num_nodes,
                                       [&](auto &e) {return e._to == from;});
                if (it != r_cost_cap_backward[to].begin() + _num_nodes) it->_residual_capacity += delta;
                
                it = std::find_if(r_cost_cap_backward[from].begin(),
                                       r_cost_cap_backward[from].begin() + _num_nodes,
                                       [&](auto &e) {return e._to == to;});
                if (it != r_cost_cap_backward[from].begin() + _num_nodes) it->_residual_capacity -= delta;

                // update e
                e[to] += delta;
                e[from] -= delta;
                to = from;
            } while (to != k);
            //---------------------------------------------------------------------------------
        }// while true (until we break when S or T is empty)
            
//        auto sumDist = [](int n, edge0<NUM_T> node) {return n + node._cost * node._flow;};
//        // compute distance from x
//        NUM_T dist = std::accumulate(x.begin(), x.begin() + _num_nodes, 0, sumDist);
        
        NUM_T dist = 0;
        for (NODE_T from = 0; from < _num_nodes; ++from)
        {
            for (auto it : x[from])
            {
                if (it._to == -1 && it._cost == -1 && it._flow == -1) break;
                    dist += (it._cost*it._flow);
            } // it
        } // from
        return dist;
    } // operator()




private:

    void compute_shortest_path(std::array< NUM_T, MAX_SIG_SIZE >& d,
                               std::array< NODE_T, MAX_SIG_SIZE >& prev,
                               NODE_T from,
                               std::array< std::array< edge1<NUM_T>,MAX_SIG_SIZE >,MAX_SIG_SIZE >& cost_forward,
                               std::array< std::array< edge2<NUM_T>,MAX_SIG_SIZE >,MAX_SIG_SIZE >& cost_backward,

                               const std::array<NUM_T, MAX_SIG_SIZE>& e,
                               NODE_T& l)
        {
            //----------------------------------------------------------------
            // Making heap (all inf except 0, so we are saving comparisons...)
            //----------------------------------------------------------------
            std::array<  edge3<NUM_T> ,MAX_SIG_SIZE  > Q;
            Q[0]._to= from;
            _nodes_to_Q[from] = 0;
            Q[0]._dist= 0;
                    
            NODE_T j = 1;
            // TODO: both of these into a function?
            for (NODE_T i = 0; i<from; ++i)
            {
                Q[j]._to= i;
                _nodes_to_Q[i]= j;
                Q[j]._dist= std::numeric_limits<NUM_T>::max();
                ++j;
            }

            for (NODE_T i=from+1; i<_num_nodes; ++i)
            {
                Q[j]._to= i;
                _nodes_to_Q[i]= j;
                Q[j]._dist= std::numeric_limits<NUM_T>::max();
                ++j;
            }

            //----------------------------------------------------------------
            // main loop
            //----------------------------------------------------------------
            std::array<NODE_T, MAX_SIG_SIZE> finalNodesFlg;
            std::fill(finalNodesFlg.begin(), finalNodesFlg.begin() + _num_nodes, false);
            int Qsize = _num_nodes;
            do
            {
                NODE_T u = Q[0]._to;
                d[u] = Q[0]._dist; // final distance
                finalNodesFlg[u] = true;
                if (e[u] < 0)
                {
                    l = u;
                    break;
                }
                
                heap_remove_first(Q, _nodes_to_Q, Qsize);
                
                // neighbors of u
                for (auto &it : cost_forward[u])
                {

                    if (it._to == -1) break;
                    assert (it._reduced_cost >= 0);
                    NUM_T alt = d[u] + it._reduced_cost;
                    NODE_T v = it._to;
//                    std::cout << it._to << ": " << _nodes_to_Q[v] << " < " << Qsize << std::endl;
                    if ( (_nodes_to_Q[v] < Qsize) && (alt < Q[_nodes_to_Q[v]]._dist) )
                    {
//                        std::cout << "u to v==" << u << " to " << v << "   " << alt << std::endl;
                        heap_decrease_key(Q, _nodes_to_Q, v, alt);
                        prev[v]= u;
                    }
                } //it
                
                for (auto &it : cost_backward[u])
                {
                    if (it._to == -1) break;
                    if (it._residual_capacity > 0)
                    {
                        assert (it._reduced_cost>=0);
                        NUM_T alt= d[u]+it._reduced_cost;
                        NODE_T v = it._to;
                        if ( (_nodes_to_Q[v] < Qsize) && (alt < Q[_nodes_to_Q[v]]._dist) )
                        {
//                            std::cout << "u to v==" << u << " to " << v << "   " << alt << std::endl;
                            heap_decrease_key(Q, _nodes_to_Q, v, alt);
                            prev[v] = u;
                        }
                    }
                } //it
                
            } while (!(Qsize == 0));

//            std::cout << std::endl;
            //tmp_tic_toc.tic();
            //---------------------------------------------------------------------------------
            // reduced costs for forward edges (c[i,j]-pi[i]+pi[j])
            if(std::any_of(d.begin(), d.begin() + _num_nodes, [](NUM_T n) {return n != 0;}))
            {
                for (NODE_T from = 0; from < _num_nodes; ++from)
                {
                    for (auto &it : cost_forward[from])
                    {
                        if (finalNodesFlg[from])
                        {
                            it._reduced_cost+= d[from] - d[l];
                        }
                        if (finalNodesFlg[it._to])
                        {
                            it._reduced_cost-= d[it._to] - d[l];
                        }
                    }
                }
                
                // reduced costs and capacity for backward edges (c[j,i]-pi[j]+pi[i])
                for (NODE_T from = 0; from < _num_nodes; ++from)
                {
                    for (auto &it : cost_backward[from])
                    {
                        if (finalNodesFlg[from])
                        {
                            it._reduced_cost+= d[from] - d[l];
                        }
                        if (finalNodesFlg[it._to])
                        {
                            it._reduced_cost-= d[it._to] - d[l];
                        }
                    }// it
                }
            }
        } // compute_shortest_path

    void heap_decrease_key(std::array<  edge3<NUM_T> ,MAX_SIG_SIZE  >& Q,
                           std::vector<NODE_T>& nodes_to_Q,
                           NODE_T v, NUM_T alt)
    {
        NODE_T i = nodes_to_Q[v];
        Q[i]._dist = alt;
        while (i > 0 && Q[PARENT(i)]._dist > Q[i]._dist)
        {
            swap_heap(Q, nodes_to_Q, i, PARENT(i));
            i = PARENT(i);
        }
    } // heap_decrease_key
    
    void heap_remove_first(std::array<  edge3<NUM_T> ,MAX_SIG_SIZE  >& Q,
                           std::vector<NODE_T>& nodes_to_Q,
                           int &Qsize)
    {
        swap_heap(Q, nodes_to_Q, 0, Qsize - 1);
//        Q.pop_back();
        Qsize -= 1 ;
        heapify(Q, nodes_to_Q, 0, Qsize);
    } // heap_remove_first

    void heapify(std::array<  edge3<NUM_T> ,MAX_SIG_SIZE  >& Q, std::vector<NODE_T>& nodes_to_Q,
                 NODE_T i, int &Qsize)
    {

        do {
            // TODO: change to loop
            NODE_T l = LEFT(i);
            NODE_T r = RIGHT(i);
            NODE_T smallest;
            if ( (l < Qsize) && (Q[l]._dist < Q[i]._dist) )
            {
                smallest = l;
            }
            else
            {
                smallest = i;
            }
            if ( (r < Qsize)&& (Q[r]._dist < Q[smallest]._dist) )
            {
                smallest = r;
            }
            if (smallest == i) return;
            swap_heap(Q, nodes_to_Q, i, smallest);
            i = smallest;
            
        } while (true);
        
    } // end heapify




    void swap_heap(std::array<  edge3<NUM_T> ,MAX_SIG_SIZE  >& Q,
                   std::vector<NODE_T>& nodes_to_Q, NODE_T i, NODE_T j)
    {
        edge3<NUM_T> tmp= Q[i];
        Q[i]= Q[j];
        Q[j]= tmp;
        nodes_to_Q[ Q[j]._to ] = j;
        nodes_to_Q[ Q[i]._to ] = i;
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





