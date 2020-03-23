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
template<typename NUM_T, typename INTERFACE_T,  int Size = 0, int Dimensions = 1>
class BaseContainer
{
constexpr static InterfaceRequirement<INTERFACE_T, arrSize> check{};
    
public:
    
    //MARK: Initializers
    BaseContainer(NODE_T numberOfNodes, std::string containerName,
                    std::vector<std::string> dataNames)
    : _numberOfNodes(_N)
    , _containerName(containerName)
    , _dataNames({_name}) {};
    
    
//    template< class T = INTERFACE_T, std::enable_if_t<isARRAY<T>, int> = 0>
//    Base1dContainer(NODE_T numberOfNodes, std::string containerName, std::vector<std::string> dataNames)
//    : _numberOfNodes(_N)
//    , _containerName(containerName)
//    , _dataNames({_name}) {};
    
    template< class T = INTERFACE_T, std::enable_if_t<isVECTOR<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes, std::string containerName,
                  std::vector<std::string> dataNames)
    : BaseContainer(numberOfNodes, containerName, dataNames)
    , data(_N){};
    
    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes, std::string containerName,
                  std::vector<std::string> dataNames)
    : BaseContainer(numberOfNodes, containerName, dataNames)
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
    

    //MARK: Getters
    inline NODE_T size() const {return _numberOfNodes;}
 
    //MARK: Setters
    inline virtual void resize(NODE_T newNumberOfNodes)
        {_numberOfNodes = newNumberOfNodes;}
    
    inline unsigned char const getFields() const {return fields;}
    
    inline auto& operator[](NODE_T idx) {return ptr()[idx];}
    inline auto const& operator[](NODE_T idx) const
        {return ptr()[idx];}
    
    template<typename... _Types>
    friend std::ostream& operator<<(std::ostream& os,
                                    const BaseContainer<_Types...>& container);
    
protected:

    NODE_T _numberOfNodes;
    std::string _containerName;
    std::vector<std::string> _dataNames;
    typeSelector<NUM_T, INTERFACE_T, Dimensions, Size> _data;
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
    : Base1dContainer<NUM_T, OPENCV>(_N, _name, _fields){};
    
    inline NUM_T * ptr() override
        {return this->data.template ptr<NUM_T>(0);}
    inline NUM_T const * ptr() const override
        {return this->data.template ptr<const NUM_T>(0);}
};

#endif /* BaseContainer_h */
