//
//  mylog.cpp
//  FastEMD
//
//  Created by Till Hainbach on 26.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#include "mylog.hpp"
#include <iostream>

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
void mylog(FastEMD::BaseNetwork const& obj)
{
   //assume MyObject is the type you want to view in Debuger
   std::cout << obj << std::endl;
}
