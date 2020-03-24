//
//  code snippets.h
//  FastEMD
//
//  Created by Till Hainbach on 24.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef code_snippets_h
#define code_snippets_h
//template<typename NUM_T, typename INTERFACE_T, int arrSize = 0>
//class TestContainer : BaseContainer<NUM_T, INTERFACE_T, arrSize>
//{
//constexpr static InterfaceRequirement<INTERFACE_T, arrSize> check{};
//
//protected:
//    inline virtual void fill(NODE_T r, NODE_T c, NUM_T i, NUM_T d) = 0;
//
//public:
//
////
////
////
////    template<class F>
////    void doit(F&& func)
////    {
////        for (int r = 0; r < this->size(); ++r)
////            for(int c = 0; c < this->size(); ++c)
////            {
////                auto i = (*this)[r][c];
////                func(r, c, i);
////            }
////    }
////
////    template<class F>
////    void doit(F&& func) const
////    {
////        for (int r = 0; r < this->size(); ++r)
////            for(int c = 0; c < this->size(); ++c)
////            {
////                     auto i = (*this)[r][c];
////                     func(r, c, i);
////            }
////    }
////
////    template<typename... Args>
////    void makeDiagonal(const Base1dContainer2& input, Args&&... args)
////    {
////        auto f = std::bind(&Base1dContainer2::fill,
////                           this, std::placeholders::_1,
////                           std::placeholders::_2,
////                           std::placeholders::_3,
////                           std::forward<Args>(args)...);
////        return input.doit(f);
////    }
////
////    void make(int i)
////    {
////        auto f = std::bind(&Base1dContainer2<NUM_T, INTERFACE_T,size>::fill,
////                           this, std::placeholders::_1,
////                           std::placeholders::_2, 6);
////        return doit(f);
////    }
//
//
////protected:
//
//    NODE_T _num_nodes;
//    typeSelector2d<NUM_T, INTERFACE_T, arrSize> data;
//};
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

template<typename... _T>
class TestCounter : public Counter2<_T..., 2>
{
public:
    TestCounter() : Counter2<_T..., 2>(1){};
    
    void sayHello(std::string name) {std::cout << "Hello " << name << "!" << std::endl;}
};



#endif /* code_snippets_h */
