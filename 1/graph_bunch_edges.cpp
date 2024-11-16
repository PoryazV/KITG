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
    //Граф представлен в виде списка ребер, списка голов списков и списка ссылок на следующий элемент
    std::vector<Edge> edges;
    std::vector<int> heads;
    std::vector<int> links;
public:
    //Метод перечисления всех ребер
    void printEdges()
    {
        std::cout << "[";
        for(int i = 0; i < heads.size(); i++)
        {
            std::cout << heads[i];
            if(i+1 < heads.size()){std::cout << ", ";}
        }
        std::cout << "]" << std::endl;
        for(int i = 0; i < edges.size(); i++)
        {
            std::cout << "[" << edges[i].nodeStart << " -> " << edges[i].nodeEnd << "] = " << edges[i].weight << " | " << links[i] << std::endl;
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
        while(a > heads.size())
        {
            heads.push_back(-1);
        }
        if(!isAConnectedToB(a, b))
        {
            edges.push_back(Edge(a, b, w));
            links.push_back(heads[a-1]);
            heads[a-1] = edges.size()-1;
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
                if(edges[i].nodeStart == a && edges[i].nodeEnd == b)
                {
                    edges.erase(edges.begin()+i);
                    int link = heads[a-1];
                    if(links[link] == -1)
                    {
                        links.erase(links.begin()+i);
                        heads[a-1] = -1;
                    }
                    else 
                    {
                        while(links[link] != i)
                        {
                            link = links[link];
                            std::cout << link << '\n';
                        }
                        links[link] = links[links[link]];
                        links.erase(links.begin()+i);
                    }
                    for(int j = i; j < edges.size(); j++)
                    {
                        if(links[j] > i){links[j]--;}
                    }
                    for(int j = i; j < heads.size(); j++)
                    {
                        if(heads[j] > i){heads[j]--;}
                    }
                }
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
    //Удаление вершины для проверки ссылок
    graph.removeEdge(2, 3);
    graph.printEdges();
}