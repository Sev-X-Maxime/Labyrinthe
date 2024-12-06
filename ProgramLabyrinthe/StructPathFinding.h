#pragma once
#include "UnderMacro.h"

struct Node
{
    int x, y;
    double cost;
    double heuristic;
    Node* parent; // Pointeur vers le parent pour reconstituer le chemin

    Node(const int _x, const int _y, const double _cost, const double _heuristic, Node* _parent = nullptr)
    {
        x = _x;
        y = _y;
        cost = _cost;
        heuristic = _heuristic;
        parent = _parent;
    }

    bool operator==(const Node& _other) const
    {
        return x == _other.x && y == _other.y;
    }
};

// Comparateur pour la file prioritaire
struct ComparByHeuristic
{
    bool operator()(const Node& _n1, const Node& _n2)
    {
        return _n1.heuristic > _n2.heuristic;
    }
};

// Fonction de hash pour Node dans unordered_set
struct HashNode
{
    size_t operator()(const Node& _n) const
    {
        return hash<int>()(_n.x) ^ hash<int>()(_n.y);
    }
};