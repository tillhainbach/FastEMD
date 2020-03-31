//
//  CostsNetwork.hpp
//  FastEMD
//
//  Created by Till Hainbach on 23.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef CostsNetwork_h
#define CostsNetwork_h
#include "BaseNetwork.hpp"

namespace FastEMD
{
using namespace types;

//MARK: CostsNetwork
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE = 0>
class CostNetwork : public BaseNetwork<NUM_T, INTERFACE_T, SIZE, 2>
{
    static int const REMOVE_NODE_FLAG = -1;
public:
    CostNetwork(NODE_T numberOfNodes)
    : BaseNetwork<NUM_T, INTERFACE_T, SIZE, 2>(numberOfNodes,
                                               "CostNetwork",
                                               {"to", "cost"})
    {};
    
    CostNetwork(typeSelector2d<NUM_T, INTERFACE_T, SIZE, 2> _data)
    : BaseNetwork<NUM_T, INTERFACE_T, SIZE, 2>(_data,
                                               "CostNetwork",
                                               {"to", "cost"})
    {};
    
    template<class _T2d>
    void fill(
        VertexWeights<NUM_T, INTERFACE_T, SIZE>& weights,
        const Counter<NODE_T, INTERFACE_T, SIZE/2>& sourceNodes,
        const Counter<NODE_T, INTERFACE_T, SIZE/2>& sinkNodes,
        Counter<NODE_T, INTERFACE_T, SIZE/2>& sinkNodeGetsFlowOnlyFromThreshold,
        const _T2d& costMatrix, const NUM_T maxC);
    
    void print()
    {
        std::cout << *this << std::endl;
    }
    
private:
    inline void fillCore(
                    typeSelector1d<NUM_T, INTERFACE_T, SIZE> const & costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, SIZE>& counters)
    override {std::cout << "not in use!" << std::endl;};
    

};

//MARK: Implementation
template<typename NUM_T, typename INTERFACE_T, NODE_T SIZE>
template<class _T2d>
void CostNetwork<NUM_T, INTERFACE_T, SIZE>::fill(
        VertexWeights<NUM_T, INTERFACE_T, SIZE>& weights,
        const Counter<NODE_T, INTERFACE_T, SIZE/2>& nonZeroWeightSourceNodesAtIndex,
        const Counter<NODE_T, INTERFACE_T, SIZE/2>& nonZeroWeightSinkNodesAtIndex,
        Counter<NODE_T, INTERFACE_T, SIZE/2>& sinkNodeGetsFlowOnlyFromThreshold,
        const _T2d& costMatrix, const NUM_T maxCost)
{
    // number of sources_that_flow_not_only_to_thresh
    NODE_T sourcesCounter = 0;
    // number of sinks_that_get_flow_not_only_from_thresh
    NODE_T sinksCounter = 0;
    auto fields = this->fields();
    
    for(const auto sourceNodeIndex : nonZeroWeightSourceNodesAtIndex)
    {
        bool sourceNodeFlowsOnlyToThreshold = true;
        int numberOfSinkNodesForSourceNode = 0;
        auto sourceNode = this->fromNode(sourcesCounter);
        for(const auto sinkNodeIndex : nonZeroWeightSinkNodesAtIndex)
        { // TODO: is costMatrix really symmetric?
            auto cost = costMatrix[sourceNodeIndex][sinkNodeIndex];
            if (cost == maxCost) continue;
            (*sourceNode)[numberOfSinkNodesForSourceNode++] = sinkNodeIndex;
            (*sourceNode)[numberOfSinkNodesForSourceNode++] = cost;
            sourceNodeFlowsOnlyToThreshold = false;
            if (sinkNodeGetsFlowOnlyFromThreshold[sinkNodeIndex])
            {
                sinkNodeGetsFlowOnlyFromThreshold[sinkNodeIndex] = false;
                sinksCounter++;
            }
        } // j
        if(sourceNodeFlowsOnlyToThreshold)
        {
            // Add source weight to Threshold node.
            weights[weights.thresholdNodeIndex()] += weights[sourceNodeIndex];
        }
        else
        {
            // mark last node
            (*sourceNode)[numberOfSinkNodesForSourceNode] = REMOVE_NODE_FLAG;
            // Move the source weight to new position.
            weights[sourcesCounter++] = weights[sourceNodeIndex];
        }
    } // i
    ;
    
    // reusable values
    NODE_T costSize = sourcesCounter + sinksCounter + 2;
    this->resize(costSize);
    auto thresholdNodeIndex  = this->thresholdNodeIndex();
    auto artificialNodeIndex = this->artificialNodeIndex();
    auto artificalNodeCost   = maxCost + 1;
    
    weights.calcPreFlowCost(nonZeroWeightSinkNodesAtIndex, sinkNodeGetsFlowOnlyFromThreshold, maxCost, this->rows());
    
    //MARK: Finalize Sources
    // Now we have to update the data for each node. So get an iterator over the
    // rows.
    auto sourceNodeIterator = this->begin();
    auto end = this->begin() + sourcesCounter;
    for(; sourceNodeIterator != end; ++sourceNodeIterator)
    {
        auto nodeIterator = sourceNodeIterator->begin();
        for(NODE_T sinkNodeIndex = 0; sinkNodeIndex < sinksCounter; ++sinkNodeIndex)
        {
            // Update Sink Index
            *nodeIterator = sinkNodeGetsFlowOnlyFromThreshold[*nodeIterator];
            nodeIterator += fields;
            // add edges to Threshold Node and Artificial Node
            if (*nodeIterator == REMOVE_NODE_FLAG)
            { // Add edge from source to Threshold and Artificial Node.
                *nodeIterator++ = thresholdNodeIndex;  // flows to node
                *nodeIterator++ = 0;                   // cost to node
                *nodeIterator++ = artificialNodeIndex; // flows to node
                *nodeIterator++ = artificalNodeCost;   // cost to node
                break;
            }
        }
    }
    
    //MARK: Edges from Sinks to ARTIFICIAL_NODE.
    for(NODE_T sinkNodeIndex = sourcesCounter; sinkNodeIndex < this->thresholdNodeIndex(); ++sinkNodeIndex)
    {
       (*this)[sinkNodeIndex][0] = artificialNodeIndex; // flows to Node
       (*this)[sinkNodeIndex][1] = artificalNodeCost;   // cost to Node
    }
    
    //MARK: Edges from Threshold node
    // The threshold node is connected to all sinks
    auto thresholdNodeIterator = this->thresholdNode()->begin();
    for (NODE_T sinkNodeIndex = 0; sinkNodeIndex < sinksCounter; ++sinkNodeIndex)
    {
        *thresholdNodeIterator++ = sinkNodeIndex + sourcesCounter; // flows to node
        *thresholdNodeIterator++ = maxCost;          // cost of flow
    }
    
    // Add edge from thresholdNodeIndex() to ARTIFICIAL_NODE
    *thresholdNodeIterator++ = artificialNodeIndex; // flows to node
    *thresholdNodeIterator   = artificalNodeCost;   // cost of flow
    
    
    //MARK: Edges from Artifical node
    auto artificialNodeIterator = this->artificialNode()->begin();
    for (NODE_T nodeIndex = 0; nodeIndex < artificialNodeIndex; ++nodeIndex)
    {
        *artificialNodeIterator++ = nodeIndex;          // flows to node
        *artificialNodeIterator++ = artificalNodeCost;  // cost of flow
    }
}

} // namespace FastEMD
#endif /* CostsNetwork_h */

