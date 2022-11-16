//
// Created by Влад on 12.10.2022.
//

#include "prac5/Graph.h"

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