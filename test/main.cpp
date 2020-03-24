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
#include "Counter.hpp"
#include "CVMatRowIterator.hpp"

typedef int NODE_T;
typedef unsigned char uchar;

template<typename NUM_T, typename INTERFACE_T, int arrSize = 0>
class Base1dContainer2
{
constexpr static InterfaceRequirement<INTERFACE_T, arrSize> check{};
   
protected:
    inline virtual void fill(NODE_T r, NODE_T c, NUM_T i, NUM_T d) {2+2;};
    
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

template<int T, typename std::conditional<T == 2, int, long>::type >
struct test { const int number = T;};

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

template<typename... _C>
class Test : public BaseContainer<_C...>
{
public:
    Test (NODE_T _N)
    : BaseContainer<_C...>(_N, "Tester", {"testResults"}){};
    
    void sayHello (std::string name)
    {
        std::cout << "Hello " << name << "!" << std::endl;
    }

};

template<typename NUM_T, typename... _T>
class Counter2 : public Base1dContainer2Impl<NUM_T, _T...>
{
public:
    Counter2(NODE_T _N)
    : Base1dContainer2Impl<NUM_T, _T...>(_N){};

private:
    inline void fill(NODE_T r, NODE_T c, NUM_T i, NUM_T d) override;

};

template<typename NUM_T, typename... _T>
inline void Counter2<NUM_T, _T...>::fill(NODE_T r, NODE_T c, NUM_T i, NUM_T d)
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
    
template< typename NUM_T, int dimensions = 1>
class Tester
{
    int n;
public:
    template<int T = dimensions, std::enable_if_t<T == 1 &&
    std::is_same_v<NUM_T, int>, int> = 0>
    inline int foo(){ return 1;};
    
    template<int T = dimensions, std::enable_if_t<T == 2 &&
                                    std::is_same_v<NUM_T, int>, int> = 0>
    inline int foo(){ return 2;};
    
};
    

int main(int argc, const char * argv[]) {
    
//    cv::Mat1i testMat(2,2, -1);
//    std::cout << testMat << std::endl;
    
    Counter<int, OPENCV> testCounter(4);
    std::cout << testCounter << std::endl;
    Test<int, VECTOR> tester(4);
    
    Counter2<int, OPENCV> dat(4);
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            dat[i][j] = i * 4 + j;
    
    std::cout << dat << std::endl;
    
    Tester<int> T;
    std::cout << T.foo() << std::endl;
    
    for(auto& row: dat)
        for(auto& element : row)
            element = 0;
    
    std::cout << dat << std::endl;
    
    return 0;
}
