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
namespace FastEMD
{
using namespace types;

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0, uchar FIELDS = 1, uchar DIMENSIONS = 1>
class VertexBaseContainer : public BaseContainer<NUM_T, INTERFACE_T, SIZE, FIELDS, DIMENSIONS>
{
    
public:
    
    //MARK: Initializers
    VertexBaseContainer(NODE_T numberOfNodes,
                        std::string containerName,
                        std::vector<std::string> dataNames)
    : BaseContainer<NUM_T, INTERFACE_T, SIZE, FIELDS, DIMENSIONS>(numberOfNodes,
                                                                  containerName,
                                                                  dataNames)
    , _thresholdNodeIndex(numberOfNodes - 2)
    , _artificialNodeIndex(numberOfNodes - 1)
    {};
    
    template<typename _T>
    VertexBaseContainer(_T _data,
                        std::string containerName,
                        std::vector<std::string> dataNames)
    : BaseContainer<NUM_T, INTERFACE_T, SIZE, FIELDS, DIMENSIONS>(_data,
                                                                  containerName,
                                                                  dataNames)
    , _thresholdNodeIndex(this->_numberOfNodes - 2)
    , _artificialNodeIndex(this->_numberOfNodes - 1)
    {};
    
    //MARK: Iterators
    inline auto thresholdNode(){return this->begin() + thresholdNodeIndex();}

    inline auto artificialNode(){return this->begin() + artificialNodeIndex();}

    inline auto thresholdNode() const {return this->begin() + thresholdNodeIndex();}
    inline auto artificialNode() const {return this->begin() + artificialNodeIndex();}
    
    //MARK: Getters
    inline NODE_T thresholdNodeIndex() const {return _thresholdNodeIndex;}
    inline NODE_T artificialNodeIndex() const {return  _artificialNodeIndex;}
    inline uchar fields() const {return this->_fields;}
    inline NODE_T toNode(NODE_T nodeIndex) const {return this->_fields * nodeIndex;}
    inline NODE_T rows() const
        {return 1 + (1 - DIMENSIONS % 2) * (this->_numberOfNodes - 1);}
    inline NODE_T cols() const {return this->_numberOfNodes * this->_fields;}
    
    //MARK: setters
    inline void resize(NODE_T newNumberOfNodes) override;
    
private:
    NODE_T _thresholdNodeIndex;
    NODE_T _artificialNodeIndex;
    
};

//MARK: Implementations
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE, uchar FIELDS, uchar DIMENSIONS>
void VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, FIELDS, DIMENSIONS>::resize(NODE_T newNumberOfNodes)
{
    BaseContainer<NUM_T, INTERFACE_T, SIZE, FIELDS,  DIMENSIONS>::resize(newNumberOfNodes);
    _thresholdNodeIndex = newNumberOfNodes - 2;
    _artificialNodeIndex = newNumberOfNodes - 1;
}


        
        
} // namespace FastEMD
#endif /* VertexBaseContainer_h */
