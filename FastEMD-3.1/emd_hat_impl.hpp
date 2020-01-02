#ifndef EMD_HAT_IMPL_HPP
#define EMD_HAT_IMPL_HPP
#define USE_SET 0
#define USE_VECTOR 0
#define USE_CC_VECTOR 0
#define TIME 0
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


template<typename NUM_T, std::size_t arraySize>
void printArray(std::array<NUM_T, arraySize>& arr, std::string &msg, size_t end)
{
    if (end == -1) end = arr.size();
    std::cout << msg;
    std::for_each(arr.begin(), arr.begin() + end, [](NUM_T item){std::cout << item << " ";});
    std::cout << std::endl;
}


template<typename NUM_T>
void fillFWithZeros(std::vector< std::vector<NUM_T> >& F)
{
    for (NODE_T i = 0; i < F.size(); ++i)
    {
        for (NODE_T j = 0; j < F[i].size(); ++j)
        {
            F[i][j] = 0;
        }
    }
}
        
// Forward declarations 
template<typename NUM_T, FLOW_TYPE_T FLOW_TYPE> struct emd_hat_impl;

template<typename NUM_T, FLOW_TYPE_T FLOW_TYPE>
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
// TODO: change implementation to a class
// the design might be as follows:
// class member are all arrays / vectors so they are intianited only ones
// an instance of mcf is also a member
// pre-flow P and Q this reduces the amount of cost calculations

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

        // creating the b vector that contains all vertexes
        //-------------------------------------------------------
        NODE_T N = static_cast<NODE_T>(P.size());
        assert(Q.size() == N);
        //-------------------------------------------------------
        const NODE_T REMOVE_NODE_FLAG = -1;         // as I'm using -1 as a special flag !!!
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
        std::array<NUM_T, MAX_SIG_SIZE> b;

        const NODE_T THRESHOLD_NODE = 2 * N;

        // Assuming metric property we can pre-flow 0-cost edges
        NUM_T sum_P = 0;
        NUM_T sum_Q = 0;
        std::array<NODE_T, MAX_SIG_SIZE> nonZeroSourceNodes{};
        std::array<NODE_T, MAX_SIG_SIZE> nonZeroSinkNodes{};
        NODE_T nonZeroSinkCounter = 0;
        NODE_T nonZeroSourceCounter = 0;
        
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
                nonZeroSinkNodes[nonZeroSinkCounter++] = i;
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
                nonZeroSourceNodes[nonZeroSourceCounter++] = i;
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

#if PRINT
        std::string msg = "non-zero source nodes: ";
        printArray<NODE_T, MAX_SIG_SIZE>(nonZeroSourceNodes, msg, nonZeroSourceCounter);
        
        msg = "non-zero sink nodes: ";
        printArray<NODE_T, MAX_SIG_SIZE>(nonZeroSinkNodes, msg, nonZeroSinkCounter);
#endif
        
        // Ensuring that the supplier - P, has more mass.
        bool needToSwapFlow = false;
        NUM_T abs_diff_sum_P_sum_Q = std::abs(sum_P - sum_Q);
        if (sum_Q > sum_P)
        {
            needToSwapFlow = true;
            std::swap_ranges(b.begin(), b.begin() + N, b.begin() + N);
            std::transform(b.begin(), b.begin() + 2 * N + 1, b.begin(),
                        std::bind(std::multiplies<NUM_T>(), std::placeholders::_1, -1));
            std::swap(nonZeroSourceCounter, nonZeroSinkCounter);
            std::swap(nonZeroSourceNodes, nonZeroSinkNodes);
#if PRINT
            std::cout << "needToSwapFlow" << std::endl;
            std::string msg = "non-zero source nodes: ";
            printArray<NODE_T, MAX_SIG_SIZE>(nonZeroSourceNodes, msg, nonZeroSourceCounter);
            
            msg = "non-zero sink nodes: ";
            printArray<NODE_T, MAX_SIG_SIZE>(nonZeroSinkNodes, msg, nonZeroSinkCounter);
#endif
        }
    
        // remark*) I put here a deficit of the extra mass, as mass that flows to the threshold node
        // can be absorbed from all sources with cost zero (this is in reverse order from the paper,
        // where incoming edges to the threshold node had the cost of the threshold and outgoing
        // edges had the cost of zero)
        // This also makes sum of b zero.
        b[THRESHOLD_NODE] = -abs_diff_sum_P_sum_Q;

        //-------------------------------------------------------
#if PRINT
        std::string msg2 = "start b: ";
        printArray<NODE_T, MAX_SIG_SIZE>(b, msg2, 2 * N + 1);
