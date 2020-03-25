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
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0, uchar DIMENSIONS = 1>
class Counter : public BaseContainer<NUM_T, INTERFACE_T, SIZE, DIMENSIONS>
{
public:
    Counter(NODE_T numberOfNodes, std::string containerName = "counter",
            std::vector<std::string> dataNames = {"counts per vertex"})
    : BaseContainer<NUM_T, INTERFACE_T, SIZE, DIMENSIONS>(numberOfNodes, containerName, dataNames){};
    
    template<typename _T, typename _I, NODE_T _S, uchar _D>
    friend std::ostream& operator<<(std::ostream& os,
                                    const Counter<_T, _I, _S, _D>& counter);
};

//MARK: implementations
        
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE, uchar DIMENSIONS>
std::ostream& operator<<(std::ostream& os,
                         const Counter<NUM_T, INTERFACE_T, SIZE, DIMENSIONS>& counter)
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
