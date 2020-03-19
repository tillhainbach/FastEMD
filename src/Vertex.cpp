//
//  Vertexe.cpp
//  FastEMD
//
//  Created by Till Hainbach on 09.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//
#ifndef VERTEX_CPP
#define VERTEX_CPP
#include "Vertex.hpp"

//MARK: Vertex Weight Implementation
template<typename NUM_T, typename INTERFACE_T, int size>
template<typename _T>
std::tuple<NUM_T, NUM_T>
VertexWeights<NUM_T, INTERFACE_T, size>::fillWeights(
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
                NUM_T maxC, NODE_T costSize)
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

//MARK: Vextex implementation
//template<NUM_T>
//void Vertex_Base< NUM_T, std::vector< std::vector<int> > >::create()
//{
//    this->matrix.resize(_num_nodes, std::vector<int>(_num_nodes));
//}
//
//template<NUM_T>
//void Vertex_Base< NUM_T, cv::Mat >::create()
//{
//    this->matrix.create(_num_nodes, _num_nodes, CV_32SC(fields));
//}

//template<typename NUM_T, typename INTERFACE_T, int size>
//inline NUM_T const * Vertex<NUM_T, INTERFACE_T, size>::row(const NODE_T _row) const override
//{
//
//}

//template<typename NUM_T, typename INTERFACE_T, int size>
//inline NUM_T * Vertex<NUM_T, INTERFACE_T, size>::row(const NODE_T _row) override
//{
//    return this->matrix.at(_row).begin();
//}

//template<typename NUM_T>
//inline NUM_T const * Vertex<NUM_T, OPENCV>::row(const NODE_T _row) const override
//{
//    return this->matrix.template ptr<const NUM_T>(_row);
//}
//
//template<typename NUM_T>
//inline NUM_T * Vertex<NUM_T, OPENCV>::row(NODE_T _row) override
//{
//    return this->matrix.template ptr<NUM_T>(_row);
//}

//MARK: Vertex Base Implentation
template<typename NUM_T, typename INTERFACE_T, int size>
template<class F>
void Vertex_Base<NUM_T, INTERFACE_T, size>::forEach(F&& func)
{
    // init flow
    NUM_T step = this->fields;
    NODE_T rows = this->rows();
    NODE_T cols = this->cols();
    for (NODE_T from = 0; from < rows; ++from)
    {
        auto thisFrom = this->row(from);
        for (NODE_T i = 0; i < cols; i += step)
        {
            NODE_T to = thisFrom[i];
            func(thisFrom, from, i);
            if (this->breakCondition(from, to)) break;
        }
    }
}

template<typename NUM_T, typename INTERFACE_T, int size>
template<class F>
void Vertex_Base<NUM_T, INTERFACE_T, size>::forEach(F&& func) const
{
    // init flow
    NUM_T step = this->fields;
    NODE_T rows = this->rows();
    NODE_T cols = this->cols();
    for (NODE_T from = 0; from < rows; ++from)
    {
        const auto thisFrom = this->row(from);
        for (NODE_T i = 0; i < cols; i += step)
        {
            NODE_T to = thisFrom[i];
            func(thisFrom, from, i);
            if (this->breakCondition(from, to)) break;
        }
    }
}

template<typename NUM_T, typename INTERFACE_T, int size>
template<typename... Args>
void Vertex_Base<NUM_T, INTERFACE_T, size>::fill(
                                        const Vertex_Base& input,
                                        Args&&... args)
{
    auto f = std::bind(&Vertex_Base::fillCore,
                       this, std::placeholders::_1,
                       std::placeholders::_2,
                       std::placeholders::_3,
                       std::forward<Args>(args)...);
    return input.forEach(f);
};

template<typename NUM_T, typename INTERFACE_T, int size>
inline void Vertex_Base<NUM_T, INTERFACE_T, size>::reduceCostCore(
            NUM_T* thisFrom,
            const NODE_T from,
            const NODE_T i,
            const Counter<NUM_T, INTERFACE_T, size>& d,
            const Counter<bool, INTERFACE_T, size>& finalNodesFlg,
            const NODE_T l)
{
    auto it = &thisFrom[2 * i];
    if (finalNodesFlg[*it]) it[1] -= d[*it] - d[l];
    if (finalNodesFlg[from]) it[1] += d[from] - d[l];
    
}

template<typename NUM_T, typename INTERFACE_T, int size>
template<typename ... Args>
void Vertex_Base<NUM_T, INTERFACE_T, size>::reduceCost(
                                                Args&&... args)
{
    auto f = std::bind(
            &Vertex_Base<NUM_T, INTERFACE_T, size>::reduceCostCore,
            this,
            std::placeholders::_1, std::placeholders::_2,
            std::placeholders::_3, std::forward<Args>(args)...);
    return this->forEach(f);
}

template<typename NUM_T, typename INTERFACE_T, int size>
inline auto Vertex_Base<NUM_T, INTERFACE_T, size>::findIndex(NODE_T node, NODE_T value)
{
    auto row = (*this)[node];
    auto it = row.begin();
    auto end = row.begin() + this->_num_nodes * this->fields;
    for ( ; it != end; it += this->fields )
    {
        if (*it == value) break;
        if (breakCondition(node, *it)) {it = row.end(); break;}
    }
    return it;
}
//MARK: Cost Implementation
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

