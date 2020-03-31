//
//  cvMatWrapper.h
//  FastEMD
//
//  Created by Till Hainbach on 30.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef cvMatSingleRow_h
#define cvMatSingleRow_h
#include <opencv2/core.hpp>

namespace FastEMD
{
namespace utils
{
class cvMatSingleRow : public cv::Mat1i
{
public:
    template<typename... Args>
    cvMatSingleRow(Args&&... args) : cv::Mat1i(std::forward<Args>(args)...) {};
    
    int& operator[](int idx) { return cv::Mat1i::operator[](0)[idx];}
    int const & operator[](int idx) const { return cv::Mat1i::operator[](0)[idx];}
};


}} //utils //FastEMD
#endif /* cvMatWrapper_h */
