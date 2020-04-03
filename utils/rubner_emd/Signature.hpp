//
//  RubnerInterface.h
//  FastEMD
//
//  Created by Till Hainbach on 25.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef Signature_h
#define Signature_h
#include "emd.h"
#include "utils/types.h"

namespace Rubner
{
using namespace FastEMD::types;
///@brief Wrapper around the Rubner signature_t struct which cleans up after itself. Class has a destructor so you
/// don't have to worry about forgetting to free the memory.
template<typename NUM_T, typename INTERFACE_T, unsigned int SIZE = 0>
class Signature
{
    
public:
    Signature(typeselector1d<NUM_T, INTERFACE_T, SIZE>& weights);
    
    ~Signature() noexcept;
    

private:
    signature_t signature;
    
};


//MARK: Implementations:
template<typename NUM_T, typename INTERFACE_T, unsigned int SIZE>
Signature<NUM_T, INTERFACE_T, SIZE>::Signature(
                                    typeselector<NUM_T, INTERFACE_T, SIZE>& weights)
{
    int n = P.size()
    signature.n = n;
    
    // Dynamically allocate memory for signature feature array
    signature.Features = new feature_t[n];
    
    // If the allocation succeded, fill in the feature ids
    if (signature.Features)
    {
        for (unsigned int i = 0; i < n; ++i)
        {
           signature.Features[i] = i;
        }
    }
    
    // Dynamically allocate memory for signature weights array
    signature.Weights = new float[n];
    
    // If the allocation succeded, copy the weights
    if (Psig->Weights && Qsig->Weights)
    {
        for (unsigned int i = 0; i < n; ++i)
        {
           signature.Weights[i] = P[i];
        }
    }
}

template<typename NUM_T, typename INTERFACE_T, unsigned int SIZE>
Signature<NUM_T, INTERFACE_T, SIZE>::~Signature()
{
    delete[] signature.Features;
    delete[] signature.Weights;
}

}
#endif /* RubnerInterface_h */
