#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <limits>

struct Edge {
    std::string neighbor;
    double cost;
};

struct PathState {
    double totalCost;
    std::vector<std::string> path;
    bool operator>(const PathState& other) const {
        return totalCost > other.totalCost;
    }
};


std::vector<std::string> oracle_search(
    const std::unordered_map<std::string, std::vector<Edge>>& graph,
    const std::string& start,
    const std::string& goal
) {
    std::priority_queue<PathState, std::vector<PathState>, std::greater<PathState>> pq;
    pq.push({0.0, {start}});

    double bestCost = std::numeric_limits<double>::infinity();
    std::vector<std::string> bestPath;

    while (!pq.empty()) {
        PathState current = pq.top();
        pq.pop();

        double cost = current.totalCost;
        const std::string& node = current.path.back();

        if (cost >= bestCost)
            continue;

        if (node == goal) {
            bestCost = cost;
            bestPath = current.path;
            continue;
        }

        if (graph.find(node) != graph.end()) {
            for (const auto& edge : graph.at(node)) {
                double newCost = cost + edge.cost;
                auto newPath = current.path;
                newPath.push_back(edge.neighbor);
                pq.push({newCost, newPath});
            }
        }
    }
    return bestPath;
}

int main() {
   
    std::unordered_map<std::string, std::vector<Edge>> graph = {
        {"S", {{"A", 2}, {"B", 5}}},
        {"A", {{"C", 4}, {"D", 7}}},
        {"B", {{"D", 3}, {"E", 8}}},
        {"C", {{"F", 5}}},
        {"D", {{"F", 2}, {"G", 6}}},
        {"E", {{"G", 1}}},
        {"F", {{"H", 3}}},
        {"G", {{"H", 1}}},
        {"H", {}} 
    };

    std::string start = "S";
    std::string goal = "H";

    
    std::vector<std::string> oraclePath = oracle_search(graph, start, goal);

    if (!oraclePath.empty()) {
        std::cout << "Oracle's Path (Optimal): ";
        for (size_t i = 0; i < oraclePath.size(); i++) {
            std::cout << oraclePath[i];
            if (i < oraclePath.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No path found from " << start << " to " << goal << "\n";
    }

    return 0;
}