//MARK: ForwardCost implementation
template<typename NUM_T, typename INTERFACE_T, int size>
inline void ForwardCost<NUM_T, INTERFACE_T, size>::fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, size>& counters)
{
    (*this)[from][i] = costFrom[i];
    (*this)[from][i + 1] = costFrom[i + 1];
}

  
//MARK: Flow implementation
template<typename NUM_T, typename INTERFACE_T, int size>
inline void Flow<NUM_T, INTERFACE_T, size>::fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, size>& counters)
{
    NODE_T to = static_cast<NODE_T>(costFrom[i]);
    NUM_T cost = costFrom[i + 1];
    (*this)[from][counters[from]] = to;
    (*this)[from][counters[from] + 1] = cost;
    (*this)[from][counters[from] + 2] = 0;
    (*this)[to][counters[to]] = from;
    (*this)[to][counters[to] + 1] = -cost;
    (*this)[to][counters[to] + 2] = 0;
    counters[from] += this->fields;
    counters[to] += this->fields;
}

template<typename NUM_T, typename INTERFACE_T, int size>
NUM_T Flow<NUM_T, INTERFACE_T, size>::calcDist()
{
    NUM_T dist = 0;
//    auto calc = [] (auto thisfrom, NODE_T from, NODE_T i) {return ;}
    unsigned char step = this->fields;
    NODE_T rows = this->rows();
    NODE_T cols = this->cols();
    for (NODE_T from = 0; from < rows; ++from)
    {
        auto thisFrom = this->row(from);
        for (int j = 0;  j < cols; j += step)
        {
            NODE_T to = static_cast<NODE_T>(thisFrom[j]);
            auto cost = thisFrom[j + 1];
            auto flow = thisFrom[j + 2];
            dist += cost * flow;
            if (this->breakCondition(from, to)) break; //lastNode = true;
        } // it
    } // from
    return dist;
}


//MARK: BackwardCost implementation
template<typename NUM_T, typename INTERFACE_T, int size>
inline void BackwardCost<NUM_T, INTERFACE_T, size>::fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, size>& counters)
{
    NODE_T to = static_cast<NODE_T>(costFrom[i]);
    (*this)[to][counters[to]] = from;
    (*this)[to][counters[to] + 1] = -costFrom[i + 1];;
    (*this)[to][counters[to] + 2] = 0;
    counters[to] += this->fields;
}
  

//MARK: operator<<
template<typename NUM_T, typename INTERFACE_T, int size>
std::ostream& operator<<(std::ostream& os,
                         const Vertex_Base<NUM_T, INTERFACE_T, size>& vertex)
{
    //MARK: print first line decribing the content of the data:
    // eg. "vertex: [to : reduced_cost : residual_capacity]"
    os << "vertex: [";
    for (auto& entry : vertex.datanames)
    {
        os << entry;
        if (&entry != &vertex.datanames.back()) os << " : ";
    }
    os << "]" << std::endl;
    
    /* now print the actual data:
     logic:
     for each row:
        rows: the vertex from which to flow
        for each colum:
            columns: data (e.g to which vertex, cost, flow)
                first channel: vertex to which to flow
                second channel: (reduced) cost or distance;
                third channel: flow or rasidual capacity, etc.
            break if condition is met and start jump to next row.
        
    */
    //MARK: Print the actual data.
    NODE_T step = vertex.fields;
    NODE_T numNodes = vertex._num_nodes;
    //iterate over the rows eg. vertex/nodes
    for (NODE_T i = 0; i < numNodes; ++i)
    {
        os << i << ": ";
        int const * rowPtr = vertex.row(i);
        // next iterate over the columns eg. data
        for (NODE_T j = 0;  j < numNodes; ++j)
        {
            
            auto to = rowPtr[j * step];
            os << "[" << to << " : ";
                // iterate over the channels eg. data entries
            for (NODE_T k = 1; k < step; ++k)
            {
                os << rowPtr[j * step + k];
                if (k != step - 1) os << " : ";
            }
            os << "] ";
            if (vertex.breakCondition(i, to)) break;
        }
        os << std::endl;
    }
    return os;
} /* operator<<()*/


template<typename NUM_T, typename INTERFACE_T, int size>
std::ostream& operator<<(std::ostream& os,
                         const Base1dContainer<NUM_T, INTERFACE_T, size>& container)
{
    // Print the container name followed by the stored data.
    for (const auto& element :  container.dataNames)
    {
        os << element << ": ";
    }
    
    for (const auto& e: container)
    {
        os << e << ", ";
    }
    return os;
}
    
template<typename NUM_T, typename INTERFACE_T, int size>
std::ostream& operator<<(std::ostream& os,
                         const Dist<NUM_T, INTERFACE_T, size>& container)
{
    // Print the container name followed by the stored data.
    os << container.name << ": ";
   
    const auto end = container.end() * container.getFields();
    for (const auto it = container.begin(),
         end = container.end() * container.getFields(); it != end;  it += 2)
    {
        //
        const auto to = it[0];
    
        // cast distance value to string
        std::string dist = std::to_string(it[0]);
    
        // If the distance is set to infinity, print the more
        // self-explanatory string `INF`.
        if (it[0] == std::numeric_limits<NUM_T>::max())
        {
            dist = "INF";
        }
    
        os << "[" << to << " : " << dist << "] ";
    }
    return os;
}

#endif
