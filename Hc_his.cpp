#include <iostream>
#include <vector>
#include <string>
#include <limits>

struct Node; 

struct Edge {
    Node* neighbor;  
    double cost;    
};

struct Node {
    std::string name;        
    double heuristic;       
    std::vector<Edge*> edges;
};


void addEdge(Node* from, Node* to, double cost) {
    Edge* e = new Edge{to, cost};
    from->edges.push_back(e);
}


Node* hillClimbWithPointers(Node* start, Node* goal, std::vector<Node*>& history) {
    Node* current = start;
    history.push_back(current);

    while (true) {
        if (current == goal) {
            std::cout << "Goal reached!\n";
            return current;
        }

        if (current->edges.empty()) {
            std::cout << "No more neighbors from " << current->name << ".\n";
            return current;
        }

        double bestScore = std::numeric_limits<double>::infinity();
        Node* nextNode = current;

    
        for (Edge* edge : current->edges) {
            double score = edge->cost + edge->neighbor->heuristic;
            if (score < bestScore) {
                bestScore = score;
                nextNode = edge->neighbor;
            }
        }

        if (nextNode == current) {
            std::cout << "Stuck at local optimum.\n";
            return current;
        }

        current = nextNode;
        history.push_back(current);
    }
}

int main() {

    Node* A = new Node{"A", 2};
    Node* B = new Node{"B", 4};
    Node* C = new Node{"C", 5};
    Node* D = new Node{"D", 7};
    Node* E = new Node{"E", 2};
    Node* F = new Node{"F", 8};
    Node* G = new Node{"G", 1};
    Node* H = new Node{"H", 0}; 

  
    addEdge(A, B, 4);
    addEdge(A, C, 2);
    addEdge(B, D, 5);
    addEdge(B, E, 1);
    addEdge(C, F, 3);
    addEdge(C, G, 6);
    addEdge(E, H, 2);
    addEdge(G, H, 1);

   
    std::vector<Node*> history;
    Node* result = hillClimbWithPointers(A, H, history);

   
    std::cout << "\nVisited path:\n";
    for (Node* node : history) {
        std::cout << node->name << " (h=" << node->heuristic << ")\n";
    }

    std::cout << "\nFinal Node: " << result->name << "\n";

  
    delete A; delete B; delete C; delete D; delete E; delete F; delete G; delete H;
    // Note: Edges should also be deleted in real code to avoid leaks

    return 0;
}
