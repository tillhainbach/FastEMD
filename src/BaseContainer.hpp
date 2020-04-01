//
//  BaseContainer.hpp
//  FastEMD
//
//  Created by Till Hainbach on 20.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef BaseContainer_h
#define BaseContainer_h
#include <iostream>
#include "utils/types.h"
#include <type_traits>
#include <typeinfo>
#include "utils/CVMatRowIterator.hpp"

namespace FastEMD
{
using namespace types;
using namespace utils;

//MARK: BaseContainer
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0, uchar FIELDS = 1, uchar DIMENSIONS = 1>
class BaseContainer
{
constexpr static InterfaceRequirement<INTERFACE_T, SIZE> check{};
    
public:
    
    //MARK: Initializers
    template< class T = INTERFACE_T, std::enable_if_t<isARRAY<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes,
                  std::string containerName,
                  std::vector<std::string> dataNames)
    : _numberOfNodes(numberOfNodes)
    , _containerName(containerName)
    , _dataNames({dataNames})
    { assert(numberOfNodes <= SIZE); };
    
    template< uchar T = DIMENSIONS, std::enable_if_t<T == 1, int> = 0>
    BaseContainer(std::vector<NUM_T> _data,
                  std::string containerName,
                  std::vector<std::string> dataNames)
    : BaseContainer(static_cast<NODE_T>(_data.size() / FIELDS),
                    containerName,
                    dataNames)
    {
        assert(_data.size() == _numberOfNodes * FIELDS);
        for(int i = 0; i < _data.size(); ++i)
        {
            data[i] = static_cast<NUM_T>(_data[i]);
        }
    };
    
    template< uchar T = DIMENSIONS, std::enable_if_t<T == 2, int> = 0>
    BaseContainer(std::vector< std::vector<NUM_T> > _data,
                  std::string containerName,
                  std::vector<std::string> dataNames)
    : BaseContainer(static_cast<NODE_T>(_data.size()),
                    containerName,
                    dataNames)
    {
        for(int i = 0; i < _data.size(); ++i)
        {
            assert(_data[i].size() <= _numberOfNodes * FIELDS);
            for(int j = 0; j < _data[i].size(); ++j)
            {
                data[i][j] = static_cast<NUM_T>(_data[i][j]);
            }
        }
    };
    
    // for VECTOR
    template< class T = INTERFACE_T, std::enable_if_t<DIMENSIONS == 1 && isVECTOR<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes,
                  std::string containerName,
                  std::vector<std::string> dataNames)
    : _numberOfNodes(numberOfNodes)
    , _containerName(containerName)
    , _dataNames({dataNames})
    , data(numberOfNodes){};
    
    template< class T = INTERFACE_T, std::enable_if_t<DIMENSIONS != 1 && isVECTOR<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes,
                  std::string containerName,
                  std::vector<std::string> dataNames)
    : _numberOfNodes(numberOfNodes)
    , _containerName(containerName)
    , _dataNames({dataNames})
    , data(numberOfNodes, std::vector<NUM_T>((numberOfNodes - 1) * FIELDS * (2 - (containerName != "Flow Network")))){};
    
    // For OPENCV
    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    BaseContainer(NODE_T numberOfNodes,
                  std::string containerName,
                  std::vector<std::string> dataNames)
    : _numberOfNodes(numberOfNodes)
    , _containerName(containerName)
    , _dataNames({dataNames})
    , data(1 + ((1 - DIMENSIONS % 2) * (numberOfNodes - 1)),
           (numberOfNodes - 1 + DIMENSIONS % 2) * FIELDS * (2 - (containerName != "Flow Network")))
    {};
        //-> will resolve to 1 if Dimension == 1 or _N if DIMENSIONS == 2
    
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
    template< class T = INTERFACE_T,
        std::enable_if_t<isARRAY<T> ||
                        (isVECTOR<T> && !std::is_same_v<NUM_T, bool>) ||
                        (isOPENCV<T> && DIMENSIONS == 1), int> = 0>
    inline auto& operator[](NODE_T idx) {return data[idx];}
    
    template< class T = INTERFACE_T,
    std::enable_if_t<isARRAY<T> ||
                    (isVECTOR<T> && !std::is_same_v<NUM_T, bool>) ||
                    (isOPENCV<T> && DIMENSIONS == 1), int> = 0>
    inline auto& operator[](NODE_T idx) const {return data[idx];}

    // special case for std::vector and NUM_T == bool. I don't fully understand
    // this but here is a workaround:
    template< class T = INTERFACE_T,
        std::enable_if_t<(isVECTOR<T> && std::is_same_v<NUM_T, bool>) ||
                        (isOPENCV<T> && DIMENSIONS == 2), int> = 0>
    inline auto operator[](NODE_T idx) {return data[idx];}
    
    template< class T = INTERFACE_T,
    std::enable_if_t<(isVECTOR<T> && std::is_same_v<NUM_T, bool>) ||
                    (isOPENCV<T> && DIMENSIONS == 2), int> = 0>
    inline auto const operator[](NODE_T idx) const {return data[idx];}
    
    //MARK: Attributes
//protected:

    NODE_T _numberOfNodes;
    static unsigned char const _fields = FIELDS;
    std::string _containerName;
    std::vector<std::string> _dataNames;
    typeSelector<NUM_T, INTERFACE_T, DIMENSIONS, SIZE, FIELDS> data;
};

} //namespace FastEMD


#endif /* BaseContainer_h */
