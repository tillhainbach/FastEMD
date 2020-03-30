//
//  TestDistanceClass.m
//  TestFastEMD
//
//  Created by Till Hainbach on 27.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#import <XCTest/XCTest.h>

@interface TestDistanceClass : XCTestCase

@end

@implementation TestDistanceClass


@end

/*
 from: 8
 nodes to Q: 1 2 3 4 5 6 7 8 0 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [8 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 31 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [8 : 0]
 nodes to Q: 1 13 3 4 5 28 7 8 31 9 10 11 12 27 30 15 16 17 18 19 20 21 22 23 24 25 26 2 6 29 0 14
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [27 : 1000] [2 : INF] [3 : INF] [4 : INF] [28 : 2828] [6 : INF] [7 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [1 : INF] [31 : 3001] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [13 : INF] [5 : INF] [29 : INF] [14 : INF] [8 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [8 : 30]
 l = 30
 delta = 87
 k == 8, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 8 8 0 8 8
 path: 30 8 from == k : 1
 e: 59 63 19 29 50 58 53 61 0 67 73 83 81 57 67 12 52 75 13 19 34 49 48 58 62 59 68 -10 -2 -10 -1347 0

 --------------------------------------------------
 from: 11
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 0 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [11 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 11 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 31 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [11 : 0]
 nodes to Q: 1 30 3 4 5 13 7 8 9 10 11 31 12 28 29 15 16 17 18 19 20 21 22 23 24 25 26 27 2 6 0 14
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 2236] [2 : INF] [3 : INF] [4 : INF] [29 : 2236] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [12 : INF] [5 : INF] [31 : 3001] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [13 : INF] [14 : INF] [1 : INF] [11 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [11 : 30]
 l = 30
 delta = 83
 k == 11, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 8 11 11 11 11
 path: 30 11 from == k : 1
 e: 59 63 19 29 50 58 53 61 0 67 73 0 81 57 67 12 52 75 13 19 34 49 48 58 62 59 68 -10 -2 -10 -1264 0

 --------------------------------------------------
 from: 12
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 0 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [12 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 12 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 31 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [12 : 0]
 nodes to Q: 1 30 3 4 5 13 7 8 9 10 11 12 31 28 29 15 16 17 18 19 20 21 22 23 24 25 26 27 6 2 0 14
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [29 : 2000] [2 : INF] [3 : INF] [4 : INF] [28 : 2828] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [31 : 3001] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [13 : INF] [14 : INF] [1 : INF] [12 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [12 : 30]
 l = 30
 delta = 81
 k == 12, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 8 12 12 12 12
 path: 30 12 from == k : 1
 e: 59 63 19 29 50 58 53 61 0 67 73 0 0 57 67 12 52 75 13 19 34 49 48 58 62 59 68 -10 -2 -10 -1183 0

 --------------------------------------------------
 from: 17
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 0 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [17 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 17 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 31 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [17 : 0]
 nodes to Q: 1 30 3 4 5 13 7 8 9 10 11 12 28 29 15 16 17 31 18 19 20 21 22 23 24 25 26 27 2 6 0 14
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 1414] [2 : INF] [3 : INF] [4 : INF] [29 : 1414] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [31 : 3001] [14 : INF] [15 : INF] [16 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [12 : INF] [13 : INF] [1 : INF] [17 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [17 : 30]
 l = 30
 delta = 75
 k == 17, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 8 17 17 17 17
 path: 30 17 from == k : 1
 e: 59 63 19 29 50 58 53 61 0 67 73 0 0 57 67 12 52 0 13 19 34 49 48 58 62 59 68 -10 -2 -10 -1108 0

 --------------------------------------------------
 from: 10
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 0 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [10 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 10 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 31 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [10 : 0]
 nodes to Q: 1 13 3 4 5 28 7 8 9 10 31 11 12 27 29 15 16 17 18 19 20 21 22 23 24 25 26 6 2 14 0 30
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 2000] [2 : INF] [3 : INF] [4 : INF] [27 : 2236] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [11 : INF] [12 : INF] [1 : INF] [29 : 2828] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [13 : INF] [5 : INF] [14 : INF] [31 : 3001] [10 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [10 : 30]
 l = 30
 delta = 73
 k == 10, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 10 10 10 10 10
 path: 30 10 from == k : 1
 e: 59 63 19 29 50 58 53 61 0 67 0 0 0 57 67 12 52 0 13 19 34 49 48 58 62 59 68 -10 -2 -10 -1035 0

 --------------------------------------------------
 from: 26
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 0 27 28 29 30 31
 distance: vertex: [to : distance]
 [26 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 26 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 31 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [26 : 0]
 nodes to Q: 1 30 3 4 5 13 7 8 9 10 11 12 28 29 15 16 17 18 19 20 21 22 23 24 25 26 31 27 6 2 0 14
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [29 : 1000] [2 : INF] [3 : INF] [4 : INF] [28 : 2236] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [31 : 3001] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [27 : INF] [12 : INF] [13 : INF] [1 : INF] [26 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [26 : 30]
 l = 30
 delta = 68
 k == 26, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 10 26 26 26 26
 path: 30 26 from == k : 1
 e: 59 63 19 29 50 58 53 61 0 67 0 0 0 57 67 12 52 0 13 19 34 49 48 58 62 59 0 -10 -2 -10 -967 0

 --------------------------------------------------
 from: 9
 nodes to Q: 1 2 3 4 5 6 7 8 9 0 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [9 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 9 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 31 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [9 : 0]
 nodes to Q: 1 13 3 4 5 28 7 8 9 31 10 11 12 27 30 15 16 17 18 19 20 21 22 23 24 25 26 2 6 29 0 14
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [27 : 1414] [2 : INF] [3 : INF] [4 : INF] [28 : 2236] [6 : INF] [7 : INF] [8 : INF] [10 : INF] [11 : INF] [12 : INF] [1 : INF] [31 : 3001] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [13 : INF] [5 : INF] [29 : INF] [14 : INF] [9 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [9 : 30]
 l = 30
 delta = 67
 k == 9, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 9 9 26 9 9
 path: 30 9 from == k : 1
 e: 59 63 19 29 50 58 53 61 0 0 0 0 0 57 67 12 52 0 13 19 34 49 48 58 62 59 0 -10 -2 -10 -900 0

 --------------------------------------------------
 from: 14
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 0 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [14 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 14 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 31 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [14 : 0]
 nodes to Q: 1 13 3 4 5 28 7 8 9 10 11 12 27 30 31 15 16 17 18 19 20 21 22 23 24 25 26 2 6 29 0 14
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [27 : 2000] [2 : INF] [3 : INF] [4 : INF] [28 : 2236] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [1 : INF] [31 : 3001] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [12 : INF] [5 : INF] [29 : INF] [13 : INF] [14 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [14 : 30]
 l = 30
 delta = 67
 k == 14, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 14 14 26 14 14
 path: 30 14 from == k : 1
 e: 59 63 19 29 50 58 53 61 0 0 0 0 0 57 0 12 52 0 13 19 34 49 48 58 62 59 0 -10 -2 -10 -833 0

 --------------------------------------------------
 from: 1
 nodes to Q: 1 0 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [1 : 0] [0 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 31 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [1 : 0]
 nodes to Q: 1 31 14 3 4 5 13 7 8 9 10 11 12 27 30 15 16 17 18 19 20 21 22 23 24 25 26 2 28 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [27 : 1000] [3 : INF] [4 : INF] [5 : INF] [31 : 3001] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [6 : INF] [2 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [13 : INF] [28 : INF] [29 : INF] [14 : INF] [1 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [1 : 30]
 l = 30
 delta = 63
 k == 1, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 14 26 1 1
 path: 30 1 from == k : 1
 e: 59 0 19 29 50 58 53 61 0 0 0 0 0 57 0 12 52 0 13 19 34 49 48 58 62 59 0 -10 -2 -10 -770 0

 --------------------------------------------------
 from: 24
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 0 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [24 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 24 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 31 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [24 : 0]
 nodes to Q: 1 30 3 4 5 13 7 8 9 10 11 12 28 29 15 16 17 18 19 20 21 22 23 24 31 25 26 27 2 6 0 14
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 1000] [2 : INF] [3 : INF] [4 : INF] [29 : 2236] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [31 : 3001] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [25 : INF] [26 : INF] [27 : INF] [12 : INF] [13 : INF] [1 : INF] [24 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [24 : 30]
 l = 30
 delta = 62
 k == 24, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 24 24 24 24
 path: 30 24 from == k : 1
 e: 59 0 19 29 50 58 53 61 0 0 0 0 0 57 0 12 52 0 13 19 34 49 48 58 0 59 0 -10 -2 -10 -708 0

 --------------------------------------------------
 from: 7
 nodes to Q: 1 2 3 4 5 6 7 0 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [7 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 7 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 31 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [7 : 0]
 nodes to Q: 1 14 3 4 5 13 7 31 8 9 10 11 12 27 30 15 16 17 18 19 20 21 22 23 24 25 26 2 28 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [27 : 1414] [2 : INF] [3 : INF] [4 : INF] [31 : 3001] [6 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [5 : INF] [1 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [13 : INF] [28 : INF] [29 : INF] [14 : INF] [7 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [7 : 30]
 l = 30
 delta = 61
 k == 7, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 7 24 24 7 7
 path: 30 7 from == k : 1
 e: 59 0 19 29 50 58 53 0 0 0 0 0 0 57 0 12 52 0 13 19 34 49 48 58 0 59 0 -10 -2 -10 -647 0

 --------------------------------------------------
 from: 0
 nodes to Q: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [0 : 0] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 31 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [0 : 0]
 nodes to Q: 31 1 14 3 4 5 13 7 8 9 10 11 12 27 30 15 16 17 18 19 20 21 22 23 24 25 26 2 28 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [1 : INF] [27 : 1414] [3 : INF] [4 : INF] [5 : INF] [31 : 3001] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [6 : INF] [2 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [13 : INF] [28 : INF] [29 : INF] [14 : INF] [0 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [0 : 30]
 l = 30
 delta = 59
 k == 0, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 24 24 0 0
 path: 30 0 from == k : 1
 e: 0 0 19 29 50 58 53 0 0 0 0 0 0 57 0 12 52 0 13 19 34 49 48 58 0 59 0 -10 -2 -10 -588 0

 --------------------------------------------------
 from: 25
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 0 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [25 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 25 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 31 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [25 : 0]
 nodes to Q: 1 30 3 4 5 13 7 8 9 10 11 12 28 29 15 16 17 18 19 20 21 22 23 24 25 31 26 27 2 6 0 14
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 1414] [2 : INF] [3 : INF] [4 : INF] [29 : 1414] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [31 : 3001] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [26 : INF] [27 : INF] [12 : INF] [13 : INF] [1 : INF] [25 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [25 : 30]
 l = 30
 delta = 59
 k == 25, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 25 25 25 25
 path: 30 25 from == k : 1
 e: 0 0 19 29 50 58 53 0 0 0 0 0 0 57 0 12 52 0 13 19 34 49 48 58 0 0 0 -10 -2 -10 -529 0

 --------------------------------------------------
 from: 5
 nodes to Q: 1 2 3 4 5 0 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [5 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 31 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [5 : 0]
 nodes to Q: 1 14 3 4 5 31 13 7 8 9 10 11 12 27 30 15 16 17 18 19 20 21 22 23 24 25 26 2 28 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [27 : 1000] [2 : INF] [3 : INF] [4 : INF] [31 : 3001] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [6 : INF] [1 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [13 : INF] [28 : INF] [29 : INF] [14 : INF] [5 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [5 : 30]
 l = 30
 delta = 58
 k == 5, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 25 25 5 5
 path: 30 5 from == k : 1
 e: 0 0 19 29 50 0 53 0 0 0 0 0 0 57 0 12 52 0 13 19 34 49 48 58 0 0 0 -10 -2 -10 -471 0

 --------------------------------------------------
 from: 23
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 0 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [23 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 23 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 31 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [23 : 0]
 nodes to Q: 1 14 3 4 5 13 7 8 9 10 11 12 28 30 15 16 17 18 19 20 21 22 23 31 24 25 26 27 2 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 1414] [2 : INF] [3 : INF] [4 : INF] [31 : 3001] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [1 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [12 : INF] [29 : INF] [13 : INF] [23 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [23 : 30]
 l = 30
 delta = 58
 k == 23, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 23 25 23 23
 path: 30 23 from == k : 1
 e: 0 0 19 29 50 0 53 0 0 0 0 0 0 57 0 12 52 0 13 19 34 49 48 0 0 0 0 -10 -2 -10 -413 0

 --------------------------------------------------
 from: 13
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 0 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [13 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 13 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 31 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [13 : 0]
 nodes to Q: 1 14 3 4 5 13 7 8 9 10 11 12 27 31 30 15 16 17 18 19 20 21 22 23 24 25 26 2 28 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [27 : 2236] [2 : INF] [3 : INF] [4 : INF] [31 : 3001] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [1 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [12 : INF] [28 : INF] [29 : INF] [14 : INF] [13 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [13 : 30]
 l = 30
 delta = 57
 k == 13, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 13 23 25 13 13
 path: 30 13 from == k : 1
 e: 0 0 19 29 50 0 53 0 0 0 0 0 0 0 0 12 52 0 13 19 34 49 48 0 0 0 0 -10 -2 -10 -356 0

 --------------------------------------------------
 from: 6
 nodes to Q: 1 2 3 4 5 6 0 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [6 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 6 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 31 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [6 : 0]
 nodes to Q: 1 14 3 4 5 13 31 7 8 9 10 11 12 27 30 15 16 17 18 19 20 21 22 23 24 25 26 2 28 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [27 : 2000] [2 : INF] [3 : INF] [4 : INF] [31 : 3001] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [5 : INF] [1 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [13 : INF] [28 : INF] [29 : INF] [14 : INF] [6 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [6 : 30]
 l = 30
 delta = 53
 k == 6, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 6 23 25 6 6
 path: 30 6 from == k : 1
 e: 0 0 19 29 50 0 0 0 0 0 0 0 0 0 0 12 52 0 13 19 34 49 48 0 0 0 0 -10 -2 -10 -303 0

 --------------------------------------------------
 from: 16
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 0 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [16 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 31 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [16 : 0]
 nodes to Q: 1 13 3 4 5 28 7 8 9 10 11 12 27 29 15 16 31 17 18 19 20 21 22 23 24 25 26 14 2 6 0 30
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 1000] [2 : INF] [3 : INF] [4 : INF] [29 : 2236] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [1 : INF] [27 : 2828] [14 : INF] [15 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [12 : INF] [5 : INF] [13 : INF] [31 : 3001] [16 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [16 : 30]
 l = 30
 delta = 52
 k == 16, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 16 16 16 16 16
 path: 30 16 from == k : 1
 e: 0 0 19 29 50 0 0 0 0 0 0 0 0 0 0 12 0 0 13 19 34 49 48 0 0 0 0 -10 -2 -10 -251 0

 --------------------------------------------------
 from: 4
 nodes to Q: 1 2 3 4 0 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [4 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 31 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [4 : 0]
 nodes to Q: 1 14 3 4 31 5 13 7 8 9 10 11 12 27 30 15 16 17 18 19 20 21 22 23 24 25 26 2 28 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [27 : 1000] [2 : INF] [3 : INF] [5 : INF] [31 : 3001] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [6 : INF] [1 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [13 : INF] [28 : INF] [29 : INF] [14 : INF] [4 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [4 : 30]
 l = 30
 delta = 50
 k == 4, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 16 16 4 4
 path: 30 4 from == k : 1
 e: 0 0 19 29 0 0 0 0 0 0 0 0 0 0 0 12 0 0 13 19 34 49 48 0 0 0 0 -10 -2 -10 -201 0

 --------------------------------------------------
 from: 21
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 0 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [21 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 21 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 31 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [21 : 0]
 nodes to Q: 1 30 3 4 5 13 7 8 9 10 11 12 28 29 15 16 17 18 19 20 21 31 22 23 24 25 26 27 2 6 0 14
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 1000] [2 : INF] [3 : INF] [4 : INF] [29 : 1000] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [31 : 3001] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [12 : INF] [13 : INF] [1 : INF] [21 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [21 : 30]
 l = 30
 delta = 49
 k == 21, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 21 21 21 21
 path: 30 21 from == k : 1
 e: 0 0 19 29 0 0 0 0 0 0 0 0 0 0 0 12 0 0 13 19 34 0 48 0 0 0 0 -10 -2 -10 -152 0

 --------------------------------------------------
 from: 22
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 0 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [22 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 22 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 31 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [22 : 0]
 nodes to Q: 1 14 3 4 5 13 7 8 9 10 11 12 28 30 15 16 17 18 19 20 21 22 31 23 24 25 26 27 2 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 2236] [2 : INF] [3 : INF] [4 : INF] [31 : 3001] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [1 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [12 : INF] [29 : INF] [13 : INF] [22 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [22 : 30]
 l = 30
 delta = 48
 k == 22, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 22 21 22 22
 path: 30 22 from == k : 1
 e: 0 0 19 29 0 0 0 0 0 0 0 0 0 0 0 12 0 0 13 19 34 0 0 0 0 0 0 -10 -2 -10 -104 0

 --------------------------------------------------
 from: 20
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 0 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [20 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 31 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [20 : 0]
 nodes to Q: 1 14 3 4 5 13 7 8 9 10 11 12 28 30 15 16 17 18 19 20 31 21 22 23 24 25 26 27 2 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 1000] [2 : INF] [3 : INF] [4 : INF] [31 : 3001] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [1 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [12 : INF] [29 : INF] [13 : INF] [20 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [20 : 30]
 l = 30
 delta = 34
 k == 20, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 20 21 20 20
 path: 30 20 from == k : 1
 e: 0 0 19 29 0 0 0 0 0 0 0 0 0 0 0 12 0 0 13 19 0 0 0 0 0 0 0 -10 -2 -10 -70 0

 --------------------------------------------------
 from: 3
 nodes to Q: 1 2 3 0 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [3 : 0] [0 : INF] [1 : INF] [2 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 31 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [3 : 0]
 nodes to Q: 1 14 3 31 4 5 13 7 8 9 10 11 12 27 30 15 16 17 18 19 20 21 22 23 24 25 26 2 28 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [27 : 2236] [2 : INF] [4 : INF] [5 : INF] [31 : 3001] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [6 : INF] [1 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [13 : INF] [28 : INF] [29 : INF] [14 : INF] [3 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [3 : 30]
 l = 30
 delta = 29
 k == 3, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 20 21 3 3
 path: 30 3 from == k : 1
 e: 0 0 19 0 0 0 0 0 0 0 0 0 0 0 0 12 0 0 13 19 0 0 0 0 0 0 0 -10 -2 -10 -41 0

 --------------------------------------------------
 from: 2
 nodes to Q: 1 2 0 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [2 : 0] [0 : INF] [1 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 31 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [2 : 0]
 nodes to Q: 1 14 31 3 4 5 13 7 8 9 10 11 12 27 30 15 16 17 18 19 20 21 22 23 24 25 26 2 28 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [27 : 1414] [3 : INF] [4 : INF] [5 : INF] [31 : 3001] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [6 : INF] [1 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [13 : INF] [28 : INF] [29 : INF] [14 : INF] [2 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [2 : 30]
 l = 30
 delta = 19
 k == 2, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 20 21 2 2
 path: 30 2 from == k : 1
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 12 0 0 13 19 0 0 0 0 0 0 0 -10 -2 -10 -22 0

 --------------------------------------------------
 from: 19
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 0 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [19 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 19 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 31 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [19 : 0]
 nodes to Q: 1 14 3 4 5 13 7 8 9 10 11 12 28 30 15 16 17 18 19 31 20 21 22 23 24 25 26 27 2 29 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 2000] [2 : INF] [3 : INF] [4 : INF] [31 : 3001] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [1 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [12 : INF] [29 : INF] [13 : INF] [19 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [19 : 30]
 l = 30
 delta = 19
 k == 19, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 19 21 19 19
 path: 30 19 from == k : 1
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 12 0 0 13 0 0 0 0 0 0 0 0 -10 -2 -10 -3 0

 --------------------------------------------------
 from: 18
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 0 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [18 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 18 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 31 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [18 : 0]
 nodes to Q: 1 30 3 4 5 13 7 8 9 10 11 12 28 29 15 16 17 18 31 19 20 21 22 23 24 25 26 27 6 2 0 14
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [29 : 1000] [2 : INF] [3 : INF] [4 : INF] [28 : 2236] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [31 : 3001] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [12 : INF] [13 : INF] [1 : INF] [18 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [18 : 30]
 l = 30
 delta = 13
 k == 18, l == 30
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 18 18 18 18
 path: 30 18 from == k : 1
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 12 0 0 0 0 0 0 0 0 0 0 0 -10 -2 -10 10 0

 --------------------------------------------------
 from: 15
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 distance: vertex: [to : distance]
 [15 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [31 : INF]
 15 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 31 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : INF] [15 : 0]
 nodes to Q: 1 13 3 4 5 28 7 8 9 10 11 12 27 30 15 31 16 17 18 19 20 21 22 23 24 25 26 6 2 29 0 14
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 1414] [2 : INF] [3 : INF] [4 : INF] [27 : 2236] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [1 : INF] [31 : 3001] [14 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [12 : INF] [5 : INF] [29 : INF] [13 : INF] [15 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 13 3 4 5 28 7 8 9 10 11 12 27 14 15 31 16 17 18 19 20 21 22 23 24 25 26 2 0 29 30 6
 distance: vertex: [to : distance]
 [28 : 1414] [0 : INF] [27 : 2236] [2 : INF] [3 : INF] [4 : INF] [31 : 3001] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [1 : INF] [13 : INF] [14 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [12 : INF] [5 : INF] [29 : INF] [30 : 0] [15 : 0]
 nodes to Q:
 0 2 1 4 5 6 3 8 9 10 11 12 13 14 7 31 16 17 18 19 20 21 22 23 24 25 26 27 15 28 30 29
 0 2 1 4 5 6 3 8 9 10 11 12 13 14 7 31 16 17 18 19 20 21 22 23 24 25 26 27 15 28
 distance: vertex: [to : distance]
 [0 : 0] [2 : 0] [1 : 0] [6 : 0] [3 : 0] [4 : 0] [5 : 0] [14 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [27 : 2236] [29 : 3000] [31 : 3001] [30 : 0] [15 : 0]
 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q:
 29 2 0 4 5 6 1 8 9 10 11 12 13 14 3 31 7 17 18 19 20 21 22 23 24 25 26 27 15 28 30 16
 29 2 0 4 5 6 1 8 9 10 11 12 13 14 3 31 16 17 18 19 20 21 22 23 24 25 26 27 7
 distance: vertex: [to : distance]
 [2 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [16 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1414] [31 : 3001] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [27 : 2236] [29 : 3000] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 0 4 5 6 1 8 9 10 11 12 13 14 3 31 7 17 18 19 20 21 22 23 24 25 26 27 15 28 30 16
 distance: vertex: [to : distance]
 [2 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [16 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1414] [31 : 3001] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [27 : 1414] [29 : 3000] [0 : 0] [30 : 0] [15 : 0]
 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 0 8 9 10 11 12 13 14 1 31 3 17 18 19 20 21 22 23 24 25 26 27 7 15 30 16
 distance: vertex: [to : distance]
 [6 : 0] [14 : 0] [1 : 0] [16 : 0] [3 : 0] [4 : 0] [5 : 0] [28 : 1414] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 3000] [31 : 3001] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [27 : 1414] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 0 8 9 10 11 12 13 14 1 31 3 17 18 19 20 21 22 23 24 25 26 27 7 15 30 16
 distance: vertex: [to : distance]
 [6 : 0] [14 : 0] [1 : 0] [16 : 0] [3 : 0] [4 : 0] [5 : 0] [28 : 1414]

------------------
 [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 3000] [31 : 3001] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [27 : 1414] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 6 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 0 31 1 8 18 19 20 21 22 23 24 25 26 17 7 15 30 16
 distance: vertex: [to : distance]
 [14 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [28 : 1414] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 3000] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 0 31 1 8 18 19 20 21 22 23 24 25 26 17 7 15 30 16
 distance: vertex: [to : distance]
 [14 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [28 : 1414] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 3000] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 14 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 21 22 23 24 25 0 17 7 15 30 16
 distance: vertex: [to : distance]
 [26 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [28 : 1414] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 3000] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 21 22 23 24 25 0 17 7 15 30 16
 distance: vertex: [to : distance]
 [26 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [28 : 1414] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 3000] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 26 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 21 22 23 24 0 25 17 7 15 30 16
 distance: vertex: [to : distance]
 [25 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [28 : 1414] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 3000] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 21 22 23 24 0 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [25 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1414] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 25 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 21 22 23 0 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [24 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1414] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 21 22 23 0 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [24 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1414] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 24 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 21 22 0 23 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [23 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1414] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 21 22 0 23 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [23 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 23 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 21 0 22 23 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [22 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 21 0 22 23 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [22 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 22 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 0 21 22 23 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [21 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 0 21 22 23 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [21 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [20 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 21 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 0 20 21 22 23 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [20 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 0 20 21 22 23 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [20 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [27 : 1414] [18 : 0] [19 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 0 19 20 21 22 23 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [19 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [27 : 1414] [18 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 0 19 20 21 22 23 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [19 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [27 : 1414] [18 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 19 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 0 18 19 20 21 22 23 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [18 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [27 : 1414] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 0 18 19 20 21 22 23 24 25 17 15 7 30 16
 distance: vertex: [to : distance]
 [18 : 0] [16 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [17 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [27 : 1414] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 18 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 27 1 9 10 11 12 13 14 26 31 0 3 17 18 19 20 21 22 23 24 25 8 15 7 30 16
 distance: vertex: [to : distance]
 [16 : 0] [7 : 0] [1 : 0] [17 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [27 : 1414] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 27 1 9 10 11 12 13 14 26 31 0 3 17 18 19 20 21 22 23 24 25 8 15 7 30 16
 distance: vertex: [to : distance]
 [16 : 0] [7 : 0] [1 : 0] [17 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 1000] [27 : 1414] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [28 : 1000] [31 : 3001] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 4 5 6 27 0 9 10 11 12 13 14 26 31 16 1 17 18 19 20 21 22 23 24 25 8 7 3 30 15
 distance: vertex: [to : distance]
 [7 : 0] [17 : 0] [1 : 0] [29 : 1000] [3 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [31 : 3001] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 4 5 6 27 0 9 10 11 12 13 14 26 31 16 1 17 18 19 20 21 22 23 24 25 8 7 3 30 15
 distance: vertex: [to : distance]
 [7 : 0] [17 : 0] [1 : 0] [29 : 1000] [3 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [31 : 3001] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 7 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 1 5 6 27 15 4 10 11 12 13 14 26 31 16 0 17 18 19 20 21 22 23 24 25 8 7 3 30 9
 distance: vertex: [to : distance]
 [17 : 0] [3 : 0] [1 : 0] [29 : 1000] [8 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [31 : 3001] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 1 5 6 27 15 4 10 11 12 13 14 26 31 16 0 17 18 19 20 21 22 23 24 25 8 7 3 30 9
 distance: vertex: [to : distance]
 [17 : 0] [3 : 0] [1 : 0] [29 : 1000] [8 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [31 : 3001] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 17 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 1 5 6 27 15 4 10 11 12 13 0 26 31 16 14 17 18 19 20 21 22 23 24 25 8 7 3 30 9
 distance: vertex: [to : distance]
 [13 : 0] [3 : 0] [1 : 0] [29 : 1000] [8 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [31 : 3001] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 1 5 6 27 15 4 10 11 12 13 0 26 31 16 14 17 18 19 20 21 22 23 24 25 8 7 3 30 9
 distance: vertex: [to : distance]
 [13 : 0] [3 : 0] [1 : 0] [29 : 1000] [8 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [31 : 3001] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 13 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 1 5 6 27 15 4 10 11 12 0 13 26 31 16 14 17 18 19 20 21 22 23 24 25 8 7 3 30 9
 distance: vertex: [to : distance]
 [12 : 0] [3 : 0] [1 : 0] [29 : 1000] [8 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [31 : 3001] [9 : 0] [10 : 0] [11 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 1 5 6 27 15 4 10 11 12 0 13 26 31 16 14 17 18 19 20 21 22 23 24 25 8 7 3 30 9
 distance: vertex: [to : distance]
 [12 : 0] [3 : 0] [1 : 0] [29 : 1000] [8 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [31 : 3001] [9 : 0] [10 : 0] [11 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 12 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 1 5 6 27 15 4 10 11 0 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 8 7 3 30 9
 distance: vertex: [to : distance]
 [11 : 0] [3 : 0] [1 : 0] [29 : 1000] [8 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [31 : 3001] [9 : 0] [10 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 1 5 6 27 15 4 10 11 0 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 8 7 3 30 9
 distance: vertex: [to : distance]
 [11 : 0] [3 : 0] [1 : 0] [29 : 1000] [8 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [31 : 3001] [9 : 0] [10 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 11 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 1 5 6 27 15 4 10 0 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 8 7 3 30 9
 distance: vertex: [to : distance]
 [10 : 0] [3 : 0] [1 : 0] [29 : 1000] [8 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [31 : 3001] [9 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 1 5 6 27 15 4 10 0 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 8 7 3 30 9
 distance: vertex: [to : distance]
 [10 : 0] [3 : 0] [1 : 0] [29 : 1000] [8 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [31 : 3001] [9 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 10 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 1 5 6 27 15 4 0 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 8 7 3 30 9
 distance: vertex: [to : distance]
 [9 : 0] [3 : 0] [1 : 0] [29 : 1000] [8 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [31 : 3001] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 1 5 6 27 15 4 0 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 8 7 3 30 9
 distance: vertex: [to : distance]
 [9 : 0] [3 : 0] [1 : 0] [29 : 1000] [8 : 0] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [31 : 3001] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 9 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 0 5 6 27 15 1 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 8 7 3 30 4
 distance: vertex: [to : distance]
 [3 : 0] [8 : 0] [1 : 0] [29 : 1000] [31 : 3001] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 0 5 6 27 15 1 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 8 7 3 30 4
 distance: vertex: [to : distance]
 [3 : 0] [8 : 0] [1 : 0] [29 : 1000] [31 : 3001] [4 : 0] [5 : 0] [28 : 1000] [27 : 1414] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 2 28 8 5 6 27 15 0 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 7 3 1 30 4
 distance: vertex: [to : distance]
 [8 : 0] [29 : 1000] [1 : 0] [28 : 1000] [31 : 3001] [4 : 0] [5 : 0] [27 : 1414] [3 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 2 28 8 5 6 27 15 0 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 7 3 1 30 4
 distance: vertex: [to : distance]
 [8 : 0] [29 : 1000] [1 : 0] [28 : 1000] [31 : 3001] [4 : 0] [5 : 0] [27 : 1414] [3 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 0 28 8 2 6 27 15 7 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 5 3 1 30 4
 distance: vertex: [to : distance]
 [1 : 0] [29 : 1000] [4 : 0] [28 : 1000] [31 : 3001] [27 : 1414] [5 : 0] [8 : 0] [3 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 0 28 8 2 6 27 15 7 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 5 3 1 30 4
 distance: vertex: [to : distance]
 [1 : 0] [29 : 1000] [4 : 0] [28 : 1000] [31 : 3001] [27 : 1000] [5 : 0] [8 : 0] [3 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 6 28 8 2 0 27 15 7 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 5 3 1 30 4
 distance: vertex: [to : distance]
 [5 : 0] [29 : 1000] [4 : 0] [28 : 1000] [31 : 3001] [27 : 1000] [1 : 0] [8 : 0] [3 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 6 28 8 2 0 27 15 7 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 5 3 1 30 4
 distance: vertex: [to : distance]
 [5 : 0] [29 : 1000] [4 : 0] [28 : 1000] [31 : 3001] [27 : 1000] [1 : 0] [8 : 0] [3 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 6 28 8 0 5 27 15 7 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 2 3 1 30 4
 distance: vertex: [to : distance]
 [4 : 0] [29 : 1000] [27 : 1000] [28 : 1000] [31 : 3001] [5 : 0] [1 : 0] [8 : 0] [3 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 6 28 8 0 5 27 15 7 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 2 3 1 30 4
 distance: vertex: [to : distance]
 [4 : 0] [29 : 1000] [27 : 1000] [28 : 1000] [31 : 3001] [5 : 0] [1 : 0] [8 : 0] [3 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 29 6 28 8 4 5 27 15 7 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 2 1 0 30 3
 distance: vertex: [to : distance]
 [29 : 1000] [28 : 1000] [27 : 1000] [31 : 3001] [4 : 0] [5 : 0] [1 : 0] [8 : 0] [3 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 nodes to Q: 29 6 28 8 4 5 27 15 7 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 2 1 0 30 3
 distance: vertex: [to : distance]
 [29 : 1000] [28 : 1000] [27 : 1000] [31 : 3001] [4 : 0] [5 : 0] [1 : 0] [8 : 0] [3 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [17 : 0] [7 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0] [15 : 0]
 29 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 [15 : 29]
 Reduced Costs For Forward Edges Network:
 vertex: [to : reduced cost]
 0: [27 : 414] [30 : 0] [31 : 2001]
 1: [27 : 0] [30 : 0] [31 : 2001]
 2: [27 : 414] [30 : 0] [31 : 2001]
 3: [27 : 1236] [30 : 0] [31 : 2001]
 4: [27 : 0] [30 : 0] [31 : 2001]
 5: [27 : 0] [30 : 0] [31 : 2001]
 6: [27 : 1000] [30 : 0] [31 : 2001]
 7: [27 : 414] [30 : 0] [31 : 2001]
 8: [27 : 0] [28 : 1828] [30 : 0] [31 : 2001]
 9: [27 : 414] [28 : 1236] [30 : 0] [31 : 2001]
 10: [27 : 1236] [28 : 1000] [29 : 1828] [30 : 0] [31 : 2001]
 11: [28 : 1236] [29 : 1236] [30 : 0] [31 : 2001]
 12: [28 : 1828] [29 : 1000] [30 : 0] [31 : 2001]
 13: [27 : 1236] [30 : 0] [31 : 2001]
 14: [27 : 1000] [28 : 1236] [30 : 0] [31 : 2001]
 15: [27 : 1236] [28 : 414] [30 : 0] [31 : 2001]
 16: [27 : 1828] [28 : 0] [29 : 1236] [30 : 0] [31 : 2001]
 17: [28 : 414] [29 : 414] [30 : 0] [31 : 2001]
 18: [28 : 1236] [29 : 0] [30 : 0] [31 : 2001]
 19: [28 : 1000] [30 : 0] [31 : 2001]
 20: [28 : 0] [30 : 0] [31 : 2001]
 21: [28 : 0] [29 : 0] [30 : 0] [31 : 2001]
 22: [28 : 1236] [30 : 0] [31 : 2001]
 23: [28 : 414] [30 : 0] [31 : 2001]
 24: [28 : 0] [29 : 1236] [30 : 0] [31 : 2001]
 25: [28 : 414] [29 : 414] [30 : 0] [31 : 2001]
 26: [28 : 1236] [29 : 0] [30 : 0] [31 : 2001]
 27: [31 : 3001]
 28: [31 : 3001]
 29: [31 : 3001]
 30: [27 : 2000] [28 : 2000] [29 : 2000] [31 : 2001]
 31: [0 : 4001] [1 : 4001] [2 : 4001] [3 : 4001] [4 : 4001] [5 : 4001] [6 : 4001] [7 : 4001] [8 : 4001] [9 : 4001] [10 : 4001] [11 : 4001] [12 : 4001] [13 : 4001] [14 : 4001] [15 : 4001] [16 : 4001] [17 : 4001] [18 : 4001] [19 : 4001] [20 : 4001] [21 : 4001] [22 : 4001] [23 : 4001] [24 : 4001] [25 : 4001] [26 : 4001] [27 : 3001] [28 : 3001] [29 : 3001] [30 : 4001]
 l = 29
 delta = 12
 k == 15, l == 29
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 prev: 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 0 30 30 30 30 30 30 30 30 30 30 30 8 24 26 15 15
 path: 29 26 from == k : 0
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 12 0 0 0 0 0 0 0 0 0 0 -12 -10 -2 2 10 0
 30 from == k : 0
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 12 0 0 0 0 0 0 0 0 0 0 0 -10 -2 2 -2 0
 15 from == k : 1
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -10 -2 2 10 0

 --------------------------------------------------
 from: 30
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0 31
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 0 31
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [31 : INF]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [29 : INF] [30 : 0]
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 14 7 16 17 18 19 20 21 22 23 24 25 26 27 15 28 29 31 30
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 14 7 16 17 18 19 20 21 22 23 24 25 26 27 15 29 28 31 30
 distance: vertex: [to : distance]
 [0 : 0] [2 : 0] [1 : 0] [6 : 0] [3 : 0] [4 : 0] [5 : 0] [14 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 2000] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [28 : 2000] [29 : 2000] [31 : 2001] [30 : 0]
 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 0 4 5 6 1 8 9 10 11 12 13 14 3 7 17 18 19 20 21 22 23 24 25 26 27 15 28 29 31 16
 nodes to Q: 30 2 0 4 5 6 1 8 9 10 11 12 13 14 3 7 17 18 19 20 21 22 23 24 25 26 27 15 29 28 31 16
 distance: vertex: [to : distance]
 [2 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 2000] [31 : 2001] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [28 : 2000] [29 : 2000] [0 : 0] [30 : 0]
 nodes to Q: 30 2 0 4 5 6 1 8 9 10 11 12 13 14 3 7 17 18 19 20 21 22 23 24 25 26 27 15 28 29 31 16
 distance: vertex: [to : distance]
 [2 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [28 : 2000] [29 : 2000] [0 : 0] [30 : 0]
 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 0 8 9 10 11 12 13 14 1 3 17 18 19 20 21 22 23 24 25 26 27 7 28 15 31 16
 distance: vertex: [to : distance]
 [6 : 0] [14 : 0] [1 : 0] [15 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 2000] [31 : 2001] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [28 : 2000] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 0 8 9 10 11 12 13 14 1 3 17 18 19 20 21 22 23 24 25 26 27 7 28 15 31 16
 distance: vertex: [to : distance]
 [6 : 0] [14 : 0] [1 : 0] [15 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 2000] [31 : 2001] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [28 : 2000] [2 : 0] [0 : 0] [30 : 0]
 6 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 0 1 8 18 19 20 21 22 23 24 25 26 27 7 17 15 31 16
 distance: vertex: [to : distance]
 [14 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 2000] [31 : 2001] [28 : 2000] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 0 1 8 18 19 20 21 22 23 24 25 26 27 7 17 15 31 16
 distance: vertex: [to : distance]
 [14 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 2000] [31 : 2001] [28 : 2000] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 14 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 25 26 0 7 17 15 31 16
 distance: vertex: [to : distance]
 [26 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 2000] [31 : 2001] [28 : 2000] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 25 26 0 7 17 15 31 16
 distance: vertex: [to : distance]
 [26 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 2000] [31 : 2001] [28 : 1236] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 26 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 25 0 26 7 17 15 31 16
 distance: vertex: [to : distance]
 [25 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [29 : 2000] [31 : 2001] [28 : 1236] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 25 0 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [25 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 1236] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 25 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 0 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [24 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 1236] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 0 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [24 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 414] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 24 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 0 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [23 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 414] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 0 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [23 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 23 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 0 23 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [22 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 0 23 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [22 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 22 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 0 22 23 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [21 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 0 22 23 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [21 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 21 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 0 21 22 23 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [20 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [17 : 0] [18 : 0] [19 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 0 21 22 23 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [20 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [17 : 0] [18 : 0] [19 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 0 20 21 22 23 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [19 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [17 : 0] [18 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 0 20 21 22 23 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [19 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [17 : 0] [18 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 19 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 0 19 20 21 22 23 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [18 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [17 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 0 19 20 21 22 23 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [18 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [17 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 18 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 0 18 19 20 21 22 23 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [17 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 0 18 19 20 21 22 23 24 25 26 15 17 7 31 16
 distance: vertex: [to : distance]
 [17 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [28 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 17 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 17 18 19 20 21 22 23 24 25 26 15 0 7 31 16
 distance: vertex: [to : distance]
 [28 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 17 18 19 20 21 22 23 24 25 26 15 0 7 31 16
 nodes to Q: 30 2 29 4 5 6 28 15 9 10 11 12 13 14 27 16 1 17 18 19 20 21 22 23 24 25 26 3 0 7 31 8
 distance: vertex: [to : distance]
 [28 : 0] [15 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [16 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [13 : 0] [27 : 414] [31 : 2001] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [26 : 0] [14 : 0] [6 : 0] [2 : 0] [0 : 0] [30 : 0]
 28 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 [30 : 28]
 Reduced Costs For Forward Edges Network:
 vertex: [to : reduced cost]
 0: [27 : 414] [30 : 0] [31 : 2001]
 1: [27 : 0] [30 : 0] [31 : 2001]
 2: [27 : 414] [30 : 0] [31 : 2001]
 3: [27 : 1236] [30 : 0] [31 : 2001]
 4: [27 : 0] [30 : 0] [31 : 2001]
 5: [27 : 0] [30 : 0] [31 : 2001]
 6: [27 : 1000] [30 : 0] [31 : 2001]
 7: [27 : 414] [30 : 0] [31 : 2001]
 8: [27 : 0] [28 : 1828] [30 : 0] [31 : 2001]
 9: [27 : 414] [28 : 1236] [30 : 0] [31 : 2001]
 10: [27 : 1236] [28 : 1000] [29 : 1828] [30 : 0] [31 : 2001]
 11: [28 : 1236] [29 : 1236] [30 : 0] [31 : 2001]
 12: [28 : 1828] [29 : 1000] [30 : 0] [31 : 2001]
 13: [27 : 1236] [30 : 0] [31 : 2001]
 14: [27 : 1000] [28 : 1236] [30 : 0] [31 : 2001]
 15: [27 : 1236] [28 : 414] [30 : 0] [31 : 2001]
 16: [27 : 1828] [28 : 0] [29 : 1236] [30 : 0] [31 : 2001]
 17: [28 : 414] [29 : 414] [30 : 0] [31 : 2001]
 18: [28 : 1236] [29 : 0] [30 : 0] [31 : 2001]
 19: [28 : 1000] [30 : 0] [31 : 2001]
 20: [28 : 0] [30 : 0] [31 : 2001]
 21: [28 : 0] [29 : 0] [30 : 0] [31 : 2001]
 22: [28 : 1236] [30 : 0] [31 : 2001]
 23: [28 : 414] [30 : 0] [31 : 2001]
 24: [28 : 0] [29 : 1236] [30 : 0] [31 : 2001]
 25: [28 : 414] [29 : 414] [30 : 0] [31 : 2001]
 26: [28 : 1236] [29 : 0] [30 : 0] [31 : 2001]
 27: [31 : 3001]
 28: [31 : 3001]
 29: [31 : 3001]
 30: [27 : 2000] [28 : 2000] [29 : 2000] [31 : 2001]
 31: [0 : 4001] [1 : 4001] [2 : 4001] [3 : 4001] [4 : 4001] [5 : 4001] [6 : 4001] [7 : 4001] [8 : 4001] [9 : 4001] [10 : 4001] [11 : 4001] [12 : 4001] [13 : 4001] [14 : 4001] [15 : 4001] [16 : 4001] [17 : 4001] [18 : 4001] [19 : 4001] [20 : 4001] [21 : 4001] [22 : 4001] [23 : 4001] [24 : 4001] [25 : 4001] [26 : 4001] [27 : 3001] [28 : 3001] [29 : 3001] [30 : 4001]
 l = 28
 delta = 10
 k == 30, l == 28
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 prev: 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 0 24 26 15 30
 path: 28 24 from == k : 0
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -10 0 0 -10 8 2 10 0
 30 from == k : 1
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -10 8 2 0 0

 --------------------------------------------------
 from: 28
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 0 29 30 31
 distance: vertex: [to : distance]
 [28 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [29 : INF] [30 : INF] [31 : INF]
 28 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 31 29 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [29 : INF] [30 : INF] [28 : 0]
 nodes to Q: 1 5 3 4 12 6 7 8 9 10 11 25 13 14 15 16 17 18 19 20 21 22 23 24 0 26 27 28 31 29 30 2
 distance: vertex: [to : distance]
 [24 : 0] [0 : INF] [31 : 3001] [2 : INF] [3 : INF] [1 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [4 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [11 : INF] [25 : INF] [26 : INF] [27 : INF] [29 : INF] [30 : INF] [28 : 0]
 24 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 1 5 3 4 12 6 7 8 9 10 11 25 13 14 15 16 17 18 19 20 21 22 23 24 30 26 27 28 31 29 2 0
 distance: vertex: [to : distance]
 [31 : 3001] [0 : INF] [30 : INF] [2 : INF] [3 : INF] [1 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [4 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [11 : INF] [25 : INF] [26 : INF] [27 : INF] [29 : INF] [24 : 0] [28 : 0]
 nodes to Q: 1 5 3 4 12 14 7 8 9 10 11 25 13 29 15 16 17 18 19 20 21 22 23 24 30 26 27 28 31 2 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [29 : 1236] [2 : INF] [3 : INF] [1 : INF] [31 : 2001] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [4 : INF] [12 : INF] [5 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [11 : INF] [25 : INF] [26 : INF] [27 : INF] [13 : INF] [24 : 0] [28 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 1 5 3 4 12 14 7 8 9 10 11 25 13 6 15 16 17 18 19 20 21 22 23 24 30 26 27 28 31 0 29 2
 distance: vertex: [to : distance]
 [29 : 1236] [0 : INF] [31 : 2001] [2 : INF] [3 : INF] [1 : INF] [13 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [4 : INF] [12 : INF] [5 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [11 : INF] [25 : INF] [26 : INF] [27 : INF] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 distance: vertex: [to : distance]
 [0 : 0] [2 : 0] [1 : 0] [6 : 0] [3 : 0] [4 : 0] [5 : 0] [14 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [29 : 1236] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [27 : 2000] [25 : 0] [26 : 0] [13 : 0] [30 : 0] [24 : 0] [28 : 0]
 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 1 4 5 6 3 8 9 10 11 12 13 0 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 distance: vertex: [to : distance]
 [13 : 0] [2 : 0] [1 : 0] [6 : 0] [3 : 0] [4 : 0] [5 : 0] [14 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [29 : 1236] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [27 : 2000] [25 : 0] [26 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 1 4 5 6 3 8 9 10 11 12 13 0 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 distance: vertex: [to : distance]
 [13 : 0] [2 : 0] [1 : 0] [6 : 0] [3 : 0] [4 : 0] [5 : 0] [14 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [29 : 1236] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [27 : 414] [25 : 0] [26 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 13 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 1 4 5 6 3 8 9 10 11 12 13 27 7 16 17 18 19 20 21 22 23 24 30 26 0 25 31 15 29 14
 distance: vertex: [to : distance]
 [26 : 0] [2 : 0] [1 : 0] [6 : 0] [3 : 0] [4 : 0] [5 : 0] [14 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [29 : 1236] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [27 : 414] [25 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 1 4 5 6 3 8 9 10 11 12 13 27 7 16 17 18 19 20 21 22 23 24 30 26 0 25 31 15 29 14
 distance: vertex: [to : distance]
 [26 : 0] [2 : 0] [1 : 0] [6 : 0] [3 : 0] [4 : 0] [5 : 0] [14 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [29 : 1236] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [27 : 414] [25 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 26 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 1 4 5 6 3 8 9 10 11 12 13 27 7 16 17 18 19 20 21 22 23 24 30 0 26 25 31 15 29 14
 distance: vertex: [to : distance]
 [25 : 0] [2 : 0] [1 : 0] [6 : 0] [3 : 0] [4 : 0] [5 : 0] [14 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [29 : 1236] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [27 : 414] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 1 4 5 6 3 8 9 10 11 12 13 27 7 16 17 18 19 20 21 22 23 24 30 0 26 25 31 15 29 14
 distance: vertex: [to : distance]
 [25 : 0] [2 : 0] [1 : 0] [6 : 0] [3 : 0] [4 : 0] [5 : 0] [14 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [29 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [27 : 414] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 25 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 0 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 19 20 21 22 23 24 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [2 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 0 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 19 20 21 22 23 24 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [2 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 19 20 21 22 23 0 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [23 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 19 20 21 22 23 0 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [23 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 23 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 19 20 21 22 0 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [22 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 19 20 21 22 0 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [22 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 22 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 19 20 21 0 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [21 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 19 20 21 0 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [21 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 21 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 19 20 0 21 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [20 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 19 20 0 21 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [20 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 19 0 20 21 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [19 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 19 0 20 21 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [19 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 19 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 0 19 20 21 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [18 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 18 0 19 20 21 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [18 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [17 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 18 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 0 18 19 20 21 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [17 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 17 0 18 19 20 21 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [17 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 17 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 0 17 18 19 20 21 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [16 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 16 0 17 18 19 20 21 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [16 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [15 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 0 16 17 18 19 20 21 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [15 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 1 8 9 10 11 12 13 27 3 0 16 17 18 19 20 21 22 23 30 25 26 15 31 7 29 14
 distance: vertex: [to : distance]
 [15 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 15 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 0 8 9 10 11 12 13 27 1 15 16 17 18 19 20 21 22 23 30 25 26 7 31 3 29 14
 distance: vertex: [to : distance]
 [6 : 0] [14 : 0] [1 : 0] [29 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 0 8 9 10 11 12 13 27 1 15 16 17 18 19 20 21 22 23 30 25 26 7 31 3 29 14
 distance: vertex: [to : distance]
 [6 : 0] [14 : 0] [1 : 0] [29 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 6 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 14 3 9 10 11 12 13 27 0 15 16 17 18 19 20 21 22 23 30 25 26 7 31 1 29 8
 distance: vertex: [to : distance]
 [14 : 0] [29 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 14 3 9 10 11 12 13 27 0 15 16 17 18 19 20 21 22 23 30 25 26 7 31 1 29 8
 distance: vertex: [to : distance]
 [14 : 0] [29 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 14 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 14 3 9 10 11 12 0 27 13 15 16 17 18 19 20 21 22 23 30 25 26 7 31 1 29 8
 distance: vertex: [to : distance]
 [12 : 0] [29 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 14 3 9 10 11 12 0 27 13 15 16 17 18 19 20 21 22 23 30 25 26 7 31 1 29 8
 distance: vertex: [to : distance]
 [12 : 0] [29 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 12 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 14 3 9 10 11 0 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 7 31 1 29 8
 distance: vertex: [to : distance]
 [11 : 0] [29 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 14 3 9 10 11 0 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 7 31 1 29 8
 distance: vertex: [to : distance]
 [11 : 0] [29 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 11 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 14 3 9 10 0 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 7 31 1 29 8
 distance: vertex: [to : distance]
 [10 : 0] [29 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 14 3 9 10 0 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 7 31 1 29 8
 distance: vertex: [to : distance]
 [10 : 0] [29 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 10 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 14 3 9 0 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 7 31 1 29 8
 distance: vertex: [to : distance]
 [9 : 0] [29 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 14 3 9 0 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 7 31 1 29 8
 distance: vertex: [to : distance]
 [9 : 0] [29 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 9 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 14 3 0 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 7 31 1 29 8
 distance: vertex: [to : distance]
 [8 : 0] [29 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 14 3 0 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 7 31 1 29 8
 distance: vertex: [to : distance]
 [8 : 0] [29 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 nodes to Q: 28 2 24 4 5 6 14 1 8 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 3 31 0 29 7
 distance: vertex: [to : distance]
 [29 : 0] [7 : 0] [1 : 0] [27 : 414] [3 : 0] [4 : 0] [5 : 0] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 14 1 8 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 3 31 0 29 7
 distance: vertex: [to : distance]
 [29 : 0] [7 : 0] [1 : 0] [27 : 0] [3 : 0] [4 : 0] [5 : 0] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 29 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 24 4 5 6 14 0 8 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 1 31 7 29 3
 distance: vertex: [to : distance]
 [7 : 0] [27 : 0] [1 : 0] [31 : 2001] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 6 14 0 8 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 1 31 7 29 3
 distance: vertex: [to : distance]
 [7 : 0] [27 : 0] [1 : 0] [31 : 2001] [3 : 0] [4 : 0] [5 : 0] [29 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 7 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 24 4 5 0 14 6 8 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 1 31 7 29 3
 distance: vertex: [to : distance]
 [5 : 0] [27 : 0] [1 : 0] [31 : 2001] [3 : 0] [4 : 0] [7 : 0] [29 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 5 0 14 6 8 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 1 31 7 29 3
 distance: vertex: [to : distance]
 [5 : 0] [27 : 0] [1 : 0] [31 : 2001] [3 : 0] [4 : 0] [7 : 0] [29 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 24 4 0 5 14 6 8 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 1 31 7 29 3
 distance: vertex: [to : distance]
 [4 : 0] [27 : 0] [1 : 0] [31 : 2001] [3 : 0] [5 : 0] [7 : 0] [29 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 4 0 5 14 6 8 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 1 31 7 29 3
 distance: vertex: [to : distance]
 [4 : 0] [27 : 0] [1 : 0] [31 : 2001] [3 : 0] [5 : 0] [7 : 0] [29 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 24 0 4 5 14 6 8 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 1 31 7 29 3
 distance: vertex: [to : distance]
 [3 : 0] [27 : 0] [1 : 0] [31 : 2001] [4 : 0] [5 : 0] [7 : 0] [29 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 0 4 5 14 6 8 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 1 31 7 29 3
 distance: vertex: [to : distance]
 [3 : 0] [27 : 0] [1 : 0] [31 : 2001] [4 : 0] [5 : 0] [7 : 0] [29 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 24 3 4 5 14 6 8 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 0 31 7 29 1
 distance: vertex: [to : distance]
 [27 : 0] [31 : 2001] [1 : 0] [3 : 0] [4 : 0] [5 : 0] [7 : 0] [29 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 nodes to Q: 28 2 24 3 4 5 14 6 8 9 10 11 12 27 13 15 16 17 18 19 20 21 22 23 30 25 26 0 31 7 29 1
 distance: vertex: [to : distance]
 [27 : 0] [31 : 2001] [1 : 0] [3 : 0] [4 : 0] [5 : 0] [7 : 0] [29 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [2 : 0] [25 : 0] [26 : 0] [13 : 0] [0 : 0] [30 : 0] [24 : 0] [28 : 0]
 27 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [28 : 27]
 l = 27
 delta = 8
 k == 28, l == 27
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 28 30 30 8 24 26 24 24
 path: 27 8 from == k : 0
 e: 0 0 0 0 0 0 0 0 -8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -2 8 2 0 0
 30 from == k : 0
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -2 8 2 -8 0
 24 from == k : 0
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -8 0 0 -2 8 2 0 0
 28 from == k : 1
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -2 0 2 0 0

 --------------------------------------------------
 from: 29
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 0 30 31
 distance: vertex: [to : distance]
 [29 : 0] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [30 : INF] [31 : INF]
 29 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 31 30 0
 distance: vertex: [to : distance]
 [31 : INF] [0 : INF] [1 : INF] [2 : INF] [3 : INF] [4 : INF] [5 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [12 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [26 : INF] [27 : INF] [28 : INF] [30 : INF] [29 : 0]
 nodes to Q: 1 6 3 4 5 13 7 8 9 10 11 12 27 14 15 16 17 18 19 20 21 22 23 24 25 26 0 28 29 31 30 2
 distance: vertex: [to : distance]
 [26 : 0] [0 : INF] [31 : 3001] [2 : INF] [3 : INF] [4 : INF] [1 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [12 : INF] [27 : INF] [28 : INF] [30 : INF] [29 : 0]
 26 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 6 3 4 5 13 7 8 9 10 11 12 27 14 15 16 17 18 19 20 21 22 23 24 25 26 30 28 29 31 2 0
 distance: vertex: [to : distance]
 [31 : 3001] [0 : INF] [30 : INF] [2 : INF] [3 : INF] [4 : INF] [1 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [13 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [12 : INF] [27 : INF] [28 : INF] [26 : 0] [29 : 0]
 nodes to Q: 1 14 3 4 5 13 7 8 9 10 11 12 27 29 15 16 17 18 19 20 21 22 23 24 25 26 30 28 2 31 0 6
 distance: vertex: [to : distance]
 [30 : 0] [0 : INF] [28 : 1236] [2 : INF] [3 : INF] [4 : INF] [31 : 2001] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [1 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [12 : INF] [27 : INF] [13 : INF] [26 : 0] [29 : 0]
 30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 1 14 3 4 5 13 7 8 9 10 11 12 27 6 15 16 17 18 19 20 21 22 23 24 25 26 30 28 0 31 29 2
 distance: vertex: [to : distance]
 [28 : 1236] [0 : INF] [31 : 2001] [2 : INF] [3 : INF] [4 : INF] [13 : INF] [6 : INF] [7 : INF] [8 : INF] [9 : INF] [10 : INF] [11 : INF] [5 : INF] [1 : INF] [14 : INF] [15 : INF] [16 : INF] [17 : INF] [18 : INF] [19 : INF] [20 : INF] [21 : INF] [22 : INF] [23 : INF] [24 : INF] [25 : INF] [12 : INF] [27 : INF] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 25 26 30 27 15 31 29 14
 distance: vertex: [to : distance]
 [0 : 0] [2 : 0] [1 : 0] [6 : 0] [3 : 0] [4 : 0] [5 : 0] [14 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 1236] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [27 : 2000] [13 : 0] [30 : 0] [26 : 0] [29 : 0]
 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 1 4 5 6 3 8 9 10 11 12 13 0 7 16 17 18 19 20 21 22 23 24 25 26 30 27 15 31 29 14
 distance: vertex: [to : distance]
 [13 : 0] [2 : 0] [1 : 0] [6 : 0] [3 : 0] [4 : 0] [5 : 0] [14 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 1236] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [27 : 2000] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 1 4 5 6 3 8 9 10 11 12 13 0 7 16 17 18 19 20 21 22 23 24 25 26 30 27 15 31 29 14
 distance: vertex: [to : distance]
 [13 : 0] [2 : 0] [1 : 0] [6 : 0] [3 : 0] [4 : 0] [5 : 0] [14 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 1236] [15 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [27 : 414] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 13 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 0 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 21 22 23 24 25 26 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [2 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 1236] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 0 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 21 22 23 24 25 26 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [2 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 1236] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 21 22 23 24 25 0 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [25 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 1236] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 21 22 23 24 25 0 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [25 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 1236] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 25 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 21 22 23 24 0 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [24 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 1236] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 21 22 23 24 0 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [24 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 414] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 24 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 21 22 23 0 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [23 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 414] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 21 22 23 0 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [23 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 23 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 21 22 0 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [22 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 21 22 0 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [22 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 22 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 21 0 22 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [21 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 21 0 22 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [21 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 21 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 0 21 22 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [20 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 20 0 21 22 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [20 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 0 20 21 22 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [19 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 19 0 20 21 22 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [19 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 19 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 0 19 20 21 22 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [18 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [17 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 18 0 19 20 21 22 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [18 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [17 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 18 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 0 18 19 20 21 22 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [17 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 17 0 18 19 20 21 22 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [17 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [16 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 17 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 0 17 18 19 20 21 22 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [16 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 1 8 9 10 11 12 13 27 3 7 0 17 18 19 20 21 22 23 24 25 30 16 15 31 29 14
 distance: vertex: [to : distance]
 [16 : 0] [6 : 0] [1 : 0] [14 : 0] [3 : 0] [4 : 0] [5 : 0] [15 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [28 : 0] [27 : 414] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 0 8 9 10 11 12 13 27 1 3 16 17 18 19 20 21 22 23 24 25 30 15 7 31 29 14
 distance: vertex: [to : distance]
 [6 : 0] [14 : 0] [1 : 0] [15 : 0] [3 : 0] [4 : 0] [5 : 0] [28 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 0 8 9 10 11 12 13 27 1 3 16 17 18 19 20 21 22 23 24 25 30 15 7 31 29 14
 distance: vertex: [to : distance]
 [6 : 0] [14 : 0] [1 : 0] [15 : 0] [3 : 0] [4 : 0] [5 : 0] [28 : 0] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [27 : 414] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 6 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 15 8 9 10 11 12 13 27 0 1 16 17 18 19 20 21 22 23 24 25 30 7 3 31 29 14
 distance: vertex: [to : distance]
 [14 : 0] [15 : 0] [1 : 0] [28 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 15 8 9 10 11 12 13 27 0 1 16 17 18 19 20 21 22 23 24 25 30 7 3 31 29 14
 distance: vertex: [to : distance]
 [14 : 0] [15 : 0] [1 : 0] [28 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [7 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [31 : 2001] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 14 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 15 3 9 10 11 12 13 27 14 0 16 17 18 19 20 21 22 23 24 25 30 7 1 31 29 8
 distance: vertex: [to : distance]
 [15 : 0] [28 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 15 3 9 10 11 12 13 27 14 0 16 17 18 19 20 21 22 23 24 25 30 7 1 31 29 8
 distance: vertex: [to : distance]
 [15 : 0] [28 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 15 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 15 3 9 10 11 12 0 27 14 13 16 17 18 19 20 21 22 23 24 25 30 7 1 31 29 8
 distance: vertex: [to : distance]
 [12 : 0] [28 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 15 3 9 10 11 12 0 27 14 13 16 17 18 19 20 21 22 23 24 25 30 7 1 31 29 8
 distance: vertex: [to : distance]
 [12 : 0] [28 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 12 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 15 3 9 10 11 0 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 7 1 31 29 8
 distance: vertex: [to : distance]
 [11 : 0] [28 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 15 3 9 10 11 0 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 7 1 31 29 8
 distance: vertex: [to : distance]
 [11 : 0] [28 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 11 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 15 3 9 10 0 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 7 1 31 29 8
 distance: vertex: [to : distance]
 [10 : 0] [28 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 15 3 9 10 0 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 7 1 31 29 8
 distance: vertex: [to : distance]
 [10 : 0] [28 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [9 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 10 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 15 3 9 0 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 7 1 31 29 8
 distance: vertex: [to : distance]
 [9 : 0] [28 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 15 3 9 0 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 7 1 31 29 8
 distance: vertex: [to : distance]
 [9 : 0] [28 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [8 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 9 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 15 3 0 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 7 1 31 29 8
 distance: vertex: [to : distance]
 [8 : 0] [28 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 15 3 0 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 7 1 31 29 8
 distance: vertex: [to : distance]
 [8 : 0] [28 : 0] [1 : 0] [7 : 0] [3 : 0] [4 : 0] [5 : 0] [27 : 414] [31 : 2001] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 15 1 8 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 3 0 31 29 7
 distance: vertex: [to : distance]
 [28 : 0] [7 : 0] [1 : 0] [27 : 414] [3 : 0] [4 : 0] [5 : 0] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 15 1 8 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 3 0 31 29 7
 distance: vertex: [to : distance]
 [28 : 0] [7 : 0] [1 : 0] [27 : 0] [3 : 0] [4 : 0] [5 : 0] [31 : 2001] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 28 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 6 15 0 8 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 1 7 31 29 3
 distance: vertex: [to : distance]
 [7 : 0] [27 : 0] [1 : 0] [31 : 2001] [3 : 0] [4 : 0] [5 : 0] [28 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 6 15 0 8 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 1 7 31 29 3
 distance: vertex: [to : distance]
 [7 : 0] [27 : 0] [1 : 0] [31 : 2001] [3 : 0] [4 : 0] [5 : 0] [28 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 7 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 5 0 15 6 8 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 1 7 31 29 3
 distance: vertex: [to : distance]
 [5 : 0] [27 : 0] [1 : 0] [31 : 2001] [3 : 0] [4 : 0] [7 : 0] [28 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 5 0 15 6 8 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 1 7 31 29 3
 distance: vertex: [to : distance]
 [5 : 0] [27 : 0] [1 : 0] [31 : 2001] [3 : 0] [4 : 0] [7 : 0] [28 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 4 0 5 15 6 8 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 1 7 31 29 3
 distance: vertex: [to : distance]
 [4 : 0] [27 : 0] [1 : 0] [31 : 2001] [3 : 0] [5 : 0] [7 : 0] [28 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 4 0 5 15 6 8 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 1 7 31 29 3
 distance: vertex: [to : distance]
 [4 : 0] [27 : 0] [1 : 0] [31 : 2001] [3 : 0] [5 : 0] [7 : 0] [28 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 0 4 5 15 6 8 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 1 7 31 29 3
 distance: vertex: [to : distance]
 [3 : 0] [27 : 0] [1 : 0] [31 : 2001] [4 : 0] [5 : 0] [7 : 0] [28 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 0 4 5 15 6 8 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 1 7 31 29 3
 distance: vertex: [to : distance]
 [3 : 0] [27 : 0] [1 : 0] [31 : 2001] [4 : 0] [5 : 0] [7 : 0] [28 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 nodes to Q: 28 2 26 3 4 5 15 6 8 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 0 7 31 29 1
 distance: vertex: [to : distance]
 [27 : 0] [31 : 2001] [1 : 0] [3 : 0] [4 : 0] [5 : 0] [7 : 0] [28 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 nodes to Q: 28 2 26 3 4 5 15 6 8 9 10 11 12 27 14 13 16 17 18 19 20 21 22 23 24 25 30 0 7 31 29 1
 distance: vertex: [to : distance]
 [27 : 0] [31 : 2001] [1 : 0] [3 : 0] [4 : 0] [5 : 0] [7 : 0] [28 : 0] [8 : 0] [9 : 0] [10 : 0] [11 : 0] [12 : 0] [15 : 0] [14 : 0] [6 : 0] [16 : 0] [17 : 0] [18 : 0] [19 : 0] [20 : 0] [21 : 0] [22 : 0] [23 : 0] [24 : 0] [25 : 0] [2 : 0] [13 : 0] [0 : 0] [30 : 0] [26 : 0] [29 : 0]
 27 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 [29 : 27]
 l = 27
 delta = 2
 k == 29, l == 27
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 prev: 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 29 8 24 26 26 26
 path: 27 8 from == k : 0
 e: 0 0 0 0 0 0 0 0 -2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0
 30 from == k : 0
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 -2 0
 26 from == k : 0
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -2 0 0 2 0 0
 29 from == k : 1
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

 --------------------------------------------------
 
 
 
 
 from: 15
 15
 1 6 3 4 5 13 7 8 9 10 11 12 27 14 15 31 16 17 18 19 20 21 22 23 24 25 26 0 28 29 30 2
 1 6 3 4 5 13 7 8 9 10 11 12 27 14 15 31 16 17 18 19 20 21 22 23 24 25 26 0 28 29 30
 
 1 13 3 4 5 28 7 8 9 10 11 12 27 14 15 31 16 17 18 19 20 21 22 23 24 25 26 2 0 29 30 6
 1 13 3 4 5 28 7 8 9 10 11 12 27 14 15 31 16 17 18 19 20 21 22 23 24 25 26 2 0 29 30
 
 1 13 3 4 5 28 7 8 9 10 11 12 27 30 15 31 16 17 18 19 20 21 22 23 24 25 26 6 2 29 0 14
 1 13 3 4 5 28 7 8 9 10 11 12 27 30 15 31 16 17 18 19 20 21 22 23 24 25 26 6 2 29 0
 
 1 13 3 4 5 28 7 8 9 10 11 12 27 30 15 31 16 17 18 19 20 21 22 23 24 25 26 6 2 29 0 14
 1 13 3 4 5 28 7 8 9 10 11 12 27 30 15 31 16 17 18 19 20 21 22 23 24 25 26 6 2 29 0
 
 30
 1 13 3 4 5 28 7 8 9 10 11 12 27 29 15 31 16 17 18 19 20 21 22 23 24 25 26 2 0 6 30 14
 1 13 3 4 5 28 7 8 9 10 11 12 27 29 15 31 16 17 18 19 20 21 22 23 24 25 26 2 0 6
 
 0
 29 2 0 4 5 6 1 8 9 10 11 12 13 14 3 31 7 17 18 19 20 21 22 23 24 25 26 27 15 28 30 16
 29 2 0 4 5 6 1 8 9 10 11 12 13 14 3 31 16 17 18 19 20 21 22 23 24 25 26 27 7
 
 
 My Version v = 27; alt = 1414
 29 2 0 4 5 6 1 8 9 10 11 12 13 14 3 31 16 17 18 19 20 21 22 23 24 25 26 27 7
 
 2 6 14 26
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 21 22 23 24 0 25 17 15 7 30 16
 25 24
 nodes to Q: 29 2 28 4 5 6 27 3 9 10 11 12 13 14 26 31 1 8 18 19 20 21 22 0 23 24 25 17 15 7 30 16
 23 22 21 20 19 18 16 7 17 13 12 11 10 9 3 8
 nodes to Q: 29 0 28 8 2 6 27 15 7 9 10 11 12 13 26 31 16 14 17 18 19 20 21 22 23 24 25 5 3 1 30 4
 1 5 4 29
 
 
 finalNodesFlg: 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 1 1 0
 finalNodesFlg: 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 1 1 0
 
 
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 prev: 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 0 30 30 30 30 30 30 30 30 30 30 30 8 24 26 15 15
 prev: 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 0 30 30 30 30 30 30 30 30 30 30 30 8 24 26 15 15
 path: 29 26 from == k : 0
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 12 0 0 0 0 0 0 0 0 0 0 -12 -10 -2 2 10 0
 30 from == k : 0
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 12 0 0 0 0 0 0 0 0 0 0 0 -10 -2 2 -2 0
 15 from == k : 1
 e: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -10 -2 2 10 0
 
 d: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1000 0 0
 prev: 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 0 30 30 30 30 30 30 30 30 30 30 30 8 24 26 15 15
 path: 29 26 from == k : 0
 Vertex Weights: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 12 0 0 0 0 0 0 0 0 0 0 -12 -10 -2 2 10 0
 30 from == k : 0
 Vertex Weights: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 12 0 0 0 0 0 0 0 0 0 0 0 -10 -2 2 -2 0
 15 from == k : 1
 Vertex Weights: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -10 -2 2 10 0
 --------------------------------------------------
 orginal Versions
 from: 30
 Reduced Costs For Forward Edges Network:
 vertex: [to : reduced cost]
 0: [27 : 414] [30 : 0] [31 : 2001]
 0: [27 : 414] [30 : 0] [31 : 2001]
 1: [27 : 0] [30 : 0] [31 : 2001]
 1: [27 : 0] [30 : 0] [31 : 2001]
 2: [27 : 414] [30 : 0] [31 : 2001]
 2: [27 : 414] [30 : 0] [31 : 2001]
 3: [27 : 1236] [30 : 0] [31 : 2001]
 3: [27 : 1236] [30 : 0] [31 : 2001]
 4: [27 : 0] [30 : 0] [31 : 2001]
 4: [27 : 0] [30 : 0] [31 : 2001]
 5: [27 : 0] [30 : 0] [31 : 2001]
 5: [27 : 0] [30 : 0] [31 : 2001]
 6: [27 : 1000] [30 : 0] [31 : 2001]
 6: [27 : 1000] [30 : 0] [31 : 2001]
 7: [27 : 414] [30 : 0] [31 : 2001]
 7: [27 : 414] [30 : 0] [31 : 2001]
 8: [27 : 0] [28 : 1828] [30 : 0] [31 : 2001]
 8: [27 : 0] [28 : 2828] [30 : 0] [31 : 3001]
 9: [27 : 414] [28 : 1236] [30 : 0] [31 : 2001]
 10: [27 : 1236] [28 : 1000] [29 : 1828] [30 : 0] [31 : 2001]
 11: [28 : 1236] [29 : 1236] [30 : 0] [31 : 2001]
 12: [28 : 1828] [29 : 1000] [30 : 0] [31 : 2001]
 13: [27 : 1236] [30 : 0] [31 : 2001]
 14: [27 : 1000] [28 : 1236] [30 : 0] [31 : 2001]
 15: [27 : 1236] [28 : 414] [30 : 0] [31 : 2001]
 16: [27 : 1828] [28 : 0] [29 : 1236] [30 : 0] [31 : 2001]
 17: [28 : 414] [29 : 414] [30 : 0] [31 : 2001]
 18: [28 : 1236] [29 : 0] [30 : 0] [31 : 2001]
 19: [28 : 1000] [30 : 0] [31 : 2001]
 20: [28 : 0] [30 : 0] [31 : 2001]
 21: [28 : 0] [29 : 0] [30 : 0] [31 : 2001]
 22: [28 : 1236] [30 : 0] [31 : 2001]
 23: [28 : 414] [30 : 0] [31 : 2001]
 24: [28 : 0] [29 : 1236] [30 : 0] [31 : 2001]
 25: [28 : 414] [29 : 414] [30 : 0] [31 : 2001]
 26: [28 : 1236] [29 : 0] [30 : 0] [31 : 2001]
 27: [31 : 3001]
 28: [31 : 3001]
 29: [31 : 3001]
 30: [27 : 2000] [28 : 2000] [29 : 2000] [31 : 2001]
 31: [0 : 4001] [1 : 4001] [2 : 4001] [3 : 4001] [4 : 4001] [5 : 4001] [6 : 4001] [7 : 4001] [8 : 4001] [9 : 4001] [10 : 4001] [11 : 4001] [12 : 4001] [13 : 4001] [14 : 4001] [15 : 4001] [16 : 4001] [17 : 4001] [18 : 4001] [19 : 4001] [20 : 4001] [21 : 4001] [22 : 4001] [23 : 4001] [24 : 4001] [25 : 4001] [26 : 4001] [27 : 3001] [28 : 3001] [29 : 3001] [30 : 4001]
 
 30
 nodes to Q: 1 5 3 4 12 14 7 8 9 10 11 25 13 29 15 16 17 18 19 20 21 22 23 24 30 26 27 28 31 2 0 6
 nodes to Q: 1 5 3 4 12 14 7 8 9 10 11 25 13 6 15 16 17 18 19 20 21 22 23 24 30 26 27 28 31 0 29 2
 cost_forward
 nodes to Q: 1 5 3 4 12 14 7 8 9 10 11 25 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 2 31 0 29 6
 cost_backward
 nodes to Q: 0 5 3 4 12 14 7 8 9 10 11 25 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 2 31 1 29 6
 nodes to Q: 0 2 3 4 12 14 7 8 9 10 11 25 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 5 31 1 29 6
 nodes to Q: 0 2 1 4 12 14 7 8 9 10 11 25 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 5 31 3 29 6
 nodes to Q: 0 2 1 4 12 14 7 8 9 10 11 25 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 5 31 3 29 6
 nodes to Q: 0 2 1 4 5 14 7 8 9 10 11 25 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 12 31 3 29 6
 nodes to Q: 0 2 1 4 5 6 7 8 9 10 11 25 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 12 31 3 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 25 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 12 31 7 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 25 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 12 31 7 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 25 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 12 31 7 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 25 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 12 31 7 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 25 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 12 31 7 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 28 13 15 16 17 18 19 20 21 22 23 24 30 26 27 25 31 7 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 15 16 17 18 19 20 21 22 23 24 30 26 27 25 31 7 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 15 16 17 18 19 20 21 22 23 24 30 26 27 25 31 7 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14
 nodes to Q: 0 2 1 4 5 6 3 8 9 10 11 12 13 28 7 16 17 18 19 20 21 22 23 24 30 26 27 25 31 15 29 14

 
 
 
 
 
 0
0 2 1 4 5 6 3 8 9 10 11 12 13 14 7 16 17 18 19 20 21 22 23 24 25 26 27 15 28 29 31 30
0 2 1 4 5 6 3 8 9 10 11 12 13 14 7 16 17 18 19 20 21 22 23 24 25 26 27 15 29 28 31 30
                                                                       ------------
 
30 2 0 4 5 6 1 8 9 10 11 12 13 14 3 7 17 18 19 20 21 22 23 24 25 26 27 15 28 29 31 16
30 2 0 4 5 6 1 8 9 10 11 12 13 14 3 7 17 18 19 20 21 22 23 24 25 26 27 15 29 28 31 16
 -----------------------------
 2
30 2 0 4 5 6 1 8 9 10 11 12 13 14 3 7 17 18 19 20 21 22 23 24 25 26 27 15 28 29 31 16
30 2 0 4 5 6 1 8 9 10 11 12 13 14 3 7 17 18 19 20 21 22 23 24 25 26 27 15 29 28 31 16
 
30 2 29 4 5 6 0 8 9 10 11 12 13 14 1 3 17 18 19 20 21 22 23 24 25 26 27 7 28 15 31 16
30 2 29 4 5 6 0 8 9 10 11 12 13 14 1 3 17 18 19 20 21 22 23 24 25 26 27 7 15 28 31 16
 
 6
30 2 29 4 5 6 0 8 9 10 11 12 13 14 1 3 17 18 19 20 21 22 23 24 25 26 27 7 28 15 31 16
30 2 29 4 5 6 0 8 9 10 11 12 13 14 1 3 17 18 19 20 21 22 23 24 25 26 27 7 15 28 31 16
 
30 2 29 4 5 6 28 3 9 10 11 12 13 14 0 1 8 18 19 20 21 22 23 24 25 26 27 7 17 15 31 16
30 2 29 4 5 6 28 3 9 10 11 12 13 14 0 1 8 18 19 20 21 22 23 24 25 26 27 7 15 17 31 16
 
 14
30 2 29 4 5 6 28 3 9 10 11 12 13 14 0 1 8 18 19 20 21 22 23 24 25 26 27 7 17 15 31 16
30 2 29 4 5 6 28 3 9 10 11 12 13 14 0 1 8 18 19 20 21 22 23 24 25 26 27 7 15 17 31 16
 
 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 25 26 0 7 17 15 31 16
 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 25 26 0 7 15 17 31 16
 
 26
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 25 26 0 7 17 15 31 16
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 25 0 26 7 17 15 31 16
 25
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 25 0 26 15 17 7 31 16
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 0 25 26 15 17 7 31 16
 24
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 24 0 25 26 15 17 7 31 16
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 0 24 25 26 15 17 7 31 16
 23
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 23 0 24 25 26 15 17 7 31 16
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 0 23 24 25 26 15 17 7 31 16
 22
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 22 0 23 24 25 26 15 17 7 31 16
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 0 22 23 24 25 26 15 17 7 31 16
 21
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 21 0 22 23 24 25 26 15 17 7 31 16
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 0 21 22 23 24 25 26 15 17 7 31 16
 20
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 20 0 21 22 23 24 25 26 15 17 7 31 16
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 0 20 21 22 23 24 25 26 15 17 7 31 16
 19
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 19 0 20 21 22 23 24 25 26 15 17 7 31 16
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 0 19 20 21 22 23 24 25 26 15 17 7 31 16
 18
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 18 0 19 20 21 22 23 24 25 26 15 17 7 31 16
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 0 18 19 20 21 22 23 24 25 26 15 17 7 31 16
 17
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 0 18 19 20 21 22 23 24 25 26 15 17 7 31 16
 nodes to Q: 30 2 29 4 5 6 28 3 9 10 11 12 13 14 27 1 8 17 18 19 20 21 22 23 24 25 26 15 0 7 31 16
 28
 */
