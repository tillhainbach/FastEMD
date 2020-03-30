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
#include "readImage.hpp"
#include "Distance.hpp"
#include "FlowNetwork.hpp"
#include "ReducedCostsForwardEdgesNetwork.hpp"

typedef int NODE_T;
typedef unsigned char uchar;
using namespace FastEMD;
using namespace types;
using namespace utils;

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
    

    template<typename T = INTERFACE_T, std::enable_if_t<!isOPENCV<T>, int> = 0>
    inline auto fromNode(NODE_T nodeIndex)
        {return this->data.begin() + nodeIndex;}
    template<typename T = INTERFACE_T, std::enable_if_t<!isOPENCV<T>, int> = 0>
    inline auto fromNode(NODE_T nodeIndex) const
        {return this->data.begin() + nodeIndex;}
    
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
 
template<typename NUM_T, typename INTERFACE_T, int size = 0>
class Test2 : public BaseNetwork<NUM_T, INTERFACE_T, size>
{

public:
    Test2 (NODE_T _N)
    : BaseNetwork<NUM_T, INTERFACE_T, size>(_N, "Tester", {"to", "from"}, 2){};

};


int main(int argc, const char * argv[]) {
    
//    cv::Mat1i testMat(2,2, -1);
//    std::cout << testMat << std::endl;
    typeSelector<bool, VECTOR, 1, 0> data(4);
    Counter<bool, VECTOR> testCounter(4);
    std::vector<bool> v(4);
//    v[0] = 1 + 2;
    testCounter[0] = true;
    std::cout << typeid(testCounter.data[0]).name() << std::endl;
    std::cout << typeid(testCounter[0]).name() << std::endl;
    std::cout << testCounter << std::endl;
    std::cout << typeid(v[0]).name() << std::endl;
    
    
    Test<int, VECTOR> tester(4);
    
    Counter2<int, OPENCV> dat(4);
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            dat[i][j] = i * 4 + j;
    
    std::cout << dat << std::endl;
    
    Tester<int> T;
    std::cout << T.foo() << std::endl;
  

//    FlowNetwork<int, VECTOR> network(4);
//    ReducedCostsForwardEdgesNetwork<int, ARRAY, 4> reducedCost(4);
//    std::cout << network << std::endl;
//    auto node = network.thresholdNode();
    
    
    
    for(auto& row: dat)
        for(auto& element : row)
            element = 0;
    
    std::cout << dat << std::endl;
    
    //MARK: Read images
    const char* im1_name= "cameraman.txt";
    const char* im2_name= "rice.txt";
    unsigned int im1_R, im1_C, im2_R, im2_C;
    std::vector<int> im1, im2;
    FastEMD::utils::readImage(im1_name, im1_R, im1_C, im1);
    FastEMD::utils::readImage(im2_name, im2_R, im2_C, im2);
    if ( (im1_R != im2_R) || (im1_C != im2_C) )
    {
        std::cerr << "Images should be of the same size" << std::endl;
    }
    #define N 6
    im1_R = N;
    im1_C = N;
    im2_R = N;
    im2_C = N;
    
    std::vector<int>v1 (im1.begin(), im1.begin() + (N*N));
    std::vector<int>v2(im2.begin(), im2.begin() + (N*N));
    std::stringstream vv;
    for (auto & e: v2)
    {
        vv << e << " ";
    }

    std::string myString("98 95 141 134 102 97 120 181 117 126 150 130 122 98 118 114 102 103 125 113 166 123 97 155 154 148 131 163 109 165 154 104 98 97 102 96 ");
    std::string vString(vv.str());
    std::cout << vString << std::endl;
    std::cout << myString << std::endl;
    std::cout << (myString == vString) << std::endl;
    std::cout << myString.size() << std::endl;
    
    for (int i = 0; i < vString.size(); ++i)
        if(vString[i] != myString[i])
            std::cout << int(vString[i]) << " != " << int(myString[i]) << std::endl;
    
    return 0;
}
