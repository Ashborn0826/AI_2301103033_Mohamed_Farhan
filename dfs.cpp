#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include <algorithm>

bool dfs_lexicographic_stop(
    const std::unordered_map<std::string, std::vector<std::string>>& graph,
    const std::string& current,
    const std::string& goal,
    std::set<std::string>& visited,
    std::vector<std::string>& path
) {
    visited.insert(current);
    path.push_back(current);

    
    if (current == goal) {
        return true;
    }

    
    if (graph.find(current) != graph.end()) {
        std::vector<std::string> neighbors = graph.at(current);
        std::sort(neighbors.begin(), neighbors.end());

        for (const auto& neighbor : neighbors) {
            if (!visited.count(neighbor)) {
                if (dfs_lexicographic_stop(graph, neighbor, goal, visited, path)) {
                    return true; 
                }
            }
        }
    }

    
    path.pop_back();
    return false;
}

int main() {
    
    std::unordered_map<std::string, std::vector<std::string>> graph = {
        {"A", {"C", "B"}},   
        {"B", {"E", "D"}},
        {"C", {"G", "F"}},
        {"D", {}},
        {"E", {"H"}},
        {"F", {}},
        {"G", {"H"}},
        {"H", {}}
    };

    std::string start = "A";
    std::string goal = "H";

    std::set<std::string> visited;
    std::vector<std::string> path;

    if (dfs_lexicographic_stop(graph, start, goal, visited, path)) {
        std::cout << "Path found: ";
        for (size_t i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if (i < path.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No path found from " << start << " to " << goal << "\n";
    }

    return 0;
}
