#ifndef EMD_HAT_IMPL_HPP
#define EMD_HAT_IMPL_HPP
#define USE_SET 0
#define USE_VECTOR 0
#define USE_CC_VECTOR 0
#define TIME 0
#define PRINT 0


//=======================================================================================
// Implementation stuff
//=================================================================

#include <set>
#include <array>
#include <limits>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "tictocChrono.hpp"
#include "utils/utils.h"
     
template<typename NUM_T, typename INTERFACE_T,
         int size, FLOW_TYPE_T FLOW_TYPE>
NUM_T FastEMD<NUM_T, INTERFACE_T, size,  FLOW_TYPE>::calcDistance(
                            const std::vector<NUM_T>& P,
                            const std::vector<NUM_T>& Q,
                            const std::vector< std::vector<NUM_T> >& C,
                            NUM_T extra_mass_penalty,
                            std::vector< std::vector<NUM_T> >* F,
                            NUM_T maxC)
{

    if (FLOW_TYPE != NO_FLOW) fillFWithZeros(*F);
        
    assert( (F != NULL) || (FLOW_TYPE == NO_FLOW) );

    return this->calcDistanceInt(P, Q, P, Q, C,
                                 extra_mass_penalty, F, maxC);
    
} // FastEMDArray

template<typename _T>
auto getMaxCost(const _T& costMatrix, const NODE_T N)
{
    auto maxCost = 0;
    for (NODE_T i = 0; i < N; ++i)
    {
        for (NODE_T j = i; j < N; ++j)
        { // cost matrix is symmetric so just check upper right half
            assert(costMatrix[i][j] >= 0);
            if (costMatrix[i][j] > maxCost) maxCost = costMatrix[i][j];
        }
    }
    return maxCost;
}

template<typename NUM_T, typename CONVERT_TO_T, typename INTERFACE_T,
         int size, FLOW_TYPE_T FLOW_TYPE>
CONVERT_TO_T FastEMD_Base<NUM_T, CONVERT_TO_T, INTERFACE_T,
        size, FLOW_TYPE>::calcDistanceInt(
                     const std::vector<CONVERT_TO_T>& POrig,
                     const std::vector<CONVERT_TO_T>& QOrig,
                     const std::vector<CONVERT_TO_T>& P,
                     const std::vector<CONVERT_TO_T>& Q,
                     const std::vector< std::vector<CONVERT_TO_T> >& Cc,
                     CONVERT_TO_T extra_mass_penalty,
                     std::vector< std::vector<CONVERT_TO_T> >* F,
                     CONVERT_TO_T maxC)
{
    // creating the b vector that contains all vertexes
    //-------------------------------------------------------
    assert(Q.size() == P.size());
    //-------------------------------------------------------
    const NODE_T REMOVE_NODE_FLAG = -1; // as I'm using -1 as a special flag !!!
    if(maxC == -1)
    {
        for (NODE_T i = 0; i < N; ++i)
        {
            for (NODE_T j = i; j < N; ++j)
            { // cost matrix is symmetric so just check upper right half
                assert(Cc[i][j] >= 0);
                if ( Cc[i][j] > maxC ) maxC = Cc[i][j];
            }
        }
    }

    std::fill(nonZeroSourceNodes.begin(), nonZeroSourceNodes.end(), 0);
    std::fill(nonZeroSinkNodes.begin(), nonZeroSinkNodes.end(), 0);
 
    // Assuming metric property we can pre-flow 0-cost edges
    auto [sum_P, sum_Q, nonZeroSourceCounter, nonZeroSinkCounter] =
    vertexWeights.template fillWeights<std::vector<CONVERT_TO_T>>(P, Q, N,
                                  nonZeroSourceNodes, nonZeroSinkNodes);
    
#if PRINT && NDEBUG
    std::string msg = "non-zero source nodes: ";
    printArray<NODE_T, size>(nonZeroSourceNodes, msg, nonZeroSourceCounter);
    
    msg = "non-zero sink nodes: ";
    printArray<NODE_T, size>(nonZeroSinkNodes, msg, nonZeroSinkCounter);
#endif
    
    // Ensuring that the supplier - P, has more mass.
    bool needToSwapFlow = false;
    CONVERT_TO_T abs_diff_sum_P_sum_Q = std::abs(sum_P - sum_Q);
    if (sum_Q > sum_P)
    {
        needToSwapFlow = true;
        vertexWeights.swapWeights();
        std::swap(nonZeroSourceCounter, nonZeroSinkCounter);
        std::swap(nonZeroSourceNodes, nonZeroSinkNodes);
        
#if PRINT && NDEBUG
        std::cout << "needToSwapFlow" << std::endl;
        std::string msg = "non-zero source nodes: ";
        printArray<NODE_T, size>(nonZeroSourceNodes, msg, nonZeroSourceCounter);
        
        msg = "non-zero sink nodes: ";
        printArray<NODE_T, size>(nonZeroSinkNodes, msg, nonZeroSinkCounter);
#endif
    }

    // remark*) I put here a deficit of the extra mass, as mass that flows to the threshold node
    // can be absorbed from all sources with cost zero (this is in reverse order from the paper,
    // where incoming edges to the threshold node had the cost of the threshold and outgoing
    // edges had the cost of zero)
    // This also makes sum of b zero.
    vertexWeights[THRESHOLD_NODE] = -abs_diff_sum_P_sum_Q;

    //-------------------------------------------------------
#if PRINT
    std::string msg2 = "start b: ";
    printArray<CONVERT_TO_T, size>(b, msg2, 2 * N + 1);
#endif
    if (extra_mass_penalty == -1) extra_mass_penalty = maxC;

    //=============================================================
    // regular edges between sinks and sources without threshold edges
    // checking which are not isolated
    // remove nodes with supply demand of 0
    // and vertexes that are connected only to the
    // threshold vertex

    
    std::fill(uniqueJs.begin(), uniqueJs.end(), 0);
    cost.fill(vertexWeights, nonZeroSourceNodes,
              nonZeroSinkNodes, uniqueJs, Cc, maxC,
              REMOVE_NODE_FLAG);
    
    CONVERT_TO_T preFlowCost = vertexWeights.calcPreFlowCost(nonZeroSinkNodes, uniqueJs, nonZeroSourceCounter, maxC, cost.rows());


    //====================================================
#if PRINT
    printCost<CONVERT_TO_T, NODE_T>(c, ccSize);
#endif

    //====================================================

#ifndef NDEBUG
#if PRINT
    msg = "b: ";
    printArray<CONVERT_TO_T, size>(b, msg, ccSize);
#endif
    CONVERT_TO_T DEBUG_sum_b = 0;
//    for (NODE_T i = 0; i < ccSize; ++i) DEBUG_sum_b += b[i];
    assert(DEBUG_sum_b == 0);
#endif

    //-------------------------------------------------------

    
    mcf.resize(cost.rows());
    CONVERT_TO_T mcf_dist = mcf(vertexWeights, cost, flows);

//    if (FLOW_TYPE != NO_FLOW) {
//        for (NODE_T new_name_from=0; new_name_from<flows.size(); ++new_name_from) {
//            for (typename std::vector<  edge0<CONVERT_TO_T>  >::const_iterator it= flows[new_name_from].begin(); it!=flows[new_name_from].end(); ++it) {
//                if (new_name_from==nodes_new_names[THRESHOLD_NODE]||it->_to==nodes_new_names[THRESHOLD_NODE]) continue;
//                NODE_T i,j;
//                CONVERT_TO_T flow= it->_flow;
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
    CONVERT_TO_T my_dist =
        preFlowCost + // pre-flowing on cases where it was possible
        mcf_dist + // solution of the transportation problem
        (abs_diff_sum_P_sum_Q * extra_mass_penalty); // emd-hat extra mass penalty

    return my_dist;
//-------------------------------------------------------
    
} // emd_hat_impl_integral_types (main implementation) operator()
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//----------------------------------------------------------------------------------------
// floating types
//----------------------------------------------------------------------------------------

