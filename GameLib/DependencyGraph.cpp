/**
 * @file DependencyGraph.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "DependencyGraph.h"

using namespace std;

/**
 * Makes the initial graph needed for sorting
 * @param gates Logic gates items
 */
void DependencyGraph::BuildDependencyGraph(const std::vector<Gate*>& gates)
{
	for (Gate* gate : gates)
	{
		for (shared_ptr<Pin> inputPin : gate->GetInputPins())
		{
			Gate* sourceGate = inputPin->getSourceGate();
			if (sourceGate)
			{
				mAdjList[sourceGate].push_back(gate);
				mDegrees[gate]++;
			}
		}
	}
}

/**
 * Preforms the sorting process
 * @param gates Logic gates items
 * @return A vector of the gates in the correct order
 */
vector<Gate*> DependencyGraph::TopologicalSort(const vector<Gate*>& gates)
{
	vector<Gate*> sortedGates;
	queue<Gate*> toProcess;

	// Initialize the queue with gates that have no dependencies.
	for (Gate* gate : gates)
	{
		if (mDegrees[gate] == 0)
		{
			toProcess.push(gate);
		}
	}

	while (!toProcess.empty())
	{
		Gate* current = toProcess.front();
		toProcess.pop();
		sortedGates.push_back(current);

		for (Gate* dependent : mAdjList[current])
		{
			mDegrees[dependent]--;
			if (mDegrees[dependent] == 0)
			{
				toProcess.push(dependent);
			}
		}
	}

	// Cycle error
	if (sortedGates.size() != gates.size())
	{
		throw runtime_error("Error: Cycle Detected");
	}

	return sortedGates;
}