#endif
        if (extra_mass_penalty == -1) extra_mass_penalty = maxC;

        //=============================================================
        // regular edges between sinks and sources without threshold edges
        // checking which are not isolated
        // remove nodes with supply demand of 0
        // and vertexes that are connected only to the
        // threshold vertex
#if USE_EDGE
        std::array< std::array< edge0<NUM_T>, MAX_SIG_SIZE  >, MAX_SIG_SIZE > flows;
        std::array< std::array< edge<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE> cc;
#endif
#if USE_ARR
        std::array< std::array< NUM_T, MAX_SIG_SIZE >, MAX_SIG_SIZE> c;
        std::array< std::array< NUM_T, MAX_SIG_SIZE >, MAX_SIG_SIZE> flows_arr;
#endif
        std::array<NODE_T, MAX_SIG_SIZE/2> uniqueJs{};
        NODE_T sourcesCounter = 0; // number of sources_that_flow_not_only_to_thresh
        NODE_T sinksCounter = -1; // number of sinks_that_get_flow_not_only_from_thresh
        NUM_T pre_flow_cost = 0;
        NUM_T cost = 0;
        for(auto i = nonZeroSourceNodes.begin(); i != nonZeroSourceNodes.begin() + nonZeroSourceCounter; ++i)
        {
            NODE_T ii = *i;
            bool once = false;
            int sinksForNode = 0;
            for(auto j = nonZeroSinkNodes.begin(); j != nonZeroSinkNodes.begin() + nonZeroSinkCounter; ++j)
            {
                NODE_T jj = *j;
                cost = needToSwapFlow ? Cc[jj][ii] : Cc[ii][jj];
                if (cost == maxC)
                {
                    continue;
                }
                if (uniqueJs[jj] != jj)
                {
                    uniqueJs[jj] = jj;
                    sinksCounter++;
                }
#if USE_EDGE
                cc[sourcesCounter][sinksForNode] = edge<NUM_T>(jj, cost);
#endif
#if USE_ARR
                c[sourcesCounter][2 * sinksForNode] = jj;
                c[sourcesCounter][2 * sinksForNode + 1] = cost;
#endif
                sinksForNode++;
                once = true;
            } // j
            if(once)
            { // mark last node
#if USE_EDGE
                cc[sourcesCounter][sinksForNode] = edge<NUM_T>(REMOVE_NODE_FLAG, REMOVE_NODE_FLAG);
                cc[sourcesCounter][sinksForNode + 1] = edge<NUM_T>(REMOVE_NODE_FLAG, REMOVE_NODE_FLAG);
#endif
#if USE_ARR
                c[sourcesCounter][2 * sinksForNode + 1] = REMOVE_NODE_FLAG;
                c[sourcesCounter][2 * sinksForNode + 2] = REMOVE_NODE_FLAG;// to THRESHOLD_NODE´
#endif
                b[sourcesCounter] = b[ii];
                sourcesCounter++;
            }
            else
            {
                b[THRESHOLD_NODE] += b[ii];
            }
        } // i
#if PRINT
        msg = "uniqueJs: ";
        printArray<NODE_T, MAX_SIG_SIZE/2>(uniqueJs, msg, N);
        msg = "bs: ";
        printArray<NODE_T, MAX_SIG_SIZE>(b, msg, 2 * N + 1);
#endif
        // calculate pre_flow_cost & add weight to THRESHOLD_NODE
        // reorder b array so that all weights are in range [0, sourcesCounter + sinksCounter + 2];
        int shrinkCounter = sourcesCounter;
        for(auto j = nonZeroSinkNodes.begin(); j != nonZeroSinkNodes.begin() + nonZeroSinkCounter; ++j)
        {
            NODE_T jj = *j;
            if (uniqueJs[jj] == 0 && b[jj + N] != 0)
            {
                pre_flow_cost -= (b[jj + N] * maxC);
                b[THRESHOLD_NODE] += b[jj + N];
            }
            else // (uniqueJs[jj] != 0)
            {
                uniqueJs[jj] = shrinkCounter;
                b[shrinkCounter++] = b[jj + N];
            }
        }
#if PRINT
        std::cout << "sources: " << sourcesCounter << " sinks: " << sinksCounter << std::endl;
        msg = "uniqueJs: ";
        printArray<NODE_T, MAX_SIG_SIZE/2>(uniqueJs, msg, N);
