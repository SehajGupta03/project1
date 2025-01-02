/**
 * @file DependencyGraph.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Dependency Graph used for Topological Sorting
 */

#ifndef DEPENDENCYGRAPH_H
#define DEPENDENCYGRAPH_H

#include <unordered_map>
#include <vector>
#include <queue>
#include "Gate.h"
#include "Pin.h"

/**
 * Dependency Graph used for Topological Sorting
 */
class DependencyGraph
{
private:
	/// Keeps track of Adjacent Gates
	std::unordered_map<Gate*, std::vector<Gate*>> mAdjList;
	/// Keeps track of the Degrees of Gates
	std::unordered_map<Gate*, int> mDegrees;
public:
	void BuildDependencyGraph(const std::vector<Gate*>& gates);

	std::vector<Gate*> TopologicalSort(const std::vector<Gate*>& gates);

	//void ComputeAllGates(std::vector<Gate*>& gates);
};


#endif //DEPENDENCYGRAPH_H
