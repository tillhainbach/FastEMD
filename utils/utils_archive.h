//
//  utils.h
//  FastEMD
//
//  Created by Till Hainbach on 05.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef utils_h
#define utils_h
#include <opencv2/core.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <utils/EMD_DEFS.hpp>

namespace FastEMD
{
namespace utils
{

#ifdef COMPUTE_RUBNER_VERSION
#include "utils/rubner_emd/emd.h"
void changeSignatures(signature_t *Psig, signature_t *Qsig, std::vector<int> &numbers, int i)
{
    std::vector <int> noise(numbers.begin() + i * 4, numbers.begin() + i * 4 + 4);
    std::array< int, 2 > sign = {-1,1};
    int idx = noise[0] % 2 == 0;
    float m = static_cast<float>(noise[1] * sign[idx]);
    for(int k = 0; k < Psig->n; ++k)
    {
        Psig->Weights[k] = std::min<float>(255, std::max<float>(0, Psig->Weights[k] + m));
    }
    idx = noise[2] % 2 == 0;
    m = static_cast<float>(noise[3] * sign[idx]);
    for(int k = 0; k < Psig->n; ++k)
    {
        Qsig->Weights[k] = std::min<float>(255, std::max<float>(0, Qsig->Weights[k] + m));
    }
}

#endif

void changeVectors(std::vector<int> & v1, std::vector<int> & v2, std::vector<int> &numbers, int i)
{
//    std::random_device rd;  //Will be used to obtain a seed for the random number engine
//    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
//    std::uniform_int_distribution<int> dis(0, 50);
//    std::vector <int> v{25, 40, 34, 36};
// { 27, 50, 33, 4};
//    for (int i = 0; i < 4; ++i)
//    {
//        v[i] = dis(gen);
//        std::cout << v[i] << std::endl;
//    }
    std::vector <int> noise(numbers.begin() + i * 4, numbers.begin() + i * 4 + 4);
    std::array< int, 2 > sign = {-1,1};
    int idx = noise[0] % 2 == 0;
    int m = noise[1] * sign[idx];
//    std::cout << v[1] << " " << sign[idx] << std::endl;
    std::for_each(v1.begin(), v1.end(), [&](int &n) {return n = std::min(255, std::max(0, n + m));});
    idx = noise[2] % 2 == 0;
    m = noise[3] * sign[idx];
    std::for_each(v2.begin(), v2.end(), [&](int &n) {return n = std::min(255, std::max(0, n + m));});
}





/*
 Helper function that prints a std:: array
 */
template<typename CONVERT_TO_T, class T>
void printArray(T& arr, std::string &msg, size_t end)
{
    if (end == -1) end = arr.size();
    std::cout << msg;
    std::for_each(arr.begin(), arr.begin() + end, [](CONVERT_TO_T item){std::cout << item << " ";});
    std::cout << std::endl;
}

/*
 Helper function that fills a 2d std::vector with zeros
 */

template<typename CONVERT_TO_T>
void fillFWithZeros(std::vector< std::vector<CONVERT_TO_T> >& F)
{
    for (NODE_T i = 0; i < F.size(); ++i)
    {
        for (NODE_T j = 0; j < F[i].size(); ++j)
        {
            F[i][j] = 0;
        }
    }
}

//-----------------------------------------------------------------------------
template<typename CONVERT_TO_T, typename NODE_T, int size = 80>
void printFlow(
#if USE_EDGE
               std::array< std::array< edge0<CONVERT_TO_T>, size >, size >& x,
#endif
#if USE_ARR
               std::array< std::array< CONVERT_TO_T, size>, size> &xx,
#endif
               NODE_T num_nodes)
{
    for (NODE_T i = 0; i < num_nodes; ++i)
    {
        std::cout << i << ": ";
#if USE_EDGE
        for (const auto &node : x[i])
        {
            if (node._to == -1 && node._cost == -1) break;
            std::cout << "[" << node._to << " : " << node._cost << " : " << node._flow << "] ";
        }
#endif
#if USE_ARR
        bool lastNode = false;
        for (int j = 0;  j <= (num_nodes - 1) * 2 * 3; j += 3)
        {

            NODE_T to = xx[i][j];
            CONVERT_TO_T cost = xx[i][j + 1];
            CONVERT_TO_T flow = xx[i][j + 2];
            std::cout << "[" << to << " : " << cost << " : " << flow << "] ";
            if ((i < num_nodes - 1 && to == num_nodes - 1) ||
                (i == num_nodes - 1 && to == num_nodes - 2))
            {
                if (lastNode) break;
                lastNode = true;
            }
        }
#endif
        std::cout << std::endl;
    }
}
template<typename CONVERT_TO_T, typename NODE_T, int size = 80>
void printCostBackward(
#if USE_EDGE
              std::array< std::array< edge2<CONVERT_TO_T>, size >, size >& x,
#endif
#if USE_ARR
              std::array< std::array< CONVERT_TO_T, size>, size> &xx,
#endif
              NODE_T num_nodes)
{
    for (NODE_T i = 0; i < num_nodes; ++i)
    {
        std::cout << i << ": ";
#if USE_EDGE
        for (const auto &node : x[i])
        {
            if (node._to == -1 && node._reduced_cost == -1) break;
            std::cout << "[" << node._to << " : " << node._reduced_cost << " : " << node._residual_capacity << "] ";
        }
#endif
#if USE_ARR
        for (int j = 0;  j <= (num_nodes - 1) * 2 * 3; j += 3)
        {

            NODE_T to = xx[i][j];
            CONVERT_TO_T reduced_cost = xx[i][j + 1];
            CONVERT_TO_T residual_capacity = xx[i][j + 2];
            std::cout << "[" << to << " : " << reduced_cost << " : " << residual_capacity << "] ";
            if (to == num_nodes - 1 || (i == num_nodes - 1 && to == num_nodes - 2)) break;
        }
#endif
        std::cout << std::endl;
    }
}

template<typename CONVERT_TO_T, typename NODE_T, class T>
void printCost(
#if USE_EDGE
              std::array< std::array< edge<CONVERT_TO_T>, size >, size >& x,
#endif
#if USE_ARR
              T &xx,
#endif
              NODE_T num_nodes)
{
    for (NODE_T i = 0; i < num_nodes; ++i)
    {
        std::cout << i << ": ";
#if USE_EDGE
        for (const auto &node : x[i])
        {
            if (node._to == -1 && node._reduced_cost == -1) break;
            std::cout << "[" << node._to << " : " << node._cost << "] ";
        }
#endif
#if USE_ARR
        for (int j = 0;  j < 2 * num_nodes; j += 2)
        {

            NODE_T to = xx[i][j];
            CONVERT_TO_T reduced_cost = xx[i][j + 1];
            std::cout << "[" << to << " : " << reduced_cost << "] ";
            if (to == num_nodes - 1 || (i == num_nodes - 1 && to == num_nodes - 2)) break;
        }
#endif
        std::cout << std::endl;
    }
}

template<typename CONVERT_TO_T, typename NODE_T, int size = 80>
void printCostForward(
#if USE_EDGE
              std::array< std::array< edge1<CONVERT_TO_T>, size >, size >& x,
#endif
#if USE_ARR
              std::array< std::array< CONVERT_TO_T, size>, size> &xx,
#endif
              NODE_T num_nodes)
{
    for (NODE_T i = 0; i < num_nodes; ++i)
    {
        std::cout << i << ": ";
#if USE_EDGE
        for (const auto &node : x[i])
        {
            if (node._to == -1 && node._reduced_cost == -1) break;
            std::cout << "[" << node._to << " : " << node._reduced_cost << "] ";
        }
#endif
#if USE_ARR
        for (int j = 0;  j <= (num_nodes - 1) * 2 * 3; j += 3)
        {

            NODE_T to = xx[i][j];
            CONVERT_TO_T reduced_cost = xx[i][j + 1];
            std::cout << "[" << to << " : " << reduced_cost << "] ";
            if (to == num_nodes - 1 || (i == num_nodes - 1 && to == num_nodes - 2)) break;
        }
#endif
        std::cout << std::endl;
    }
}




}
} //utils //FastEMD

#endif /* utils_h */
