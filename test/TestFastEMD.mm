//
//  TestFastEMD.m
//  TestFastEMD
//
//  Created by Till Hainbach on 16.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <vector>
#include <

@interface TestFastEMD : XCTestCase

@end

@implementation TestFastEMD

- (void)setUp {
    //MARK: Read images
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
    
    std::vector< std::vector<int> > cost_mat;
    
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
    
    std::vector<int>v1 (im1.begin(), im1.begin() + (N*N));
    std::vector<int>v2(im2.begin(), im2.begin() + (N*N));
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

// 

-(void)testFlowFill {
    
}


@end
