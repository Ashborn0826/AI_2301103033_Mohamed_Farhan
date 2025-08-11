#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include <algorithm>

void bms_lexicographic(
    const std::unordered_map<std::string, std::vector<std::string>>& graph,
    const std::string& current,
    const std::string& goal,
    std::vector<std::string> path,
    std::set<std::string> visited,
    std::vector<std::vector<std::string>>& all_paths
) {
    
    if (current == goal) {
        all_paths.push_back(path);
        return;
    }

    visited.insert(current);

   
    auto it = graph.find(current);
    if (it != graph.end()) {
        std::vector<std::string> neighbors = it->second;
        std::sort(neighbors.begin(), neighbors.end());

        for (const auto& neighbor : neighbors) {
            if (!visited.count(neighbor)) {
                auto newPath = path;
                newPath.push_back(neighbor);
                bms_lexicographic(graph, neighbor, goal, newPath, visited, all_paths);
            }
        }
    }
}

int main() {
    // Graph
    std::unordered_map<std::string, std::vector<std::string>> graph = {
        {"A", {"B", "C"}},
        {"B", {"D", "E"}},
        {"C", {"F", "G"}},
        {"D", {}},
        {"E", {"H"}},
        {"F", {}},
        {"G", {"H"}},
        {"H", {}}
    };

    std::string start = "A";
    std::string goal = "H";

    std::vector<std::vector<std::string>> all_paths;
    bms_lexicographic(graph, start, goal, {start}, {}, all_paths);

   
    std::cout << "All paths from " << start << " to " << goal << " (Lexicographical Order):\n";
    for (const auto& path : all_paths) {
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i < path.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";
    }

    return 0;
}
