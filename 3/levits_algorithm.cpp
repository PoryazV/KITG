#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

int main()
{
    //Число вершин графа, начальная вершина, конечная вершина
    int size = 6, start = 0, finish= 5;
    //Создание графа по образцу
    std::vector <std::vector<std::pair<int,int>>> graph
    {
        //0
        {{1,3},{2,1}},
        //1
        {{3,2}},
        //2
        {{3,3},{4,2}},
        //3
        {{4,1},{5,3}},
        //4
        {{5,5}}
    };
    //Сигнал начала работы алгоритма
    std::cout << "Searching path from " << start << " to " << finish << std::endl;
    //Список кратчайших путей из вершины start до всех других. Расстояние от start до самой себя ставим = 0
    std::vector<int> lengths(size, 999999999);
    lengths[start] = 0;
    //Список состояний для вершин
    //0 - Вершины, расстояние до которых уже вычислено (но, возможно, не окончательно)
    //1 - Вершины, расстояние до которых вычисляется
    //2 - Вершины, расстояние до которых ещё не вычислено
    std::vector<int> state(size, 2);
    state[start] = 1;
    //Очередь, из которой мы берем вершины на обработку. Начинаем со start
    std::deque<int> queue;
    queue.push_back(start);
    //Список, в котором хранится сам кратчайший путь
    std::vector<int> path(size, -1);
    //Цикл, работает до опустошения очереди
    while (!queue.empty())
    {
        //берем обрабатываемую вершину
        int a = queue.front();  
        queue.pop_front();
        state[a] = 0;
        for (int i = 0; i < graph[a].size(); i++)
        {
            //b - вершина, в которую идет ребро с весом w
            int b = graph[a][i].first, w = graph[a][i].second;
            if (lengths[a] + w < lengths[b])
            {
                lengths[b] = lengths[a] + w;
                if (state[b] == 2)
                    queue.push_back(b);
                else if (state[b] == 0)
                    queue.push_front(b);
                path[b] = a;
                state[b] = 1;
            }
        }
    }
    //На случай, если нет ребер, ведущих к конечной вершине
    if (path[finish] == -1)
    {
        std::cout << "No solution" << std::endl;
    }
    //Итоговый вывод через список с решением solution
    else
    {
        std::vector<int> solution;
        for (int i = finish; i != -1; i = path[i])
        {
            solution.push_back(i);
        }
        std::reverse(solution.begin(), solution.end());
        std::cout << "Shortest path: ";
        for (size_t i = 0; i < solution.size(); i++)
        {
            std::cout << solution[i] << ' ';
        }
        std::cout << std::endl << "With lenght = " << lengths[finish] << std::endl;
    }
}