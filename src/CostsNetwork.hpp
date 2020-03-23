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

//MARK: CostsNetwork
template<typename... _Types, int size = 0>
class CostsNetwork : public BaseNetwork<_Types..., size>
{
public:
    Cost(NODE_T numberOfNodes)
    : VBaseNetwork<_Types..., size>(numberOfNodes, "CostsNetwork",
                                    {"to", "cost"}, 2) {};
    
    template<class _T2d>
    void fill(
        VertexWeights<_Types...>& weights,
        const Counter<_Types..., size/2>& sourceNodes,
        const Counter<_Types..., size/2>& sinkNodes,
        Counter<_Types..., size/2>& uniqueJs,
        const _T2d& costMatrix, const NUM_T maxC,
        const int REMOVE_NODE_FLAG);
    
private:
    inline void fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<_Types..., size>& counters)
    override {std::cout << "not in use!" << std::endl;};
};

//MARK: Implementation
template<typename NUM_T, typename INTERFACE_T, int size>
template<class _T2d>
void Cost<NUM_T, INTERFACE_T, size>::fill(
                                          VertexWeights<NUM_T, INTERFACE_T, size>& weights,
                                          const Counter<NODE_T, INTERFACE_T, size/2>& nonZeroWeightSourceNodesAtIndex,
                                          const Counter<NODE_T, INTERFACE_T, size/2>& nonZeroWeightSinkNodesAtIndex,
                                          Counter<bool, INTERFACE_T, size/2>& sinkNodeGetsFlowOnlyFromThreshold,
                                          const _T2d& costMatrix, const NUM_T maxCost,
                                          const int REMOVE_NODE_FLAG)
{
    // number of sources_that_flow_not_only_to_thresh
    NODE_T sourcesCounter = 0;
    // number of sinks_that_get_flow_not_only_from_thresh
    NODE_T sinksCounter = 0;
    unsigned char step = this->fields;
    
    for(const auto sourceNodeIndex : nonZeroWeightSourceNodesAtIndex)
    {
        bool sourceNodeFlowsOnlyToThreshold = true;
        int numberOfSinkNodesForSourceNode = 0;
        auto sourceNode = this->row(sourcesCounter);
        for(const auto sinkNodeIndex : nonZeroWeightSinkNodesAtIndex)
        { // TODO: is costMatrix really symmetric?
            auto cost = costMatrix[sourceNodeIndex][sinkNodeIndex];
            if (cost == maxCost) continue;
            sourceNode[step * numberOfSinkNodesForSourceNode++] = sinkNodeIndex;
            sourceNode[step * numberOfSinkNodesForSourceNode++] = cost;
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
            weights[weights.THRESHOLD_NODE] += weights[sourceNodeIndex];
        }
        else
        {
            // mark last node
            sourceNode[step * numberOfSinkNodesForSourceNode] = REMOVE_NODE_FLAG;
            // Move the source weight to new position.
            weights[sourcesCounter++] = weights[sourceNodeIndex];
        }
    } // i
    
    // reusable values
    NODE_T costSize = sourcesCounter + sinksCounter + 2;
    this->resize(costSize);
    auto thresholdNodeIndex  = this->thresholdNode();
    auto artificialNodeIndex = this->artificialNode();
    auto artificalNodeCost   = maxCost + 1;
    auto fields              = this->fields();
    
    //MARK: Finalize Sources
    // Now we have to update the data for each node. So get and iterator over the
    // rows.
    auto nodeIterator = this->begin();
    auto end = this->begin() + sourcesCounter;
    for(; nodeIterator != end; ++nodeIterator)
    {
        for(NODE_T sinkNodeIndex = 0; sinkNodeIndex < sinksCounter; sinkNodeIndex =+ fields)
        {
            // Update Sink Index
            nodeIterator = sinkNodeGetsFlowOnlyFromThreshold[nodeIterator;
            nodeIterator += this->getFields();
            // add edges to Threshold Node and Artificial Node
            if (*nodeIterator == REMOVE_NODE_FLAG)
            { // Add edge from source to Threshold and Artificial Node.
                *nodeIterator++ = thresholdNodeIndex;  // flows to node
                *nodeIterator++ = 0;                   // cost to node
                *nodeIterator++ = artificialNodeIndex; // flows to node
                *sourceNode++ = artificalNodeCost;   // cost to node
                break;
            }
        }
    }
    
    //MARK: Edges from Sinks to ARTIFICIAL_NODE.
    for(NODE_T sinkNodeIndex = sourcesCounter; sinkNodeIndex < thresholdNode; ++sinkNodeIndex)
    {
       (*this)[sinkNodeIndex][0] = artificialNodeIndex; // flows to Node
       (*this)[sinkNodeIndex][1] = artificalNodeCost;   // cost to Node
    }
    
    //MARK: Edges from Threshold node
    // The threshold node is connected to all somls
    auto thresholdNode = this->row(thresholdNodeIndex);
    for (NODE_T sinkNodeIndex = 0; sinkNodeIndex < sinksCounter; ++sinkNodeIndex)
    {
        *thresholdNode++ = sinkNodeIndex; // flows to node
        *thresholdNode++ = maxCost;          // cost of flow
    }
    
    // Add edge from THRESHOLD_NODE to ARTIFICIAL_NODE
    *thresholdNode++ = artificialNodeIndex; // flows to node
    *thresholdNode   = artificalNodeCost;   // cost of flow
    
    
    //MARK: Edges from Artifical node
    auto artificialNode = this->row(artificialNodeIndex);
    for (NODE_T nodeIndex = 0; nodeIndex < artificialNodeIndex; ++nodeIndex)
    {
        *artificialNode++ = nodeIndex;          // flows to node
        *artificialNode++ = artificalNodeCost;  // cost of flow
    }
    
    std::cout << *this << std::endl;
}


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
//        vertexNotFlowingToThreshold.reserve(nonZeroSinkNode.size() * nonZeroSourceNode.size());
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
