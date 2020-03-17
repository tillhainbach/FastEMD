//
//  TestFastEMD.m
//  TestFastEMD
//
//  Created by Till Hainbach on 16.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <vector>
#include "utils/utils.h"

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


/* cost:
 0: [7 : 1414] [30 : 0] [31 : 3001]
 1: [7 : 1000] [30 : 0] [31 : 3001]
 2: [7 : 1414] [30 : 0] [31 : 3001]
 3: [7 : 2236] [30 : 0] [31 : 3001]
 4: [7 : 1000] [30 : 0] [31 : 3001]
 5: [7 : 1000] [30 : 0] [31 : 3001]
 6: [7 : 2000] [30 : 0] [31 : 3001]
 7: [7 : 1414] [30 : 0] [31 : 3001]
 8: [7 : 1000] [27 : 2828] [30 : 0] [31 : 3001]
 9: [7 : 1414] [27 : 2236] [30 : 0] [31 : 3001]
 10: [7 : 2236] [27 : 2000] [29 : 2828] [30 : 0] [31 : 3001]
 11: [27 : 2236] [29 : 2236] [30 : 0] [31 : 3001]
 12: [27 : 2828] [29 : 2000] [30 : 0] [31 : 3001]
 13: [7 : 2236] [30 : 0] [31 : 3001]
 14: [7 : 2000] [27 : 2236] [30 : 0] [31 : 3001]
 15: [7 : 2236] [27 : 1414] [30 : 0] [31 : 3001]
 16: [7 : 2828] [27 : 1000] [29 : 2236] [30 : 0] [31 : 3001]
 17: [27 : 1414] [29 : 1414] [30 : 0] [31 : 3001]
 18: [27 : 2236] [29 : 1000] [30 : 0] [31 : 3001]
 19: [27 : 2000] [30 : 0] [31 : 3001]
 20: [27 : 1000] [30 : 0] [31 : 3001]
 21: [27 : 1000] [29 : 1000] [30 : 0] [31 : 3001]
 22: [27 : 2236] [30 : 0] [31 : 3001]
 23: [27 : 1414] [30 : 0] [31 : 3001]
 24: [27 : 1000] [29 : 2236] [30 : 0] [31 : 3001]
 25: [27 : 1414] [29 : 1414] [30 : 0] [31 : 3001]
 26: [27 : 2236] [29 : 1000] [30 : 0] [31 : 3001]
 27: [31 : 3001]
 28: [31 : 3001]
 29: [31 : 3001]
 30: [27 : 3000] [28 : 3000] [29 : 3000] [30 : 3000] [31 : 3001]
 31: [0 : 3001] [1 : 3001] [2 : 3001] [3 : 3001] [4 : 3001] [5 : 3001] [6 : 3001] [7 : 3001] [8 : 3001] [9 : 3001] [10 : 3001] [11 : 3001] [12 : 3001] [13 : 3001] [14 : 3001] [15 : 3001] [16 : 3001] [17 : 3001] [18 : 3001] [19 : 3001] [20 : 3001] [21 : 3001] [22 : 3001] [23 : 3001] [24 : 3001] [25 : 3001] [26 : 3001] [27 : 3001] [28 : 3001] [29 : 3001] [30 : 3001]
 
 
 */
