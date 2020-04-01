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

namespace FastEMD
{
using namespace types;
//MARK: Counter Class
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0>
class Counter : public BaseContainer<NUM_T, INTERFACE_T, SIZE, 1, 1>
{
public:
    Counter(NODE_T numberOfNodes,
            std::string containerName = "counter",
            std::vector<std::string> dataNames = {"counts per vertex"})
    : BaseContainer<NUM_T, INTERFACE_T, SIZE, 1, 1>(numberOfNodes,
                                                    containerName,
                                                    dataNames)
    {};
    
    Counter(std::vector<NUM_T> _data,
            std::string containerName = "counter",
            std::vector<std::string> dataNames = {"counts per vertex"})
    : BaseContainer<NUM_T, INTERFACE_T, SIZE, 1, 1>(_data,
                                                    containerName,
                                                    dataNames)
    {};
    
    template<typename _T, typename _I, NODE_T _S>
    friend std::ostream& operator<<(std::ostream& os,
                                    const Counter<_T, _I, _S>& counter);
};

//MARK: implementations
        
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
std::ostream& operator<<(std::ostream& os,
                         const Counter<NUM_T, INTERFACE_T, SIZE>& counter)
{
    os << counter._containerName << ": ";
    for (auto element : counter)
    {
        os << element << " ";
    }
    return os;
}
} // namespace FastEMD
#endif /* Counter_h */
