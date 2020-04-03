//#define COMPUTE_RUBNER_VERSION


#include <chrono>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "cvFastEMD.hpp"
#include "utils/utils.h"
#include "utils/tictocChrono.hpp"

#ifdef COMPUTE_RUBNER_VERSION
#include "emd.h"
#endif

std::vector< std::vector<int> > cost_mat; // for emd_hat version, defined globally only because of Rubner's version
#ifdef COMPUTE_RUBNER_VERSION
float cost_mat_dist(feature_t *F1, feature_t *F2) { return cost_mat[*F1][*F2]; } // for Rubner's version
#endif

//--------------------------------------------------------------------------------------------
void readImage(const char* im_name, unsigned int& im_R,
               unsigned int& im_C, std::vector<int>& im); // readImage
//--------------------------------------------------------------------------------------------



int main( int argc, char* argv[])
{
    //-----------------------------------------------
    // Read images
    const char* im1_name= "cameraman.txt";
    const char* im2_name= "rice.txt";
    unsigned int im1_R, im1_C, im2_R, im2_C;
    std::vector<int> im1, im2;
    readImage(im1_name, im1_R, im1_C, im1);
    readImage(im2_name, im2_R, im2_C, im2);
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
    int maxC = calculateCostMatVector(im1_R, im1_C, im2_R, im2_C,
                                      cost_mat, THRESHOLD, COST_MULT_FACTOR);
    

    //-----------------------------------------------
    std::vector<int>v1 (im1.begin(), im1.begin() + (N*N));
    std::vector<int>v2(im2.begin(), im2.begin() + (N*N));
    long iterations = strtol(argv[1], NULL, 10);
    std::ifstream is("quadruples.txt");
    std::istream_iterator<double> start(is), end;
    std::vector<int> numbers(start, end);
    std::cout << "I am doing stuff for " << iterations << " times..." << std::endl;
    std::vector <long> emdValues(iterations);
    
    tictoc timer;
    timer.tic();
    FastEMD<int> fastEMD(N * N);
    for (int i = 0; i < iterations; i++)
    {
//        std::cout << "iter: " << i << "\r";
//        changeVectors(v1, v2, numbers, i);
        emdValues[i] = fastEMD.calcDistance(v1, v2, cost_mat,
                                            THRESHOLD, NULL, maxC);
    }
    timer.toc();
    std::cout << "emd_hat_gd_metric time in µs: "
              << timer.totalTime<std::chrono::microseconds>() << std::endl;
    std::cerr << "emd_hat_gd_metric_val == " << emdValues[0] << std::endl;
    std::ofstream output;
    output.open("outputMyVersion.txt");
    for (auto &value : emdValues) output << value << std::endl;
    output.close();

    #ifdef COMPUTE_RUBNER_VERSION
    timer.clear();
    timer.tic();
    int sumBig= 0;
    int sumSmall= 0;
    {for (unsigned int i=0; i<im1.size(); ++i) {
        sumBig+= im1[i];
        sumSmall+= im2[i];
    }}
    if (sumSmall>sumBig) {
        std::swap(sumSmall,sumBig);
    }
    int emd_rubner_val = 0;
//    for (int i = 0; i < iterations; i++)
    for (int i = 7; i < 8; i++)
    {
        changeSignatures(&Psig, &Qsig, numbers, i);
        emd_rubner_val = static_cast<int>((sumSmall*emd(&Psig, &Qsig, cost_mat_dist, NULL, NULL)) +
                                             (sumBig-sumSmall)*max_cost_mat);
    }
    timer.toc();
    std::cout << "emd_rubner time in seconds: " << timer.totalTime<std::chrono::seconds>() << std::endl;
    #endif
    
} // end main
    
//--------------------------------------------------------------------------------------------
// Read images of the format:
// im_rows_num im_columns_num
// im_pixels ...
void readImage(const char* im_name,
               unsigned int& im_R,
               unsigned int& im_C,
               std::vector<int>& im) {
    
    std::fstream fin(im_name);
    if (!fin) goto readImageErrLabel;
    
    fin >> im_R;
    if (!fin) goto readImageErrLabel;
    fin >> im_C;
    if (!fin) goto readImageErrLabel;
    
    int tmp;
    while (fin >> tmp) {
        im.push_back(tmp);
    }
    
    if (im.size()==im_R*im_C) return;
readImageErrLabel:
    std::cerr << "Image " << im_name << " has a problem in its format" << std::endl;
    exit(1);
    
} // readImage
//--------------------------------------------------------------------------------------------

    
// Copyright (c) 2009-2012, Ofir Pele
// Copyright (c) 2019, Till Hainbach
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

