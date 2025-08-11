#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <limits>
#include <functional>
#include <algorithm>


std::vector<std::string> hill_climbing_search(
    const std::unordered_map<std::string, std::vector<std::string>>& graph,
    const std::string& start,
    const std::string& goal,
    const std::unordered_map<std::string, double>& heuristic)
{
    std::string current_node = start;
    std::vector<std::string> path = {start};

    while (current_node != goal) {
       
        auto it = graph.find(current_node);
        if (it == graph.end() || it->second.empty()) {
            
            return {}; 
        }

       
        auto neighbors = it->second;

     
        auto next_it = std::min_element(neighbors.begin(), neighbors.end(),
            [&](const std::string& a, const std::string& b) {
                return heuristic.at(a) < heuristic.at(b);
            });

        if (next_it == neighbors.end()) {
            return {}; 
        }

        current_node = *next_it;
        path.push_back(current_node);
    }

    return path;
}

int main() {
    
    std::unordered_map<std::string, std::vector<std::string>> graph = {
        {"A", {"B", "C"}},
        {"B", {"D", "E"}},
        {"C", {"F"}},
        {"D", {}},
        {"E", {"G"}},
        {"F", {"G"}},
        {"G", {}}
    };

  
    std::unordered_map<std::string, double> heuristic = {
        {"A", 5.0},
        {"B", 4.0},
        {"C", 6.0},
        {"D", 7.0},
        {"E", 2.0},
        {"F", 3.0},
        {"G", 0.0}  
    };

    std::string start = "A";
    std::string goal = "G";

    auto path = hill_climbing_search(graph, start, goal, heuristic);

    if (!path.empty()) {
        std::cout << "Hill Climbing path found:\n";
        for (const auto& node : path) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No path found by Hill Climbing\n";
    }

    return 0;
}
