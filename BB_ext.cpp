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


std::vector<std::string> oracle_search_extended(
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

       
        if (cost >= bestCost) continue;

        
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
        {"S", {{"A", 2}, {"B", 5}, {"C", 9}}},
        {"A", {{"D", 4}, {"E", 7}, {"F", 8}}},
        {"B", {{"E", 3}, {"G", 6}}},
        {"C", {{"F", 2}, {"H", 5}}},
        {"D", {{"I", 6}}},
        {"E", {{"I", 4}, {"J", 3}}},
        {"F", {{"J", 2}, {"K", 5}}},
        {"G", {{"J", 4}, {"L", 6}}},
        {"H", {{"K", 3}}},
        {"I", {{"M", 4}}},
        {"J", {{"M", 2}, {"N", 6}}},
        {"K", {{"N", 4}}},
        {"L", {{"N", 3}}},
        {"M", {{"Goal", 3}}},
        {"N", {{"Goal", 2}}},
        {"Goal", {}}
    };

    std::string start = "S";
    std::string goal = "Goal";

    // Call the Oracle
    std::vector<std::string> oraclePath = oracle_search_extended(graph, start, goal);

    if (!oraclePath.empty()) {
        std::cout << "✅ Oracle's Optimal Path: ";
        for (size_t i = 0; i < oraclePath.size(); ++i) {
            std::cout << oraclePath[i];
            if (i < oraclePath.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";
    } else {
        std::cout << "❌ No path found from " << start << " to " << goal << "\n";
    }

    return 0;
}