//    void fillCostOPENCV(cv::InputArray _VertexWeights, cv::InputArray _costMatrix, int N, int maxC)
//    {
//        CV_Assert(_VertexWeights.rows() == 1); // must be flat.
//
//        cv::Mat1i VertexWeights;
//        cv::Mat costMatrix;
//        if (!_VertexWeights.empty())
//        {
//            VertexWeights = _VertexWeights.getMat();
//        }
//        if (!_costMatrix.empty())
//        {
//            costMatrix = _costMatrix.getMat();
//        }
//
//        cv::Mat data = this->matrix;
//
//        cv::Rect sources(0, 0, N, 1);
//        cv::Rect sinks(N, 0, N, 1);
//        std::vector<cv::Point2i> nonZeroSinkNode;
//        std::vector<cv::Point2i> nonZeroSourceNode;
//        cv::findNonZero(VertexWeights(sources), nonZeroSourceNode);
//        cv::findNonZero(VertexWeights(sinks), nonZeroSinkNode);
//
//        std::vector<cv::Point> vertexNotFlowingToThreshold;
//        vertexNotFlowingToThreshold.reserve(nonZeroSinkNode.SIZE() * nonZeroSourceNode.SIZE());
//        for (auto& point : nonZeroSourceNode)
//        {
//            for (auto& p : nonZeroSinkNode)
//            {
//                cv::Point k(point.x, p.x);
//                if (costMatrix.at<int>(k) != maxC) vertexNotFlowingToThreshold.push_back(k);
//            }
//        }
//
//        int* dataPtr = data.ptr<int>(0);
//        int i = -1;
//        int j = 0;
//        int prevX = -1;
//        int prevY = -1;
//
//        for (auto& point : vertexNotFlowingToThreshold)
//        {
//
//            if(prevX != point.x) ++i;
//            std::cout << point << " " << i << " ";
//            j = (prevX == point.x && prevY != point.y) ? j + 2 : 0;
//            dataPtr[i * (data.cols * data.channels()) + j] = j/data.channels();
//            dataPtr[i * (data.cols * data.channels()) + j + 1] = costMatrix.at<int>(point);
//            prevX = point.x;
//            prevY = point.y;
//        }
//
//
//        int j;
//        i = 0;
//        for (auto& point : nonZeroSourceNode)
//        {
//            j = 0;
//            for (auto& p : nonZeroSinkNode)
//            {
//                cv::Point k(point.x, p.x);
//                if (costMatrix.at<int>(k) == maxC) continue;
//                dataPtr[i * (data.cols * data.channels()) + j] = j/data.channels();
//                dataPtr[i * (data.cols * data.channels()) + j + 1] = costMatrix.at<int>(k);
//                std::cout << dataPtr[i * data.rows + j + 1] << " ";
//                j += data.channels();
//            }
//            if (j != 0)
//            {
//                dataPtr[i * (data.cols * data.channels()) + j] = -1;
//                ++i;
//            }
//        }
//        this->_num_nodes = i + 1;
//    }
