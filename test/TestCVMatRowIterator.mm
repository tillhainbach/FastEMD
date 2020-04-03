//
//  TestCVMatRowIterator.m
//  TestFastEMD
//
//  Created by Till Hainbach on 24.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <opencv2/core.hpp>
#include "utils/CVMatRowIterator.hpp"
#include <iostream>

@interface TestCVMatRowIterator : XCTestCase

@end

@implementation TestCVMatRowIterator
cv::Mat1i testMat(4, 4 , -1);
- (void)setUp{
}

- (void)testPrefixIncrementOperator {
    FastEMD::utils::CVMatRowIterator firstRow(testMat);
    FastEMD::utils::CVMatRowIterator nextRow(testMat, 1);
    XCTAssert(++firstRow == nextRow);
}

- (void)testPostfixIncrementOperator {
    FastEMD::utils::CVMatRowIterator firstRow(testMat);
    FastEMD::utils::CVMatRowIterator nextRow(testMat, 1);
    XCTAssert(firstRow++ != nextRow);
    XCTAssert(firstRow == nextRow);
}

-(void)testInequalityOperator {
    FastEMD::utils::CVMatRowIterator firstRow(testMat);
    FastEMD::utils::CVMatRowIterator nextRow(testMat, 1);
    XCTAssert(firstRow != nextRow);
}

@end