#endif
        NODE_T ccSize = sourcesCounter + sinksCounter + 3;
        b[ccSize - 2] = b[THRESHOLD_NODE]; //THREHOLD_NODE weight;
        b[ccSize - 1] = 0; //Artificialnode;
        
        
        // add THRESHOLD_NODE
        for (NODE_T i = sourcesCounter; i <= sourcesCounter + sinksCounter; ++i)
        {
#if USE_EDGE
            cc[ccSize - 2][i - sourcesCounter] = edge<NUM_T>(i, maxC);
#endif
#if USE_ARR
            c[ccSize - 2][2 * (i - sourcesCounter)] = i;
            c[ccSize - 2][2 * (i - sourcesCounter) + 1] = maxC;
#endif
        }
        // add Artifical_NODE
        for (NODE_T i = 0; i < ccSize - 1; ++i)
        {
#if USE_EDGE
            cc[ccSize - 1][i] = edge<NUM_T>(i, maxC + 1);
#endif
#if USE_ARR
            c[ccSize - 1][2 * i] = i;
            c[ccSize - 1][2 * i + 1] = maxC + 1;
#endif
        }
        
        // add edges from sources to THRESHOLD_NODE and ARTIFICIAL_NODE
        for(NODE_T i = 0; i < sourcesCounter; ++i)
        {
            for(NODE_T j = 0; j < sinksCounter + 2; ++j)
            {
#if USE_EDGE
                if (cc[i][j]._to != REMOVE_NODE_FLAG && cc[i][j]._cost != REMOVE_NODE_FLAG) continue;
                cc[i][j] = edge<NUM_T>(ccSize - 2, 0);
                cc[i][j + 1] = edge<NUM_T>(ccSize - 1, maxC + 1);
#endif
#if USE_ARR
                if (c[i][2 * j] != REMOVE_NODE_FLAG && c[i][2 * j + 1] != REMOVE_NODE_FLAG) continue;
                c[i][2 * j] = ccSize - 2;
                c[i][2 * j + 1] = 0;// to THRESHOLD_NODE
                c[i][2 * j + 2] = ccSize - 1;
                c[i][2 * j + 3] = maxC + 1;// to ARTIFICIAL_NODE
#endif
                break;
            }
        }

        // add edges from sinks to THRESHOLD_NODE and ARTIFICIAL_NODE
        for(NODE_T i = sourcesCounter; i < ccSize - 2; ++i)
        {
#if USE_EDGE
                cc[i][0] = edge<NUM_T>(ccSize - 1, maxC + 1);
#endif
#if USE_ARR
                c[i][0] = ccSize - 1;
                c[i][1] = maxC + 1;// to ARTIFICAL_NODE
#endif
        }

        // add edge from THRESHOLD_NODE to ARTIFICIAL_NODE
#if USE_EDGE
        cc[ccSize - 2][sinksCounter + 1] = edge<NUM_T>(ccSize - 1, maxC + 1);// to ARTIFICAL_NODE
#endif
#if USE_ARR
        c[ccSize - 2][2 * sinksCounter + 2] = ccSize - 1;
        c[ccSize - 2][2 * sinksCounter + 3] = maxC + 1;
#endif
#if PRINT
        printCost<NUM_T, NODE_T>(c, ccSize);
#endif
        // update sink names ([sourcesCounter; sourcesCounter + sinksCounter))
        for (NODE_T i = 0; i < sourcesCounter; ++i)
        {
            for (NODE_T j = 0; j < sinksCounter + 1; ++j)
            {
#if USE_EDGE
                if (cc[i][j]._to == ccSize - 2) break;
                cc[i][j]._to = uniqueJs[cc[i][j]._to];
#endif
#if USE_ARR
                if (c[i][2 * j] == ccSize - 2) break;
                c[i][2 * j] = uniqueJs[c[i][2 * j]];
#endif
            }
        }

        //====================================================
#if PRINT
        printCost<NUM_T, NODE_T>(c, ccSize);
#endif

#if USE_EDGE && USE_ARR
        for (NODE_T from = 0; from < ccSize; ++from)
        {
            for (NODE_T i = 0; i < ccSize; ++i)
            {
                if (cc[from][i]._to == -1) break;
                assert(cc[from][i]._to == c[from][ 2 * i]);
                assert(cc[from][i]._cost == c[from][ 2 * i + 1]);
            }
        }
#endif
        //====================================================

#ifndef NDEBUG
#if PRINT
        msg = "b: ";
        printArray<NODE_T, MAX_SIG_SIZE>(b, msg, ccSize);
#endif
        NUM_T DEBUG_sum_b = 0;
        for (NODE_T i = 0; i < ccSize; ++i) DEBUG_sum_b += b[i];
        assert(DEBUG_sum_b == 0);
#endif

        //-------------------------------------------------------

        min_cost_flow<NUM_T> mcf;

        NUM_T mcf_dist = mcf(b,
#if USE_EDGE
                             cc, flows,
#endif
#if USE_ARR
                             c, flows_arr,
#endif
                             ccSize);

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
