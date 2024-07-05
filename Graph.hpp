#include "Libreries.hpp"
#include <vector>

template <class T, T _empty = -1>
class Graph
{
private:
    class Bow
    {
    public:
        int v;
        double weight; // Peso del arco
        Bow(int v, double weight) : v(v), weight(weight) {}
    };

    class Vertex
    {
    public:
        T data;
        std::vector<Bow *> *adj; // Lista de adyacencia con std::vector
        Vertex(T data) : data(data), adj(new std::vector<Bow *>()) {}
        ~Vertex()
        {
            for (auto bow : *adj)
            {
                delete bow;
            }
            delete adj;
        }
    };

    std::vector<Vertex *> *vertices;

public:
    Graph() : vertices(new std::vector<Vertex *>()) {}
    ~Graph()
    {
        for (auto vertex : *vertices)
        {
            delete vertex;
        }
        delete vertices;
    }

    int addVertex(T data)
    {
        Vertex *vertex = new Vertex(data);
        vertices->push_back(vertex);
        return vertices->size() - 1;
    }

    int cantVertices()
    {
        return vertices->size();
    }

    T getVertexData(int v)
    {
        return vertices->at(v)->data;
    }

    void modifyVertexData(int v, T data)
    {
        vertices->at(v)->data = data;
    }

    int addEdge(int v, int w, double weight)
    {
        Vertex *vertex = vertices->at(v);
        Bow *bow = new Bow(w, weight);
        vertex->adj->push_back(bow);
        return vertex->adj->size() - 1;
    }

    int cantEdges(int v)
    {
        return vertices->at(v)->adj->size();
    }

    double getEdgeWeight(int v, int w)
    {
        for (auto bow : *vertices->at(v)->adj)
        {
            if (bow->v == w)
            {
                return bow->weight;
            }
        }
        return _empty;
    }

    void modifyEdgeWeight(int v, int w, double weight)
    {
        for (auto bow : *vertices->at(v)->adj)
        {
            if (bow->v == w)
            {
                bow->weight = weight;
                return;
            }
        }
    }

    std::vector<std::pair<int, double>> getAdjacents(int v)
    {
        std::vector<std::pair<int, double>> adjacents;
        Vertex *vertex = vertices->at(v);
        for (auto bow : *vertex->adj)
        {
            adjacents.push_back(std::make_pair(bow->v, bow->weight));
        }
        return adjacents;
    }
};