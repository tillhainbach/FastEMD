//
//  utils.hpp
//  FastEMD
//
//  Created by Till Hainbach on 25.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef utils_h
#define utils_h
#include <fstream>
#include <vector>
#include <iostream>

namespace FastEMD
{
namespace utils
{

void readImage(const char* im_name, unsigned int& im_R,
               unsigned int& im_C, std::vector<int>& im)
{
    
    std::fstream fin(im_name);
    if (!fin) goto readImageErrLabel;
    
    fin >> im_R;
    if (!fin) goto readImageErrLabel;
    fin >> im_C;
    if (!fin) goto readImageErrLabel;
    
    int tmp;
    while (fin >> tmp) {
        im.push_back(tmp);
    }
    
    if (im.size()==im_R*im_C) return;
readImageErrLabel:
    std::cerr << "Image " << im_name << " has a problem in its format" << std::endl;
    exit(1);
    
} // readImage

}} // utils // FastEMD

#endif /* utils_h */
