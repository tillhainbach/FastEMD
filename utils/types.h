//
//  types.h
//  FastEMD
//
//  Created by Till Hainbach on 10.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef types_h
#define types_h

#include <opencv2/core.hpp>
#include "cvMatSingleRow.h"
namespace FastEMD
{
namespace types
{

enum class INTERFACE_TYPE_T
{
    OPENCV,
    ARRAY,
    VECTOR
};

//------------------------------------------------------------------------------
// Should be integral and 0 should convert automatically to the type
// Did not check if can be changed to other types.
typedef int NODE_T;
//------------------------------------------------------------------------------

struct UNKNOWN {}; // used to test against in static_assert()

using OPENCV = std::integral_constant<INTERFACE_TYPE_T, INTERFACE_TYPE_T::OPENCV>;
using VECTOR = std::integral_constant<INTERFACE_TYPE_T, INTERFACE_TYPE_T::VECTOR>;
using ARRAY = std::integral_constant<INTERFACE_TYPE_T, INTERFACE_TYPE_T::ARRAY>;

template<typename NUM_T, uint SIZE>
using array1d = std::array<NUM_T, SIZE>;

template<typename NUM_T, uint SIZE, uchar FIELDS>
using array2d = std::array< array1d<NUM_T, SIZE * FIELDS>, SIZE>;

template<typename NUM_T>
using vector1d = std::vector<NUM_T>;

template<typename NUM_T>
using vector2d = std::vector< vector1d<NUM_T> >;

template<typename NUM_T>
using cvType = typename cv::traits::Type<NUM_T>::value;

template<typename INTERFACE_T>
inline constexpr bool isOPENCV = std::is_same_v<INTERFACE_T, OPENCV>;

template<typename INTERFACE_T>
inline constexpr bool isARRAY = std::is_same_v<INTERFACE_T, ARRAY>;

template<typename INTERFACE_T>
inline constexpr bool isVECTOR = std::is_same_v<INTERFACE_T, VECTOR>;

template<typename INTERFACE_T>
inline constexpr bool isUNKNOWN = std::is_same_v<INTERFACE_T, UNKNOWN>;

template< typename _INT, typename _A, typename _V, typename _C>
using typeSelectorStructure = typename std::conditional<isARRAY<_INT>, _A,
                        typename std::conditional< isVECTOR< _INT>, _V,
                            typename std::conditional<isOPENCV< _INT>, _C, UNKNOWN
                                >::type
                            >::type
                        >::type;

template< typename NUM_T, typename _INT, uint SIZE, uchar FIELDS = 1>
using typeSelector1d = typeSelectorStructure< _INT, array1d< NUM_T, SIZE * FIELDS >, vector1d <NUM_T>, utils::cvMatSingleRow>;

template<typename NUM_T, typename _INT, uint SIZE, uchar FIELDS = 1 >
using typeSelector2d = typeSelectorStructure< _INT, array2d< NUM_T, SIZE, FIELDS >, vector2d <NUM_T>, cv::Mat1i>;

template< typename NUM_T, typename _INT, int Dimensions, uint SIZE = 0, uchar FIELDS = 1>
using typeSelector = typename std::conditional<Dimensions == 1,
                            typeSelector1d<NUM_T, _INT, SIZE, FIELDS>,
                        typename std::conditional<Dimensions == 2,
                            typeSelector2d<NUM_T, _INT, SIZE, FIELDS>, UNKNOWN>
                            ::type>
                        ::type;

template<typename INTERFACE_T, uint SIZE>
struct InterfaceRequirement
{
    static_assert(!(isUNKNOWN<INTERFACE_T>),
                  "Unkwnown Interface selected! Must be of type OPENCV, VECTOR or ARRAY!");
    
    static_assert(!(isARRAY<INTERFACE_T> && SIZE == 0),
                  "SIZE must be greater than 0 if ARRAY-Interface is choosen");
};

}

} //types //FastEMD
#endif /* types_h */
