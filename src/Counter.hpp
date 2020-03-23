//
//  Counter.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef Counter_h
#define Counter_h

#include "BaseContainer.hpp"

//MARK: Counter Class
template<typename... _Types>
class Counter : public BaseContainer<_Types...>
{
public:
    Counter(NODE_T _N, std::string _name = "Counter")
    : Base1dContainerImpl<NUM_T, INTERFACE_T, size>(_N, {_name}){};
};


#endif /* Counter_h */
