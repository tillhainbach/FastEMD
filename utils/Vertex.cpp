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

// ------------ Vertex_Base Weight Implementation -------------------
//template<typename NUM_T,

template<typename NUM_T, typename INTERFACE_T, int size>
template<typename _T>
std::tuple<NUM_T, NUM_T, NODE_T, NODE_T>
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
//                if (FLOW_TYPE != NO_FLOW) ((*F)[i][i]) = Q[i];
                sum_P += tempSum;
                (*this)[i] = tempSum;
                (*this)[i + N] = 0;
                nonZeroSourceNodes[nonZeroSourceCounter++] = i;
                break;
            case 1:
                switch (static_cast<unsigned char>(tempSum < 0))
                {
                    case 0: // P[i] == Q[i]
//                        if (FLOW_TYPE != NO_FLOW) ((*F)[i][i]) = Q[i];
                        (*this)[i] = (*this)[i + N] = 0;
                        break;
                        
                    case 1: // P[i] < Q[i]
//                        if (FLOW_TYPE != NO_FLOW) ((*F)[i][i]) = P[i];
                        sum_Q += -tempSum;
                        (*this)[i] = 0;
                        (*this)[i + N] = tempSum;
                        nonZeroSinkNodes[nonZeroSinkCounter++] = i;
                        break;
                }
        }
    }
    return {sum_P, sum_Q, nonZeroSourceCounter, nonZeroSinkCounter};
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
                NUM_T sourcesCounter, NUM_T maxC, NODE_T costSize)
{
    // calculate pre_flow_cost & add weight to THRESHOLD_NODE
    // reorder b array so that all weights are in range [0, sourcesCounter + sinksCounter + 2];
    auto N = (this->size() - 2)/2;
    auto preFlowCost = 0;
    int shrinkCounter = sourcesCounter;
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
    
    //THREHOLD_NODE weight;
    (*this)[_num_nodes - 2] = (*this)[THRESHOLD_NODE];
    THRESHOLD_NODE = _num_nodes - 2;
    ARTIFICIAL_NODE = _num_nodes - 1;
    (*this)[ARTIFICIAL_NODE] = 0; //Artificialnode;
    
    return preFlowCost;
}

// ----------------- Vextex implementation ----------------------
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

