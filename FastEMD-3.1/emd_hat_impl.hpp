#ifndef EMD_HAT_IMPL_HPP
#define EMD_HAT_IMPL_HPP
#define USE_SET 0
#define USE_VECTOR 0
#define USE_CC_VECTOR 1
#define TIME 0
#define USE_EDGE 1
#define PRINT 0


//=======================================================================================
// Implementation stuff
//=======================================================================================

#include "min_cost_flow.hpp"
#include <set>
#include <array>
#include <limits>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "tictoc.hpp"


template<typename NUM_T>
void fillFWithZeros(std::vector< std::vector<NUM_T> >& F) {
    for (NODE_T i= 0; i<F.size(); ++i) {
        for (NODE_T j= 0; j<F[i].size(); ++j) {
            F[i][j]= 0;
        }
    }
}
        
// Forward declarations 
template<typename NUM_T, FLOW_TYPE_T FLOW_TYPE> struct emd_hat_impl;

template<typename NUM_T,FLOW_TYPE_T FLOW_TYPE>
NUM_T emd_hat_gd_metric<NUM_T,FLOW_TYPE>::operator()(const std::vector<NUM_T>& Pc, const std::vector<NUM_T>& Qc,
                                                     const std::vector< std::vector<NUM_T> >& C,
                                                     NUM_T extra_mass_penalty,
                                                     std::vector< std::vector<NUM_T> >* F,
                                                     NUM_T maxC)
{

    if (FLOW_TYPE != NO_FLOW) fillFWithZeros(*F);
        
    assert( (F != NULL) || (FLOW_TYPE == NO_FLOW) );

    return emd_hat_impl<NUM_T,FLOW_TYPE>()(Pc,Qc,Pc,Qc,C,extra_mass_penalty,F, maxC);
    
} // emd_hat_gd_metric

template<typename NUM_T,FLOW_TYPE_T FLOW_TYPE>
NUM_T emd_hat<NUM_T,FLOW_TYPE>::operator()(const std::vector<NUM_T>& P, const std::vector<NUM_T>& Q,
                                           const std::vector< std::vector<NUM_T> >& C,
                                           NUM_T extra_mass_penalty,
                                           std::vector< std::vector<NUM_T> >* F)
{

    if (FLOW_TYPE!=NO_FLOW) fillFWithZeros(*F);
    return emd_hat_impl<NUM_T,FLOW_TYPE>()(P,Q,P,Q,C,extra_mass_penalty,F);

} // emd_hat


//-----------------------------------------------------------------------------------------------
// Implementing it for different types
//-----------------------------------------------------------------------------------------------

// Blocking instantiation for a non-overloaded template param
template<typename NUM_T, FLOW_TYPE_T FLOW_TYPE>
struct emd_hat_impl {
        
}; // emd_hat_impl


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Main implementation
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
template<typename NUM_T, FLOW_TYPE_T FLOW_TYPE>
struct emd_hat_impl_integral_types
{

