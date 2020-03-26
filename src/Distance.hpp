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

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0>
class Distance : public VertexBaseContainer<NUM_T, INTERFACE_T, SIZE>
{
public:
    Distance(NODE_T numberOfNodes)
    : VertexBaseContainer<NUM_T, INTERFACE_T, SIZE>(numberOfNodes, "Distance",
                                     {"to", "distance"}, 2) {};
};

} // namespace FastEMD
#endif /* Distance_h */
