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

//MARK: BaseContainer
template<typename NUM_T, typename INTERFACE_T, int Size = 0, int Dimensions = 1>
class BaseContainer
{
constexpr static InterfaceRequirement<INTERFACE_T, Size> check{};
    
public:
    
    //MARK: Initializers
    template< class T = INTERFACE_T, std::enable_if_t<isARRAY<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes, std::string containerName,
                    std::vector<std::string> dataNames)
    : _numberOfNodes(numberOfNodes)
    , _containerName(containerName)
    , _dataNames({dataNames}) {};
    
    template< class T = INTERFACE_T, std::enable_if_t<isVECTOR<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes, std::string containerName,
                  std::vector<std::string> dataNames)
    : _numberOfNodes(numberOfNodes)
    , _containerName(containerName)
    , _dataNames({dataNames})
    , data(numberOfNodes){};
    
    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes, std::string containerName,
                  std::vector<std::string> dataNames)
    : _numberOfNodes(numberOfNodes)
    , _containerName(containerName)
    , _dataNames({dataNames})
    , data(1 + ((1 - Dimensions % 2) * (Dimensions - 1)), numberOfNodes){};
        //-> will resolve to 1 if Dimension == 1 or _N if Dimensions == 2
    
    //TODO: check if ptr() is really necessary.
//    virtual inline NUM_T * ptr() = 0;
//    virtual inline NUM_T const * ptr() const = 0;
    
    //MARK: Iterators
    template<int T = Dimensions, std::enable_if_t<T == 1, int> = 0>
    inline auto begin() {return data.begin();}
    template<int T = Dimensions, std::enable_if_t<T == 1, int> = 0>
    inline auto begin() const {return data.begin();}
    template<int T = Dimensions, std::enable_if_t<T == 1, int> = 0>
    inline auto end() {return data.begin() + _numberOfNodes;}
    template<int T = Dimensions, std::enable_if_t<T == 1, int> = 0>
    inline auto end() const {return data.begin() + _numberOfNodes;}
    
    template<int T = Dimensions, std::enable_if_t<T == 2 &&
    isOPENCV<INTERFACE_T>, int> = 0>
    inline auto begin() {return CVMatRowIterator(data);}
        template<int T = Dimensions, std::enable_if_t<T == 2 &&
    isOPENCV<INTERFACE_T>, int> = 0>
    inline auto begin() const {return CVMatRowIterator(data);}
        template<int T = Dimensions, std::enable_if_t<T == 2 &&
    isOPENCV<INTERFACE_T>, int> = 0>
    inline auto end() {return CVMatRowIterator(data, _numberOfNodes);}
        template<int T = Dimensions, std::enable_if_t<T == 2 &&
    isOPENCV<INTERFACE_T>, int> = 0>
    inline auto end() const {return CVMatRowIterator(data, _numberOfNodes);}
    

    //MARK: Getters
    inline NODE_T size() const {return _numberOfNodes;}
 
    //MARK: Setters
    inline virtual void resize(NODE_T newNumberOfNodes)
        {_numberOfNodes = newNumberOfNodes;}
    
    //MARK: Operator Overloading
    template< class T = INTERFACE_T, std::enable_if_t<!isOPENCV<T>, int> = 0>
    inline auto& operator[](NODE_T idx){return data[idx];}
    
    template< class T = INTERFACE_T, std::enable_if_t<!isOPENCV<T>, int> = 0>
    inline auto& operator[](NODE_T idx) const
     {return data[idx];}

    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    inline auto operator[](NODE_T idx){return data[idx];}

    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    inline const auto operator[](NODE_T idx)const
     {return data[idx];}

    //MARK: Attributes
protected:

    NODE_T _numberOfNodes;
    std::string _containerName;
    std::vector<std::string> _dataNames;
    typeSelector<NUM_T, INTERFACE_T, Dimensions, Size> data;
};

//MARK: Base1dContainerImpl Class
template<typename NUM_T, typename INTERFACE_T, int size = 0>
class BaseContainerImpl : public BaseContainer<NUM_T, INTERFACE_T, size>
{
public:
    BaseContainerImpl(NODE_T _N, std::vector<std::string> _name,
                        unsigned char _fields = 1)
    : BaseContainer<NUM_T, INTERFACE_T, size>(_N, _name, _fields) {};

    inline NUM_T * ptr() override
        {return static_cast<NUM_T*>(this->data.data());}
    inline NUM_T const * ptr() const override
        {return static_cast<NUM_T const *>(this->data.data());}
};

template<typename NUM_T>
class BaseContainerImpl<NUM_T, OPENCV>: public BaseContainer<NUM_T, OPENCV>
{
public:
    BaseContainerImpl(NODE_T _N, std::vector<std::string> _name,
                        unsigned char _fields = 1)
    : BaseContainer<NUM_T, OPENCV>(_N, _name, _fields){};

    inline NUM_T * ptr() override
        {return this->data.template ptr<NUM_T>(0);}
    inline NUM_T const * ptr() const override
        {return this->data.template ptr<const NUM_T>(0);}
};




#endif /* BaseContainer_h */
