#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <limits>
#include <set>

struct Edge {
    std::string neighbor;
    double cost;
};

struct PathState {
    std::string node;
    double g_cost;                  // cost so far
    double f_cost;                  // g + h
    std::vector<std::string> path;  // full path to this node
    bool operator>(const PathState& other) const {
        return f_cost > other.f_cost;
    }
};

// Standard A* implementation
std::vector<std::string> a_star_search(
    const std::unordered_map<std::string, std::vector<Edge>>& graph,
    const std::unordered_map<std::string, double>& heuristic,
    const std::string& start,
    const std::string& goal
) {
    std::priority_queue<PathState, std::vector<PathState>, std::greater<PathState>> openSet;
    std::set<std::string> closedSet;

    openSet.push({start, 0.0, heuristic.at(start), {start}});

    while (!openSet.empty()) {
        PathState current = openSet.top();
        openSet.pop();

        if (current.node == goal) {
            return current.path; 
        }

        if (closedSet.count(current.node)) continue;
        closedSet.insert(current.node);

        if (graph.find(current.node) != graph.end()) {
            for (const auto& edge : graph.at(current.node)) {
                if (closedSet.count(edge.neighbor)) continue;
                double new_g = current.g_cost + edge.cost;
                double new_f = new_g + heuristic.at(edge.neighbor);
                auto newPath = current.path;
                newPath.push_back(edge.neighbor);
                openSet.push({edge.neighbor, new_g, new_f, newPath});
            }
        }
    }
    return {};
}


std::vector<std::string> oracle_search_a_star(
    const std::unordered_map<std::string, std::vector<Edge>>& graph,
    const std::unordered_map<std::string, double>& heuristic,
    const std::string& start,
    const std::string& goal
) {
    
    return a_star_search(graph, heuristic, start, goal);
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

   
    std::unordered_map<std::string, double> heuristic = {
        {"S", 10}, {"A", 8}, {"B", 9}, {"C", 7},
        {"D", 7}, {"E", 6}, {"F", 5}, {"G", 7},
        {"H", 5}, {"I", 4}, {"J", 3}, {"K", 3},
        {"L", 4}, {"M", 2}, {"N", 1}, {"Goal", 0}
    };

    std::string start = "S";
    std::string goal = "Goal";

    // Call the Oracle
    std::vector<std::string> oraclePath = oracle_search_a_star(graph, heuristic, start, goal);

    if (!oraclePath.empty()) {
        std::cout << "Oracle's A* Path: ";
        for (size_t i = 0; i < oraclePath.size(); ++i) {
            std::cout << oraclePath[i];
            if (i < oraclePath.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";
    } else {
        std::cout << " No path found\n";
    }

    return 0;
}
