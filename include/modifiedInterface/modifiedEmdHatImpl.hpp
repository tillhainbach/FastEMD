#ifndef EMD_HAT_IMPL_HPP
#define EMD_HAT_IMPL_HPP
#define USE_SET 0
#define USE_VECTOR 0
#define USE_CC_VECTOR 0
#define TIME 0
#define PRINT 1


//=======================================================================================
// Implementation stuff
//=======================================================================================

#include <set>
#include <array>
#include <limits>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "tictocChrono.hpp"
#include "MinCostFlowVector.hpp"
#include "utils/utils.h"
namespace FastEMD
{
namespace modified
{
template<typename CONVERT_TO_T, FLOW_TYPE_T FLOW_TYPE>
CONVERT_TO_T EMDHat<CONVERT_TO_T, FLOW_TYPE>::calcDistance(const std::vector<CONVERT_TO_T>& Pc,
                                                     const std::vector<CONVERT_TO_T>& Qc,
                                                     const std::vector< std::vector<CONVERT_TO_T> >& C,
                                                     CONVERT_TO_T extra_mass_penalty,
                                                     std::vector< std::vector<CONVERT_TO_T> >* F,
                                                     CONVERT_TO_T maxC)
{

    if (FLOW_TYPE != NO_FLOW) fillFWithZeros(*F);
        
    assert( (F != NULL) || (FLOW_TYPE == NO_FLOW) );

    return FastEMDArray<CONVERT_TO_T, FLOW_TYPE>::calcDistanceInt
    (
        Pc, Qc,Pc,Qc,C,extra_mass_penalty,F, maxC
    );
    
} // FastEMDArray

template<typename NUM_T, typename CONVERT_TO_T, FLOW_TYPE_T FLOW_TYPE>
CONVERT_TO_T EMDHat_Base<NUM_T, CONVERT_TO_T, FLOW_TYPE>::calcDistanceInt(
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

        const NODE_T THRESHOLD_NODE = 2 * N;

        // Assuming metric property we can pre-flow 0-cost edges
        CONVERT_TO_T sum_P = 0;
        CONVERT_TO_T sum_Q = 0;
    
        std::fill(nonZeroSourceNodes.begin(), nonZeroSourceNodes.end(), 0);
        std::fill(nonZeroSinkNodes.begin(), nonZeroSinkNodes.end(), 0);

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
        printArray<CONVERT_TO_T, std::vector<CONVERT_TO_T> >(nonZeroSourceNodes, msg, nonZeroSourceCounter);
        
        msg = "non-zero sink nodes: ";
        printArray<CONVERT_TO_T, std::vector<CONVERT_TO_T> >(nonZeroSinkNodes, msg, nonZeroSinkCounter);
#endif
        
        // Ensuring that the supplier - P, has more mass.
        bool needToSwapFlow = false;
        CONVERT_TO_T abs_diff_sum_P_sum_Q = std::abs(sum_P - sum_Q);
        if (sum_Q > sum_P)
        {
            needToSwapFlow = true;
            std::swap_ranges(b.begin(), b.begin() + N, b.begin() + N);
            std::transform(b.begin(), b.begin() + 2 * N + 1, b.begin(),
                        std::bind(std::multiplies<CONVERT_TO_T>(), std::placeholders::_1, -1));
            std::swap(nonZeroSourceCounter, nonZeroSinkCounter);
            std::swap(nonZeroSourceNodes, nonZeroSinkNodes);
#if PRINT
            std::cout << "needToSwapFlow" << std::endl;
            std::string msg = "non-zero source nodes: ";
            printArray<CONVERT_TO_T, std::vector<CONVERT_TO_T> >(nonZeroSourceNodes, msg, nonZeroSourceCounter);
            
            msg = "non-zero sink nodes: ";
            printArray<CONVERT_TO_T, std::vector<CONVERT_TO_T> >(nonZeroSinkNodes, msg, nonZeroSinkCounter);
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
        printArray<CONVERT_TO_T, std::vector<CONVERT_TO_T> >(b, msg2, 2 * N + 1);
#endif
        if (extra_mass_penalty == -1) extra_mass_penalty = maxC;

        //=============================================================
        // regular edges between sinks and sources without threshold edges
        // checking which are not isolated
        // remove nodes with supply demand of 0
        // and vertexes that are connected only to the
        // threshold vertex

        
        std::fill(uniqueJs.begin(), uniqueJs.end(), 0);
        NODE_T sourcesCounter = 0; // number of sources_that_flow_not_only_to_thresh
        NODE_T sinksCounter = -1; // number of sinks_that_get_flow_not_only_from_thresh
        CONVERT_TO_T pre_flow_cost = 0;
        CONVERT_TO_T cost = 0;
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
                c[sourcesCounter][2 * sinksForNode] = jj;
                c[sourcesCounter][2 * sinksForNode + 1] = cost;
                sinksForNode++;
                once = true;
            } // j
            if(once)
            { // mark last node
                c[sourcesCounter][2 * sinksForNode + 1] = REMOVE_NODE_FLAG;
                c[sourcesCounter][2 * sinksForNode + 2] = REMOVE_NODE_FLAG;// to THRESHOLD_NODE´
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
        printArray<CONVERT_TO_T, std::vector<CONVERT_TO_T> >(uniqueJs, msg, N);
        msg = "bs: ";
        printArray<CONVERT_TO_T, std::vector<CONVERT_TO_T> >(b, msg, 2 * N + 1);
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
        printArray<CONVERT_TO_T, std::vector<CONVERT_TO_T> >(uniqueJs, msg, N);
#endif
        NODE_T ccSize = sourcesCounter + sinksCounter + 3;
        b[ccSize - 2] = b[THRESHOLD_NODE]; //THREHOLD_NODE weight;
        b[ccSize - 1] = 0; //Artificialnode;
        
        
        // add THRESHOLD_NODE
        for (NODE_T i = sourcesCounter; i <= sourcesCounter + sinksCounter; ++i)
        {

            c[ccSize - 2][2 * (i - sourcesCounter)] = i;
            c[ccSize - 2][2 * (i - sourcesCounter) + 1] = maxC;
        }
        // add Artifical_NODE
        for (NODE_T i = 0; i < ccSize - 1; ++i)
        {
            c[ccSize - 1][2 * i] = i;
            c[ccSize - 1][2 * i + 1] = maxC + 1;
        }
        
        // add edges from sources to THRESHOLD_NODE and ARTIFICIAL_NODE
        for(NODE_T i = 0; i < sourcesCounter; ++i)
        {
            for(NODE_T j = 0; j < sinksCounter + 2; ++j)
            {
                if (c[i][2 * j] != REMOVE_NODE_FLAG && c[i][2 * j + 1] != REMOVE_NODE_FLAG) continue;
                c[i][2 * j] = ccSize - 2;
                c[i][2 * j + 1] = 0;// to THRESHOLD_NODE
                c[i][2 * j + 2] = ccSize - 1;
                c[i][2 * j + 3] = maxC + 1;// to ARTIFICIAL_NODE
                break;
            }
        }

        // add edges from sinks to THRESHOLD_NODE and ARTIFICIAL_NODE
        for(NODE_T i = sourcesCounter; i < ccSize - 2; ++i)
        {
                c[i][0] = ccSize - 1;
                c[i][1] = maxC + 1;// to ARTIFICAL_NODE
        }

        // add edge from THRESHOLD_NODE to ARTIFICIAL_NODE
        c[ccSize - 2][2 * sinksCounter + 2] = ccSize - 1;
        c[ccSize - 2][2 * sinksCounter + 3] = maxC + 1;
#if PRINT
        printCost<CONVERT_TO_T, NODE_T, std::vector< std::vector<CONVERT_TO_T> > >(c, ccSize);
#endif
        // update sink names ([sourcesCounter; sourcesCounter + sinksCounter))
        for (NODE_T i = 0; i < sourcesCounter; ++i)
        {
            for (NODE_T j = 0; j < sinksCounter + 1; ++j)
            {
                if (c[i][2 * j] == ccSize - 2) break;
                c[i][2 * j] = uniqueJs[c[i][2 * j]];
            }
        }

        //====================================================
#if PRINT
        printCost<CONVERT_TO_T, NODE_T, std::vector< std::vector<CONVERT_TO_T> > >(c, ccSize);
#endif

        //====================================================

#ifndef NDEBUG
#if PRINT
        msg = "b: ";
        printArray<CONVERT_TO_T, std::vector<CONVERT_TO_T> >(b, msg, ccSize);
#endif
        CONVERT_TO_T DEBUG_sum_b = 0;
        for (NODE_T i = 0; i < ccSize; ++i) DEBUG_sum_b += b[i];
        assert(DEBUG_sum_b == 0);
#endif

        //-------------------------------------------------------

        

        CONVERT_TO_T mcf_dist = mcf(b, c, flows_arr, ccSize);

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
        pre_flow_cost + // pre-flowing on cases where it was possible
        mcf_dist + // solution of the transportation problem
        (abs_diff_sum_P_sum_Q * extra_mass_penalty); // emd-hat extra mass penalty

    return my_dist;
    //-------------------------------------------------------
    
} // emd_hat_impl_integral_types (main implementation) operator()
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//----------------------------------------------------------------------------------------
// floating types
//----------------------------------------------------------------------------------------

template<FLOW_TYPE_T FLOW_TYPE>
double EMDHat<double, FLOW_TYPE>::calcDistance(const std::vector<double>& P,
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
    double dist = FastEMDArray<double, FLOW_TYPE>::calcDistanceInt(iP, iQ, iP, iQ, iC, 0, &iF, iMaxC);
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


}} // modified // FastEMD
#endif

// Copyright (c) 2009-2012, Ofir Pele
// Copyright (c) 2019-2020, Till Hainbach
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
