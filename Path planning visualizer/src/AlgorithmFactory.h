#pragma once
#include "Algorithm.h"
#include "DFS.h"
#include "BFS.h"
#include "AStar.h"
#include "Dijkstra.h"
#include "BiBFS.h"
#include "biDFS.h"

class AlgorithmFactory {
public:
	static std::unique_ptr<Algorithm> generateAlgorithm(const std::string_view& graphtype ,Graph& graph) {
		if (graphtype == "BFS") {
			return std::make_unique<BFS>(graph);
		}

		else if (graphtype == "DFS") {
			return std::make_unique<DFS>(graph);
		}

		else if (graphtype == "biDFS") {
			return std::make_unique<biDFS>(graph);
		}

		else if (graphtype == "biBFS") {
			return std::make_unique<biBFS>(graph);
		}

		else if (graphtype == "AStar") {
			return std::make_unique<AStar>(graph);
		}

		else if (graphtype == "Dijkstra") {
			return std::make_unique<Dijkstra>(graph);
		}

		else if (graphtype == "BestFS") {
			return std::make_unique<BestFS>(graph);
		}
		else return nullptr;
	}

};