#ifndef MIN_COST_FLOW_HXX
#define MIN_COST_FLOW_HXX
#define USE_ARRAY 1
#define USE_EDGE 0
#define USE_ARR 1
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
//-----------------------------------------------------------------------------
template<typename NUM_T, typename NODE_T>
void printFlow(
#if USE_EDGE
               std::array< std::array< edge0<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE >& x,
#endif
#if USE_ARR
               std::array< std::array< NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE> &xx,
#endif
               NODE_T num_nodes)
{
    for (NODE_T i = 0; i < num_nodes; ++i)
    {
        std::cout << i << ": ";
#if USE_EDGE
        for (const auto &node : x[i])
        {
            if (node._to == -1 && node._cost == -1) break;
            std::cout << "[" << node._to << " : " << node._cost << " : " << node._flow << "] ";
        }
#endif
#if USE_ARR
        bool lastNode = false;
        for (int j = 0;  j <= (num_nodes - 1) * 2 * 3; j += 3)
        {

            NODE_T to = xx[i][j];
            NUM_T cost = xx[i][j + 1];
            NUM_T flow = xx[i][j + 2];
            std::cout << "[" << to << " : " << cost << " : " << flow << "] ";
            if ((i < num_nodes - 1 && to == num_nodes - 1) ||
                (i == num_nodes - 1 && to == num_nodes - 2))
            {
                if (lastNode) break;
                lastNode = true;
            }
        }
#endif
        std::cout << std::endl;
    }
}
template<typename NUM_T, typename NODE_T>
void printCostBackward(
#if USE_EDGE
              std::array< std::array< edge2<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE >& x,
#endif
#if USE_ARR
              std::array< std::array< NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE> &xx,
#endif
              NODE_T num_nodes)
{
    for (NODE_T i = 0; i < num_nodes; ++i)
    {
        std::cout << i << ": ";
#if USE_EDGE
        for (const auto &node : x[i])
        {
            if (node._to == -1 && node._reduced_cost == -1) break;
            std::cout << "[" << node._to << " : " << node._reduced_cost << " : " << node._residual_capacity << "] ";
        }
#endif
#if USE_ARR
        for (int j = 0;  j <= (num_nodes - 1) * 2 * 3; j += 3)
        {

            NODE_T to = xx[i][j];
            NUM_T reduced_cost = xx[i][j + 1];
            NUM_T residual_capacity = xx[i][j + 2];
            std::cout << "[" << to << " : " << reduced_cost << " : " << residual_capacity << "] ";
            if (to == num_nodes - 1 || (i == num_nodes - 1 && to == num_nodes - 2)) break;
        }
#endif
        std::cout << std::endl;
    }
}

template<typename NUM_T, typename NODE_T>
void printCost(
#if USE_EDGE
              std::array< std::array< edge<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE >& x,
#endif
#if USE_ARR
              std::array< std::array< NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE> &xx,
#endif
              NODE_T num_nodes)
{
    for (NODE_T i = 0; i < num_nodes; ++i)
    {
        std::cout << i << ": ";
#if USE_EDGE
        for (const auto &node : x[i])
        {
            if (node._to == -1 && node._reduced_cost == -1) break;
            std::cout << "[" << node._to << " : " << node._cost << "] ";
        }
#endif
#if USE_ARR
        for (int j = 0;  j < 2 * num_nodes; j += 2)
        {

            NODE_T to = xx[i][j];
            NUM_T reduced_cost = xx[i][j + 1];
            std::cout << "[" << to << " : " << reduced_cost << "] ";
            if (to == num_nodes - 1 || (i == num_nodes - 1 && to == num_nodes - 2)) break;
        }
#endif
        std::cout << std::endl;
    }
}

