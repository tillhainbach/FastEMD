//
//  TestVertexWeightClass.m
//  TestFastEMD
//
//  Created by Till Hainbach on 25.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "VertexWeights.hpp"
#include <iostream>

@interface TestVertexWeight : XCTestCase

@end

@implementation TestVertexWeight

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)testFillWeights{
    std::vector<int> const v1 = {157, 158, 160, 163, 165, 168, 170, 171, 175, 179,
                          180, 182, 183, 185, 185, 187, 185, 184, 182, 180,
                          178, 175, 172, 168, 168, 167, 165, 161, 158, 155,
                          154, 152, 156, 159, 161, 164};
    std::vector<int> const v2 = {98, 95, 141, 134, 102, 97, 120, 181, 117, 126, 150,
                          130, 122, 98, 118, 114, 102, 103, 125, 113, 166, 123,
                          97, 155, 154, 148, 131, 163, 109, 165, 154, 104, 98,
                          97, 102, 96};
    
    std::string targetString ("Vertex Weights: vertex: [weight]\n[59][63][19][29][63][71][50][0][58][53][30][52][61][87][67][73][83][81][57][67][12][52][75][13][14][19][34][0][49][0][0][48][58][62][59][68][0][0][0][0][0][0][0][-10][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][-2][0][-10][0][0][0][0][0][0][0][0]");
    
    FastEMD::NODE_T N = static_cast<FastEMD::NODE_T>(v1.size() * 2 + 2);
    FastEMD::VertexWeights<int, FastEMD::VECTOR> weights(N);
    FastEMD::Counter<int,  FastEMD::VECTOR> nonZeroSourceNodes(N);
    FastEMD::Counter<int,  FastEMD::VECTOR> nonZeroSinkNodes(N);
    weights.fillWeights(v1, v2, nonZeroSourceNodes, nonZeroSinkNodes);
    std::stringstream weightsStringStream;
    weightsStringStream << weights;
    std::string weightsString(weightsStringStream.str());
    
//    for (int i = 0; i < weightsString.size(); ++i)
//        if(weightsString[i] != targetString[i])
//            std::cout << weightsString[i] << " != " << targetString[i] << " "
//            << int(weightsString[i]) << " != " << int(targetString[i]) << std::endl;
    
    XCTAssert(weightsString == targetString);
}

-(void)testCalcPreFlowCost {
    
}

@end
