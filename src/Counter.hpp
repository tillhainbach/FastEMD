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
    Counter(NODE_T numberOfNodes, std::string containerName = "counter",
            std::vector<std::string> dataNames = {"counts per vertex"})
    : BaseContainer<_Types...>(numberOfNodes, containerName, dataNames){};
    
    friend std::ostream& operator<<(std::ostream& os,
                                    const Counter<_Types...>& counter)
    {
        os << counter._containerName << ": ";
        for (auto element : counter)
        {
            os << element << " ";
        }
        return os;
    }
};

#endif /* Counter_h */
