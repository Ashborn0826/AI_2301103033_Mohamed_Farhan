#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <set>
#include <algorithm>


bool bfs_lexicographic_with_history(
    const std::unordered_map<std::string, std::vector<std::string>>& graph,
    const std::string& start,
    const std::string& goal,
    std::vector<std::vector<std::vector<std::string>>>& history 
) {
    std::set<std::string> visited;
    std::queue<std::vector<std::string>> q;

    q.push({start});
    visited.insert(start);

    while (!q.empty()) {
        int levelSize = q.size();
        std::vector<std::vector<std::string>> levelPaths;

       
        std::queue<std::vector<std::string>> tempQ = q;
        while (!tempQ.empty()) {
            levelPaths.push_back(tempQ.front());
            tempQ.pop();
        }
        history.push_back(levelPaths);

        
        for (int i = 0; i < levelSize; i++) {
            std::vector<std::string> path = q.front();
            q.pop();

            std::string node = path.back();
            if (node == goal) {
                return true;
            }

           
            if (graph.find(node) != graph.end()) {
                std::vector<std::string> neighbors = graph.at(node);
                std::sort(neighbors.begin(), neighbors.end());
                for (const auto& neighbor : neighbors) {
                    if (!visited.count(neighbor)) {
                        visited.insert(neighbor);
                        auto newPath = path;
                        newPath.push_back(neighbor);
                        q.push(newPath);
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    // Example graph
    std::unordered_map<std::string, std::vector<std::string>> graph = {
        {"A", {"C", "B"}}, // unsorted intentionally
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

    std::vector<std::vector<std::vector<std::string>>> history;
    bool found = bfs_lexicographic_with_history(graph, start, goal, history);

    if (found) {
        std::cout << "Path to goal was found during BFS.\n";
    } else {
        std::cout << "No path found from " << start << " to " << goal << "\n";
    }

    // Print BFS history
    std::cout << "\n=== BFS History (Lexicographical Order) ===\n";
    for (size_t level = 0; level < history.size(); level++) {
        std::cout << "Level " << level << ":\n";
        for (const auto& path : history[level]) {
            for (size_t i = 0; i < path.size(); i++) {
                std::cout << path[i];
                if (i < path.size() - 1) std::cout << " -> ";
            }
            std::cout << "\n";
        }
    }

    return 0;
}
