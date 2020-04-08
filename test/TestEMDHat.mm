//
//  TestEMDHat.m
//  FastEMD
//
//  Created by Till Hainbach on 31.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <iostream>
#include "EMDHat.hpp"

@interface TestEMDHat : XCTestCase

@end

@implementation TestEMDHat

//MARK: variables for all test cases
static const int N = 6;
static const int COST_MULT_FACTOR = 1000;
static const int THRESHOLD = 3 * COST_MULT_FACTOR;
std::vector< std::vector<int> > _costMat(N * N, std::vector<int> (N * N));

int const maxC = FastEMD::utils::calculateCostMatrix(N, N, N, N, _costMat,
                                              THRESHOLD, COST_MULT_FACTOR);

std::vector<int> const v1 = {157, 158, 160, 163, 165, 168, 170, 171, 175, 179,
                      180, 182, 183, 185, 185, 187, 185, 184, 182, 180,
                      178, 175, 172, 168, 168, 167, 165, 161, 158, 155,
                      154, 152, 156, 159, 161, 164};
std::vector<int> const v2 = {98, 95, 141, 134, 102, 97, 120, 181, 117, 126, 150,
                      130, 122, 98, 118, 114, 102, 103, 125, 113, 166, 123,
                      97, 155, 154, 148, 131, 163, 109, 165, 154, 104, 98,
                      97, 102, 96};

- (void)setUp {
    

}


- (void)testArrayInterface {
    FastEMD::EMDHat<int, FastEMD::types::ARRAY, 80> fastEMD(static_cast<NODE_T>(v1.size()));
    int emdValues = fastEMD.calcDistance(v1, v2, _costMat, THRESHOLD, NULL, maxC);
    XCTAssert(emdValues == 5014000);
    
}

- (void)testVectorInterface {
    FastEMD::EMDHat<int, FastEMD::types::VECTOR> fastEMD(static_cast<NODE_T>(v1.size()));
    int emdValues = fastEMD.calcDistance(v1, v2, _costMat, THRESHOLD, NULL, maxC);
    XCTAssert(emdValues == 5014000);
    
}

- (void)testOpenCVInterface {
    FastEMD::EMDHat<int, FastEMD::types::OPENCV> fastEMD(static_cast<NODE_T>(v1.size()));
    int emdValues = fastEMD.calcDistance(v1, v2, _costMat, THRESHOLD, NULL, maxC);
    XCTAssert(emdValues == 5014000);
    
}

@end
