#include <iostream>
#include <vector>

class Graph
{
private:
    //Само ребро - содержит 2 точки, которые оно соединяет, по направлению, и вес ребра
    struct Edge
    {
        int nodeStart, nodeEnd, weight = 1;
        Edge(){}
        Edge(int nodeStart_, int nodeEnd_, int weight_){nodeStart = nodeStart_; nodeEnd = nodeEnd_; weight = weight_;}
    };
    //Граф представлен в виде списка ребер
    std::vector<Edge> edges;
public:
    //Метод перечисления всех ребер
    void printEdges()
    {
        for(int i = 0; i < edges.size(); i++)
        {
            std::cout << "[" << edges[i].nodeStart << " -> " << edges[i].nodeEnd << "] = " << edges[i].weight << std::endl;
        }
    }
    //Метод перечисления вершин, смежных с вершиной A
    void printConnectedToA(int a)
    {
        std::vector<int> connectedFrom;
        std::vector<int> connectedTo;
        for(int i = 0; i < edges.size(); i++)
        {
            if(edges[i].nodeStart == a){connectedFrom.push_back(edges[i].nodeEnd);}
            if(edges[i].nodeEnd == a){connectedTo.push_back(edges[i].nodeStart);}
        }
        std::cout << "Connections from " << a << ": ";
        for(int i = 0; i < connectedFrom.size(); i++)
        {
            std::cout << connectedFrom[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Connections to " << a << ": ";
        for(int i = 0; i < connectedTo.size(); i++)
        {
            std::cout << connectedTo[i] << " ";
        }
        std::cout << std::endl;
    }
    //Метод проверки смежности ребер A и B 
    bool isAConnectedToB(int a, int b)
    {
        for(int i = 0; i < edges.size(); i++)
        {
            if(edges[i].nodeStart == a && edges[i].nodeEnd == b){return true;}
        }
        return false;
    }
    //Метод добавления ребра
    void addEdge(int a, int b, int w = 1)
    {
        if(!isAConnectedToB(a, b))
        {
            edges.push_back(Edge(a, b, w));
        }
        else{std::cout << "Err: Edge already exists" << std::endl;}
    }
    //Метод удаления ребра
    void removeEdge(int a, int b)
    {
        if(isAConnectedToB(a, b))
        {
            for(int i = 0; i < edges.size(); i++)
            {
                if(edges[i].nodeStart == a && edges[i].nodeEnd == b) {edges.erase(edges.begin()+i);}
            }
        }
        else{std::cout << "Err: Edge does not exist" << std::endl;}
    }
};

int main()
{
    Graph graph;
    //Создание графа из примера
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 1); //Добавит ребро, противоположное по направлению уже существующему [1 -> 2]
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4, 3);
    graph.addEdge(4, 5, 2);
    graph.addEdge(5, 1, 1);
    graph.addEdge(1, 2); //Уведомляет об ошибке и ничего не добавляет т.к ребро [1 -> 2] уже есть
    //Перечисление всех ребер
    graph.printEdges();
    //Смежные с 4 вершиной (2, 3, 5)
    graph.printConnectedToA(4);
    //Смежность вершин 2 c 4 (true) и 3 с 5 (false) и 1 с 5 (false из-за направления)
    std::cout << "2->4: " << graph.isAConnectedToB(2, 4) << " 3->5: " << graph.isAConnectedToB(3, 5) << " 1->5: " << graph.isAConnectedToB(1, 5) << std::endl;
    //Удаление вершины из графа (2 раза для проверки ошибки)
    graph.removeEdge(1, 2);
    graph.removeEdge(1, 2);
    graph.printEdges();
}
