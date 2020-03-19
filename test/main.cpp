//
//  main.cpp
//  test
//
//  Created by Till Hainbach on 07.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#include <iostream>
#include <vector>
#include <array>
#include "utils/types.h"
//#include "Vertex.hpp"

typedef int NODE_T;

template<typename NUM_T, typename INTERFACE_T, int arrSize = 0>
class Base1dContainer2
{
constexpr static InterfaceRequirement<INTERFACE_T, arrSize> check{};
   
protected:
    inline virtual void fill(NODE_T r, NODE_T c, NUM_T i, NUM_T d) = 0;
    
public:
    template< class T = INTERFACE_T, std::enable_if_t<isARRAY<T>, int> = 0>
    Base1dContainer2(NODE_T _N) : _num_nodes(_N) {};
    
    template< class T = INTERFACE_T, std::enable_if_t<isVECTOR<T>, int> = 0>
    Base1dContainer2(NODE_T _N)
    : _num_nodes(_N)
    , data(_N, std::vector<NUM_T>(_N, -1)) {};
    
    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    Base1dContainer2(NODE_T _N)
    : _num_nodes(_N)
    , data(_N, _N, -1) {};

    //TODO: check if ptr() is really necessary.
//    virtual inline NUM_T* ptr() = 0;
//    virtual inline NUM_T const * ptr() const = 0;
    

    
    inline const auto size() const {return _num_nodes;}
    inline auto resize(NODE_T _newSize){_num_nodes = _newSize;}
    
    template< class T = INTERFACE_T, std::enable_if_t<!isOPENCV<T>, int> = 0>
    inline auto& operator[](NODE_T idx){return data[idx];}
    
    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    inline auto operator[](NODE_T idx){return data[idx];}
    
    template< class T = INTERFACE_T, std::enable_if_t<!isOPENCV<T>, int> = 0>
    inline const auto& operator[](NODE_T idx) const
        {return data[idx];}
    
    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    inline const auto operator[](NODE_T idx)const
        {return data[idx];}
    
    template<typename _T, typename _F, int _s>
    friend std::ostream& operator<<(std::ostream& os,
                               const Base1dContainer2<_T, _F, _s>& counter);


    
    template<class F>
    void doit(F&& func)
    {
        for (int r = 0; r < this->size(); ++r)
            for(int c = 0; c < this->size(); ++c)
            {
                auto i = (*this)[r][c];
                func(r, c, i);
            }
    }
    
    template<class F>
    void doit(F&& func) const
    {
        for (int r = 0; r < this->size(); ++r)
            for(int c = 0; c < this->size(); ++c)
            {
                     auto i = (*this)[r][c];
                     func(r, c, i);
            }
    }
    
    template<typename... Args>
    void makeDiagonal(const Base1dContainer2& input, Args&&... args)
    {
        auto f = std::bind(&Base1dContainer2::fill,
                           this, std::placeholders::_1,
                           std::placeholders::_2,
                           std::placeholders::_3,
                           std::forward<Args>(args)...);
        return input.doit(f);
    }

    void make(int i)
    {
        auto f = std::bind(&Base1dContainer2<NUM_T, INTERFACE_T,size>::fill,
                           this, std::placeholders::_1,
                           std::placeholders::_2, 6);
        return doit(f);
    }
    
            
//protected:

    NODE_T _num_nodes;
    typeSelector2d<NUM_T, INTERFACE_T, arrSize> data;
};
// ------------------- VertexWeights Class ----------------------
template<typename NUM_T, typename INTERFACE_T, int size = 0>
class Base1dContainer2Impl : public Base1dContainer2<NUM_T, INTERFACE_T, size>
{
public:
    Base1dContainer2Impl(NODE_T _N) : Base1dContainer2<NUM_T, INTERFACE_T, size>(_N) {};
    
    inline auto begin(){return this->data.begin();}
    inline auto end(){return this->data.begin() + this->_num_nodes;}
    
//    inline NUM_T* ptr() override
//        {return static_cast<NUM_T*>(this->data.data());}
//    inline NUM_T const * ptr() const override
//        {return static_cast<NUM_T const *>(this->data.data());}
};

