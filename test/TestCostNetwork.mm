//
//  TestFastEMD.m
//  TestFastEMD
//
//  Created by Till Hainbach on 16.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <iostream>
#include "Counter.hpp"
#include "VertexWeights.hpp"
#include "CostNetwork.hpp"
#include "utils/utils.h"

@interface TestCostNetwork : XCTestCase

@end

@implementation TestCostNetwork

std::string const targetString = R"(CostNetwork:
vertex: [to : cost]
0: [27 : 1414] [30 : 0] [31 : 3001]
1: [27 : 1000] [30 : 0] [31 : 3001]
2: [27 : 1414] [30 : 0] [31 : 3001]
3: [27 : 2236] [30 : 0] [31 : 3001]
4: [27 : 1000] [30 : 0] [31 : 3001]
5: [27 : 1000] [30 : 0] [31 : 3001]
6: [27 : 2000] [30 : 0] [31 : 3001]
7: [27 : 1414] [30 : 0] [31 : 3001]
8: [27 : 1000] [28 : 2828] [30 : 0] [31 : 3001]
9: [27 : 1414] [28 : 2236] [30 : 0] [31 : 3001]
10: [27 : 2236] [28 : 2000] [29 : 2828] [30 : 0] [31 : 3001]
11: [28 : 2236] [29 : 2236] [30 : 0] [31 : 3001]
12: [28 : 2828] [29 : 2000] [30 : 0] [31 : 3001]
13: [27 : 2236] [30 : 0] [31 : 3001]
14: [27 : 2000] [28 : 2236] [30 : 0] [31 : 3001]
15: [27 : 2236] [28 : 1414] [30 : 0] [31 : 3001]
16: [27 : 2828] [28 : 1000] [29 : 2236] [30 : 0] [31 : 3001]
17: [28 : 1414] [29 : 1414] [30 : 0] [31 : 3001]
18: [28 : 2236] [29 : 1000] [30 : 0] [31 : 3001]
19: [28 : 2000] [30 : 0] [31 : 3001]
20: [28 : 1000] [30 : 0] [31 : 3001]
21: [28 : 1000] [29 : 1000] [30 : 0] [31 : 3001]
22: [28 : 2236] [30 : 0] [31 : 3001]
23: [28 : 1414] [30 : 0] [31 : 3001]
24: [28 : 1000] [29 : 2236] [30 : 0] [31 : 3001]
25: [28 : 1414] [29 : 1414] [30 : 0] [31 : 3001]
26: [28 : 2236] [29 : 1000] [30 : 0] [31 : 3001]
27: [31 : 3001]
28: [31 : 3001]
29: [31 : 3001]
30: [27 : 3000] [28 : 3000] [29 : 3000] [31 : 3001]
31: [0 : 3001] [1 : 3001] [2 : 3001] [3 : 3001] [4 : 3001] [5 : 3001] [6 : 3001] [7 : 3001] [8 : 3001] [9 : 3001] [10 : 3001] [11 : 3001] [12 : 3001] [13 : 3001] [14 : 3001] [15 : 3001] [16 : 3001] [17 : 3001] [18 : 3001] [19 : 3001] [20 : 3001] [21 : 3001] [22 : 3001] [23 : 3001] [24 : 3001] [25 : 3001] [26 : 3001] [27 : 3001] [28 : 3001] [29 : 3001] [30 : 3001]
)";
static const int N = 6;
std::vector<int> const initWeights = {59, 63, 19, 29, 63, 71, 50, 0, 58, 53, 30, 52, 61, 87, 67, 73, 83, 81, 57, 67, 12, 52, 75, 13, 14, 19, 34, 0, 49, 0, 0, 48, 58, 62, 59, 68, 0, 0, 0, 0, 0, 0, 0, -10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, -10, 0, 0, 0, 0, 0, 0, -1664, 0};

static const int COST_MULT_FACTOR = 1000;
static const int THRESHOLD = 3 * COST_MULT_FACTOR;
std::vector< std::vector<int> > cost_mat(N * N, std::vector<int> (N * N));

int const maxC = FastEMD::utils::calculateCostMatVector(N, N, N, N, cost_mat,
                                              THRESHOLD, COST_MULT_FACTOR);