    NUM_T operator()(
                     const std::vector<NUM_T>& POrig, const std::vector<NUM_T>& QOrig,
                     const std::vector<NUM_T>& P, const std::vector<NUM_T>& Q,
                     const std::vector< std::vector<NUM_T> >& Cc,
                     NUM_T extra_mass_penalty,
                     std::vector< std::vector<NUM_T> >* F,
                     NUM_T maxC)
    {
#if TIME
        tictoc timerOperator;
        timerOperator.tic();
#endif
//        std::for_each(P.begin(), P.end(), [](int n ) {std::cout << n << " ";});
//        std::cout << std::endl;
//        std::for_each(Q.begin(), Q.end(), [](int n ) {std::cout << n << " ";});
//        std::cout << std::endl;
        // creating the b vector that contains all vertexes
        //-------------------------------------------------------
        NODE_T N = static_cast<NODE_T>(P.size());
        assert(Q.size() == N);
        //-------------------------------------------------------
        const int REMOVE_NODE_FLAG = -1;         // as I'm using -1 as a special flag !!!
        if(maxC == -1)
        {
            for (NODE_T i = 0; i < N; ++i)
            {
                for (NODE_T j = 0; j < N; ++j)
                {
                    assert(Cc[i][j] >= 0);
                    if ( Cc[i][j] > maxC ) maxC = Cc[i][j];
                }
            }
        }
        std::array<NUM_T, MAX_SIG_SIZE > b{};
//        size_t bSize = 2 * N + 2;
        const NODE_T THRESHOLD_NODE = 2 * N;
        const NODE_T ARTIFICIAL_NODE = 2 * N + 1; // need to be last !
        // Assuming metric property we can pre-flow 0-cost edges
        NUM_T sum_P = 0;
        NUM_T sum_Q = 0;
        
        for (NODE_T i = 0; i < N; ++i)
        {
            if (P[i] < Q[i])
            {
                if (FLOW_TYPE != NO_FLOW)
                {
                    ((*F)[i][i]) = P[i];
                }
                sum_Q += Q[i] - P[i];
                b[i] = 0;
                b[i + N] = P[i] - Q[i];
            }
            else if (P[i] > Q [i])
            {
                if (FLOW_TYPE != NO_FLOW)
                {
                    ((*F)[i][i]) = Q[i];
                }
                sum_P += P[i] - Q[i];
                b[i] = P[i] - Q[i];
                b[i + N] = 0;
            }
            else // P[i] == Q[i]
            {
                if (FLOW_TYPE != NO_FLOW)
                {
                    ((*F)[i][i]) = Q[i];
                }
                b[i] = b[i + N] = 0;
            }
        }
        // Ensuring that the supplier - P, has more mass.
//        std::cout << sum_Q << " " << sum_P << std::endl;
//        std::for_each(b.begin(), b.begin() + 2 * N + 2, [](int n ) {std::cout << n << " ";});
//        std::cout << std::endl;
        bool needToSwapFlow = false;
        NUM_T abs_diff_sum_P_sum_Q = std::abs(sum_P - sum_Q);
        if (sum_Q > sum_P)
        {
            needToSwapFlow = true;
            std::swap_ranges(b.begin(), b.begin() + N, b.begin() + N);
            std::transform(b.begin(), b.begin() + 2 * N + 2, b.begin(),
                        std::bind(std::multiplies<NUM_T>(), std::placeholders::_1, -1));
        }


//        if (needToSwapFlow) std::cout << "needToSwapFlow" << std::endl;
    
        // remark*) I put here a deficit of the extra mass, as mass that flows to the threshold node
        // can be absorbed from all sources with cost zero (this is in reverse order from the paper,
        // where incoming edges to the threshold node had the cost of the threshold and outgoing
        // edges had the cost of zero)
        // This also makes sum of b zero.
        b[THRESHOLD_NODE] = -abs_diff_sum_P_sum_Q;
        b[ARTIFICIAL_NODE] = 0;
        // + 1 because b[ARTIFICIAL_NODE] == 0;
        //-------------------------------------------------------
    
        if (extra_mass_penalty == -1) extra_mass_penalty = maxC;

        //=============================================================
        // regular edges between sinks and sources without threshold edges
        // checking which are not isolated
        // remove nodes with supply demand of 0
        // and vertexes that are connected only to the
        // threshold vertex
#if USE_SET
        std::set< NODE_T > sources_that_flow_not_only_to_thresh;
        std::set< NODE_T > sinks_that_get_flow_not_only_from_thresh;
#endif
        std::array< std::array< edge0<NUM_T>, MAX_SIG_SIZE  >, MAX_SIG_SIZE > flows{};
#if USE_EDGE
        std::array< std::array< edge<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE> cc;
#else
        std::array< std::array< NUM_T, MAX_SIG_SIZE >, MAX_SIG_SIZE> c;
#endif
        std::array<NODE_T, MAX_SIG_SIZE/2> uniqueJs{};
        NODE_T sourcesCounter = 0; // number of sources_that_flow_not_only_to_thresh
        NODE_T sinksCounter = -1; // number of sinks_that_get_flow_not_only_from_thresh
        NODE_T lastJ = 0;
        NUM_T pre_flow_cost = 0;
        NUM_T cost = 0;
        for (NODE_T i = 0; i < N; ++i)
        {
            if (b[i] == 0)
            {
                continue;
            }
            bool once = false;
            int sinksForNode = 0;
            for (NODE_T j = 0; j < N; ++j)
            {
                if (b[j + N] == 0)
                {
                    continue;
                }
                cost = needToSwapFlow ? Cc[j][i] : Cc[i][j];
                if (cost == maxC)
                {
                    continue;
                }
                if (uniqueJs[j] != j)
                {
                    uniqueJs[j] = j;
                    sinksCounter++;
//                    std::cout << sinksCounter << " " << j + N << " ";
                }
#if USE_EDGE
                cc[sourcesCounter][sinksForNode] = edge<NUM_T>(j, Cc[i][j]);
#else
                c[sourcesCounter][2 * sinksForNode] = sinksCounter;
                c[sourcesCounter][2 * sinksForNode + 1] = cost;
#endif
                sinksForNode++;
                once = true;
#if USE_SET
                sources_that_flow_not_only_to_thresh.insert(i);
                sinks_that_get_flow_not_only_from_thresh.insert(j + N);
#endif
            } // j
            if(once)
            { // mark last node
#if USE_EDGE
                cc[sourcesCounter][sinksForNode] = edge<NUM_T>(-1, -1);
                cc[sourcesCounter][sinksForNode + 1] = edge<NUM_T>(-1, -1);
#else
                
                c[sourcesCounter][2 * sinksForNode + 1] = -1;
                c[sourcesCounter][2 * sinksForNode + 2] = -1;// to THRESHOLD_NODE´
#endif
                sourcesCounter++;
            }
            else
            {
                b[THRESHOLD_NODE] += b[i];
                b[i] = 0;
            }
        } // i
        for (int i = 0; i < N; ++i)
        {
            if (uniqueJs[i] == 0 && b[i + N] != 0)
            {
                //TODO: fix pre_flow_cost
                pre_flow_cost -= (b[i + N] * maxC);
                b[THRESHOLD_NODE] += b[i + N];
                b[i + N] = 0;
            }
        }
        // reorder b array so that all weights are in range [0, sourcesCounter + sinksCounter + 2];
        int shrinkCounter = 0;
        for (int i = 0; i < 2 * N + 1; ++i)
        {
            if (b[i] != 0)
            {
                if (i >= N && uniqueJs[i - N] != 0)
                {
                    uniqueJs[i - N] = shrinkCounter;
                }
                b[shrinkCounter] = b[i];
                shrinkCounter++;
            }
        }
        b[shrinkCounter] = 0;
//        std::cout << "b after shrink: ";
//        for(auto &elem : b) std::cout << elem << " ";
//        std::cout << std::endl;
#if USE_SET
        std::cout << std::endl;
        std::cout << "printing sets" << std::endl;
        for(auto & elem : sinks_that_get_flow_not_only_from_thresh) std::cout << elem << " ";
        std::cout << sinks_that_get_flow_not_only_from_thresh.size() << std::endl;
        for(auto & elem : sources_that_flow_not_only_to_thresh) std::cout << elem << " ";
        std::cout << sources_that_flow_not_only_to_thresh.size() << std::endl;
#endif
//        std::cout << sinksCounter << " " << sourcesCounter << std::endl;
        NODE_T ccSize = sourcesCounter + sinksCounter + 3;
        // update the edge._to values to new node names:
//        for(auto &node : cc)
//        {
//            for(auto &e : node)
//            {
//                if(e._to == -1 && e._cost == -1) break;
//                e._to += sourcesCounter;
//            }
//        }
        // add THRESHOLD_NODE
        for (NODE_T i = sourcesCounter; i <= sourcesCounter + sinksCounter; ++i)
        {
#if USE_EDGE
            cc[ccSize - 2][i - sourcesCounter] = edge<NUM_T>(i, maxC);
#else
            c[ccSize - 2][2 * (i - sourcesCounter)] = i;
            c[ccSize - 2][2 * (i - sourcesCounter) + 1] = maxC;
#endif
        }
        // add Artifical_NODE
        for (NODE_T i = 0; i < ccSize - 1; ++i)
        {
#if USE_EDGE
            cc[ccSize - 1][i] = edge<NUM_T>(i, maxC + 1);
#else
            c[ccSize - 1][2 * i] = i;
            c[ccSize - 1][2 * i + 1] = maxC + 1;
#endif
        }
        for(NODE_T i = 0; i < ccSize - 2; ++i)
        {
            for(NODE_T j = 0; j < sinksCounter + 2; ++j)
            {
#if USE_EDGE
                if (cc[i][j]._to != -1 && cc[i][j]._cost != -1) continue;
                if (i < sourcesCounter)
                {
                    cc[i][j] = edge<NUM_T>(ccSize - 2, 0);
                    cc[i][j + 1] = edge<NUM_T>(ccSize - 1, maxC + 1);
                }
                else
                {
                    cc[i][j] = edge<NUM_T>(ccSize - 1, maxC + 1);
                }
#else
                if (i < sourcesCounter &&
                    c[i][2 * j] != REMOVE_NODE_FLAG &&
                     c[i][2 * j + 1] != REMOVE_NODE_FLAG) continue;
                c[i][2 * j] = ccSize - 2;
                c[i][2 * j + 1] = 0;// to THRESHOLD_NODE
                c[i][2 * j + 2] = ccSize - 1;
                c[i][2 * j + 3] = maxC;// to ARTIFICAL_NODE
#endif
                break;
            }
        }
        // add edge from THRESHOLD_NODE to ARTIFICIAL_NODE
#if USE_EDGE
        cc[ccSize - 2][sinksCounter + 1] = edge<NUM_T>(ccSize - 1, maxC + 1);// to ARTIFICAL_NODE
#else
        c[ccSize - 2][2 * sinksCounter + 2] = ccSize - 1;
        c[ccSize - 2][2 * sinksCounter + 3] = maxC + 1;
#endif
        // update sink names ([sourcesCounter; sourcesCounter + sinksCounter))
        for (NODE_T i = 0; i < sourcesCounter; ++i)
        {
            for (NODE_T j = 0; j < sinksCounter + 1; ++j)
            {
#if USE_EDGE
                if (cc[i][j]._to == ccSize - 2) break;
                cc[i][j]._to = uniqueJs[cc[i][j]._to];
#else
                if (c[i][2 * j] == ccSize - 2) break;
                c[i][2 * j] += sourcesCounter;
#endif
            }
        }

        //====================================================
#if PRINT && !USE_EDGE
        for (NODE_T i = 0; i < ccSize; ++i)
        {
            std::cout << i << ": ";
            for (NODE_T j = 0; j < 2 * ccSize; j += 2)
            {
                std::cout << "[" << c[i][j] << " : " << c[i][j + 1] << "] ";
                if (c[i][j] == ccSize - 1) break;
                if (i == ccSize - 1 && c[i][j] == ccSize - 2) break;
            }
            std::cout << std::endl;
        }
#endif

#if PRINT && USE_EDGE
        for (NODE_T i = 0; i < ccSize; ++i)
        {
            std::cout << i << ": ";
            for (auto &edge : cc[i])
            {
                if (edge._to == -1 && edge._cost == -1) break;
                std::cout << "[" << edge._to << " : " << edge._cost << "] ";
            }
            std::cout << std::endl;
        }
#endif
        //====================================================

        #ifndef NDEBUG
//        for (int i = 0; i < )
//        std::for_each(b.begin(), b.begin() + ccSize, [](int n ) {std::cout << n << " ";});
//        std::cout << std::endl;
        NUM_T DEBUG_sum_b = 0;
        for (NODE_T i = 0; i < ccSize; ++i) DEBUG_sum_b += b[i];
        assert(DEBUG_sum_b == 0);
        #endif

        //-------------------------------------------------------
#if TIME
        timerOperator.toc();
        std::cout << "operator before min_cost_flowtime == "
                << timerOperator.totalTime<std::chrono::microseconds>() << std::endl;
//        tictoc timer;
//        timer.tic();
#endif
        min_cost_flow<NUM_T> mcf;
//#if USE_VECTOR
//        NUM_T mcf_dist = mcf(bb, cc, flows);
//#else
        NUM_T mcf_dist = mcf(b, ccSize, cc, flows);
//#endif
//#if TIME
//        timer.toc();
//        std::cout << "min_cost_flow time == " << timer.totalTime<std::chrono::microseconds>() << std::endl;
//#endif
//        NUM_T mcf_dist = 0;

//    if (FLOW_TYPE != NO_FLOW) {
//        for (NODE_T new_name_from=0; new_name_from<flows.size(); ++new_name_from) {
//            for (typename std::vector<  edge0<NUM_T>  >::const_iterator it= flows[new_name_from].begin(); it!=flows[new_name_from].end(); ++it) {
//                if (new_name_from==nodes_new_names[THRESHOLD_NODE]||it->_to==nodes_new_names[THRESHOLD_NODE]) continue;
//                NODE_T i,j;
//                NUM_T flow= it->_flow;
//                bool reverseEdge= it->_to<new_name_from;
//                if (!reverseEdge) {
//                    i= nodes_old_names[new_name_from];
//                    j= nodes_old_names[it->_to]-N;
//                } else {
//                    i= nodes_old_names[it->_to];
//                    j= nodes_old_names[new_name_from]-N;
//                }
//                if (flow!=0&&new_name_from!=nodes_new_names[THRESHOLD_NODE]&&it->_to!=nodes_new_names[THRESHOLD_NODE]) {
//                    assert(i<N&&j<N);
//                    if (needToSwapFlow) std::swap(i,j);
//                    if (!reverseEdge) {
//                        (*F)[i][j]+= flow;
//                    } else {
//                        (*F)[i][j]-= flow;
//                    }
//                }
//            }
//        }
//    }
//
//    if (FLOW_TYPE == WITHOUT_EXTRA_MASS_FLOW)
//    {
//        transform_flow_to_regular(*F, POrig, QOrig);
//    }
//    std::cout << pre_flow_cost << " + " << mcf_dist << " + " << (abs_diff_sum_P_sum_Q * extra_mass_penalty) << std::endl;
    NUM_T my_dist =
        pre_flow_cost + // pre-flowing on cases where it was possible
        mcf_dist + // solution of the transportation problem
        (abs_diff_sum_P_sum_Q * extra_mass_penalty); // emd-hat extra mass penalty

    return my_dist;
    //-------------------------------------------------------
    
} // emd_hat_impl_integral_types (main implementation) operator()
};
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//----------------------------------------------------------------------------------------
// integral types
//----------------------------------------------------------------------------------------
template<FLOW_TYPE_T FLOW_TYPE>
struct emd_hat_impl<int,FLOW_TYPE> {

