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
#include "utils/types.h"
#include <type_traits>
#include <typeinfo>
#include "utils/CVMatRowIterator.hpp"

namespace FastEMD
{
using namespace types;
using namespace utils;

//MARK: BaseContainer
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0, uchar DIMENSIONS = 1>
class BaseContainer
{
constexpr static InterfaceRequirement<INTERFACE_T, SIZE> check{};
    
public:
    
    //MARK: Initializers
    template< class T = INTERFACE_T, std::enable_if_t<isARRAY<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes, std::string containerName,
                    std::vector<std::string> dataNames)
    : _numberOfNodes(numberOfNodes)
    , _containerName(containerName)
    , _dataNames({dataNames}) {};
    
    template< class T = INTERFACE_T, std::enable_if_t<DIMENSIONS == 1 && isVECTOR<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes, std::string containerName,
                  std::vector<std::string> dataNames)
    : _numberOfNodes(numberOfNodes)
    , _containerName(containerName)
    , _dataNames({dataNames})
    , data(numberOfNodes){};
    
    template< class T = INTERFACE_T, std::enable_if_t<DIMENSIONS != 1 && isVECTOR<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes, std::string containerName,
                  std::vector<std::string> dataNames)
    : _numberOfNodes(numberOfNodes)
    , _containerName(containerName)
    , _dataNames({dataNames})
    , data(numberOfNodes, std::vector<NUM_T>(numberOfNodes * DIMENSIONS)){};
    
    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes, std::string containerName,
                  std::vector<std::string> dataNames)
    : _numberOfNodes(numberOfNodes)
    , _containerName(containerName)
    , _dataNames({dataNames})
    , data(1 + ((1 - DIMENSIONS % 2) * (numberOfNodes - 1)), numberOfNodes){};
        //-> will resolve to 1 if Dimension == 1 or _N if DIMENSIONS == 2
    
    //TODO: check if ptr() is really necessary.
//    virtual inline NUM_T * ptr() = 0;
//    virtual inline NUM_T const * ptr() const = 0;
    
    //MARK: Iterators
    template<uchar T = DIMENSIONS, std::enable_if_t<!(T == 2 &&
    isOPENCV<INTERFACE_T>), uchar> = 0>
    inline auto begin() {return data.begin();}
    template<uchar T = DIMENSIONS, std::enable_if_t<!(T == 2 &&
    isOPENCV<INTERFACE_T>), uchar> = 0>
    inline auto begin() const {return data.begin();}
    template<uchar T = DIMENSIONS, std::enable_if_t<!(T == 2 &&
    isOPENCV<INTERFACE_T>), uchar> = 0>
    inline auto end() {return data.begin() + _numberOfNodes;}
    template<uchar T = DIMENSIONS, std::enable_if_t<!(T == 2 &&
    isOPENCV<INTERFACE_T>), uchar> = 0>
    inline auto end() const {return data.begin() + _numberOfNodes;}
    
    template<uchar T = DIMENSIONS, std::enable_if_t<T == 2 &&
    isOPENCV<INTERFACE_T>, uchar> = 0>
    inline auto begin() {return CVMatRowIterator(data);}
        template<uchar T = DIMENSIONS, std::enable_if_t<T == 2 &&
    isOPENCV<INTERFACE_T>, uchar> = 0>
    inline auto begin() const {return CVMatRowIterator(data);}
        template<uchar T = DIMENSIONS, std::enable_if_t<T == 2 &&
    isOPENCV<INTERFACE_T>, uchar> = 0>
    inline auto end() {return CVMatRowIterator(data, _numberOfNodes);}
        template<uchar T = DIMENSIONS, std::enable_if_t<T == 2 &&
    isOPENCV<INTERFACE_T>, uchar> = 0>
    inline auto end() const {return CVMatRowIterator(data, _numberOfNodes);}
    

    //MARK: Getters
    inline NODE_T size() const {return _numberOfNodes;}
 
    //MARK: Setters
    inline virtual void resize(NODE_T newNumberOfNodes)
        {_numberOfNodes = newNumberOfNodes;}
    
    //MARK: Operator Overloading
    template< class T = INTERFACE_T, std::enable_if_t<!isOPENCV<T> && !std::is_same_v<NUM_T, bool>, int> = 0>
    inline auto& operator[](NODE_T idx) {return data[idx];}
    
    template< class T = INTERFACE_T, std::enable_if_t<!isOPENCV<T> && !std::is_same_v<NUM_T, bool>, int> = 0>
    inline auto& operator[](NODE_T idx) const {return data[idx];}

    // spezial case for std::vector and NUM_T == bool. I don't fully understand
    // but here this is a workaround
    
    template< class T = INTERFACE_T, std::enable_if_t<isVECTOR<T> && std::is_same_v<NUM_T, bool>, int> = 0>
    inline auto operator[](NODE_T idx) {return data[idx];}
    
    template< class T = INTERFACE_T, std::enable_if_t<isVECTOR<T> && std::is_same_v<NUM_T, bool>, int> = 0>
    inline auto operator[](NODE_T idx) const {return data[idx];}
    


    // cv::Mat_.operator[]() returns a pointer to the elements which for
    // 1-row cv::Mat_ means one has to call the subcript operator twice
    // with first [] being 0 for the first row.
    // In other words, you have say give be a pointer to the first row and then
    // return the n-th object.
    template< class T = INTERFACE_T, std::enable_if_t<DIMENSIONS == 1 && isOPENCV<T>, int> = 0>
    inline auto& operator[](NODE_T idx){return *data[idx];}

    template< class T = INTERFACE_T, std::enable_if_t<DIMENSIONS == 1 && isOPENCV<T>, int> = 0>
    inline auto const & operator[](NODE_T idx)const
     {return *data[idx];}
    
    template< class T = INTERFACE_T, std::enable_if_t<DIMENSIONS == 2 && isOPENCV<T>, int> = 0>
    inline auto operator[](NODE_T idx) {return data[idx];}

    template< class T = INTERFACE_T, std::enable_if_t<DIMENSIONS == 2 && isOPENCV<T>, int> = 0>
    inline auto const operator[](NODE_T idx)const {return data[idx];}

    //MARK: Attributes
//protected:

    NODE_T _numberOfNodes;
    std::string _containerName;
    std::vector<std::string> _dataNames;
    typeSelector<NUM_T, INTERFACE_T, DIMENSIONS, SIZE> data;
};

} //namespace FastEMD


#endif /* BaseContainer_h */