template<typename NUM_T, typename NODE_T>
void printCostForward(
#if USE_EDGE
              std::array< std::array< edge1<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE >& x,
#endif
#if USE_ARR
              std::array< std::array< NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE> &xx,
#endif
              NODE_T num_nodes)
{
    for (NODE_T i = 0; i < num_nodes; ++i)
    {
        std::cout << i << ": ";
#if USE_EDGE
        for (const auto &node : x[i])
        {
            if (node._to == -1 && node._reduced_cost == -1) break;
            std::cout << "[" << node._to << " : " << node._reduced_cost << "] ";
        }
#endif
#if USE_ARR
        for (int j = 0;  j <= (num_nodes - 1) * 2 * 3; j += 3)
        {

            NODE_T to = xx[i][j];
            NUM_T reduced_cost = xx[i][j + 1];
            std::cout << "[" << to << " : " << reduced_cost << "] ";
            if (to == num_nodes - 1 || (i == num_nodes - 1 && to == num_nodes - 2)) break;
        }
#endif
        std::cout << std::endl;
    }
}


//------------------------------------------------------------------------------
template<typename NUM_T>
class min_cost_flow {

    NODE_T _num_nodes;
    std::array<NODE_T, MAX_SIG_SIZE> _nodes_to_Q;
    std::array<NODE_T, MAX_SIG_SIZE> _nodes_to_Qq;
    std::array< NUM_T, MAX_SIG_SIZE > d;
    std::array< NODE_T, MAX_SIG_SIZE > prev;
    #if USE_EDGE
            std::array<int, MAX_SIG_SIZE > counters;
    #endif
    #if USE_ARR
            std::array<int, MAX_SIG_SIZE > counters_arr;
    #endif
    #if USE_EDGE
            std::array< std::array< edge1<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE> r_cost_forward;
    #endif
    #if USE_ARR
            std::array< std::array< NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE> r_cost_forward_arr;
    #endif
    #if USE_EDGE
            std::array< std::array< edge2<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE > r_cost_cap_backward;
    #endif
    #if USE_ARR
            std::array< std::array< NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE> r_cost_cap_backward_arr;
    #endif

//    tictoc tictoc_shortest_path;
//    tictoc tictoc_while_true;
//    tictoc tmp_tic_toc;
//    tictoc tictoc_all_function;

public:

