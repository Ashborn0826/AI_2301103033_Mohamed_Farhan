#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <set>
#include <algorithm>

void bfs_lexicographic(
    const std::unordered_map<std::string, std::vector<std::string>>& graph,
    const std::string& start,
    const std::string& goal
) {
    std::set<std::string> visited;
    std::queue<std::vector<std::string>> q; 

    
    q.push({start});
    visited.insert(start);

    while (!q.empty()) {
        
        std::vector<std::string> path = q.front();
        q.pop();

        std::string node = path.back();

        
        if (node == goal) {
            std::cout << "Path found: ";
            for (size_t i = 0; i < path.size(); ++i) {
                std::cout << path[i];
                if (i < path.size() - 1) std::cout << " -> ";
            }
            std::cout << "\n";
            return;
        }

        
        if (graph.find(node) != graph.end()) {
            std::vector<std::string> neighbors = graph.at(node);
            std::sort(neighbors.begin(), neighbors.end());

            for (const auto& neighbor : neighbors) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    std::vector<std::string> newPath = path;
                    newPath.push_back(neighbor);
                    q.push(newPath);
                }
            }
        }
    }

    std::cout << "No path found from " << start << " to " << goal << "\n";
}

int main() {
    // Example graph
    std::unordered_map<std::string, std::vector<std::string>> graph = {
        {"A", {"C", "B"}}, // Unsorted on purpose
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

    bfs_lexicographic(graph, start, goal);

    return 0;
}
