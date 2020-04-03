//
//  Distance.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef Distance_h
#define Distance_h

#include "VertexBaseContainer.hpp"


namespace FastEMD
{
using namespace types;

//TODO: let Distance be a child of BaseNetwork.
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0>
class Distance : public VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, 2>
{
public:
    Distance(NODE_T numberOfNodes)
    : VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, 2>(numberOfNodes,
                                                       "Distance",
                                                       {"to", "distance"})
    , _nodesToQ(numberOfNodes, "nodes to Q") {};
    
    Distance(std::vector<NUM_T> _data)
    : VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, 2>(_data,
                                                    "Distance",
                                                    {"to", "distance"})
    , _nodesToQ(this->_numberOfNodes, "nodes to Q") {};
    
    template<typename _T, typename _I, NODE_T _S>
    friend std::ostream& operator<<(std::ostream& os,
                                   const Distance<_T, _I, _S>& container);
    
    inline void heapDecreaseKey(NODE_T v, NUM_T alt);
            
    inline void heapRemoveFirst();
    
    inline virtual void resize(NODE_T newNumberOfNodes) override;
    
    inline bool check(NODE_T v, NUM_T alt);
    
    inline void fill(NODE_T from, NODE_T numberOfNodes);
    
    void log() {std::cout << (*this) << std::endl;}
    
    Counter<NODE_T, INTERFACE_T, SIZE> _nodesToQ;

private:
    inline auto& to(NODE_T node) {return (*this)[node * this->fields()];}
    
    inline auto& distance(NODE_T node) {return (*this)[node * this->fields() + 1];}
    
    inline auto const & to(NODE_T node) const
        {return (*this)[node * this->fields()];}
    
    inline auto const & distance(NODE_T node) const
        {return (*this)[node * this->fields() + 1];}
    
    inline void heapify(NODE_T i);
        
    inline void swapHeap(NODE_T i, NODE_T j);
    
    inline NODE_T LEFT(NODE_T i) {return 2 * (i + 1) - 1;}

    inline NODE_T RIGHT(NODE_T i) {return 2 * (i + 1);}

    inline NODE_T PARENT(NODE_T i) {return (i - 1) / 2;}
    
  
};

//MARK: Implementations
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE> inline
void Distance<NUM_T, INTERFACE_T, SIZE>::fill(NODE_T from, NODE_T numberOfNodes)
{
    // Making heap (all inf except 0, so we are saving
    // comparisons...)
    this->resize(numberOfNodes);

    (*this)[0] = from;
    (*this)[1] = 0;

    _nodesToQ[from] = 0;
    NODE_T j = 1;
    for (NODE_T i = 0; i < from; ++i, ++j)
    {
        _nodesToQ[i] = j;
        to(j) = i;
        distance(j) = std::numeric_limits<NUM_T>::max();
    }

    for (NODE_T i = from + 1; i < this->size(); ++i, ++j)
    {
        _nodesToQ[i] = j;
        to(j) = i;
        distance(j) = std::numeric_limits<NUM_T>::max();
    }

}

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE> inline
bool Distance<NUM_T, INTERFACE_T, SIZE>::check(NODE_T v, NUM_T alt)
{
    NODE_T node = _nodesToQ[v];
    return (node < this->size() && alt < distance(node));
}

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
void Distance<NUM_T, INTERFACE_T, SIZE>::resize(NODE_T newNumberOfNodes)
{
    VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, 2>::resize(newNumberOfNodes);
    _nodesToQ.resize(newNumberOfNodes);
}


// Heap Decrease Key
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE> inline
void Distance<NUM_T, INTERFACE_T, SIZE>::heapDecreaseKey(NODE_T v, NUM_T alt)
{
    NODE_T i = _nodesToQ[v];
    distance(i) = alt;
    while (i > 0 && distance(PARENT(i)) > distance(i))
    {
        swapHeap(i, PARENT(i));
        i = PARENT(i);
    }
} // heap_decrease_key

// Heap Remove Frist
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE> inline
void Distance<NUM_T, INTERFACE_T, SIZE>::heapRemoveFirst()
{
    this->_numberOfNodes -= 1;
    swapHeap(0, this->size());
    heapify(0);
} // heap_remove_first

// Heapify
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE> inline
void Distance<NUM_T, INTERFACE_T, SIZE>::heapify(NODE_T i)
{
    assert(i % this->fields() == 0);
    NODE_T size = this->size();
    do {
        // TODO: change to loop
        NODE_T l = LEFT(i);
        NODE_T r = RIGHT(i);
        NODE_T smallest;
        if ( (l < size) && (distance(l) < distance(i)) )
        {
            smallest = l;
        }
        else
        {
            smallest = i;
        }
        if ( (r < size) && (distance(r) < distance(smallest)) )
        {
            smallest = r;
        }
        if (smallest == i) return;
        swapHeap(i, smallest);
        i = smallest;
    } while (true);
    
} // end heapify

// Swap Heap
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE> inline
void Distance<NUM_T, INTERFACE_T, SIZE>::swapHeap(NODE_T i, NODE_T j)
{
    std::swap(to(i), to(j));
    std::swap(distance(i), distance(j));
    _nodesToQ[ to(j) ] = j;
    _nodesToQ[ to(i) ] = i;
} // swapHeapify

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
std::ostream& operator<<(std::ostream& os,
                        const Distance<NUM_T, INTERFACE_T, SIZE>& container)
{
    os << container._nodesToQ << std::endl;
    // Print the container name.
    os << container._containerName << ": ";
    // Print one line describing the containing data.
    os << "vertex: [";
    for (auto& dataName : container._dataNames)
    {
        os << dataName;
        if (&dataName != &container._dataNames.back()) os << " : ";
    }
    os << "]" << std::endl;
    
    // Now, print the actual data.
    for(uint counter = 0; counter < container.size(); ++counter)
    {
        os << "[" << container.to(counter) << " : ";
        NUM_T dist = container.distance(counter);
        if (dist == std::numeric_limits<NUM_T>::max()) os << "INF";
        else os << dist;
        os << "] ";
    }
    return os;
}
} // namespace FastEMD
#endif /* Distance_h */
