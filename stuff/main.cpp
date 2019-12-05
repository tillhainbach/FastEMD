//
//  main.cpp
//  stuff
//
//  Created by Till Hainbach on 22.11.19.
//  Copyright © 2019 Till Hainbach. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <array>
#include <set>
#include <numeric>

typedef int NODE_T;
typedef int NUM_T;

// make struct no egde or something
template<typename NUM_T>
struct edge {
    edge(NODE_T to = 0, NUM_T cost = 0) : _to(to), _cost(cost) {}
    NODE_T _to;
    NUM_T _cost;
    edge& operator=(const edge& e)
    {
        _to = e._to;
        _cost = e._cost;
        return *this;
    };
};

void foo(std::array<std::array<edge<int>, 80>, 80 > &cc,
         int sourcesCounter, int sinksCounter, int maxC)
{
    NODE_T ccSize = sourcesCounter + sinksCounter + 3;
    for (NODE_T i = sourcesCounter; i <= sourcesCounter + sinksCounter; ++i)
    {
        cc[ccSize - 2][i - sourcesCounter] = edge<NUM_T>(i, maxC);
    }
    // add Artifical_NODE
    for (NODE_T i = 0; i < ccSize - 1; ++i)
    {
        cc[ccSize - 1][i] = edge<NUM_T>(i, maxC + 1);
    }
    for(NODE_T i = 0; i < ccSize - 2; ++i)
    {
        for(NODE_T j = 0; j < sinksCounter + 1; ++j)
        {
            if (cc[i][j]._to != -1 && cc[i][j]._cost != -1) continue;
            cc[i][j] = edge<NUM_T>(ccSize - 2, 0);
            cc[i][j + 1] = edge<NUM_T>(ccSize - 1, maxC + 1);
            break;
        }
    }
    cc[ccSize - 2][sinksCounter + 1] = edge<NUM_T>(ccSize - 1, maxC + 1);// to ARTIFICAL_NODE
    for (NODE_T i = 0; i < sourcesCounter; ++i)
    {
        for (NODE_T j = 0; j < sinksCounter; ++j)
        {
            if (cc[i][j]._to == ccSize - 2) break;
            cc[i][j]._to += sourcesCounter;
        }
    }
}

void makeEdges(int N, std::array<int, 80> &b,
               std::vector<std::vector<int>> &Cc,
               int &sourcesCounter, int &sinksCounter,
               std::array<std::array<edge<int>, 80>, 80 > &cc)
{
    int maxC = 3000;
//    NODE_T sourcesCounter = 0; // number of sources_that_flow_not_only_to_thresh
//    NODE_T sinksCounter = 0; // number of sinks_that_get_flow_not_only_from_thresh
    NODE_T lastJ = 0;
    NODE_T THRESHOLD_NODE = 72;
    NUM_T pre_flow_cost = 0;
    for (NODE_T i = 0; i < N; ++i)
    {
        if (b[i] == 0)
        {
            continue;
        }
        bool once = false;
        int sinksForNode = 0;
        for (NODE_T j = 0; j < N; ++j)
        {
            if (b[j + N] == 0)
            {
                continue;
            }
            if (Cc[i][j] == maxC)
            {
                continue;
            }
            if (j != lastJ)
            {
                if(lastJ == 0) pre_flow_cost -= (b[N] * maxC);
                for (int k = lastJ + 1; k < j; ++k)
                { // sink
                    pre_flow_cost -= (b[k + N] * maxC);
                }
                lastJ = j;
                sinksCounter++;
            }
            cc[sourcesCounter][sinksForNode] = edge<NUM_T>(sinksCounter, Cc[i][j]);
            sinksForNode++;
            once = true;
        } // j
        if(once)
        {
            sourcesCounter++;
        }
        else
        {
            b[THRESHOLD_NODE] += b[i];
            b[i] = 0;
        }
    } // i
    for (int k = lastJ + 1; k < N; ++k)
    { // sink
        pre_flow_cost -= (b[k + N] * maxC);
    }
    // shrink b array
    int shrinkCounter = 0;
    for (int i = 0; i < 2 * N + 2; ++i)
    {
        if (b[i] != 0)
        {
            b[shrinkCounter] = b[i];
            shrinkCounter++;
        }
    }
}
void clear(std::array< std::array<edge<int>, 80>, 80> &cc)
{
    for (int i = 0; i < 80; ++i)
    {
        for(int j = 0; j < 80; ++j)
        {
            cc[i][j] = edge<int>(3,3);
        }
    }
}

int main(int argc, const char * argv[]) {

        
//        std::cout << "done!" << std::endl;
    
    std::array<edge<int>, 2> b{edge<int>(1,1), edge<int>(2,2)};
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::cout << b[0]._cost << std::endl;
    std::swap(b[0], b[1]);
    std::cout << b[0]._cost << std::endl;
    
//    auto myLambda = [](int n, edge<int> node) {return n + node._to * node._cost;};
//    int s = std::accumulate(b.begin(), b.end(), 0, myLambda);
//    std::cout << s << std::endl;
    
//    int N = 36;
//    std::array<int, 80> b{};
//    b[5] = 71;
//    b[6] = 50;
//    b[8] = 58;
//    std::vector<std::vector<int>> Cc(36, std::vector<int>(36, 2000));
//    int sourcesCounter = 0;
//    int sinksCounter = 0;
//
//    for (int i = 0; i < 1e6; ++i)
//    {
//        std::array< std::array<edge<int>, 80>, 80> cc;
//        makeEdges(N, b, Cc, sourcesCounter, sinksCounter, cc);
//        foo(cc, sourcesCounter, sinksCounter, 3000);
////
//        clear(cc);
//    }
    
//    int sum = 0;
//    for (int i = 0; i < 80; ++i)
//    {
//        for(int j = 0; j < 80; ++j)
//        {
//            sum += cc[i][j]._to;
//        }
//    }
//    std::array< std::array<edge<int>, 80>, 80> cc;
//    for (int i = 0; i < 1e6; ++i)
//    {
////        makeEdges(N, b, Cc, sourcesCounter, sinksCounter, cc);
////        foo(cc, sourcesCounter, sinksCounter, 3000);
////
//        clear(cc);
//    }
//
    std::cout << "done!" << std::endl;
}