-(void)testArrayCostFill {
    typedef FastEMD::types::ARRAY INTERFACE;
    static const unsigned int SIZE = 80;

    std::vector<int> startWeights {59, 63, 19, 29, 63, 71, 50, 0, 58, 53, 30, 52, 61, 87, 67, 73, 83, 81, 57, 67, 12, 52, 75, 13, 14, 19, 34, 0, 49, 0, 0, 48, 58, 62, 59, 68, 0, 0, 0, 0, 0, 0, 0, -10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, -10, 0, 0, 0, 0, 0, 0, -1664, 0};
    
    FastEMD::VertexWeights<int, INTERFACE, SIZE> weights(startWeights);
    FastEMD::Counter<int,  INTERFACE, SIZE/2> nonZeroSourceNodes({0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 28, 31, 32, 33, 34, 35}, "sources");
    FastEMD::Counter<int,  INTERFACE, SIZE/2> nonZeroSinkNodes({7, 27, 29}, "sinks");
    FastEMD::Counter<FastEMD::types::NODE_T, INTERFACE, SIZE/2> sinkNodeGetsFlowOnlyFromThreshold(std::vector<int>(weights.size() / 2, 1));
    FastEMD::CostNetwork<int, INTERFACE, SIZE> cost(weights.size());
    cost.fill(weights, nonZeroSourceNodes, nonZeroSinkNodes,
              sinkNodeGetsFlowOnlyFromThreshold, cost_mat, maxC);
    std::stringstream costStringStream;
    costStringStream << cost;
    std::string costString(costStringStream.str());
    
//    FastEMD::utils::showStringInequality(costString, targetString);
    
    XCTAssert(costString == targetString);
    
}

-(void)testVectorCostFill {
    typedef FastEMD::types::VECTOR INTERFACE;
    static const unsigned int SIZE = 80;

    std::vector<int> startWeights {59, 63, 19, 29, 63, 71, 50, 0, 58, 53, 30, 52, 61, 87, 67, 73, 83, 81, 57, 67, 12, 52, 75, 13, 14, 19, 34, 0, 49, 0, 0, 48, 58, 62, 59, 68, 0, 0, 0, 0, 0, 0, 0, -10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, -10, 0, 0, 0, 0, 0, 0, -1664, 0};
    
    FastEMD::VertexWeights<int, INTERFACE, SIZE> weights(startWeights);
    FastEMD::Counter<int,  INTERFACE, SIZE/2> nonZeroSourceNodes({0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 28, 31, 32, 33, 34, 35}, "sources");
    FastEMD::Counter<int,  INTERFACE, SIZE/2> nonZeroSinkNodes({7, 27, 29}, "sinks");
    FastEMD::Counter<FastEMD::types::NODE_T, INTERFACE, SIZE/2> sinkNodeGetsFlowOnlyFromThreshold(std::vector<int>(weights.size() / 2, 1));
    FastEMD::CostNetwork<int, INTERFACE, SIZE> cost(weights.size());
    cost.fill(weights, nonZeroSourceNodes, nonZeroSinkNodes,
              sinkNodeGetsFlowOnlyFromThreshold, cost_mat, maxC);
   
    
    std::stringstream costStringStream;
    costStringStream << cost;
    std::string costString(costStringStream.str());
    
//    FastEMD::utils::showStringInequality(costString, targetString);
    
    XCTAssert(costString == targetString);
    
}

-(void)testOpenCVCostFill {
    typedef FastEMD::types::OPENCV INTERFACE;
    static const unsigned int SIZE = 80;

    std::vector<int> startWeights {59, 63, 19, 29, 63, 71, 50, 0, 58, 53, 30, 52, 61, 87, 67, 73, 83, 81, 57, 67, 12, 52, 75, 13, 14, 19, 34, 0, 49, 0, 0, 48, 58, 62, 59, 68, 0, 0, 0, 0, 0, 0, 0, -10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, -10, 0, 0, 0, 0, 0, 0, -1664, 0};
    
    FastEMD::VertexWeights<int, INTERFACE, SIZE> weights(startWeights);
    FastEMD::Counter<int,  INTERFACE, SIZE/2> nonZeroSourceNodes({0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 28, 31, 32, 33, 34, 35}, "sources");
    FastEMD::Counter<int,  INTERFACE, SIZE/2> nonZeroSinkNodes({7, 27, 29}, "sinks");
   
    FastEMD::Counter<FastEMD::types::NODE_T, INTERFACE, SIZE/2> sinkNodeGetsFlowOnlyFromThreshold(std::vector<int>(weights.size() / 2, 1));
    FastEMD::CostNetwork<int, INTERFACE, SIZE> cost(weights.size());
    cost.fill(weights, nonZeroSourceNodes, nonZeroSinkNodes,
              sinkNodeGetsFlowOnlyFromThreshold, cost_mat, maxC);
    std::stringstream costStringStream;
    costStringStream << cost;
    std::string costString(costStringStream.str());
    
//    FastEMD::utils::showStringInequality(costString, targetString);
    
    XCTAssert(costString == targetString);
    
}


@end