///@brief thin wrapper that holds a reference to an cv::Mat-object. Gets called by begin() or end().
///  It can be incremented to be used in c++ range-for.
///  @NOTE: The derefenrecing operator*() calls cv::Mat::row() which return a tempory object (It creates a
///  new header for the specified row. Therefore catching by referenc in the for:-loop (e.g. auto& : ) is not
///  supported.
template<typename _T>
class CVMatRowIterator
{
public:
    
    CVMatRowIterator& operator++() {_row++; return *this;}
    
    cv::Mat_<_T> operator*(){return _cvMat.row(_row);}
    bool operator!=(CVMatRowIterator& rhs)
    {return _row != rhs._row && &_cvMat == &(rhs._cvMat);}
    
    CVMatRowIterator(cv::Mat_<_T>& mat, int row = 0)
    : _cvMat(mat)
    , _row(row) {};
    
    
    
//private:
    cv::Mat_<_T>& _cvMat;
    int _row;
    
};

template<typename NUM_T>
class Base1dContainer2Impl<NUM_T, OPENCV>: public Base1dContainer2<NUM_T, OPENCV>
{
public:
    
    
    Base1dContainer2Impl(NODE_T _N) : Base1dContainer2<NUM_T, OPENCV>(_N){};
    
    
    inline auto begin(){return CVMatRowIterator(this->data);}
    inline auto end(){return CVMatRowIterator(this->data, this->_num_nodes);}
//    inline NUM_T * ptr() override
//        {return this->data.template ptr<NUM_T>(0);}
//    inline NUM_T const * ptr() const override
//        {return this->data.template ptr<const NUM_T>(0);}
};
// ---------------------- Counter Class --------------------------



template<typename NUM_T, typename INTERFACE_T, int size = 0>
class Counter2 : public Base1dContainer2Impl<NUM_T, INTERFACE_T, size>
{
public:
    Counter2(NODE_T _N)
    : Base1dContainer2Impl<NUM_T, INTERFACE_T, size>(_N){};

private:
    inline void fill(NODE_T r, NODE_T c, NUM_T i, NUM_T d) override;

};

template<typename NUM_T, typename INTERFACE_T, int size>
inline void Counter2<NUM_T, INTERFACE_T, size>::fill(NODE_T r, NODE_T c, NUM_T i, NUM_T d)
{
    (*this)[r][c] = i + d;
}

template<typename NUM_T, typename INTERFACE_T, int size>
std::ostream& operator<<(std::ostream&os, const Base1dContainer2<NUM_T, INTERFACE_T, size>& counter)
{
    auto n =  counter.size();
    std::cout << "[";
    for (int r = 0; r < n; ++r)
    {
        for(int i = 0; i < n; ++i)
        {
            os << counter[r][i];
            if (i != n - 1) os << ", ";
            else if (r == n - 1 && i == n - 1) os << "]\n";
            else os << ";\n";
        }
    }
    return os;
}

int main(int argc, const char * argv[]) {
    
    
    // insert code here...
    Counter2<int, VECTOR> dat(4);
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            dat[i][j] = i * 4 + j;
    
    std::cout << dat << std::endl;
    
    for(auto row: dat)
        for(auto& element : row)
            element = 0;
 
    std::cout << dat << std::endl;
    
//    Cost<int, OPENCV> cost(4);
//    int* p = cost.row(0);
//    for (int i = 0; i < cost.rows() * cost.rows() * cost.getFields(); ++i)
//        *p++ = i;
//
//    std::cout << cost << std::endl;
//
//    Counter<int, OPENCV, 0> count(4);
//    count[0] = 9;
//
//    Counter<int, ARRAY, 4> myCounter(4);
//    myCounter[0] = 9;
//
//
//    ForwardCost<int, OPENCV> flow(4);
//
//    flow.fill(cost, count);
//    std::cout << flow << std::endl;
//
    
    // bind to a member function
//    Foo<int> foo;
//    auto f3 = std::bind(&Foo<int>::print_sum, &foo, 95, std::placeholders::_1);
//    f3(5);
//    dat.doit(4, std::bind(f3, 5));
    
    
//    std::cout << "[";
//    for(const auto& r: dat.data)
//    {
//        for(const auto& e: r)
//            std::cout<< e <<", ";
//        std::cout << std::endl;
//    }
    return 0;
}
