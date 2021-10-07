#pragma once
#include <iostream>
#include "Array.h"
template <typename T>
class Graph
{
public:
    Graph(int vertexes_number);
    ~Graph();

    auto addVertex(int vertex) -> void;
    auto addEdge(int from, int to, T weight, bool isOriented = false) -> void;

    auto isEdgeExists(int from, int to) -> bool;
    auto vertexExists(int vertex) -> bool;
    auto delVertex(int vnumber) -> void;
    auto delEdge(int v1, int v2, bool isOriented = false) -> void;
    auto findMinPath(int min_path) -> void;

private:
    int _max_vertexes_number{0};
    Array<T> _matrix;
    int _vertexCount{0};
    Array<int> _vertexes;

    auto findMinPath_internal(int original_vertex, int vertex, int min_path, Array<int>& pairs_array) -> int;
};

template <typename T>
inline Graph<T>::Graph(int vertexes_number) : _max_vertexes_number(vertexes_number)
{
    _vertexes.resize(_max_vertexes_number);
    _matrix.resize(_max_vertexes_number * _max_vertexes_number);
}

template <typename T>
inline Graph<T>::~Graph()
{
}

template <typename T>
inline auto Graph<T>::addVertex(int vertex) -> void
{
    _vertexes[_vertexCount++] = vertex;
}

template <typename T>
inline auto Graph<T>::addEdge(int from, int to, T weight, bool isOriented) -> void
{
    _matrix[from * _max_vertexes_number + to] = weight;
    if (!isOriented) _matrix[to * _max_vertexes_number + from] = weight;
}

template <typename T>
inline auto Graph<T>::isEdgeExists(int from, int to) -> bool
{
    return _matrix[from * _max_vertexes_number + to];
}

template <typename T>
auto Graph<T>::vertexExists(int vertex) -> bool
{
    auto index{_vertexes.findValue(vertex)};

    if (index == VALUE_NOT_FOUND) return false;
    return true;
}

template <typename T>
auto Graph<T>::delVertex(int vnumber) -> void
{
    auto index{_vertexes.findValue(vnumber)};
    if (index == VALUE_NOT_FOUND) return;

    _vertexes.remove(index);

    --_vertexCount;
    for (auto i{0}; i < _vertexes.getArrayLength(); ++i)
    {
        _matrix[vnumber][i] = 0;
        _matrix[i][vnumber] = 0;
    }
}

template <typename T>
auto Graph<T>::delEdge(int from, int to, bool isOriented) -> void
{
    _matrix[from][to] = 0;
    if (!isOriented) _matrix[to][from] = 0;
}

template <typename T>
auto Graph<T>::findMinPath(int min_path) -> void
{
    if (!_vertexes.getArrayLength() || min_path <= 0) return;

    Array<int> pairs_array(_max_vertexes_number * _max_vertexes_number);
    for (auto i{0}; i < _vertexCount; ++i)
    {
        auto vertex{_vertexes[i]};
        findMinPath_internal(vertex, vertex, min_path, pairs_array);
    }

    for (auto i{0}; i < _vertexCount; ++i)
    {
        auto vertex{_vertexes[i]};
        std::cout << "Vertex" << vertex << " knows - ";
        for (auto j{0}; j < _max_vertexes_number; ++j)
        {
            if (i == j || !pairs_array[vertex * _max_vertexes_number + j]) continue;
            
            std::cout << "V" << j << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
auto Graph<T>::findMinPath_internal(int original_vertex, int vertex, int min_path, Array<int>& pairs_array) -> int
{
    static std::shared_ptr<bool[]> used (new bool[_max_vertexes_number]{});

    used[vertex] = true;

    if (min_path)
    {
        for (auto i{0}; i < _max_vertexes_number; ++i)
        {
            if (used[i] || !isEdgeExists(vertex, i)) continue;
            pairs_array[original_vertex * _max_vertexes_number + i] = 1;
            findMinPath_internal(original_vertex, i, min_path - 1, pairs_array);
        }
    }
    else
    {
        pairs_array[original_vertex * _max_vertexes_number + vertex] = 1;
    }
    used[vertex] = false;

    return 0;
}
