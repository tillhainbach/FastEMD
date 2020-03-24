//
//  TestCVMatRowIterator.m
//  TestFastEMD
//
//  Created by Till Hainbach on 24.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <opencv2/core.hpp>
#include "CVMatRowIterator.hpp"

@interface TestCVMatRowIterator : XCTestCase

@end

@implementation TestCVMatRowIterator

- (void)testPostfixIncrementOperator {
    cv::Mat1i testMat(4, 4 , -1);
    CVMatRowIterator firstRow(testMat);
    CVMatRowIterator nextRow(testMat, 1);
    XCTAssert(++firstRow == nextRow);
}

-(void)testInequalityOperator {
    cv::Mat1i testMat(4, 4 , -1);
    CVMatRowIterator firstRow(testMat);
    CVMatRowIterator nextRow(testMat, 1);
    XCTAssert(firstRow != nextRow);
}

@end
