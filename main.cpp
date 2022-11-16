#include <iostream>
#include "Graph.h"

int main() {
    setlocale(LC_ALL, "");
    int n;
    std::cout << "Введите количество вершин в графе: ";
    std::cin >> n;
    Graph graph(n);
    graph.graphFill();
    graph.buildOstovTree();
    graph.displayOstovTree();
}

//0 1 2 0 10
//1 0 0 3 6
//2 0 0 4 7
//0 3 4 0 11
//10 6 7 11 0


//0 20 0 0 0 23 1
//20 0 15 0 0 0 4
//0 15 0 3 0 0 9
//0 0 3 0 17 0 16
//0 0 0 17 0 28 25
//23 0 0 0 28 0 36
//1 4 9 16 25 36 0