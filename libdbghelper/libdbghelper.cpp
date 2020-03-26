//
//  libdbghelper.cpp
//  libdbghelper
//
//  Created by Till Hainbach on 26.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#include <iostream>
#include "libdbghelper.hpp"
#include "libdbghelperPriv.hpp"

void libdbghelper::HelloWorld(const char * s)
{
    libdbghelperPriv *theObj = new libdbghelperPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void libdbghelperPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

