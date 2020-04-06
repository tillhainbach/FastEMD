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
#include <iostream>

namespace FastEMD
{
namespace utils
{

enum class TextAlignment
{
    leftAligned,
    centered,
    rightAligned
};

std::string padding(size_t size)
{
    std::stringstream whitespace;
    for(int j = 0; j <= size; ++j) whitespace << " ";
    
    return whitespace.str();
}

std::ostream& makeHeader(std::ostream& os,
                         std::vector<std::string> const& header,
                         TextAlignment alignment,
                         size_t columnWidth,
                         std::string& columnSeparator)
{
    size_t headerSize = header.size();
    for(size_t i = 0; i < headerSize; ++i)
    {
        std::string name = header[i];
        size_t whitespace = columnWidth * 4 - name.size();
        switch (alignment)
        {
            case TextAlignment::leftAligned:
                os << name;
                if (i < headerSize - 1) os << padding(whitespace);
                break;
                    
            case TextAlignment::rightAligned:
                os << padding(whitespace);
                os << name;
                break;
                
            case TextAlignment::centered:
                
                size_t leading = whitespace / 2;
                size_t trailing = whitespace - name.size() - leading;
                os << padding(leading);
                os << name;
                os << padding(trailing);
                break;
        }
        os << columnSeparator;
    }
    
    os << std::endl;
    return os;
}


std::ostream& makeUnderline(std::ostream& os,
                            size_t tableWidth)
{
    for (uint i = 0; i < tableWidth; ++i) os << "-";
    os << std::endl;
    return os;
}

std::ostream& makeBody(std::ostream& os,
                       std::vector< std::vector<std::string> > const& data)
{
    // print table data
    size_t numberOfRows = 0;
    for (auto const & column : data)
    {
        if (numberOfRows < column.size()) numberOfRows = column.size();
    }
    for (size_t row = 0; row < numberOfRows; ++row)
    {
        size_t columnCounter = 0;
        for (auto const & column : data)
        {
            // check if there are enough elements
            std::string item = column.at(row % column.size());
            os << item;
            if (columnCounter < data.size() - 1)
            {
                os << padding(item.size());
            }
            else os << std::endl;
            ++columnCounter;
        }
    }
    return os;
}

std::ostream& makeTable(std::ostream& os,
                        std::vector<std::string> const & header,
                        std::vector< std::vector<std::string> > const & data,
                        TextAlignment alignment = TextAlignment::leftAligned,
                        size_t columnWidth = 3,
                        bool underlineHeader = true,
                        std::string columnSeparator = "\t")
                        
{
    makeHeader(os, header, alignment, columnWidth, columnSeparator);
    size_t numberOfColumns = header.size();
    size_t tableWidth = 4 * columnWidth * numberOfColumns;
    if (underlineHeader) makeUnderline (os, tableWidth);
    makeBody(os, data);
    return os;
}

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
uint calculateCostMatrix(int im1_R, int im1_C, int im2_R, int im2_C,
                           std::vector< std::vector<int> >& costmat,
                           const int THRESHOLD, const int COST_MULT_FACTOR)
{
    uint maxCost = 0;
    for (unsigned int c1 = 0, j = 0; c1 < im1_C; ++c1)
    {
        for (unsigned int r1 = 0; r1<im1_R; ++r1, ++j)
        {
            for (unsigned int c2 = 0, i = 0; c2 < im1_C; ++c2)
            {
                for (unsigned int r2 = 0; r2<im1_R; ++r2, ++i)
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
    uint im1_C = src1.cols;
    uint im1_R = src1.rows;
    uint im2_C = src2.cols;
    uint im2_R = src2.rows;
    uint COST_MULT_FACTOR = 1000;
    for (unsigned int c1 = 0, j = 0; c1 < im1_C; ++c1)
    {
        for (unsigned int r1 = 0; r1 < im1_R; ++r1, ++j)
        {
            for (unsigned int c2 = 0, i = 0; c2 < im2_C; ++c2)
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

inline void vector1D2cvMat(std::vector<int>& vector1d, cv::Mat& cvMat)
{
    cvMat.create(1, static_cast<int>(vector1d.size()), CV_32SC1);
    cvMat.data = (uchar*) vector1d.data();
}

inline void cvMat2vector1D(std::vector<int>& vector1d, cv::Mat& cvMat)
{
    if (cvMat.isContinuous())
    {
        vector1d.assign(cvMat.ptr<int>(0), cvMat.ptr<int>(0) + cvMat.total());
    }
}

inline void vector2d2cvMat(std::vector< std::vector<int> >& vector2d, cv::Mat& cvMat)
{
    cvMat.create(static_cast<int>(vector2d.size()), static_cast<int>(vector2d[0].size()), CV_32S);
    for(auto& row : vector2d)
    {
        cv::Mat matRow(1, static_cast<int>(row.size()), CV_32SC1, row.data());
        cvMat.push_back(matRow);
    }
}

inline void cvMat2vector2D(std::vector< std::vector<int> >& vector2d, cv::Mat1i& cvMat)
{
    for(unsigned int r = 0; r < cvMat.rows; ++r)
    {
        vector2d[r].assign(cvMat.ptr<int>(r), cvMat.ptr<int>(r) + cvMat.cols);
    }
}

}}

#endif /* utils_h */
