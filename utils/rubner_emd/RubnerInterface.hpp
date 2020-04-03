//
//  RubnerInterface.hpp
//  FastEMD
//
//  Created by Till Hainbach on 25.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef RubnerInterface_h
#define RubnerInterface_h
#include "Signature.hpp"

namespace Rubner {
// should be implemented in calling file
float costMatDist(feature_t *F1, feature_t *F2);

template<class _T>
class RubnerInterface
{
public:
    RubnerInterface(_T const & weightsP,
                    _T const & weightsQ)
    : P(weightsP)
    , Q(weightsQ)
    {
        sumP = std::accumulate(weightsP.begin(), weightsP.end(), 0);
        sumQ = std::accumulate(weightsQ.begin(), weightsQ.end(), 0);
        if (sumP < sumQ)
        {
            std::swap(sumP, sumQ);
        }
    };
    
    int calcEMD(int maxCost)
    {
        float rubnerEMD = emd(&P.signature, &Q.signature, costMatDist, NULL, NULL);
        return (sumP - sumQ) * maxCost + static_cast<int>(sumP * rubnerEMD);
                
    }
 
private:
    Signature<_T> P;
    Signature<_T> Q;
    int sumP, sumQ;
};

} // Rubner

#endif /* RubnerInterface_h */
