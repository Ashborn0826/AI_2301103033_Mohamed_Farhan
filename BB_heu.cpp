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
    double estimatedTotal;   
    std::vector<std::string> path;
    bool operator>(const PathState& other) const {
        return estimatedTotal > other.estimatedTotal;
    }
};


std::vector<std::string> oracle_search_with_heuristic(
    const std::unordered_map<std::string, std::vector<Edge>>& graph,
    const std::unordered_map<std::string, double>& heuristic,
    const std::string& start,
    const std::string& goal
) {
    std::priority_queue<PathState, std::vector<PathState>, std::greater<PathState>> pq;
    
    pq.push({0.0, heuristic.at(start), {start}});

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

        // Expand neighbors
        if (graph.find(node) != graph.end()) {
            for (const auto& edge : graph.at(node)) {
                double newCost = cost + edge.cost;
               
                double estTotal = newCost + heuristic.at(edge.neighbor);
                auto newPath = current.path;
                newPath.push_back(edge.neighbor);
                pq.push({newCost, estTotal, newPath});
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

    
    std::unordered_map<std::string, double> heuristic = {
        {"S", 7.0},
        {"A", 6.0},
        {"B", 8.0},
        {"C", 7.0},
        {"D", 4.0},
        {"E", 6.0},
        {"F", 3.0},
        {"G", 1.5},
        {"H", 0.0} 
    };

    std::string start = "S";
    std::string goal = "H";

    std::vector<std::string> oraclePath = oracle_search_with_heuristic(graph, heuristic, start, goal);

    if (!oraclePath.empty()) {
        std::cout << "Oracle's Optimal Path (with heuristic): ";
        for (size_t i = 0; i < oraclePath.size(); ++i) {
            std::cout << oraclePath[i];
            if (i < oraclePath.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No path found from " << start << " to " << goal << "\n";
    }

    return 0;
}
