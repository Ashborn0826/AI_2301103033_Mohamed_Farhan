#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <unordered_set>

bool dfs_find_path(
    const std::unordered_map<std::string, std::vector<std::string>>& graph,
    const std::string& current,
    const std::string& goal,
    std::unordered_set<std::string>& visited,
    std::vector<std::string>& path
) {
    visited.insert(current);
    path.push_back(current);

    if (current == goal) {
        return true; // Goal found
    }

    if (graph.find(current) != graph.end()) {
        for (const auto& neighbor : graph.at(current)) {
            if (!visited.count(neighbor)) {
                if (dfs_find_path(graph, neighbor, goal, visited, path)) {
                    return true;
                }
            }
        }
    }

    // Backtrack
    path.pop_back();
    return false;
}


std::vector<std::string> oracle_search(
    const std::unordered_map<std::string, std::vector<std::string>>& graph,
    const std::string& start,
    const std::string& goal
) {
    std::unordered_set<std::string> visited;
    std::vector<std::string> path;
    dfs_find_path(graph, start, goal, visited, path);
    return path;
}

int main() {
    // Example graph as adjacency list
    std::unordered_map<std::string, std::vector<std::string>> graph = {
        {"A", {"B", "C"}},
        {"B", {"D", "E"}},
        {"C", {"F", "G"}},
        {"E", {"H"}},
        {"G", {"H"}},
        {"D", {}},
        {"F", {}},
        {"H", {}}
    };

    std::string start = "A";
    std::string goal = "H";

    std::vector<std::string> oracle_path = oracle_search(graph, start, goal);

    if (!oracle_path.empty() && oracle_path.back() == goal) {
        std::cout << " Oracle found path: ";
        for (size_t i = 0; i < oracle_path.size(); ++i) {
            std::cout << oracle_path[i];
            if (i < oracle_path.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No path found from " << start << " to " << goal << "\n";
    }

    return 0;
}