    typedef int NUM_T;
    
    NUM_T operator()(
        const std::vector<NUM_T>& POrig, const std::vector<NUM_T>& QOrig,
        const std::vector<NUM_T>& P, const std::vector<NUM_T>& Q,
        const std::vector< std::vector<NUM_T> >& C,
        NUM_T extra_mass_penalty,
        std::vector< std::vector<NUM_T> >* F,
        NUM_T maxC) {
        return emd_hat_impl_integral_types<NUM_T,FLOW_TYPE>()(POrig, QOrig, P, Q, C, extra_mass_penalty, F, maxC);
    }
    
}; // emd_hat_impl<int>

template<FLOW_TYPE_T FLOW_TYPE>
struct emd_hat_impl<long int,FLOW_TYPE> {

    typedef long int NUM_T;
        
    NUM_T operator()(
        const std::vector<NUM_T>& POrig, const std::vector<NUM_T>& QOrig,
        const std::vector<NUM_T>& P, const std::vector<NUM_T>& Q,
        const std::vector< std::vector<NUM_T> >& C,
        NUM_T extra_mass_penalty,
        std::vector< std::vector<NUM_T> >* F) {
        return emd_hat_impl_integral_types<NUM_T,FLOW_TYPE>()(POrig,QOrig,P,Q,C,extra_mass_penalty,F);
    }

    
}; // emd_hat_impl<long int>

