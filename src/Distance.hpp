//
//  Distance.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef Distance_h
#define Distance_h

#include "VertexBaseContainer.hpp"


namespace FastEMD
{
using namespace types;

template<typename... _Types>
class Distance : public VertexBaseContainer<_Types...>
{
public:
    Distance(NODE_T numberOfNodes)
    : VertexBaseContainer<_Types...>(numberOfNodes, "Distance",
                                     {"to", "distance"}, 2) {};
};

} // namespace FastEMD
#endif /* Distance_h */
