#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <algorithm>

struct Edge {
    int a, b, v;

    Edge(int a = 0, int b = 0, int v = 0) {
        if (a > b)
            std::swap(a, b);
        this->a = a;
        this->b = b;
        this->v = v;
    }

    bool operator< (Edge e1) {
        if (v < e1.v)
            return true;
        return false;
    }
};

struct components {
    std::vector<Edge> edges = std::vector<Edge>(0);
    int sum{};

    void add(Edge e) {
        edges.push_back(e);
        sum += e.v;
    }

    void merge(components comp1) {
        for (int i = 0; i < comp1.edges.size(); i++) {
            edges.push_back(comp1.edges[i]);
        }
        std::sort(edges.begin(), edges.end());
        sum += comp1.sum;
    }

    bool include(int a) {
        for (int i = 0; i < edges.size(); i++) {
            if (edges[i].a == a || edges[i].b == a)
                return true;
        }
        return false;
    }
};

class Graph {
private:
    std::vector<std::vector<int>> matrix;
    std::vector<Edge> edgesList;
    std::vector<Edge> ostov;

protected:
    bool include(std::vector<Edge>& edges, int a, int b) {
        bool isA = false;
        bool isB = false;
        for (int i = 0; i < edges.size(); i++) {
            if (edges[i].a == a || edges[i].b == a)
                isA = true;
            if (edges[i].a == b || edges[i].b == b)
                isB = true;
        }
        return isA and isB;
    }

    std::vector<Edge> getEdgesList() { // функция для получения списка всех рёбер
        std::vector<Edge> result = std::vector<Edge>(0);
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = i; j < matrix.size(); j++)
                if (matrix[i][j] > 0)
                    result.push_back(*(new Edge(i, j, matrix[i][j])));
        }
        std::sort(result.begin(), result.end());
        return result;
    }
public:
    Graph(int count) {
        matrix  = std::vector< std::vector<int>>(count, std::vector<int>(count));
    }

    void graphFill() { // построение графа
        std::cout << "Введите построчно матрицу смежности:\n";
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.size(); j++) {
                int value;
                std::cin >> value;
                matrix[i][j] = value;
            }
        }
        edgesList = getEdgesList();
    }

    void displayGraph() { // вывод матрицы смежности графа
        std::cout << "Матрица смежности графа:\n";
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.size(); j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void buildOstovTree() {
        std::vector<components> comps = std::vector<components>(1);
        for (int i = 0; i < edgesList.size(); i++) {
            bool flag = true;
            int posA = -1;
            int posB = -1;
            for (int j = 0; j < comps.size(); j++) {
                if (comps[j].include(edgesList[i].a) and !comps[j].include(edgesList[i].b)) // если одна вершина лежит в компоненте связности, а другая нет
                {
                    comps[j].add(edgesList[i]);
                    posA = j;
                }
                else if (comps[j].include(edgesList[i].b) and !comps[j].include(edgesList[i].a)) {
                    comps[j].add(edgesList[i]);
                    posB = j;
                }
                else if (comps[j].include(edgesList[i].b) and comps[j].include(edgesList[i].a)) { // если обе вершины находятся в одной компоненте
                    flag = false;
                }
            }

            if (flag) { // если обе вершины не лежат ни в одной из компонент, то надо создать новую
                comps.push_back(*(new components()));
                comps[comps.size() - 1].add(edgesList[i]);
                continue;
            }

            if (posA != posB and posA != -1 and posB != -1) { // если выршины лежат в разных компонентах, то надо объединить
                comps[posA].merge(comps[posB]);
                comps.erase(comps.begin() + posB);
            }

        }

        int minSum = 1000000;
        for (int i = 0; i < comps.size(); i++) {
            if (comps[i].edges.size() == matrix.size()-1)
                if (comps[i].sum < minSum) {
                    ostov = comps[i].edges;
                    minSum = comps[i].sum;
                }
        }
    }

    void displayOstovTree() { // вывод дерева в консоль
        int sum{};
        std::cout << "Остовное дерево:\n";
        for (Edge x : ostov) {
            std::cout << x.a << " <--> " << x.b << " Weight: " << x.v << std::endl;
            sum += x.v;
        }
        std::cout << "Вес остовного дерева: " << sum << std::endl;
    }
};
#endif // !GRAPH_H