template<FLOW_TYPE_T FLOW_TYPE>
struct emd_hat_impl<long long int,FLOW_TYPE> {

    typedef long long int NUM_T;
    
    NUM_T operator()(
        const std::vector<NUM_T>& POrig, const std::vector<NUM_T>& QOrig,
        const std::vector<NUM_T>& P, const std::vector<NUM_T>& Q,
        const std::vector< std::vector<NUM_T> >& C,
        NUM_T extra_mass_penalty,
        std::vector< std::vector<NUM_T> >* F) {
        return emd_hat_impl_integral_types<NUM_T,FLOW_TYPE>()(POrig,QOrig,P,Q,C,extra_mass_penalty,F);
    }
    
}; // emd_hat_impl<long long int>
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// floating types
//----------------------------------------------------------------------------------------
template<FLOW_TYPE_T FLOW_TYPE>
struct emd_hat_impl<double,FLOW_TYPE> {

    typedef double NUM_T;
    typedef long long int CONVERT_TO_T;
        
    NUM_T operator()(
        const std::vector<NUM_T>& POrig, const std::vector<NUM_T>& QOrig,
        const std::vector<NUM_T>& P, const std::vector<NUM_T>& Q,
        const std::vector< std::vector<NUM_T> >& C,
        NUM_T extra_mass_penalty,
        std::vector< std::vector<NUM_T> >* F) {
        
    // TODO: static assert
    assert(sizeof(CONVERT_TO_T)>=8);
    
    // This condition should hold:
    // ( 2^(sizeof(CONVERT_TO_T*8)) >= ( MULT_FACTOR^2 )
    // Note that it can be problematic to check it because
    // of overflow problems. I simply checked it with Linux calc
    // which has arbitrary precision.
    const double MULT_FACTOR= 1000000; 

    // Constructing the input
    const NODE_T N = P.size();
    std::vector<CONVERT_TO_T> iPOrig(N);
    std::vector<CONVERT_TO_T> iQOrig(N);
    std::vector<CONVERT_TO_T> iP(N);
    std::vector<CONVERT_TO_T> iQ(N);
    std::vector< std::vector<CONVERT_TO_T> > iC(N, std::vector<CONVERT_TO_T>(N) );
    std::vector< std::vector<CONVERT_TO_T> > iF(N, std::vector<CONVERT_TO_T>(N) );

    // Converting to CONVERT_TO_T
    double sumP= 0.0;
    double sumQ= 0.0;
    double maxC= C[0][0];
    for (NODE_T i= 0; i<N; ++i) {
        sumP+= POrig[i];
        sumQ+= QOrig[i];
        for (NODE_T j= 0; j<N; ++j) {
            if (C[i][j]>maxC) maxC= C[i][j];
        }
    }
    double minSum= std::min(sumP,sumQ);
    double maxSum= std::max(sumP,sumQ);
    double PQnormFactor= MULT_FACTOR/maxSum;
    double CnormFactor= MULT_FACTOR/maxC;
    for (NODE_T i= 0; i<N; ++i) {
        iPOrig[i]= static_cast<CONVERT_TO_T>(floor(POrig[i]*PQnormFactor+0.5));
        iQOrig[i]= static_cast<CONVERT_TO_T>(floor(QOrig[i]*PQnormFactor+0.5));
        iP[i]= static_cast<CONVERT_TO_T>(floor(P[i]*PQnormFactor+0.5));
        iQ[i]= static_cast<CONVERT_TO_T>(floor(Q[i]*PQnormFactor+0.5));
        for (NODE_T j= 0; j<N; ++j) {
            iC[i][j]= static_cast<CONVERT_TO_T>(floor(C[i][j]*CnormFactor+0.5));
            if (FLOW_TYPE!=NO_FLOW) {
                iF[i][j]= static_cast<CONVERT_TO_T>(floor(((*F)[i][j])*PQnormFactor+0.5));
            }
        }
    }

    // computing distance without extra mass penalty
    double dist= emd_hat_impl<CONVERT_TO_T,FLOW_TYPE>()(iPOrig,iQOrig,iP,iQ,iC,0,&iF);
    // unnormalize
    dist= dist/PQnormFactor;
    dist= dist/CnormFactor;
    
    // adding extra mass penalty
    if (extra_mass_penalty==-1) extra_mass_penalty= maxC;
    dist+= (maxSum-minSum)*extra_mass_penalty;
        
    // converting flow to double
    if (FLOW_TYPE!=NO_FLOW) {
        for (NODE_T i= 0; i<N; ++i) {
            for (NODE_T j= 0; j<N; ++j) {
                (*F)[i][j]= (iF[i][j]/PQnormFactor);
            }
        }
    }
    
    return dist;
    }
    
}; // emd_hat_impl<double>
//----------------------------------------------------------------------------------------
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
