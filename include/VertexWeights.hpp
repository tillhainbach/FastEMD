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
class VertexWeights : public VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, 1>
{
    
public:
    
    //MARK: Initializer
    VertexWeights(NODE_T numberOfNodes)
    :  VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, 1>(numberOfNodes,
                                                     "Vertex Weights",
                                                     {"weight"}) {};
    
    VertexWeights(std::vector<NUM_T> _data)
    :  VertexBaseContainer<NUM_T, INTERFACE_T, SIZE, 1>(_data,
                                                     "Vertex Weights",
                                                     {"weight"}) {};

    //MARK: Setters
    template<typename _T>
    NUM_T fillWeights(const _T& P, const _T& Q,
            Counter<NUM_T, INTERFACE_T, SIZE/2>& nonZeroSourceNodes,
            Counter<NUM_T, INTERFACE_T, SIZE/2>& nonZeroSinkNodes);
    
    template<typename _T>
    void preFlowWeights(const _T& P, const _T& Q);
    
    void swapWeights();
    
    //MARK: Getters
    void calcPreFlowCost(
            Counter<NUM_T, INTERFACE_T, SIZE/2> const& sinkNodes,
            Counter<NUM_T, INTERFACE_T, SIZE/2>& uniqueJs,
            NUM_T maxC, NODE_T costSize);
        
    auto sum() const {NUM_T sum = 0; for (auto e: *this) sum += e; return sum;}
    
    NUM_T preFlowCost = 0;
    
    template<typename _T, typename _I, NODE_T _S>
    friend std::ostream& operator<<(std::ostream& os,
                                   const VertexWeights<_T, _I, _S>& container);
            
};

//MARK: Implementations
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
template<typename _T>
NUM_T VertexWeights<NUM_T, INTERFACE_T, SIZE>::fillWeights(
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
    
    //TODO: untangle this function into several smaller functions...
#if PRINT && DEBUG
    std::cout << *this << std::endl;
    
    std::cout << nonZeroSourceNodes << std::endl;
    
    std::cout << nonZeroSinkNodes << std::endl;
#endif
    //MARK: Ensuring that the supplier - P, has more mass.
    NUM_T abs_diff_sum_P_sum_Q = std::abs(sum_P - sum_Q);
    if (sum_Q > sum_P)
    {
        this->swapWeights();
        std::swap(nonZeroSourceNodes, nonZeroSinkNodes);
        
#if PRINT && DEBUG
        std::cout << "needToSwapFlow" << std::endl;
        std::cout << nonZeroSourceNodes << std::endl;
        
        std::cout << nonZeroSinkNodes << std::endl;
#endif
    }
        
    /* remark*) I put here a deficit of the extra mass, as mass that flows
     to the threshold node can be absorbed from all sources with cost zero
     (this is in reverse order from the paper, where incoming edges to the
     threshold node had the cost of the threshold and outgoing edges had
     the cost of zero) This also makes sum of b zero. */
    *(this->thresholdNode()) = -abs_diff_sum_P_sum_Q;
    
    return abs_diff_sum_P_sum_Q;
}

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
void VertexWeights<NUM_T, INTERFACE_T, SIZE>::swapWeights()
{
    NODE_T N = (this->_numberOfNodes - 2) / 2;
    std::swap_ranges(this->begin(), this->begin() + N, this->begin() + N);
    std::transform(this->begin(), this->end(), this->begin(),
                   std::bind(std::multiplies<NUM_T>(),
                             std::placeholders::_1, -1));
}

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
void VertexWeights<NUM_T, INTERFACE_T, SIZE>::calcPreFlowCost(
                Counter<NUM_T, INTERFACE_T, SIZE/2> const & sinkNodes,
                Counter<NUM_T, INTERFACE_T, SIZE/2>& sinkNodeGetsFlowOnlyFromThreshold,
                NUM_T maxC, NODE_T costSize)
{
    // calculate pre_flow_cost & add weight to this->_thresholdNodeIndex
    // reorder b array so that all weights are in range [0, sourcesCounter + sinksCounter + 2];
    auto N = (this->size() - 2)/2;
    int shrinkCounter = costSize - sinkNodes.size() - 2;
    
    // for each sink node check whether it gets flow only from threshold node
    // if true add its weight to Threshold Node else move it weight to new position
    for(auto j : sinkNodes)
    {
        auto weight = (*this)[j + N];
        if (sinkNodeGetsFlowOnlyFromThreshold[j] && weight != 0)
        {
            preFlowCost -= (weight * maxC);
            *this->thresholdNode() += weight;
        }
        else // (sinkNodeGetsFlowOnlyFromThreshold[j] != 0)
        {
            sinkNodeGetsFlowOnlyFromThreshold[j] = shrinkCounter;
            (*this)[shrinkCounter++] = weight;
        }
    }
    
    // move this->_thresholdNodeIndex weight;
    (*this)[shrinkCounter] = *this->thresholdNode();
    
    // resize weights to new SIZE
    this->resize(costSize);
    
    // add zero-weight Artificial node
    *this->artificialNode() = 0; //Artificialnode;
}

template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
std::ostream& operator<<(std::ostream& os,
                        const VertexWeights<NUM_T, INTERFACE_T, SIZE>& container)
{
    // Print the container name.
    os << container._containerName << ": ";
    // Print one line describing the containing data.
    
    // Now, print the actual data.
    for(auto element : container)
    {
        os << element << " ";
    }

    return os;
}

} // namespace FastEMD
#endif /* VertexWeights_h */
