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

namespace Rubner
{

///@brief Wrapper around the Rubner signature_t struct which cleans up after itself. Class has a destructor so you
/// don't have to worry about forgetting to free the memory.
template<class _T>
class Signature
{
    
public:
    Signature(_T const & weights);
    
    ~Signature() noexcept;
    
    signature_t signature;
    
};


//MARK: Implementations:
template<class _T>
Signature<_T>::Signature(_T const & weights)
{
    int n = weights.size();
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
    if (signature.Weights)
    {
        for (unsigned int i = 0; i < n; ++i)
        {
           signature.Weights[i] = weights[i];
        }
    }
}

template<class _T>
Signature<_T>::~Signature() noexcept
{
    delete[] signature.Features;
    delete[] signature.Weights;
}

}
#endif /* RubnerInterface_h */
