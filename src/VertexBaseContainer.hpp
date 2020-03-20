//
//  VertexBaseContainer.hpp
//  FastEMD
//
//  Created by Till Hainbach on 20.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef VertexBaseContainer_h
#define VertexBaseContainer_h

template <typename... _Types>
class VertexBaseContainer : public BaseContainer<_Types...>
{
    
public:
    inline uchar fields() const {return _fields;}
    inline NODE_T thresholdNodeIndex() const {return _thresholdNodeIndex;}
    inline NODE_T artificialNodeIndex() const {return  _artificialNodeIndex;}
    inline NODE_T toNode(NODE_T nodeIndex) const {return _fields * nodeIndex;}
    
private:
    NODE_T _thresholdNodeIndex;
    NODE_T _artificialNodeIndex;
    unsigned char _fields;
    
};

#endif /* VertexBaseContainer_h */
