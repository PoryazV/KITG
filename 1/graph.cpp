#include <iostream>
#include <vector>

class Graph
{
private:
    //Само ребро - содержит 2 точки, которые оно соединяет
    struct Edge
    {
        int node1, node2;
        Edge(int node1_, int node2_){node1 = node1_; node2 = node2_;}
    };
    //Граф представлен в виде списка ребер
    std::vector<Edge> edges;
public:
    //Метод перечисления всех ребер
    void printEdges()
    {
        for(int i = 0; i < edges.size(); i++)
        {
            std::cout << "[" << edges[i].node1 << " - " << edges[i].node2 << "]" << std::endl;
        }
    }
    //Метод перечисления вершин, смежних с вершиной A
    void printConnectedToA(int a)
    {
        std::vector<int> connected;
        for(int i = 0; i < edges.size(); i++)
        {
            if(edges[i].node1 == a){connected.push_back(edges[i].node2);}
            else if(edges[i].node2 == a){connected.push_back(edges[i].node1);}
        }
        std::cout << "Connected with " << a << ": ";
        for(int i = 0; i < connected.size(); i++)
        {
            std::cout << connected[i] << " ";
        }
        std::cout << std::endl;
    }
    //Метод проверки смежности вершин A и B 
    bool isAConnectedToB(int a, int b)
    {
        for(int i = 0; i < edges.size(); i++)
        {
            if(edges[i].node1 == a && edges[i].node2 == b){return true;}
            if(edges[i].node2 == a && edges[i].node1 == b){return true;}
        }
        return false;
    }
    //Метод добавления ребра
    void addEdge(int a, int b)
    {
        if(!isAConnectedToB(a, b))
        {
            if(a <= b){edges.push_back(Edge(a, b));}
            else{edges.push_back(Edge(b, a));}
        }
        else{std::cout << "Edge already exists" << std::endl;}
    }
};

int main()
{
    Graph graph;
    //Создание графа из примера
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(5, 1);
    graph.addEdge(1, 2); //Уведомляет об ошибке и ничего не добавляет т.к ребро [1 - 2] уже есть
    //Перечисление всех ребер
    graph.printEdges();
    //Смежные с 4 вершиной (2, 3, 5)
    graph.printConnectedToA(4);
    //Смежность вершин 2 c 4 (true) и 3 с 5 (false)
    std::cout << "2-4: " << graph.isAConnectedToB(2, 4) << ", 3-5: " << graph.isAConnectedToB(3, 5) << std::endl;
}