// ------------------------------------
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
inline auto Vertex_Base<NUM_T, INTERFACE_T, size>::findIndex(NODE_T& node, NODE_T& value)
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
// --------------- Cost Implementation -------------------------
template<typename NUM_T, typename INTERFACE_T, int size>
template<class _T2d>
void Cost<NUM_T, INTERFACE_T, size>::fill(
        VertexWeights<NUM_T, INTERFACE_T, size>& weights,
        Counter<NUM_T, INTERFACE_T, size/2>& sourceNodes,
        Counter<NUM_T, INTERFACE_T, size/2>& sinkNodes,
        Counter<NUM_T, INTERFACE_T, size/2>& uniqueJs,
        const _T2d& costMatrix, const NUM_T maxC,
        const int REMOVE_NODE_FLAG)
{
    // number of sources_that_flow_not_only_to_thresh
    NODE_T sourcesCounter = 0;
    // number of sinks_that_get_flow_not_only_from_thresh
    NODE_T sinksCounter = 0;
    for(auto i : sourceNodes)
    {
        bool once = false;
        int sinksForNode = 0;
        for(auto j : sinkNodes)
        { // TODO: is costMatrix really symmetric?
            auto cost = costMatrix[i][j];
            if (cost == maxC) continue;
            (*this)[sourcesCounter][2 * sinksForNode] = j;
            (*this)[sourcesCounter][2 * sinksForNode + 1] = cost;
            sinksForNode++;
            once = true;
            if (uniqueJs[j] != j)
            {
                uniqueJs[j] = j;
                sinksCounter++;
            }
        } // j
        if(once)
        { // mark last node
            (*this)[sourcesCounter][2 * sinksForNode + 1] = REMOVE_NODE_FLAG;
            (*this)[sourcesCounter][2 * sinksForNode + 2] = REMOVE_NODE_FLAG;// to THRESHOLD_NODE´
            weights[sourcesCounter] = weights[i];
            sourcesCounter++;
        }
        else
        {
            weights[weights.THRESHOLD_NODE] += weights[i];
        }
    } // i

    NODE_T ccSize = sourcesCounter + sinksCounter + 2;
    this->_num_nodes = ccSize;
    
    
    // add THRESHOLD_NODE
    for (NODE_T i = sourcesCounter; i <= sourcesCounter + sinksCounter; ++i)
    {

        (*this)[ccSize - 2][2 * (i - sourcesCounter)] = i;
        (*this)[ccSize - 2][2 * (i - sourcesCounter) + 1] = maxC;
    }
    // add Artifical_NODE
    for (NODE_T i = 0; i < ccSize - 1; ++i)
    {
        (*this)[ccSize - 1][2 * i] = i;
        (*this)[ccSize - 1][2 * i + 1] = maxC + 1;
    }
    
    // add edges from sources to THRESHOLD_NODE and ARTIFICIAL_NODE
    for(NODE_T i = 0; i < sourcesCounter; ++i)
    {
        for(NODE_T j = 0; j < sinksCounter + 1; ++j)
        {
            if ((*this)[i][2 * j] != REMOVE_NODE_FLAG && (*this)[i][2 * j + 1] != REMOVE_NODE_FLAG) continue;
            (*this)[i][2 * j] = ccSize - 2;
            (*this)[i][2 * j + 1] = 0;// to THRESHOLD_NODE
            (*this)[i][2 * j + 2] = ccSize - 1;
            (*this)[i][2 * j + 3] = maxC + 1;// to ARTIFICIAL_NODE
            break;
        }
    }

    // add edges from sinks to THRESHOLD_NODE and ARTIFICIAL_NODE
    for(NODE_T i = sourcesCounter; i < ccSize - 2; ++i)
    {
            (*this)[i][0] = ccSize - 1;
            (*this)[i][1] = maxC + 1;// to ARTIFICAL_NODE
    }

    // add edge from THRESHOLD_NODE to ARTIFICIAL_NODE
    (*this)[ccSize - 2][2 * sinksCounter + 2] = ccSize - 1;
    (*this)[ccSize - 2][2 * sinksCounter + 3] = maxC + 1;
#if PRINT
    printCost<CONVERT_TO_T, NODE_T>(c, ccSize);
#endif
    // update sink names ([sourcesCounter; sourcesCounter + sinksCounter))
    for (NODE_T i = 0; i < sourcesCounter; ++i)
    {
        for (NODE_T j = 0; j < sinksCounter + 1; ++j)
        {
            if ((*this)[i][2 * j] == ccSize - 2) break;
            (*this)[i][2 * j] = uniqueJs[(*this)[i][2 * j]];
        }
    }
}

// ------------ ForwardCost implementation -----------------------
template<typename NUM_T, typename INTERFACE_T, int size>
inline void ForwardCost<NUM_T, INTERFACE_T, size>::fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, size>& counters)
{
    (*this)[from][i] = costFrom[i];
    (*this)[from][i + 1] = costFrom[i + 1];
}

  
// ------------------- Flow implementation -----------------------
template<typename NUM_T, typename INTERFACE_T, int size>
inline void Flow<NUM_T, INTERFACE_T, size>::fillCore(
                    const NUM_T* costFrom, NODE_T from, NODE_T i,
                    Counter<NUM_T, INTERFACE_T, size> & counters)
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


// ------------ BackwardCost implementation ----------------------
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
  

// --------------------- operator<< ------------------------------
template<typename NUM_T, typename INTERFACE_T, int size>
std::ostream& operator<<(std::ostream& os,
                         const Vertex_Base<NUM_T, INTERFACE_T, size>& vertex)
{
    // print first line decribing the content of the data:
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
            if (rowPtr[j * step] == - 1) break;
            os << "[";
            
            // iterate over the channels eg. data entries
            for (NODE_T k = 0; k < step; ++k)
            {
                os << rowPtr[j * step + k];
                if (k != step - 1) os << " : ";
            }
            os << "] ";
        }
        os << std::endl;
    }
    return os;
} /* operator<<()*/

#endif
