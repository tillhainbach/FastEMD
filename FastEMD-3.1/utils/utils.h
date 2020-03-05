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
#include <vector>
/*
 Helper function that prints a std:: array
 */
template<typename NUM_T, std::size_t arraySize>
void printArray(std::array<NUM_T, arraySize>& arr, std::string &msg, size_t end)
{
    if (end == -1) end = arr.size();
    std::cout << msg;
    std::for_each(arr.begin(), arr.begin() + end, [](NUM_T item){std::cout << item << " ";});
    std::cout << std::endl;
}

/*
 Helper function that fills a 2d std::vector with zeros
 */

template<typename NUM_T>
void fillFWithZeros(std::vector< std::vector<NUM_T> >& F)
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
template<typename NUM_T, typename NODE_T>
void printFlow(
#if USE_EDGE
               std::array< std::array< edge0<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE >& x,
#endif
#if USE_ARR
               std::array< std::array< NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE> &xx,
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
            NUM_T cost = xx[i][j + 1];
            NUM_T flow = xx[i][j + 2];
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
template<typename NUM_T, typename NODE_T>
void printCostBackward(
#if USE_EDGE
              std::array< std::array< edge2<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE >& x,
#endif
#if USE_ARR
              std::array< std::array< NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE> &xx,
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
            NUM_T reduced_cost = xx[i][j + 1];
            NUM_T residual_capacity = xx[i][j + 2];
            std::cout << "[" << to << " : " << reduced_cost << " : " << residual_capacity << "] ";
            if (to == num_nodes - 1 || (i == num_nodes - 1 && to == num_nodes - 2)) break;
        }
#endif
        std::cout << std::endl;
    }
}

template<typename NUM_T, typename NODE_T>
void printCost(
#if USE_EDGE
              std::array< std::array< edge<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE >& x,
#endif
#if USE_ARR
              std::array< std::array< NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE> &xx,
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
            NUM_T reduced_cost = xx[i][j + 1];
            std::cout << "[" << to << " : " << reduced_cost << "] ";
            if (to == num_nodes - 1 || (i == num_nodes - 1 && to == num_nodes - 2)) break;
        }
#endif
        std::cout << std::endl;
    }
}

template<typename NUM_T, typename NODE_T>
void printCostForward(
#if USE_EDGE
              std::array< std::array< edge1<NUM_T>, MAX_SIG_SIZE >, MAX_SIG_SIZE >& x,
#endif
#if USE_ARR
              std::array< std::array< NUM_T, MAX_SIG_SIZE>, MAX_SIG_SIZE> &xx,
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
            NUM_T reduced_cost = xx[i][j + 1];
            std::cout << "[" << to << " : " << reduced_cost << "] ";
            if (to == num_nodes - 1 || (i == num_nodes - 1 && to == num_nodes - 2)) break;
        }
#endif
        std::cout << std::endl;
    }
}

template <class NUM_T>
class Vertexes
{
    cv::Mat matrix;
    NODE_T _num_nodes;
    std::vector<std::string> datanames;
    
public:
    Vertexes(NODE_T num_nodes, NODE_T channels, std::vector<std::string> names) :
    _num_nodes (num_nodes),
    matrix(num_nodes, num_nodes, CV_322S(channels)),
    datanames(names) {};
    
    
    friend ostream& operator<<(ostream& os, const Vertexes& vertexes);
    
};

ostream& operator<<(ostream& os, const Vertexes& vertexes)
{
    // print first line decribing the content of the data:
    // eg. "vertex: [to : reduced_cost : residual_capacity]"
    os << "vertex: [";
    for (auto& entry : vertex.datanames)
    {
        os << entry;
        if (&entry != &vertex.datanames.back()) os << " : ";
    }
    os << "]";
    
    /* now print the actual data:
     logic:
     for each row:
        rows: the vertex from which to flow
        for each colum:
            columns: data (e.g to which vertex, cost, flow)
                first channel: vertex to which to flow
                second channel: (reduced) cost or distance;
                third channel: flow or rasidual capacity, etc.
            break if condition is met and start jump to next row.
        
    */
    NODE_T step = vertexes.matrix.channels();
    NODE_T numNodes = vertex._num_nodes;
    //iterate over the rows eg. vertexes/nodes
    for (NODE_T i = 0; i < num_nodes; ++i)
    {
        os << i << ": ";
        // next iterate over the columns eg. data
        for (NODE_T j = 0;  j <= (num_nodes - 1) * 2 * step; j += step)
        {
            os << "[";
            // iterate over the channels eg. data entries
            for (NODE_T k = 0; k < step; ++k)
            {
                os << vertexes.matrix.at(i, j, k);
                if (k != step - 1) os << " : ";
            }
            os << "] ";
            if (to == num_nodes - 1 || (i == num_nodes - 1 && to == num_nodes - 2)) break;
        }
    }
}

#endif /* utils_h */
