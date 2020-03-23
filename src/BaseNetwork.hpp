//
//  BaseNetwork.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef BaseNetwork_h
#define BaseNetwork_h
#include "VertexBaseContainer.hpp"

//MARK: Vertex Base Class
template<typename... _Types, >
class BaseNetwork : public VertexBaseContainer<_Types..., 2>
{
    
protected:
    inline void reduceCostCore(
            NUM_T* thisFrom,
            const NODE_T from,
            const NODE_T i,
            const Counter<NUM_T, INTERFACE_T, _size>& d,
            const Counter<bool, INTERFACE_T, _size>& finalNodesFlg,
            const NODE_T l);
    
public:
    
    // MARK: public member functions
    template<typename... Args>
    void fill(const Vertex_Base& input, Args&&... args);
    
    template <class F>
    void forEach(F&& func);
    
    template <class F>
    void forEach(F&& func) const;
   
    // break condition for inner loop
    inline bool breakCondition(NODE_T rowIndex, NODE_T colIndex) const
        {return ((rowIndex < _artificialNodeIndex && colIndex == _artificialNodeIndex) ||
                (rowIndex == _artificialNodeIndex && colIndex == _thresholdNodeIndex));}
    
    // returns an iterator to "value" in row "node"
    inline auto findIndex(NODE_T node, NODE_T value);

   
    //MARK: operator overloading
    
//    // std::array + std::vector need be return as reference.
//    template< class T = INTERFACE_T, std::enable_if_t<!isOPENCV<T>, int> = 0>
//    inline auto& operator[](NODE_T idx) {return matrix[idx]; }
//
//    // opencv operator[] returns NUM_T * !!
//    template< class T = INTERFACE_T, std::enable_if_t<isOPENCV<T>, int> = 0>
//    inline auto operator[](NODE_T idx) {return matrix[idx]; }
//
//    template<typename _T, typename _F, int _s>
//    friend std::ostream& operator<<(std::ostream& os,
//                            const Vertex_Base<_T, _F, _s>& vertex);
    
private:
    inline virtual void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, _size>& counters) = 0;
};
#endif /* BaseNetwork_h */
