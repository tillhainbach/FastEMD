//
//  main.cpp
//  test
//
//  Created by Till Hainbach on 07.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#include <iostream>
//#include <type_traits>
#include <vector>
#include <array>
//#include <typeinfo>
#include "utils/types.h"
#include "Vertex.hpp"


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
    virtual inline NUM_T* ptr() = 0;
    virtual inline NUM_T const * ptr() const = 0;
    
    inline auto begin(){return data.begin();}
    inline auto end(){return data.begin() + data.size();}
    
    inline const auto size() const {return _num_nodes;}
    inline auto resize(NODE_T _newSize){_num_nodes = _newSize;}
    
    template< class T = INTERFACE_T, std::enable_if_t<!isOPENCV<T>, int> = 0>
    inline auto& operator[](NODE_T idx){return data[idx];}
    
    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
    inline auto operator[](NODE_T idx){return data[idx];}
    
    template< class T = INTERFACE_T, std::enable_if_t<!isOPENCV<T>, int> = 0>
    inline const auto& operator[](NODE_T idx) const
        {return ptr()[idx];}
    
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
    
    
    inline NUM_T* ptr() override
        {return static_cast<NUM_T*>(this->data.data());}
    inline NUM_T const * ptr() const override
        {return static_cast<NUM_T const *>(this->data.data());}
};

template<typename NUM_T>
class Base1dContainer2Impl<NUM_T, OPENCV>: public Base1dContainer2<NUM_T, OPENCV>
{
public:
    Base1dContainer2Impl(NODE_T _N) : Base1dContainer2<NUM_T, OPENCV>(_N){};
    
    inline NUM_T * ptr() override
        {return this->data.template ptr<NUM_T>(0);}
    inline NUM_T const * ptr() const override
        {return this->data.template ptr<const NUM_T>(0);}
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
    Counter2<int, OPENCV> dat1(4);
    dat1[0][0] *= -1;
    std::cout << dat1 << std::endl;
    
    Counter2<int, OPENCV> dat(4);
    dat.makeDiagonal(dat1, 4);
    
    std::cout << dat << std::endl;
    
    Cost<int, OPENCV> cost(4);
    int* p = cost.row(0);
    for (int i = 0; i < cost.rows() * cost.rows() * cost.getFields(); ++i)
        *p++ = i;

    std::cout << cost << std::endl;
    
    Counter<int, OPENCV, 0> count(4);
    count[0] = 9;
    
    Counter<int, ARRAY, 4> myCounter(4);
    myCounter[0] = 9;
    
    
    ForwardCost<int, OPENCV> flow(4);

    flow.fill(cost, count);
    std::cout << flow << std::endl;
    
    
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
    
    auto it = dat[0];
    std::cout << typeid(it).name() << std::endl;
    return 0;
}
