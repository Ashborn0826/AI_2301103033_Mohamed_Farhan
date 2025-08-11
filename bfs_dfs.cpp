#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include <algorithm>

// Depth-Limited DFS (helper for IDDFS)
bool depth_limited_dfs(
    const std::unordered_map<std::string, std::vector<std::string>>& graph,
    const std::string& current,
    const std::string& goal,
    std::set<std::string>& visited,
    std::vector<std::string>& path,
    int depth_limit
) {
    visited.insert(current);
    path.push_back(current);

    if (current == goal) {
        return true; // Goal found
    }
    if (depth_limit <= 0) {
        path.pop_back();
        visited.erase(current);
        return false; // Limit reached
    }

    if (graph.find(current) != graph.end()) {
        std::vector<std::string> neighbors = graph.at(current);
        std::sort(neighbors.begin(), neighbors.end()); // Lexicographical order

        for (const auto& neighbor : neighbors) {
            if (!visited.count(neighbor)) {
                if (depth_limited_dfs(graph, neighbor, goal, visited, path, depth_limit - 1)) {
                    return true;
                }
            }
        }
    }

    path.pop_back();
    visited.erase(current);
    return false;
}

// Iterative Deepening DFS - combines BFS level expansion with DFS depth search
bool iddfs(
    const std::unordered_map<std::string, std::vector<std::string>>& graph,
    const std::string& start,
    const std::string& goal,
    std::vector<std::string>& result_path
) {
    for (int depth = 0;; depth++) { // Increase depth until goal is found
        std::set<std::string> visited;
        std::vector<std::string> path;
        if (depth_limited_dfs(graph, start, goal, visited, path, depth)) {
            result_path = path;
            return true;
        }
    }
    return false;
}

int main() {
    // Example graph (unordered on purpose)
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
    std::string goal  = "H";
    std::vector<std::string> result_path;

    if (iddfs(graph, start, goal, result_path)) {
        std::cout << "✅ IDDFS Path (BFS + DFS best): ";
        for (size_t i = 0; i < result_path.size(); ++i) {
            std::cout << result_path[i] << (i < result_path.size() - 1 ? " -> " : "");
        }
        std::cout << "\n";
    } else {
        std::cout << "No path found\n";
    }

    return 0;
}
