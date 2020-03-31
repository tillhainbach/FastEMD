//
//  utils.h
//  FastEMD
//
//  Created by Till Hainbach on 26.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef utils_h
#define utils_h

namespace FastEMD
{
namespace utils
{

template<typename _T>
auto getMaxCost(const _T& costMatrix, const NODE_T N)
{
    auto maxCost = 0;
    for (NODE_T i = 0; i < N; ++i)
    {
        for (NODE_T j = i; j < N; ++j)
        { // cost matrix is symmetric so just check upper right half
            assert(costMatrix[i][j] >= 0);
            if (costMatrix[i][j] > maxCost) maxCost = costMatrix[i][j];
        }
    }
    return maxCost;
}

int calculateCostMatVector(int im1_R, int im1_C, int im2_R, int im2_C,
                           std::vector< std::vector<int> >& costmat,
                           const int THRESHOLD, const int COST_MULT_FACTOR)
{
    int max_cost_mat = -1;
    int j = -1;
    for (unsigned int c1 = 0; c1 < im1_C; ++c1)
    {
        for (unsigned int r1=0; r1<im1_R; ++r1)
        {
            ++j;
            int i = -1;
            for (unsigned int c2 = 0; c2 < im1_C; ++c2)
            {
                for (unsigned int r2=0; r2<im1_R; ++r2)
                {
                    ++i;
                    double L1 = sqrt((r1-r2)*(r1-r2)+(c1-c2)*(c1-c2));
                    costmat[i][j] = std::min(THRESHOLD, static_cast<int>(COST_MULT_FACTOR * L1));
                    if (costmat[i][j] > max_cost_mat) max_cost_mat = costmat[i][j];
                }
            }
        }
    }
    return max_cost_mat;
}

}}

#endif /* utils_h */