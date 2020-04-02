//
//  preFlow.cpp
//  test2
//
//  Created by Till Hainbach on 17.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#include "preFlow.hpp"
#include "Vertex.hpp"
// quick and dirty preFlow


void preFlow(const std::vector<int>& P, const std::vector<int>& Q)
{
    
    assert(P.size() == Q.size())
    VertexWeights<int, Vector> weights(P.size() + Q.size());
    
    //
    auto pWeight = P.begin();
    auto qWeight = Q.begin();
    auto weight = weights.begin();
    auto end = P.end();
    for(: pWeight != end; ++pWeight, ++qWeight, ++weight)
    {
        weight = pWeight - qWeight;
    }
    
    // the weights is now an array of filled positive or negative numbers
    // in Range 0, P.size()
    
    
    // Check which weights are negative and positive. Store the corresponding
    // indices into separate arrays. Negative values indicate sinks. Positive
    // values indicate sources. Zero values can be skipped.
    Counter<int, Vector> sinksAt(P.size());
    Counter<int, Vector> sourcesAt(P.size());
    
    // if P and Q are not pre-flowed both arrays are concatenated
    unsigned int weightsSize = P.size();
    if (!preflow) weightsSize += Q.size();
    
    unsigned int sourceCount = 0;
    unsigned int sinkCount = 0;
    for(unsigned int weightIndex = 0; weighIndex < weightsSize; ++weightIndex)
    {
        const auto elem = weight[weightIndex];
        if(elem > 0) sourcesAt[sourceIdx++] = weightIndex;
        else if(elem < 0) sinksAt[sinkIdx++] = weightIndex;
        else continue; // Weight is Zero and can therefore be skipped.
    }
    
    /* For each source-sink-combination check if cost.at([sourceIndx, sinkIndex])
    // is less then the maximum (e.g. threshold) cost.
    // sources/sinks: 0 1 3 !once
    // |            0 1 0 0 0
       |            1 0 0 0 1  <- binary mat c[i][j] < maxCost.
                    2 1 1 0 0
               !once  0 0 1    <- sink node receives flow only from
                                  threshold?
                            ^
                            |- source node flows only to threshold?
     */
    for(auto & sourceIndex : sourcesAt)
    {
        for(auto& sinkIndex : sinksAt)
        {
            if (c[i][j] = maxC) continue;
            arrayOfEdges[counter++] = sourceIndex;
            arrayOfEdges[counter++] = sinkIndex;
            
        }
    }
}
