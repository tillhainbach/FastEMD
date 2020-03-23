//
//  VertexWeights.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef VertexWeights_h
#define VertexWeights_h
#include "VertexBaseContainer.hpp"

//MARK: Vertex Weights Class
template <typename... _Types>
class VertexWeights : public VertexBaseContainer<_Types...>
{
    
public:
    
    //MARK: Initializer
    VertexWeights(NODE_T numberOfNodes)
    :  VertexBaseContainer<NUM_T, INTERFACE_T, size>(numberOfNodes,
                                                     "Vertex Weights",
                                                     {"weight"}, 1) {};

    //MARK: Setters
    template<typename _T>
    std::tuple<NUM_T, NUM_T>
        fillWeights(const _T& P, const _T& Q,  const NODE_T N,
            Counter<NUM_T, INTERFACE_T, size/2>& nonZeroSourceNodes,
            Counter<NUM_T, INTERFACE_T, size/2>& nonZeroSinkNodes);
    
    template<typename _T>
    void preFlowWeights(const _T& P, const _T& Q);
    
    void swapWeights();
    
    //MARK: Getters
    NUM_T calcPreFlowCost(
            Counter<NUM_T, INTERFACE_T, size/2>& sinkNodes,
            Counter<NUM_T, INTERFACE_T, size/2>& uniqueJs,
            NUM_T maxC, NODE_T costSize) const;
        
    auto sum() const {NUM_T sum = 0; for (auto e: *this) sum += e; return sum;}
            
};

//MARK: Implementations
template <typename... _Types>
template<typename _T>
std::tuple<NUM_T, NUM_T> VertexWeights<_Types...>::fillWeights(
                const _T& P, const _T& Q,  const NODE_T N,
                Counter<NUM_T, INTERFACE_T, size/2> & nonZeroSourceNodes,
                Counter<NUM_T, INTERFACE_T, size/2> & nonZeroSinkNodes)
{
    NODE_T nonZeroSourceCounter = 0, nonZeroSinkCounter = 0;
    NUM_T sum_P = 0, sum_Q = 0;
    
    for (NODE_T i = 0; i < N; ++i)
    {
        NUM_T tempSum = P[i] - Q[i];
        switch (static_cast<unsigned char>(tempSum > 0)) // P[i] > Q[i]
        {
            case 0:
                switch (static_cast<unsigned char>(tempSum < 0))
                {
                    case 0: // P[i] == Q[i]
//TODO: implement flow     if (FLOW_TYPE != NO_FLOW) ((*F)[i][i]) = Q[i];
                        (*this)[i] = (*this)[i + N] = 0;
                        break;

                    case 1: // P[i] < Q[i]
//TODO: implement flow  if (FLOW_TYPE != NO_FLOW) ((*F)[i][i]) = P[i];
                        sum_Q -= tempSum;
                        (*this)[i] = 0;
                        (*this)[i + N] = tempSum;
                        nonZeroSinkNodes[nonZeroSinkCounter++] = i;
                        break;
                } // inner switch
                break;
            case 1: // P[i] > Q[i]
//TODO: implement flow   if (FLOW_TYPE != NO_FLOW) ((*F)[i][i]) = Q[i];
                sum_P += tempSum;
                (*this)[i] = tempSum;
                (*this)[i + N] = 0;
                nonZeroSourceNodes[nonZeroSourceCounter++] = i;
                break;
        } // outer switch
    }
    nonZeroSourceNodes.resize(nonZeroSourceCounter);
    nonZeroSinkNodes.resize(nonZeroSinkCounter);
    return {sum_P, sum_Q};
}

template<typename NUM_T, typename INTERFACE_T, int size>
void VertexWeights<NUM_T, INTERFACE_T, size>::swapWeights()
{
    NODE_T N = (this->_num_nodes - 2) / 2;
    std::swap_ranges(this->begin(), this->begin() + N, this->begin() + N);
    std::transform(this->begin(), this->end(), this->begin(),
                   std::bind(std::multiplies<NUM_T>(),
                             std::placeholders::_1, -1));
}

template<typename NUM_T, typename INTERFACE_T, int size>
NUM_T VertexWeights<NUM_T, INTERFACE_T, size>::calcPreFlowCost(
                Counter<NUM_T, INTERFACE_T, size/2>& sinkNodes,
                Counter<NUM_T, INTERFACE_T, size/2>& uniqueJs,
                NUM_T maxC, NODE_T costSize) const
{
    // calculate pre_flow_cost & add weight to THRESHOLD_NODE
    // reorder b array so that all weights are in range [0, sourcesCounter + sinksCounter + 2];
    auto N = (this->size() - 2)/2;
    auto preFlowCost = 0;
    int shrinkCounter = costSize - sinkNodes.size() - 2;
    
    // for each sink node check whether it gets flow only from threshold node
    // if true add its weight to Threshold Node else move it weight to new position
    for(auto j : sinkNodes)
    {
        auto weight = (*this)[j + N];
        if (uniqueJs[j] == 0 && weight != 0)
        {
            preFlowCost -= (weight * maxC);
            (*this)[THRESHOLD_NODE] += weight;
        }
        else // (uniqueJs[j] != 0)
        {
            uniqueJs[j] = shrinkCounter;
            (*this)[shrinkCounter++] = weight;
        }
    }
    
    // move THRESHOLD_NODE weight;
    (*this)[shrinkCounter] = (*this)[this->THRESHOLD_NODE];
    
    // resize weights to new size
    this->resize(costSize);
    
    // add zero-weight Artificial node
    (*this)[ARTIFICIAL_NODE] = 0; //Artificialnode;
    
    return preFlowCost;
}

#endif /* VertexWeights_h */
