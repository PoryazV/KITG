#include <iostream>
#include <vector>

class Graph
{
private:
    //Граф представлен в виде списка смежности
    //Вместе со смежными вершиной хранятся и веса ребер ведущих к ним
    std::vector<std::vector<std::pair<int, int>>> adjacencies;
public:
    //Метод перечисления всех ребер
    void printEdges()
    {
        for(int i = 0; i < adjacencies.size(); i++)
        {
            for(int j = 0; j < adjacencies[i].size(); j++)
            {
                std::cout << "[" << i + 1 << " -> " << adjacencies[i][j].first << "] = " << adjacencies[i][j].second << std::endl;
            }
        }
    }
    //Метод перечисления вершин, смежных с вершиной A
    void printConnectedToA(int a)
    {
        std::vector<int> connectedFrom;
        std::vector<int> connectedTo;
        for(int j = 0; j < adjacencies[a-1].size(); j++)
        {
            connectedFrom.push_back(adjacencies[a-1][j].first);
        }
        for(int i = 0; i < adjacencies.size(); i++)
        { 
            if(i == a-1){continue;}
            for(int j = 0; j < adjacencies[i].size(); j++)
            {
                if(adjacencies[i][j].first == a){connectedTo.push_back(i+1);}
            }
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
        for(int j = 0; j < adjacencies[a-1].size(); j++)
        {
            if(adjacencies[a-1][j].first == b){return true;}
        }
        return false;
    }
    //Метод добавления ребра
    void addEdge(int a, int b, int w = 1)
    {
        while(a > adjacencies.size())
        {
            std::vector<std::pair<int, int>> add;
            adjacencies.push_back(add);
        }
        if(!isAConnectedToB(a, b))
        {
            adjacencies[a-1].push_back(std::make_pair(b, w));
        }
        else{std::cout << "Err: Edge already exists" << std::endl;}
    }
    //Метод удаления ребра
    void removeEdge(int a, int b)
    {
        if(isAConnectedToB(a, b))
        {
            for(int j = 0; j < adjacencies[a-1].size(); j++)
            {
                if(adjacencies[a-1][j].first == b) {adjacencies[a-1].erase(adjacencies[a-1].begin()+j);}
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