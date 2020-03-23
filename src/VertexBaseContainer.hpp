//
//  VertexBaseContainer.hpp
//  FastEMD
//
//  Created by Till Hainbach on 20.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef VertexBaseContainer_h
#define VertexBaseContainer_h
#include "BaseContainer.hpp"

template <typename... _Types>
class VertexBaseContainer : public BaseContainer<_Types...>
{
    
public:
    
    //MARK: Initializers
    VertexBaseContainer(NODE_T numberOfNodes, std::string containerName,
                        std::vector<std::string> dataNames, uchar fields)
    : BaseContainer(numberOfNodes, _name)
    , _thresholdNodeIndex(numberOfNodes - 2)
    , _artificialNodeIndex(numberOfNodes - 1)
    , _fields(fields)
    
    
    //MARK: Iterators
    inline auto thresholdNode(){return data.begin() + thresholdNodeIndex();}
    inline auto artificialNode(){return data.begin() + artificialNodeIndex();}
    
    
    //MARK: Getters
    inline NODE_T thresholdNodeIndex() const {return _thresholdNodeIndex;}
    inline NODE_T artificialNodeIndex() const {return  _artificialNodeIndex;}
    inline uchar fields() const {return _fields;}
    inline NODE_T toNode(NODE_T nodeIndex) const {return _fields * nodeIndex;}
    inline NODE_T rows() const {return _numberOfNodes;}
    inline NODE_T cols() const {return _numberOfNodes * _fields;}
    
    //MARK: setters
    void resize(NODE_T newNumberOfNodes) override;
    
private:
    NODE_T _thresholdNodeIndex;
    NODE_T _artificialNodeIndex;
    unsigned char _fields;
    
};

//MARK: Implementations
template <typename... _Types>
void VertexBaseContainer<_Types...>::resize(NODE_T newNumberOfNodes)
{
    BaseContainer<_Types...>::resize(newNumberOfNodes);
    _thresholdNodeIndex = newNumberOfNodes - 2;
    _artificialNodeIndex = newNumberOfNodes - 1;
}



#endif /* VertexBaseContainer_h */
