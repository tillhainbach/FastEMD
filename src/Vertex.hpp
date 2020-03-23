//
//  Vertex.hpp
//  FastEMD
//
//  Created by Till Hainbach on 09.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include "utils/utils.h"
#include "utils/types.h"
#include <type_traits>
#include <typeinfo>


////MARK: Vertex partial specialization
//template<typename NUM_T, typename INTERFACE_T, int size = 0>
//class Vertex : public Vertex_Base<NUM_T, INTERFACE_T, size>
//{
//public:
//    Vertex(NODE_T num_nodes, unsigned char channels,
//            std::vector<std::string> names)
//    : Vertex_Base<NUM_T, INTERFACE_T, size >(num_nodes, channels, names){};
//
//    inline NUM_T const * row(const NODE_T _row) const override
//        {return this->matrix.at(_row).begin();}
//    inline NUM_T * row(const NODE_T _row) override
//        {return this->matrix.at(_row).begin();}
//};
//
//template<typename NUM_T>
//class Vertex <NUM_T, OPENCV>: public Vertex_Base<NUM_T, OPENCV>
//{
//public:
//    Vertex (NODE_T num_nodes, unsigned char channels,
//            std::vector<std::string> names)
//    : Vertex_Base<NUM_T, OPENCV>(num_nodes, channels, names){};
//
//    NODE_T _num_nodes;
//    inline NUM_T const * row(const NODE_T _row) const override
//        {return this->matrix.template ptr<const NUM_T>(_row);}
//    inline NUM_T *  row(const NODE_T _row) override
//        {return this->matrix.template ptr<NUM_T>(_row);}
//};


template<typename NUM_T, typename INTERFACE_T, int size = 0>
class ForwardCost : public Vertex<NUM_T, INTERFACE_T, size >
{
public:
    ForwardCost(NODE_T num_nodes)
    : Vertex<NUM_T, INTERFACE_T, size >(num_nodes, 2, {"to", "reduced cost"}) {};
    
private:
    inline void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                         Counter<NUM_T, INTERFACE_T, size>& counters) override;
    
};

template<typename NUM_T, typename INTERFACE_T, int size = 0>
class Flow : public Vertex<NUM_T, INTERFACE_T, size >
{
public:
    Flow(NODE_T num_nodes)
    : Vertex<NUM_T, INTERFACE_T, size>(num_nodes, 3, {"to", "cost", "flow"}) {};
    
    NUM_T calcDist();
    
private:
    inline void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                         Counter<NUM_T, INTERFACE_T, size>& counters) override;
};

template<typename NUM_T, typename INTERFACE_T, int size = 0>
class BackwardCost : public Vertex<NUM_T, INTERFACE_T, size >
{
public:
    BackwardCost(NODE_T num_nodes)
    : Vertex<NUM_T, INTERFACE_T, size >(num_nodes, 3,
            {"to", "reduced cost", "residual capacity"})
    {};

private:
    inline void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                         Counter<NUM_T, INTERFACE_T, size>& counters) override;
};


#include "Vertex.cpp"
#endif /* Vertex_hpp */
