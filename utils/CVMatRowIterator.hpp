//
//  CVMatRowIterator.hpp
//  FastEMD
//
//  Created by Till Hainbach on 24.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef CVMatRowIterator_h
#define CVMatRowIterator_h
#include <opencv2/core.hpp>
#include "cvMatSingleRow.h"

namespace FastEMD
{
namespace utils
{

///@brief thin wrapper that holds a reference to an cv::Mat-object. Gets called by begin() or end().
///  It can be incremented to be used in c++ range-for. This Wrapper is supposed to mimic the behaviour when
///  looping over a vector of vectors (or array of arrays).
template<typename _T>
class CVMatRowIterator
{
public:
    
    CVMatRowIterator(cv::Mat_<_T>& mat, int row = 0)
    : _cvMat(mat)
    , currentRow(_cvMat.row(0))
    , _row(row) {};
    
    CVMatRowIterator(cv::Mat_<_T> const& mat, int row = 0)
    : _cvMat(mat)
    , currentRow(_cvMat.row(0))
    , _row(row) {};
    
    CVMatRowIterator& operator++();
    CVMatRowIterator& operator++(int);
    CVMatRowIterator& operator--();
    CVMatRowIterator& operator--(int);
    CVMatRowIterator& operator+(int idx);
    CVMatRowIterator& operator-(int idx);
    
    cvMatSingleRow& operator*(){currentRow = _cvMat.row(_row); return currentRow;}
    
    cvMatSingleRow* operator->(){return &currentRow;}
    
    ///@brief overloaded equality operator==(). It checks whether the row counters are equal while
    /// referenceing the same cv::Mat-Instance.
    template<typename _C>
    friend bool operator==(CVMatRowIterator<_C> const & lhs,
                           CVMatRowIterator<_C> const & rhs);
    
    ///@brief overloaded "not-equal" operator!=(). It checks whether the row counters are not equal while
    /// referenceing the same cv::Mat-Instance.
    template<typename _C>
    friend bool operator!=(CVMatRowIterator<_C> const & lhs,
                           CVMatRowIterator<_C> const & rhs);

  
private:
    cv::Mat_<_T> const& _cvMat;
    cvMatSingleRow currentRow; // cache for the currentRow Header
    int _row;
    
};

//MARK: Implementations
template<typename _T>
CVMatRowIterator<_T>& CVMatRowIterator<_T>::operator++()
{
    _row++;
    return *this;
}

template<typename _T>
CVMatRowIterator<_T>& CVMatRowIterator<_T>::operator++(int)
{
    CVMatRowIterator temp = *this;
    ++*this;
    return temp;
}

template<typename _T>
CVMatRowIterator<_T>& CVMatRowIterator<_T>::operator--()
{
    _row--;
    return *this;
}

template<typename _T>
CVMatRowIterator<_T>& CVMatRowIterator<_T>::operator--(int)
{
    CVMatRowIterator temp = *this;
    --*this;
    return temp;
}

template<typename _T>
CVMatRowIterator<_T>& CVMatRowIterator<_T>::operator+(int idx)
{
    _row += idx;
    return *this;
}

template<typename _T>
CVMatRowIterator<_T>& CVMatRowIterator<_T>::operator-(int idx)
{
    _row -= idx;
    return *this;
}

template<typename _T>
inline bool operator==(CVMatRowIterator<_T> const & lhs,
                       CVMatRowIterator<_T> const & rhs)
{
    return lhs._row == rhs._row && &lhs._cvMat == &rhs._cvMat;
}
    
template<typename _T>
inline bool operator!=(CVMatRowIterator<_T> const & lhs,
                       CVMatRowIterator<_T> const & rhs)
{
    return !(lhs==rhs);
}


}} // utils //FastEMD



#endif /* CVMatRowIterator_h */
