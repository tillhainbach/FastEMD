//
//  utils.h
//  FastEMD
//
//  Created by Till Hainbach on 26.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp
#include <opencv2/core.hpp>

namespace FastEMD
{
namespace utils
{

template<typename _T> inline
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

inline
uint calculateCostMatVector(int im1_R, int im1_C, int im2_R, int im2_C,
                           std::vector< std::vector<int> >& costmat,
                           const int THRESHOLD, const int COST_MULT_FACTOR)
{
    uint maxCost = 0;
    uint j = 0;
    for (unsigned int c1 = 0; c1 < im1_C; ++c1)
    {
        for (unsigned int r1=0; r1<im1_R; ++r1, ++j)
        {
            uint i = 0;
            for (unsigned int c2 = 0; c2 < im1_C; ++c2)
            {
                for (unsigned int r2=0; r2<im1_R; ++r2, ++i)
                {
                    
                    double L1 = sqrt((r1-r2)*(r1-r2)+(c1-c2)*(c1-c2));
                    costmat[i][j] = std::min(THRESHOLD, static_cast<int>(COST_MULT_FACTOR * L1));
                    if (costmat[i][j] > maxCost) maxCost = costmat[i][j];
                }
            }
        }
    }
    return maxCost;
}

inline
void showStringInequality(std::string const& sample, std::string const& target)
{
    if(sample.size() != target.size())
    {
        std::cout << "string sizes are not equal!" << std::endl;
        std::cout << "sample has size " << sample.size() << " and target has size "
        << target.size() << std::endl;
    }
//    assert(sample.size() <= target.size());
    for(unsigned int i = 0; i < target.size(); ++i)
    {
        if (sample[i] != target[i])
        {
            std::cout << sample[i] << " != " << target[i] << " | ";
            std::cout << (int)sample[i] << " != " << (int)target[i] << std::endl;
        }
    }
}

template<class _ITER>
bool isEnd(_ITER& it, _ITER& end)
{
    return (&(*it) == &(*end));
}

bool hasEnding (std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length())
    {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    }
    else
    {
        return false;
    }
}

uint calculateCostMatrix(cv::InputArray _src1, cv::InputArray _src2,
                        cv::OutputArray _costMat, int THRESHOLD)
{
    cv::Mat src1 = _src1.getMat();
    cv::Mat src2 = _src2.getMat();
    
    if (_costMat.needed())
    {
        _costMat.create(src1.total(), src2.total(), CV_32S);
    }
    
    cv::Mat costMat = _costMat.getMat();
    
    uint maxCost = 0;
    uint j = 0;
    uint im1_C = src1.cols;
    uint im1_R = src1.rows;
    uint im2_C = src2.cols;
    uint im2_R = src2.rows;
    uint COST_MULT_FACTOR = 1000;
    for (unsigned int c1 = 0; c1 < im1_C; ++c1)
    {
        for (unsigned int r1 = 0; r1 < im1_R; ++r1, ++j)
        {
            uint i = 0;
            for (unsigned int c2 = 0; c2 < im2_C; ++c2)
            {
                for (unsigned int r2 = 0; r2 < im2_R; ++r2, ++i)
                {
                    costMat.at<int>(i, j) = std::min(THRESHOLD, static_cast<int>(COST_MULT_FACTOR*sqrt((r1-r2)*(r1-r2)+(c1-c2)*(c1-c2))));
                    if (costMat.at<int>(i, j) > maxCost) maxCost = costMat.at<int>(i, j);
                }
            }
        }
    }
    return maxCost;
}

}}

#endif /* utils_h */
