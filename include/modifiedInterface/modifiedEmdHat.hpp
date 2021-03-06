#ifndef MODIFIED_EMD_HAT_HPP
#define MODIFIED_EMD_HAT_HPP

#include <vector>
#include "utils/EMD_DEFS.hpp"
#include "utils/flow_utils.hpp"
#include "utils/types.h"
#include "modifiedMinCostFlow.hpp"

/// Fastest version of EMD. Also, in my experience metric ground distance yields better
/// performance. 
///
/// Required params:
/// P,Q - Two histograms of size N
/// C - The NxN matrix of the ground distance between bins of P and Q. Must be a metric. I
///     recommend it to be a thresholded metric (which is also a metric, see ICCV paper).
///
/// Optional params:
/// extra_mass_penalty - The penalty for extra mass - If you want the
///                     resulting distance to be a metric, it should be
///                     at least half the diameter of the space (maximum
///                     possible distance between any two points). If you
///                     want partial matching you can set it to zero (but
///                     then the resulting distance is not guaranteed to be a metric).
///                     Default value is -1 which means 1*max_element_in_C
/// F - *F is filled with flows or nothing happens to F. See template param FLOW_TYPE.
///     Note that EMD and EMD-HAT does not necessarily have a unique flow solution.
///     We assume *F is already allocated and has enough space and is initialized to zeros.
///     See also flow_utils.hpp file for flow-related utils.
///     Default value: NULL and then FLOW_TYPE must be NO_FLOW.
///     
/// Required template params:
/// NUM_T - the type of the histogram bins count (should be one of: int, long int, long long int, double)
///
/// Optional template params:
/// FLOW_TYPE == NO_FLOW - does nothing with the given F.
///           == WITHOUT_TRANSHIPMENT_FLOW - fills F with the flows between bins connected
///              with edges smaller than max(C).
///           == WITHOUT_EXTRA_MASS_FLOW - fills F with the flows between all bins, except the flow
///              to the extra mass bin.
///           Note that if F is the default NULL then FLOW_TYPE must be NO_FLOW.
namespace FastEMD
{
namespace modified
{
using namespace types;
template<typename NUM_T, typename CONVERT_TO_T,
        typename INTERFACE_T, NODE_T SIZE, FLOW_TYPE_T FLOW_TYPE = NO_FLOW>
class EMDHat_Base
{
    static_assert(!isOPENCV<INTERFACE_T>, "Usage with Opencv is not supported!");
public:
    
    template<typename I = INTERFACE_T, std::enable_if_t<isARRAY<I>, int> = 0>
    EMDHat_Base(NODE_T numberOfNodes)
    : mcf(2 * numberOfNodes + 2)
    {};
    
    template<typename I = INTERFACE_T, std::enable_if_t<isVECTOR<I>, int> = 0>
    EMDHat_Base(NODE_T numberOfNodes)
    : mcf(2 * numberOfNodes + 2)
    , vertexWeights(2 * numberOfNodes + 2)
    , nonZeroWeightSourceNodes(numberOfNodes)
    , nonZeroWeightSinkNodes(numberOfNodes)
    , cost(numberOfNodes, std::vector<CONVERT_TO_T>(2 * numberOfNodes))
    , flow(numberOfNodes, std::vector<CONVERT_TO_T>(3 * numberOfNodes))
    , sinkNodesGettingFlowNotOnlyFromThreshold(numberOfNodes)
    {};
    
    
    
    virtual NUM_T calcDistance(const std::vector<NUM_T>& P,
                     const std::vector<NUM_T>& Q,
                     const std::vector< std::vector<NUM_T> >& C,
                     NUM_T extra_mass_penalty = -1,
                     std::vector< std::vector<NUM_T> >* F = NULL,
                     NUM_T maxC = -1) = 0;
    
protected:
    CONVERT_TO_T calcDistanceInt(const std::vector<CONVERT_TO_T>& POrig,
                          const std::vector<CONVERT_TO_T>& QOrig,
                          const std::vector<CONVERT_TO_T>& P,
                          const std::vector<CONVERT_TO_T>& Q,
                          const std::vector< std::vector<CONVERT_TO_T> >& Cc,
                          CONVERT_TO_T extra_mass_penalty,
                          std::vector< std::vector<CONVERT_TO_T> >* F,
                          CONVERT_TO_T maxC);
    
    MinCostFlow<CONVERT_TO_T, INTERFACE_T, SIZE> mcf;
    typeSelector1d<CONVERT_TO_T, INTERFACE_T, SIZE> vertexWeights;
    typeSelector1d<NODE_T, INTERFACE_T, SIZE> nonZeroWeightSourceNodes;
    typeSelector1d<NODE_T, INTERFACE_T, SIZE> nonZeroWeightSinkNodes;
    typeSelector1d<NODE_T, INTERFACE_T, SIZE> sinkNodesGettingFlowNotOnlyFromThreshold;
    typeSelector2d<CONVERT_TO_T, INTERFACE_T, SIZE, 2> cost;
    typeSelector2d<CONVERT_TO_T, INTERFACE_T, SIZE, 3> flow;
    
};

//MARK: Partial Spacialization for EMDHat
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0, FLOW_TYPE_T FLOW_TYPE = NO_FLOW>
class EMDHat : public EMDHat_Base<NUM_T, NUM_T, INTERFACE_T, SIZE, FLOW_TYPE>
{
public:
    EMDHat(NODE_T _N) : EMDHat_Base<NUM_T, NUM_T, INTERFACE_T, SIZE, FLOW_TYPE>(_N) {};
    
    virtual NUM_T calcDistance(const std::vector<NUM_T>& P,
                 const std::vector<NUM_T>& Q,
                 const std::vector< std::vector<NUM_T> >& C,
                 NUM_T extra_mass_penalty = -1,
                 std::vector< std::vector<NUM_T> >* F = NULL,
                 NUM_T maxC = -1) override;
    
};

template<typename INTERFACE_T, NODE_T SIZE, FLOW_TYPE_T FLOW_TYPE>
class EMDHat <double, INTERFACE_T, SIZE, FLOW_TYPE> : public EMDHat_Base<double, long long int, INTERFACE_T, SIZE, FLOW_TYPE>
{
public:
    EMDHat(NODE_T _N)
    : EMDHat_Base<double, long long int, INTERFACE_T, SIZE, FLOW_TYPE>(_N)
    {};
    
    virtual double calcDistance(std::vector<double> const& P,
                     std::vector<double> const& Q,
                     std::vector< std::vector<double> > const& C,
                     double extra_mass_penalty = -1,
                     std::vector< std::vector<double> >* F = NULL,
                     double maxC = -1) override;
    
};

}} //modified // FastEMD
#include "include/modifiedInterface/modifiedEmdHatImpl.hpp"

#endif

// Copyright (c) 2009-2012, Ofir Pele
// Copyright (c) 2020, Till Hainbach
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