template<typename INTERFACE_T, int size, FLOW_TYPE_T FLOW_TYPE>
double FastEMD<double, INTERFACE_T, size, FLOW_TYPE>::calcDistance(const std::vector<double>& P,
                                                    const std::vector<double>& Q,
                                                    const std::vector< std::vector<double> >& C,
                                                    double extra_mass_penalty,
                                                    std::vector< std::vector<double> >* F,
                                                     double maxC)
{
    typedef long long int CONVERT_TO_T;
     
    // TODO: static assert
    assert(sizeof(CONVERT_TO_T) >= 8);
    
    // This condition should hold:
    // ( 2^(sizeof(CONVERT_TO_T*8)) >= ( MULT_FACTOR^2 )
    // Note that it can be problematic to check it because
    // of overflow problems. I simply checked it with Linux calc
    // which has arbitrary precision.
    const double MULT_FACTOR = 1000000;

    // Constructing the input
    const NODE_T N = static_cast<NODE_T>(P.size());
    std::vector<CONVERT_TO_T> iP(N);
    std::vector<CONVERT_TO_T> iQ(N);
    std::vector< std::vector<CONVERT_TO_T> > iC(N, std::vector<CONVERT_TO_T>(N) );
    std::vector< std::vector<CONVERT_TO_T> > iF(N, std::vector<CONVERT_TO_T>(N) );

    // Converting to CONVERT_TO_T
    double sumP = 0.0;
    double sumQ = 0.0;
    for (NODE_T i= 0; i<N; ++i)
    {
        sumP += P[i];
        sumQ += Q[i];
    }
    
    double minSum = std::min(sumP, sumQ);
    double maxSum = std::max(sumP, sumQ);
    double PQnormFactor = MULT_FACTOR/maxSum;
    double CnormFactor = MULT_FACTOR/maxC;
    CONVERT_TO_T iMaxC = floor(maxC * CnormFactor + 0.5);
    for (NODE_T i = 0; i < N; ++i)
    {
        iP[i]= static_cast<CONVERT_TO_T>(floor(P[i] * PQnormFactor + 0.5));
        iQ[i]= static_cast<CONVERT_TO_T>(floor(Q[i] * PQnormFactor + 0.5));
        for (NODE_T j = 0; j < N; ++j)
        {
            iC[i][j] = static_cast<CONVERT_TO_T>(floor(C[i][j] * CnormFactor + 0.5));
            if (FLOW_TYPE != NO_FLOW)
            {
                iF[i][j] = static_cast<CONVERT_TO_T>(floor(((*F)[i][j]) * PQnormFactor + 0.5));
            }
        }
    }

    // computing distance without extra mass penalty
    double dist = this->calcDistanceInt(iP, iQ, iP, iQ, iC, 0, &iF, iMaxC);
    // unnormalize
    dist = dist/PQnormFactor;
    dist = dist/CnormFactor;
    
    // adding extra mass penalty
    if (extra_mass_penalty == -1) extra_mass_penalty = maxC;
    dist += (maxSum - minSum) * extra_mass_penalty;
        
    // converting flow to double
    if (FLOW_TYPE != NO_FLOW)
    {
        for (NODE_T i = 0; i < N; ++i)
        {
            for (NODE_T j = 0; j < N; ++j)
            {
                (*F)[i][j] = (iF[i][j]/PQnormFactor);
            }
        }
    }
    
    return dist;
} // emd_hat_impl<double>
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
