#pragma once
#ifndef TREE_H
#define TREE_H

#include <string>
#include <iostream>

struct Node { // структура одного узла дерева
    bool color; // цвет узла
    Node* left; // левый потомок узла
    Node* right; // правый потомок узла
    Node* parent; // родительский узел
    std::string data; // информация в узле

    int hash() // вычисление хеша узла
    {
        int sum{};
        for (int i = 0; i < data.length(); i++)
        {
            sum += int(data[i]);
        }
        return sum;
    }

    Node(bool color, Node* left, Node* right, Node* parent, std::string data)
    {
        this->color = color;
        this->left = left;
        this->right = right;
        this->parent = parent;
        this->data = data;
    }
};

class Tree {
private:
    Node* root; // корень дерева

protected:
    // балансировка дерева
    void balance(Node*& current) // функция балансировки дерева
    {
        if (current->parent == NULL)
        {
            if (current->color == 1)
            {
                current->color = 0;
            }
            return;
        }

        Node* P = current->parent;
        if (P->color == 0)
            return;

        Node* G = P->parent;
        Node* U;
        if (P == G->right)
        {
            U = G->left;
        }
        else {
            U = G->right;
        }

        // случай 1 (дядя красный)
        if (U != NULL and U->color == 1)
        {
            P->color = 0;
            U->color = 0;
            G->color = 1;
            balance(G);
            return;
        }

        //случай 2 (дядя черный, папа и дед в разных сторонах)
        if (P->right == current and G->left == P)
        {
            G->left = current;
            current->left = P;
            P->right = NULL;
            current->parent = G;
            P->parent = current;
            balance(P);
        }
        else if (P->left == current and G->right == P)
        {
            G->right = current;
            current->parent = G;
            current->right = P;
            P->parent = current;
            P->left = NULL;
            balance(P);
        }

        //случай 3 (дяд чёрный, папа и дед на одинаковых сторонах)
        if (G->right == P and P->right == current)
        {
            G->color = 1;
            P->color = 0;
            P->parent = G->parent;
            if (G->parent != NULL)
            {
                if (G->parent->left == G)
                {
                    G->parent->left = P;
                }
                else
                {
                    G->parent->right = P;
                }
            }
            G->parent = P;
            G->right = P->left;
            P->left = G;
            if (root == G)
            {
                root = P;
                return;
            }

        }
        else if (G->left == P and P->left == current)
        {
            G->color = 1;
            P->color = 0;
            P->parent = G->parent;
            if (G->parent != NULL)
            {
                if (G->parent->left == G)
                {
                    G->parent->left = P;
                }
                else
                {
                    G->parent->right = P;
                }
            }
            G->parent = P;
            G->left = P->right;
            P->right = G;
            if (root == G)
            {
                root = P;
            }
        }
    }

    // прямой обход дерева
    void preOrder(Node* current)
    {
        std::cout << current->data << std::endl;
        if (current->left != NULL)
            preOrder(current->left);
        if (current->right != NULL)
            preOrder(current->right);
    }

    // симметричный обход дерева
    void inOrder(Node* current)
    {
        if (current->left != NULL)
            inOrder(current->left);
        std::cout << current->data << std::endl;
        if (current->right != NULL)
            inOrder(current->right);
    }

    //функция вывода дерева в консоль
    void display(Node* node)
    {
        if (node == NULL)
            return;
        if (node->left != NULL)
            std::cout << node->data << "(" << node->color << ")" << " - left - " << node->left->data << "(" << node->left->color << ")" << std::endl;
        if (node->right != NULL)
            std::cout << node->data << "(" << node->color << ")" << " - right - " << node->right->data << "(" << node->right->color << ")" << std::endl;
        if (node->left != NULL)
            display(node->left);
        if (node->right != NULL)
            display(node->right);
    }

    // функция нахождения суммы всех узлов
    int sum(Node* current)
    {
        int summ = 0;
        if (current->left != NULL)
            summ += sum(current->left);
        if (current->right != NULL)
            summ += sum(current->right);
        summ += current->hash();
        return summ;
    }

    // функция нахождения глубины дерева
    int depth(Node* current, int dep = 0)
    {
        dep += 1;
        int depth_left{};
        int depth_right{};
        if (current->left != NULL)
            depth_left = depth(current->left, dep);
        else
            depth_left = dep;
        if (current->right != NULL)
            depth_right = depth(current->right, dep);
        else
            depth_right = dep;
        return std::max(depth_left, depth_right);
    }

public:
    Tree(std::string data) {
        root = new Node(0, NULL, NULL, NULL, data);
    }

    // функция поиска места для вставки
    Node* find_place(Node* insert_node, Node* current)
    {
        if (insert_node->hash() >= current->hash())
        {
            if (current->right == NULL)
            {
                return current;
            }
            else {
                return find_place(insert_node, current->right);
            }
        }

        if (current->left == NULL)
        {
            return current;
        }
        return find_place(insert_node, current->left);
    }

    // функция вставки нового узла
    void insert(std::string data)
    {
        Node* insert_node = new Node(1, NULL, NULL, NULL, data);
        Node* insert = find_place(insert_node, root);
        insert_node->parent = insert;
        if (insert_node->hash() >= insert->hash())
        {
            insert->right = insert_node;
        }
        else {
            insert->left = insert_node;
        }

        balance(insert_node);
    }

    void print()
    {
        display(root);
    }

    void preOrder()
    {
        preOrder(root);
    }

    void inOrder()
    {
        inOrder(root);
    }

    int sum()
    {
        return sum(root);
    }

    int depth()
    {
        return depth(root, 0);
    }
};

#endif