    // e - supply(positive) and demand(negative).
    // c[i] - edges that goes from node i. first is the second nod
    // x - the flow is returned in it
    NUM_T operator()(
                     std::array<NUM_T, MAX_SIG_SIZE>& e,
#if USE_EDGE
                     const std::array< std::array< edge<NUM_T>, MAX_SIG_SIZE >,MAX_SIG_SIZE >& c,
                     std::array< std::array< edge0<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE >& x,
#endif
#if USE_ARR
                     const std::array< std::array< NUM_T, MAX_SIG_SIZE >, MAX_SIG_SIZE >& cc,
                     std::array< std::array< NUM_T, MAX_SIG_SIZE >, MAX_SIG_SIZE >& xx,
#endif
                     const NODE_T eSize)
    {
        //for (NODE_T i = 0; i < e.size(); ++i) cout << e[i]<< " ";
        //cout << endl;
//        tictoc_all_function.tic();
        
        _num_nodes = eSize;
//        _nodes_to_Q.resize(_num_nodes);
#if USE_EDGE
        std::fill(counters.begin(), counters.begin() + _num_nodes, 0);
#endif
#if USE_ARR
        std::fill(counters_arr.begin(), counters_arr.begin() + _num_nodes, 0);
#endif
        // init flow
        for (NODE_T from = 0; from < _num_nodes; ++from)
        {
#if USE_EDGE
            for (const auto &node : c[from])
            {
                if (node._to == -1 && node._cost == -1) break;
                x[from][counters[from]] = edge0<NUM_T> (node._to, node._cost, 0);
                x[node._to][counters[node._to]] = edge0<NUM_T>(from, -node._cost, 0);
                counters[from]++;
                counters[node._to]++;
            }
#endif
#if USE_ARR
            for (int i = 0; i < _num_nodes * 2; i += 2)
            {
                NODE_T to = cc[from][i];
                NUM_T cost = cc[from][i + 1];
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
#endif
        } // from

//        printFlow<NUM_T, NODE_T>(x, _num_nodes);
            
        
        // reduced costs for forward edges (c[i,j]-pi[i]+pi[j])
        // Note that for forward edges the residual capacity is infinity

        for (NODE_T from = 0; from < _num_nodes; ++from)
        {
#if USE_EDGE
            int i = 0;
            for (const auto &node : c[from])
            {
                if (node._to == -1 && node._cost == -1) break;
                r_cost_forward[from][i] = edge1<NUM_T>(node._to, node._cost);
                i++;
            }
#endif
#if USE_ARR
            for (int i = 0; i < _num_nodes * 2; i += 2)
            {
                NODE_T to = cc[from][i];
                NUM_T cost = cc[from][i + 1];
                r_cost_forward_arr[from][i] = to;
                r_cost_forward_arr[from][i + 1] = cost;
                if (to == _num_nodes - 1 || (from == _num_nodes - 1 && to == _num_nodes - 2)) break;
            } // node
#endif
        } // from
            
//        printCostForward<NUM_T, NODE_T>(r_cost_forward, _num_nodes);
        
        // reduced costs and capacity for backward edges (c[j,i]-pi[j]+pi[i])
        // Since the flow at the beginning is 0, the residual capacity is also zero
#if USE_EDGE
        std::fill(counters.begin(), counters.begin() + _num_nodes, 0);
#endif
#if USE_ARR
        std::fill(counters_arr.begin(), counters_arr.begin() + _num_nodes, 0);
#endif
        for (NODE_T from = 0; from < _num_nodes; ++from)
        {
#if USE_EDGE
            for (const auto &node : c[from])
            {
                if (node._to == -1 && node._cost == -1) break;
                r_cost_cap_backward[node._to][counters[node._to]] = edge2<NUM_T>(from, -node._cost, 0);
                counters[node._to]++;
            }
                
#endif
#if USE_ARR
            for (int i = 0; i < _num_nodes * 2; i += 2)
            {
                NODE_T to = cc[from][i];
                NUM_T cost = cc[from][i + 1];

                r_cost_cap_backward_arr[to][counters_arr[to]] = from;
                r_cost_cap_backward_arr[to][counters_arr[to] + 1] = -cost;
                r_cost_cap_backward_arr[to][counters_arr[to] + 2] = 0;
                counters_arr[to] += 3;
                if (to == _num_nodes - 1 || (from == _num_nodes - 1 && to == _num_nodes - 2)) break;
            } // node
#endif
        } // from
//                printCostBackward<NUM_T, NODE_T>(r_cost_cap_backward, _num_nodes);
            
#if USE_EDGE && USE_ARR
            for (NODE_T from = 0; from < _num_nodes; ++from)
            {
                for (NODE_T i = 0; i < _num_nodes; ++i)
                {
                    if (r_cost_forward[from][i]._to == -1) break;
                    assert(r_cost_forward[from][i]._to == r_cost_forward_arr[from][ 2 * i]);
                    assert(r_cost_forward[from][i]._reduced_cost == r_cost_forward_arr[from][ 2 * i + 1]);
                }
            }
            for (NODE_T from = 0; from < _num_nodes; ++from)
            {
                for (NODE_T i = 0; i < _num_nodes; ++i)
                {
                    if (r_cost_cap_backward[from][i]._to == -1) break;
                    assert(r_cost_cap_backward[from][i]._to == r_cost_cap_backward_arr[from][ 3 * i]);
                    assert(r_cost_cap_backward[from][i]._reduced_cost == r_cost_cap_backward_arr[from][ 3 * i + 1]);
                    assert(r_cost_cap_backward[from][i]._residual_capacity == r_cost_cap_backward_arr[from][ 3 * i + 2]);
                }
            }
            
#endif

            
        // Max supply TODO:demand?, given U?, optimization-> min out of demand, supply
//        NUM_T U = *(std::max_element(e.begin(), e.begin() + _num_nodes));
    
        //NUM_T delta = static_cast<NUM_T>(pow(2.0l,ceil(log(static_cast<long double>(U))/log(2.0))));

#if USE_EDGE
        NUM_T delta = 1;
#endif
        NUM_T deltaq = 1;
        while (true)
        { //until we break when S or T is empty
            NODE_T k = static_cast<NODE_T>(std::distance(e.begin(),
                                    std::max_element(e.begin(), e.begin() + _num_nodes)));
            NUM_T maxSupply = e[k];
            if (maxSupply == 0) break;
#if USE_EDGE
            delta = maxSupply;
#endif
#if USE_ARR
            deltaq = maxSupply;
#endif
//        std::cout << "comput shortest path" << std::endl;
            NODE_T l;
            //tictoc_shortest_path.tic();
            compute_shortest_path(d, prev, k,
#if USE_EDGE
                                  r_cost_forward, r_cost_cap_backward,
#endif
#if USE_ARR
                                  r_cost_forward_arr, r_cost_cap_backward_arr,
#endif
                                  e, l);
            
            

            //tictoc_shortest_path.toc();
            
//        std::cout << "l = " << l << std::endl;

            
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
#if USE_EDGE
                auto it = std::find_if(r_cost_cap_backward[from].begin(),
                                       r_cost_cap_backward[from].begin() + _num_nodes,
                                       [&](auto &e) {return e._to == to;});
                if (it != r_cost_cap_backward[from].begin() + _num_nodes)
                {
                    if (it->_to != -1 && it->_residual_capacity < delta) delta = it->_residual_capacity;
                }
#endif
#if USE_ARR
                auto it_arr = findIndex <std::array<std::array<NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE>>
                        (r_cost_cap_backward_arr, _num_nodes, from, to);
                if (it_arr != r_cost_cap_backward_arr[from].end())
                {
                    if (it_arr[2] < deltaq) deltaq = it_arr[2];
                }

#endif
#if USE_EDGE && USE_ARR
                assert(delta == deltaq);
#endif
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
#if USE_EDGE
                std::find_if(x[from].begin(), x[from].begin() + _num_nodes, [&](auto &e) {return e._to == to;})->_flow += delta;
#endif
#if USE_ARR
                findIndex <std::array<std::array<NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE>> (xx, _num_nodes, from, to)[2] += deltaq;
#endif
                // update residual for backward edges
#if USE_EDGE
                auto it = std::find_if(r_cost_cap_backward[to].begin(),
                                       r_cost_cap_backward[to].begin() + _num_nodes,
                                       [&](auto &e) {return e._to == from;});
                if (it != r_cost_cap_backward[to].begin() + _num_nodes) it->_residual_capacity += delta;
                
                it = std::find_if(r_cost_cap_backward[from].begin(),
                                       r_cost_cap_backward[from].begin() + _num_nodes,
                                       [&](auto &e) {return e._to == to;});
                if (it != r_cost_cap_backward[from].begin() + _num_nodes) it->_residual_capacity -= delta;
#endif
#if USE_ARR
                auto it_arr = findIndex <std::array<std::array<NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE>>
                (r_cost_cap_backward_arr, _num_nodes, to, from);
                if (it_arr != r_cost_cap_backward_arr[to].end()) it_arr [2] += deltaq;

                it_arr = findIndex <std::array<std::array<NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE>>
                        (r_cost_cap_backward_arr, _num_nodes, from, to);
                if (it_arr != r_cost_cap_backward_arr[from].end()) it_arr [2] -= deltaq;
#endif
#if USE_EDGE && USE_ARR
                for (NODE_T from = 0; from < _num_nodes; ++from)
                {
                    for (NODE_T i = 0; i < _num_nodes; ++i)
                    {
                        if (r_cost_cap_backward[from][i]._to == -1) break;
                        assert(r_cost_cap_backward[from][i]._to == r_cost_cap_backward_arr[from][ 3 * i]);
                        assert(r_cost_cap_backward[from][i]._reduced_cost == r_cost_cap_backward_arr[from][ 3 * i + 1]);
                        assert(r_cost_cap_backward[from][i]._residual_capacity == r_cost_cap_backward_arr[from][ 3 * i + 2]);
                    }
                }
                for (NODE_T from = 0; from < _num_nodes; ++from)
                {
                    for (NODE_T i = 0; i < _num_nodes; ++i)
                    {
                        if (r_cost_forward[from][i]._to == -1) break;
                        assert(r_cost_forward[from][i]._to == r_cost_forward_arr[from][ 2 * i]);
                        assert(r_cost_forward[from][i]._reduced_cost == r_cost_forward_arr[from][ 2 * i + 1]);
                    }
                }
#endif

                // update e
#if USE_EDGE && !USE_ARR
                e[to] += delta;
                e[from] -= delta;
#endif
#if USE_ARR
                e[to] += deltaq;
                e[from] -= deltaq;
#endif
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
#if USE_EDGE
            for (auto it : x[from])
            {
                if (it._to == -1 && it._cost == -1 && it._flow == -1) break;
                    dist += (it._cost*it._flow);
            }
#endif
#if USE_ARR
            bool lastNode = false;
            for (int j = 0;  j < _num_nodes * 3; j += 3)
            {

                if (lastNode) break;
                NODE_T to = xx[from][j];
                NUM_T cost = xx[from][j + 1];
                NUM_T flow = xx[from][j + 2];
                dist += cost * flow;
                if ((from < _num_nodes - 1 && to == _num_nodes - 1) ||
                    (from == _num_nodes - 1 && to == _num_nodes - 2))
                    lastNode = true;
            } // it
#endif
        } // from
        return dist;
    } // operator()




private:
    #if USE_EDGE
                std::array<  edge3<NUM_T> ,MAX_SIG_SIZE  > Q;
    #endif
    #if USE_ARR
                std::array< NUM_T, MAX_SIG_SIZE> Qq;
    #endif
    std::array<NODE_T, MAX_SIG_SIZE> finalNodesFlg;

    void compute_shortest_path(std::array< NUM_T, MAX_SIG_SIZE >& d,
                               std::array< NODE_T, MAX_SIG_SIZE >& prev,
                               NODE_T from,
#if USE_EDGE
                               std::array< std::array< edge1<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE >& cost_forward,
                               std::array< std::array< edge2<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE >& cost_backward,
#endif
#if USE_ARR
                               std::array< std::array< NUM_T, MAX_SIG_SIZE >, MAX_SIG_SIZE >& cost_forward_arr,
                               std::array< std::array< NUM_T, MAX_SIG_SIZE >, MAX_SIG_SIZE >& cost_backward_arr,
#endif
                               const std::array<NUM_T, MAX_SIG_SIZE>& e,
                               NODE_T& l)
        {
            //----------------------------------------------------------------
            // Making heap (all inf except 0, so we are saving comparisons...)
            //----------------------------------------------------------------
#if USE_EDGE
            Q[0]._to = from;
            Q[0]._dist = 0;
            NODE_T j = 1;
#endif
#if USE_ARR
            Qq[0] = from;
            Qq[1] = 0;
            NODE_T jq = 2;
#endif
            _nodes_to_Q[from] = 0;
            _nodes_to_Qq[from] = 0;
            

            // TODO: both of these into a function?
            for (NODE_T i = 0; i < from; ++i)
            {
#if USE_EDGE
                _nodes_to_Q[i] = j;
                Q[j]._to = i;
                Q[j]._dist = std::numeric_limits<NUM_T>::max();
                ++j;
#endif
#if USE_ARR
                _nodes_to_Qq[i] = jq;
                Qq[jq] = i;
                Qq[jq + 1] = std::numeric_limits<NUM_T>::max();
                jq += 2;
#endif
            }

            for (NODE_T i = from + 1; i < _num_nodes; ++i)
            {
#if USE_EDGE
                _nodes_to_Q[i] = j;
                Q[j]._to = i;
                Q[j]._dist = std::numeric_limits<NUM_T>::max();
                ++j;
#endif
#if USE_ARR
                _nodes_to_Qq[i] = jq;
                Qq[jq] = i;
                Qq[jq + 1] = std::numeric_limits<NUM_T>::max();
                jq += 2;
#endif
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
#if USE_EDGE
                u = Q[0]._to;
                d[u] = Q[0]._dist; // final distance
#endif
#if USE_ARR
                u = Qq[0];
                d[u] = Qq[1]; // final distance
#endif
                
                
//                std::cout << u << " ";
                finalNodesFlg[u] = true;
                if (e[u] < 0)
                {
                    l = u;
                    break;
                }
//#if USE_EDGE
//                for (int i = 0; i < Qsize; ++i)
//                    std::cout << "[" << Q[i]._to << " : " << Q[i]._dist << "]";
//                std::cout << std::endl;
//#endif
//#if USE_ARR
//                for (int i = 0; i < Qqsize; i += 2)
//                    std::cout << "[" << Qq[i] << " : " << Qq[i + 1] << "]";
//                std::cout << std::endl;
//#endif
#if USE_EDGE
                heap_remove_first(Q, _nodes_to_Q, Qsize);
#endif
#if USE_ARR
                heap_remove_first_arr(Qq, _nodes_to_Qq, Qqsize);
#endif

#if USE_EDGE && USE_ARR
                assert(Qsize == Qqsize/2);
                for(NODE_T i = 0; i < _num_nodes; ++i)
                {
                    assert(Q[i]._to == Qq[2 * i] && Q[i]._dist == Qq[2 * i + 1]);
                    assert(_nodes_to_Q[i] == _nodes_to_Qq[i]/2);
                }
#endif
                
                // neighbors of u
                for (NODE_T i = 0; i < _num_nodes; ++i)
                {
#if USE_EDGE
                    const auto &it = cost_forward[u][i];
                    if (it._to == -1) break;
                    assert (it._reduced_cost >= 0);
                    NUM_T alt = d[u] + it._reduced_cost;
                    NODE_T v = it._to;
                    if ( (_nodes_to_Q[v] < Qsize) && (alt < Q[_nodes_to_Q[v]]._dist) )
                    {
                        heap_decrease_key(Q, _nodes_to_Q, v, alt);
                        prev[v]= u;
                    }
#endif
#if USE_ARR
                    
                    auto itq = &cost_forward_arr[u][2 * i];
                    assert (itq[1] >= 0);
                    NUM_T altq = d[u] + itq[1];
                    NODE_T vq = *itq;
//                  std::cout << it._to << ": " << _nodes_to_Q[v] << " < " << Qsize << std::endl;
            
                    if ( (_nodes_to_Qq[vq] < Qqsize) && (altq < Qq[_nodes_to_Qq[vq] + 1]) )
                    {
                        heap_decrease_key_arr(Qq, _nodes_to_Qq, vq, altq);
                        prev[vq]= u;
                    }
                    if (*itq == _num_nodes - 1 || (from == _num_nodes - 1 && *itq == _num_nodes - 2)) break;
#endif
#if USE_EDGE && USE_ARR
                    assert(Qsize == Qqsize/2);
                    for(NODE_T i = 0; i < _num_nodes; ++i)
                    {
                        assert(Q[i]._to == Qq[2 * i] && Q[i]._dist == Qq[2 * i + 1]);
                        assert(_nodes_to_Q[i] == _nodes_to_Qq[i]/2);
                    }
#endif
                } //it
                        
                for (NODE_T i = 0; i < _num_nodes; ++i)
                {
#if USE_EDGE
                    const auto &it = cost_backward[u][i];
                    if (it._to == -1) break;
                    if (it._residual_capacity > 0)
                    {
                        assert (it._reduced_cost>=0);
                        NUM_T alt = d[u] + it._reduced_cost;
                        NODE_T v = it._to;
                        if ( (_nodes_to_Q[v] < Qsize) && (alt < Q[_nodes_to_Q[v]]._dist) )
                        {
                            heap_decrease_key(Q, _nodes_to_Q, v, alt);
                            prev[v] = u;
                        }
                    }
                    
#endif
#if USE_ARR
                    auto itq = &cost_backward_arr[u][3 * i];
                    if (itq[2] > 0)
                    {
                        assert (itq[1] >= 0);
                        NUM_T altq = d[u] + itq[1];
                        NODE_T vq = *itq;
                        if ( (_nodes_to_Qq[vq] < Qqsize) && (altq < Qq[_nodes_to_Qq[vq] + 1]) )
                        {
                            heap_decrease_key_arr(Qq, _nodes_to_Qq, vq, altq);
                            prev[vq] = u;
                        }
                    }
                    if (*itq == _num_nodes - 1 || (from == _num_nodes - 1 && *itq == _num_nodes - 2)) break;
#endif
#if USE_EDGE && USE_ARR
                    assert(Qsize == Qqsize/2);
                    for(NODE_T i = 0; i < _num_nodes; ++i)
                    {
                        assert(Q[i]._to == Qq[2 * i] && Q[i]._dist == Qq[2 * i + 1]);
                        assert(_nodes_to_Q[i] == _nodes_to_Qq[i]/2);
                    }
#endif
                }
                
            } while (!(Qsize == 0));

//            std::cout << std::endl;
            //tmp_tic_toc.tic();
            //---------------------------------------------------------------------------------
            // reduced costs for forward edges (c[i,j]-pi[i]+pi[j])
            if(std::any_of(d.begin(), d.begin() + _num_nodes, [](NUM_T n) {return n != 0;}))
            {
                for (NODE_T from = 0; from < _num_nodes; ++from)
                {
                    for (NODE_T i = 0; i < _num_nodes; ++i)
                    {
#if USE_EDGE
                        auto &it = cost_forward[from][i];
                        if (it._to == -1 && it._reduced_cost == -1) break;
                        if (finalNodesFlg[from])
                        {
                            it._reduced_cost += d[from] - d[l];
                        }
                        if (finalNodesFlg[it._to])
                        {
                            it._reduced_cost -= d[it._to] - d[l];
                        }
#endif
#if USE_ARR
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
#endif
#if USE_EDGE && USE_ARR
                        for (NODE_T k = 0; k < _num_nodes; ++k)
                        {
                            for (NODE_T m = 0; i < _num_nodes; ++m)
                            {
                                if (cost_forward[k][m]._to == -1) break;
                                assert(cost_forward[k][m]._to == cost_forward_arr[k][ 2 * m]);
                                assert(cost_forward[k][m]._reduced_cost == cost_forward_arr[k][ 2 * m + 1]);
                            }
                        }
#endif
                    }
                }
                
                // reduced costs and capacity for backward edges (c[j,i]-pi[j]+pi[i])
                for (NODE_T from = 0; from < _num_nodes; ++from)
                {
                    for (NODE_T i = 0; i < _num_nodes; ++i)
                    {
#if USE_EDGE
                        auto &it = cost_backward[from][i];
                        if (it._to == -1 && it._reduced_cost == -1) break;
                        if (finalNodesFlg[from])
                        {
                            it._reduced_cost += d[from] - d[l];
                        }
                        if (finalNodesFlg[it._to])
                        {
                            it._reduced_cost -= d[it._to] - d[l];
                        }
#endif
#if USE_ARR
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
#endif
#if USE_EDGE && USE_ARR
                        for (NODE_T k = 0; k < _num_nodes; ++k)
                        {
                            for (NODE_T m = 0; i < _num_nodes; ++m)
                            {
                                if (cost_backward[k][m]._to == -1) break;
                                assert(cost_backward[k][m]._to == cost_backward_arr[k][ 3 * m]);
                                assert(cost_backward[k][m]._reduced_cost == cost_backward_arr[k][ 3 * m + 1]);
                            }
                        }
#endif
                    }
                }
            } // if...
#if USE_EDGE && USE_ARR
//            std::cout << "checking..." << std::endl;
            for (NODE_T from = 0; from < _num_nodes; ++from)
            {
                for (NODE_T i = 0; i < _num_nodes; ++i)
                {
                    if (cost_forward[from][i]._to == -1) break;
                    assert(cost_forward[from][i]._to == cost_forward_arr[from][ 2 * i]);
                    assert(cost_forward[from][i]._reduced_cost == cost_forward_arr[from][ 2 * i + 1]);
                }
            }
            for (NODE_T from = 0; from < _num_nodes; ++from)
            {
                for (NODE_T i = 0; i < _num_nodes; ++i)
                {
                    if (cost_backward[from][i]._to == -1) break;
                    assert(cost_backward[from][i]._to == cost_backward_arr[from][ 3 * i]);
                    assert(cost_backward[from][i]._reduced_cost == cost_backward_arr[from][ 3 * i + 1]);
                }
            }
            
#endif
            
            
        } // compute_shortest_path


#if USE_EDGE
    void heap_decrease_key(std::array<  edge3<NUM_T> ,MAX_SIG_SIZE  >& Q,
                           std::array<NODE_T, MAX_SIG_SIZE>& nodes_to_Q,
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
                           std::array<NODE_T, MAX_SIG_SIZE>& nodes_to_Q,
                           int &Qsize)
    {
        Qsize -= 1;
        swap_heap(Q, nodes_to_Q, 0, Qsize);
        heapify(Q, nodes_to_Q, 0, Qsize);
    } // heap_remove_first
        
    void heapify(std::array<  edge3<NUM_T> ,MAX_SIG_SIZE  >& Q, std::array<NODE_T, MAX_SIG_SIZE>& nodes_to_Q,
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
        
    void swap_heap(std::array<  edge3<NUM_T>, MAX_SIG_SIZE  >& Q,
                   std::array<NODE_T, MAX_SIG_SIZE>& nodes_to_Q, NODE_T i, NODE_T j)
    {
        edge3<NUM_T> tmp = Q[i];
        Q[i] = Q[j];
        Q[j] = tmp;
        nodes_to_Q[ Q[j]._to ] = j;
        nodes_to_Q[ Q[i]._to ] = i;
    } // swap_heapify
#endif
#if USE_ARR
    template <typename T>
    auto findIndex(T &input, NODE_T _num_nodes, NODE_T node, NODE_T value)
    {
        auto it_arr = input[node].end();
        for (NODE_T i = 0; i < _num_nodes; ++i)
        {
            it_arr = &input[node][3 * i];
            if (*it_arr == value) break;
            if (*it_arr == _num_nodes - 1 || (node == _num_nodes - 1 && *it_arr == _num_nodes - 2))
            {
                it_arr = input[node].end();
                break;
            }
        }
        return it_arr;
    }
    
    void heap_decrease_key_arr(std::array< NUM_T, MAX_SIG_SIZE >& Q,
                           std::array< NODE_T, MAX_SIG_SIZE> & nodes_to_Q,
                           NODE_T v, NUM_T alt)
    {
        NODE_T i = nodes_to_Q[v];
        Q[i + 1] = alt;
        while (i > 0 && Q[PARENT(i / 2) * 2 + 1] > Q[i + 1])
        {
            swap_heap_arr(Q, nodes_to_Q, i, PARENT(i / 2) * 2);
            i = PARENT(i / 2) * 2;
        }
    } // heap_decrease_key
            
    void heap_remove_first_arr(std::array< NUM_T, MAX_SIG_SIZE >& Q,
                           std::array< NODE_T, MAX_SIG_SIZE >& nodes_to_Q,
                           int &Qsize)
    {
        Qsize -= 2;
        swap_heap_arr(Q, nodes_to_Q, 0, Qsize);
        heapify_arr(Q, nodes_to_Q, 0, Qsize);
    } // heap_remove_first
        
    void heapify_arr(std::array< NUM_T, MAX_SIG_SIZE >& Q,
                 std::array< NODE_T, MAX_SIG_SIZE >& nodes_to_Q,
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
        
    void swap_heap_arr(std::array< NUM_T, MAX_SIG_SIZE  >& Q,
                   std::array< NODE_T, MAX_SIG_SIZE> & nodes_to_Q, NODE_T i, NODE_T j)
    {
        std::swap(Q[i], Q[j]);
        std::swap(Q[i + 1], Q[j + 1]);
        nodes_to_Q[ Q[j] ] = j;
        nodes_to_Q[ Q[i] ] = i;
    } // swap_heapify
#endif

    
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





