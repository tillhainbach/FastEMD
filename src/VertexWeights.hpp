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
#include "Counter.hpp"

namespace FastEMD
{
using namespace types;

//MARK: Vertex Weights Class
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0>
class VertexWeights : public VertexBaseContainer<NUM_T, INTERFACE_T, SIZE>
{
    
public:
    
    //MARK: Initializer
    VertexWeights(NODE_T numberOfNodes)
    :  VertexBaseContainer<NUM_T, INTERFACE_T, SIZE>(numberOfNodes,
                                                     "Vertex Weights",
                                                     {"weight"}, 1) {};

    //MARK: Setters
    template<typename _T>
    std::tuple<NUM_T, NUM_T>
        fillWeights(const _T& P, const _T& Q,
            Counter<NUM_T, INTERFACE_T, SIZE/2>& nonZeroSourceNodes,
            Counter<NUM_T, INTERFACE_T, SIZE/2>& nonZeroSinkNodes);
    
    template<typename _T>
    void preFlowWeights(const _T& P, const _T& Q);
    
    void swapWeights();
    
    //MARK: Getters
    NUM_T calcPreFlowCost(
            Counter<NUM_T, INTERFACE_T, SIZE/2>& sinkNodes,
            Counter<NUM_T, INTERFACE_T, SIZE/2>& uniqueJs,
            NUM_T maxC, NODE_T costSize) const;
        
    auto sum() const {NUM_T sum = 0; for (auto e: *this) sum += e; return sum;}
            
};

//MARK: Implementations
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
template<typename _T>
std::tuple<NUM_T, NUM_T> VertexWeights<NUM_T, INTERFACE_T, SIZE>::fillWeights(
                _T const & P, _T const & Q,
                Counter<NUM_T, INTERFACE_T, SIZE/2> & nonZeroSourceNodes,
                Counter<NUM_T, INTERFACE_T, SIZE/2> & nonZeroSinkNodes)
{
    NODE_T nonZeroSourceCounter = 0, nonZeroSinkCounter = 0;
    NUM_T sum_P = 0, sum_Q = 0;
    NODE_T const N = static_cast<NODE_T>(P.size());
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

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
void VertexWeights<NUM_T, INTERFACE_T, SIZE>::swapWeights()
{
    NODE_T N = (this->_num_nodes - 2) / 2;
    std::swap_ranges(this->begin(), this->begin() + N, this->begin() + N);
    std::transform(this->begin(), this->end(), this->begin(),
                   std::bind(std::multiplies<NUM_T>(),
                             std::placeholders::_1, -1));
}

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
NUM_T VertexWeights<NUM_T, INTERFACE_T, SIZE>::calcPreFlowCost(
                Counter<NUM_T, INTERFACE_T, SIZE/2>& sinkNodes,
                Counter<NUM_T, INTERFACE_T, SIZE/2>& uniqueJs,
                NUM_T maxC, NODE_T costSize) const
{
    // calculate pre_flow_cost & add weight to this->_thresholdNodeIndex
    // reorder b array so that all weights are in range [0, sourcesCounter + sinksCounter + 2];
    auto N = (this->SIZE() - 2)/2;
    auto preFlowCost = 0;
    int shrinkCounter = costSize - sinkNodes.SIZE() - 2;
    
    // for each sink node check whether it gets flow only from threshold node
    // if true add its weight to Threshold Node else move it weight to new position
    for(auto j : sinkNodes)
    {
        auto weight = (*this)[j + N];
        if (uniqueJs[j] == 0 && weight != 0)
        {
            preFlowCost -= (weight * maxC);
            (*this)[this->_thresholdNodeIndex] += weight;
        }
        else // (uniqueJs[j] != 0)
        {
            uniqueJs[j] = shrinkCounter;
            (*this)[shrinkCounter++] = weight;
        }
    }
    
    // move this->_thresholdNodeIndex weight;
    (*this)[shrinkCounter] = (*this)[this->_thresholdNodeIndex];
    
    // resize weights to new SIZE
    this->resize(costSize);
    
    // add zero-weight Artificial node
    (*this)[this->_artificialNodeIndex] = 0; //Artificialnode;
    
    return preFlowCost;
}

} // namespace FastEMD
#endif /* VertexWeights_h */
