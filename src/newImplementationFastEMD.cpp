//#define COMPUTE_RUBNER_VERSION
#define PRINT 0
#define DEBUGMODE 1
#define ORIGINAL 1

#include <chrono>
#include <iostream>
#include "include/EMDHat.hpp"
#include "include/modifiedInterface/modifiedEmdHat.hpp"
#include "utils/tictocChrono.hpp"
#include "utils/readImage.hpp"

#if ORGINAL
#include "include/original/emd_hat.hpp"
#endif
#include "include/original/emd_hat.hpp"
#ifdef COMPUTE_RUBNER_VERSION
#include "emd.h"
#endif

std::vector< std::vector<int> > cost_mat; // for emd_hat version, defined globally only because of Rubner's version
#ifdef COMPUTE_RUBNER_VERSION
float cost_mat_dist(feature_t *F1, feature_t *F2) { return cost_mat[*F1][*F2]; } // for Rubner's version
#endif

//-------------------------------------------------------------------------------

int main( int argc, char* argv[])
{
    //MARK: Check if there are enough arguments.
    if(argc < 2)
    {
        std::cerr << "Provide number of iterations!" << std::endl;
        return 0;
    }

    //MARK: Read images
    const char* im1_name= "cameraman.txt";
    const char* im2_name= "rice.txt";
    unsigned int im1_R, im1_C, im2_R, im2_C;
    std::vector<int> im1, im2;
    FastEMD::utils::readImage(im1_name, im1_R, im1_C, im1);
    FastEMD::utils::readImage(im2_name, im2_R, im2_C, im2);
    if ( (im1_R != im2_R) || (im1_C != im2_C) )
    {
        std::cerr << "Images should be of the same size" << std::endl;
    }
    //-----------------------------------------------
    
#ifndef COMPUTE_RUBNER_VERSION
    // declare local if Rubner_emd ist not calculated.
    std::vector< std::vector<int> > cost_mat;
#endif
    //-----------------------------------------------
    // The ground distance - thresholded Euclidean distance.
    // Since everything is ints, we multiply by COST_MULT_FACTOR.
    const int COST_MULT_FACTOR = 1000;
    const int THRESHOLD = 3 * COST_MULT_FACTOR; //1.412*COST_MULT_FACTOR;
    
#define N 6
    im1_R = N;
    im1_C = N;
    im2_R = N;
    im2_C = N;

    std::vector<int> cost_mat_row(im1_R * im1_C);
    for (unsigned int i = 0; i < im1_R * im1_C; ++i) cost_mat.push_back(cost_mat_row);
    int maxC = FastEMD::utils::calculateCostMatrix(im1_R, im1_C, im2_R, im2_C,
                                      cost_mat, THRESHOLD, COST_MULT_FACTOR);

    //-----------------------------------------------
    std::vector<int>v1 (im1.begin(), im1.begin() + (N*N));
    std::vector<int>v2(im2.begin(), im2.begin() + (N*N));
    long iterations = strtol(argv[1], NULL, 10);

    typedef FastEMD::types::ARRAY INTERFACE;
    static FastEMD::NODE_T const SIZE = 80;
    
    std::cout << "I am doing stuff for " << iterations << " times..." << std::endl;
    std::vector <long> emdValues(iterations);

    tictoc timer;
    timer.tic();
    FastEMD::EMDHat<int, INTERFACE, SIZE> fastEMD(static_cast<NODE_T>(v1.size()));

    int emdDistanceUniversalInterface = 0;
    for (int i = 0; i < iterations; i++)
    {
        emdDistanceUniversalInterface = fastEMD.calcDistance(v1, v2, cost_mat, THRESHOLD, NULL, maxC);
    }
    timer.toc();
    std::cout << "emdDistanceUniversalInterface time in µs: " << timer.totalTime<std::chrono::microseconds>() << std::endl;
    std::cerr << "emdDistanceUniversalInterface = " << emdDistanceUniversalInterface<< std::endl;
    
    timer.clear();
    timer.tic();
    FastEMD::modified::EMDHat<int, INTERFACE, SIZE> modifiedFastEMD(static_cast<NODE_T>(v1.size()));

    int emdDistanceModifiedInterface = 0;
    for (int i = 0; i < iterations; i++)
    {
        emdDistanceModifiedInterface = modifiedFastEMD.calcDistance(v1, v2, cost_mat, THRESHOLD, NULL, maxC);
    }
    timer.toc();
    std::cout << "emdDistanceModifiedInterface time in µs: " << timer.totalTime<std::chrono::microseconds>() << std::endl;
    std::cerr << "emdDistanceModifiedInterface = " << emdDistanceModifiedInterface << std::endl;
    
#if ORIGINAL
    timer.clear();
    timer.tic();
    int emdDistanceOrginal;
    for (int i = 0; i < iterations; i++)
    {
        emdDistanceOrginal = emd_hat_gd_metric<int>()(v1, v2, cost_mat, THRESHOLD);
    }
    timer.toc();
    std::cout << "emdDistanceOriginal time in µs: " << timer.totalTime<std::chrono::microseconds>()  << std::endl;
    std::cout << "emdDistanceOrginal = " << emdDistanceOrginal << std::endl;
#endif
    
    
} // end main
    
    
// Copyright (c) 2009-2012, Ofir Pele
// Copyright (c) 2019-2020, Till Hainbach
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

