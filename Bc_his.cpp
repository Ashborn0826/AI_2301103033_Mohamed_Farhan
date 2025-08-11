#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>


std::vector<std::string> beam_search_with_history(
    const std::unordered_map<std::string, std::vector<std::string>>& graph,
    const std::string& start,
    const std::string& goal,
    const std::unordered_map<std::string, double>& heuristic,
    int k,
    std::vector<std::vector<std::string>>& history 
) {
   
    std::vector<std::vector<std::string>> queue = {{start}};

    while (!queue.empty()) {
    
        for (const auto& path : queue) {
            history.push_back(path);
        }

        
        std::sort(queue.begin(), queue.end(),
                  [&](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                      return heuristic.at(a.back()) < heuristic.at(b.back());
                  });

     
        if ((int)queue.size() > k) {
            queue.resize(k);
        }

        std::vector<std::vector<std::string>> new_queue;

        for (const auto& path : queue) {
            const std::string& node = path.back();
            if (node == goal) {
                return path; // Found goal
            }
            if (graph.find(node) != graph.end()) {
                for (const auto& neighbor : graph.at(node)) {
                    auto new_path = path;
                    new_path.push_back(neighbor);
                    new_queue.push_back(new_path);
                }
            }
        }
        queue = std::move(new_queue);
    }

    return {}; // No path found
}

int main() {
    // Graph (unweighted version)
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

    
    std::unordered_map<std::string, double> heuristic = {
        {"A", 6}, {"B", 4}, {"C", 5},
        {"D", 3}, {"E", 2}, {"F", 4},
        {"G", 4}, {"H", 0}
    };

    std::string start = "A";
    std::string goal = "H";
    int beamWidth = 2;

    std::vector<std::vector<std::string>> history; // All visited paths
    std::vector<std::string> solution = beam_search_with_history(graph, start, goal, heuristic, beamWidth, history);

    if (!solution.empty()) {
        std::cout << "Path found: ";
        for (const auto& node : solution) std::cout << node << " ";
        std::cout << "\n";
    } else {
        std::cout << "No path found within beam width " << beamWidth << "\n";
    }

    // Print history
    std::cout << "\n=== Search History ===\n";
    for (size_t i = 0; i < history.size(); i++) {
        std::cout << "Beam Step " << i+1 << ": ";
        for (const auto& n : history[i]) std::cout << n << " ";
        std::cout << "\n";
    }

    return 0;
}
