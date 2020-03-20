//
//  BaseContainer.hpp
//  FastEMD
//
//  Created by Till Hainbach on 20.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef BaseContainer_h
#define BaseContainer_h
#include <stdio.h>
#include "utils/utils.h"
#include "utils/types.h"
#include <type_traits>
#include <typeinfo>

//MARK: Base1dContainer
template<typename NUM_T, typename INTERFACE_T, int Dimensions = 1, int Size = 0>
class BaseContainer
{
constexpr static InterfaceRequirement<INTERFACE_T, arrSize> check{};
    
public:
    
    template< class T = INTERFACE_T, std::enable_if_t<isARRAY<T>, int> = 0>
    Base1dContainer(NODE_T _N, std::vector<std::string> _name, uchar _fields = 1)
    : _num_nodes(_N)
    , dataNames({_name}) {};
    
    template< class T = INTERFACE_T, std::enable_if_t<isVECTOR<T>, int> = 0>
    Base1dContainer(NODE_T _N, std::vector<std::string> _name, uchar _fields = 1)
    : _num_nodes(_N)
    , dataNames({_name})
    , data(_N){};
    
    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    Base1dContainer(NODE_T _N, std::vector<std::string> _name, uchar _fields = 1)
    : _num_nodes(_N)
    , dataNames({_name})
    , data(1 + ((1 - Dimensions % 2) * (_N - 1)), _N){};
        //-> will resolve to 1 if Dimension == 1 or _N if Dimensions == 2
    
    //TODO: check if ptr() is really necessary.
    virtual inline NUM_T * ptr() = 0;
    virtual inline NUM_T const * ptr() const = 0;
    
    //MARK: Iterators
    inline auto begin() {return data.begin();}
    inline auto begin() const {return data.begin();}
    inline auto end() {return data.begin() + _numberOfNodes;}
    inline auto end() const {return data.begin() + _numberOfNodes;}
    inline auto thresholdNode(){return data.begin() + thresholdNodeIndex();}
    inline auto artificialNode(){return data.begin() + artificialNodeIndex();}
    

    //MARK: Getters
    inline NODE_T size() const {return _numberOfNodes;}
    
    //
    inline NODE_T rows() const {return _numberOfNodes;}
    inline NODE_T cols() const {return _numberOfNodes * _fields;}


    
    //MARK: Setters
    inline virtual void resize(NODE_T _newSize) {_num_nodes = _newSize;}
    
    inline const unsigned char getFields() const {return fields;}
    
    inline auto& operator[](NODE_T idx) {return ptr()[idx];}
    inline const auto& operator[](NODE_T idx) const
        {return ptr()[idx];}
    
    template<typename _T, typename _F, int _s>
    friend std::ostream& operator<<(std::ostream& os,
                                    const Base1dContainer<_T, _F, _s>& container);
    
protected:

    NODE_T _numberOfNodes;
    std::string containerName;
    std::vector<std::string> dataNames;
    typeSelector<NUM_T, INTERFACE_T, Dimensions, Size> data;
};

//MARK: Base1dContainerImpl Class
template<typename NUM_T, typename INTERFACE_T, int size = 0>
class Base1dContainerImpl : public Base1dContainer<NUM_T, INTERFACE_T, size>
{
public:
    Base1dContainerImpl(NODE_T _N, std::vector<std::string> _name,
                        unsigned char _fields = 1)
    : Base1dContainer<NUM_T, INTERFACE_T, size>(_N, _name, _fields) {};
    
    inline NUM_T * ptr() override
        {return static_cast<NUM_T*>(this->data.data());}
    inline NUM_T const * ptr() const override
        {return static_cast<NUM_T const *>(this->data.data());}
};

#endif /* BaseContainer_h */
