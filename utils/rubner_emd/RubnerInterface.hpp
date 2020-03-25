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

template<typename NUM_T, typename INTERFACE_T, uint SIZE>
class RubnerInterface
{
public:
    RubnerInterface(typeselector1d<NUM_T, INTERFACE_T, SIZE>& weightsP,
                    typeselector1d<NUM_T, INTERFACE_T, SIZE>& weightsQ,
                    typeselectro2d<NUM_T, INTERFACE_T, SIZE>& costMat)
    : P(weightsP)
    , Q(weightsQ)
    , _costMat(costMat) {};
    
    float calcEMD(){ return emd (&P, &Q, costMatDist, NULL, NULL); }
 
private:
    float costMatDist(feature_t *F1, feature_t *F2) { return _costMat[*F1][*F2]; }
    
    Signature P;
    Signature Q;
    typeselector2d<NUM_T, INTERFACE_T, SIZE>& _costMat;
}

} // Rubner

#endif /* RubnerInterface_h */
