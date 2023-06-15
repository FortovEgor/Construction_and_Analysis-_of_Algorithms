#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>

using namespace std;

// Генерация полного графа
// Ф-ия возвращает число ребер
int generateCompleteGraph(int n, vector<vector<pair<int, int>>>& graph) {
    int m = 0;
    graph.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            graph[i].push_back(make_pair(j, rand() % 10 + 1)); // случайный вес ребра
            graph[j].push_back(make_pair(i, rand() % 10 + 1));
            m += 2;
        }
    }
    return m;
}

// Генерация связного графа с коэффициентом плотности 0.4-0.5
// Ф-ия возвращает число ребер
int generateSparseGraph(int n, vector<vector<pair<int, int>>>& graph) {
    graph.resize(n);
    int m = 0; // число ребер
    for (int i = 1; i < n; i++) {
        int j = rand() % i; // случайная вершина, к которой будет добавляться ребро
        int w = rand() % 10 + 1; // случайный вес ребра
        graph[i].push_back(make_pair(j, w));
        graph[j].push_back(make_pair(i, w));
        m++;
    }
    while (m < n*(n-1)/2 * 0.4 || m > n*(n-1)/2 * 0.5) { // пока не достигнут нужный коэффициент плотности
        int i = rand() % n;
        int j = rand() % n;
        if (i == j || find(graph[i].begin(), graph[i].end(), make_pair(j,0)) != graph[i].end()) {
            continue; // уже есть ребро или петля
        }
        int w = rand() % 10 + 1; // случайный вес ребра
        graph[i].push_back(make_pair(j, w));
        graph[j].push_back(make_pair(i, w));
        m++;
    }
    return m;
}

// Генерация разреженного графа - дерева
// Ф-ия возвращает число ребер
int generateSparseTree(int n, vector<vector<pair<int, int>>>& graph) {
    int m = 0;
    graph.resize(n);
    for (int i = 1; i < n; i++) {
        int p = rand() % i; // случайный предок
        int w = rand() % 10 + 1; // случайный вес ребра
        graph[i].push_back(make_pair(p, w));
        graph[p].push_back(make_pair(i, w));
        m += 2;
    }
    return m;
}


void dijkstra(const vector<vector<pair<int, int>>>& edges, int start, int end) {
    int n = edges.size();
    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, start));
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        for (int i = 0; i < edges[u].size(); i++) {
            int v = edges[u][i].first;
            int w = edges[u][i].second;
            if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    // cout << "Dijkstra algorithm: " << dist[end] << endl;
}

void floyd_warshall(const vector<vector<pair<int, int>>>& edges, int start, int end) {
    int n = edges.size();
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        for (int j = 0; j < edges[i].size(); j++) {
            int k = edges[i][j].first;
            int w = edges[i][j].second;
            dist[i][k] = w;
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    // cout << "Floyd-Warshall algorithm: " << dist[start][end] << endl;
}

void bellman_ford(const vector<vector<pair<int, int>>>& edges, int start, int end) {
    int n = edges.size();
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (int j = 0; j < edges[u].size(); j++) {
                int v = edges[u][j].first;
                int w = edges[u][j].second;
                if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }
    bool cycle = false;
    for (int u = 0; u < n; u++) {
        for (int j = 0; j < edges[u].size(); j++) {
            int v = edges[u][j].first;
            int w = edges[u][j].second;
            if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
                cycle = true;
            }
        }
    }
    // if (cycle) {
    //     cout << "Bellman-Ford algorithm: negative cycle exists" << endl;
    // } else {
    //     cout << "Bellman-Ford algorithm: " << dist[end] << endl;
    // }
}

int main(void) {
    // ДЕЙКСТРА:
    string filename_1_d = "1_vertexes_dijkstra.csv";  // 1-ый тип Графов
    string filename_2_d = "1_edges_dijkstra.csv";  // 1-ый тип Графов
    string filename_3_d = "2_vertexes_dijkstra.csv";  // 2-ой тип Графов
    string filename_4_d = "2_edges_dijkstra.csv";  // 2-ой тип Графов
    string filename_5_d = "3_vertexes_dijkstra.csv";  // 3-ий тип Графов
    string filename_6_d = "3_edges_dijkstra.csv";  // 3-ий тип Графов

    // Флойд-Уоршалл:
    string filename_1_f = "1_vertexes_floyd_warshall.csv";  // 1-ый тип Графов
    string filename_2_f = "1_edges_floyd_warshall.csv";  // 1-ый тип Графов
    string filename_3_f = "2_vertexes_floyd_warshall.csv";  // 2-ой тип Графов
    string filename_4_f = "2_edges_floyd_warshall.csv";  // 2-ой тип Графов
    string filename_5_f = "3_vertexes_floyd_warshall.csv";  // 3-ий тип Графов
    string filename_6_f = "3_edges_floyd_warshall.csv";  // 3-ий тип Графов

    // Беллман-форд:bellman_ford
    string filename_1_b = "1_vertexes_bellman_ford.csv";  // 1-ый тип Графов
    string filename_2_b = "1_edges_bellman_ford.csv";  // 1-ый тип Графов
    string filename_3_b = "2_vertexes_bellman_ford.csv";  // 2-ой тип Графов
    string filename_4_b = "2_edges_bellman_ford.csv";  // 2-ой тип Графов
    string filename_5_b = "3_vertexes_bellman_ford.csv";  // 3-ий тип Графов
    string filename_6_b = "3_edges_bellman_ford.csv";  // 3-ий тип Графов

    /////////////// ЧАСТЬ 2 (агрегированные графики) ///////////////
    string full_graph_vertexes = "full_graph_vertexes.csv";
    string connected_graph_vertexes = "connected_graph_vertexes.csv";
    string sparse_graph_vertexes = "sparse_graph_vertexes.csv";
    string full_graph_edges = "full_graph_edges.csv";
    string connected_graph_edges = "connected_graph_edges.csv";
    string sparse_graph_edges = "sparse_graph_edges.csv";
    /////////////// /////////////// /////////////// ///////////////
    
    // для ДЕЙКСТРЫ:
    ofstream file_1_d(filename_1_d), file_2_d(filename_2_d), file_3_d(filename_3_d), file_4_d(filename_4_d), file_5_d(filename_5_d), file_6_d(filename_6_d);
    // для Флойда-Уоршелла:
    ofstream file_1_f(filename_1_f), file_2_f(filename_2_f), file_3_f(filename_3_f), file_4_f(filename_4_f), file_5_f(filename_5_f), file_6_f(filename_6_f);
    // для Беллмана-форда:
    ofstream file_1_b(filename_1_b), file_2_b(filename_2_b), file_3_b(filename_3_b), file_4_b(filename_4_b), file_5_b(filename_5_b), file_6_b(filename_6_b);
    // для агрегированных графов:
    ofstream file_full_graph_vertexes(full_graph_vertexes);
    ofstream file_connected_graph_vertexes(connected_graph_vertexes);
    ofstream file_sparse_graph_vertexes(sparse_graph_vertexes);
    ofstream file_full_graph_edges(full_graph_edges);
    ofstream file_connected_graph_edges(connected_graph_edges);
    ofstream file_sparse_graph_edges(sparse_graph_edges);
    if (!file_1_d.is_open() || !file_2_d.is_open() || !file_3_d.is_open() || !file_4_d.is_open() || !file_5_d.is_open() || !file_6_d.is_open() || !file_1_f.is_open() || !file_2_f.is_open() || !file_3_f.is_open() || !file_4_f.is_open() || !file_5_f.is_open() || !file_6_f.is_open() || !file_1_b.is_open() || !file_2_b.is_open() || !file_3_b.is_open() || !file_4_b.is_open() || !file_5_b.is_open() || !file_6_b.is_open() || !file_full_graph_vertexes.is_open() || !file_connected_graph_vertexes.is_open() || !file_sparse_graph_vertexes.is_open() || !file_full_graph_edges.is_open() || !file_connected_graph_edges.is_open() || !file_sparse_graph_edges.is_open()) {
        cerr << "Unable to create file\n";
        // file << "Name, Age, Gender" << endl; // записываем заголовок
        // file << "John, 25, Male" << endl; // записываем данные
        // file << "Sarah, 30, Female" << endl;
        return 0;
    } else {
        std::cout << "All files successfully created!\n";

        // Дейкстра:
        file_1_d << "x,y\n";
        file_2_d << "x,y\n";
        file_3_d << "x,y\n";
        file_4_d << "x,y\n";
        file_5_d << "x,y\n";
        file_6_d << "x,y\n";

        // Флойд-Уоршалл
        file_1_f << "x,y\n";
        file_2_f << "x,y\n";
        file_3_f << "x,y\n";
        file_4_f << "x,y\n";
        file_5_f << "x,y\n";
        file_6_f << "x,y\n";

        // Беллман-Форд
        file_1_b << "x,y\n";
        file_2_b << "x,y\n";
        file_3_b << "x,y\n";
        file_4_b << "x,y\n";
        file_5_b << "x,y\n";
        file_6_b << "x,y\n";

        // ЧАСТЬ 2
        file_full_graph_vertexes << "x,y1,y2,y3\n";
        file_connected_graph_vertexes << "x,y1,y2,y3\n";
        file_sparse_graph_vertexes << "x,y1,y2,y3\n";
        file_full_graph_edges << "x,y1,y2,y3\n";
        file_connected_graph_edges << "x,y1,y2,y3\n";
        file_sparse_graph_edges << "x,y1,y2,y3\n";
    }

    srand(time(NULL)); // инициализация генератора случайных чисел
    // n - кол-во вершин
    int edges_count = 0; // кол-во ребер
    for (int n = 10; n <= 1010; n += 50) {
        cout << "N: " << n << '\n';
        vector<vector<pair<int, int>>> graph;

        // ------------------------ ПОЛНЫЕ ГРАФЫ (а) ------------------------
        edges_count = generateCompleteGraph(n, graph); // Полные графы с числом вершин от 10 до 1010 (шаг 50)
        std::__1::chrono::steady_clock::time_point start_time, stop_time;
        std::__1::chrono::nanoseconds duration_time_nanoseconds;
        start_time = std::chrono::high_resolution_clock::now();
        dijkstra(graph, 0, n-1);
        stop_time = std::chrono::high_resolution_clock::now();
        duration_time_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
        cout << duration_time_nanoseconds.count() << ' ';
        file_1_d << n << "," << duration_time_nanoseconds.count() << endl;
        file_2_d << edges_count << "," << duration_time_nanoseconds.count() << endl;
        // PART 2
        file_full_graph_vertexes << n << "," << duration_time_nanoseconds.count();
        file_full_graph_edges << edges_count << "," << duration_time_nanoseconds.count();

        start_time = std::chrono::high_resolution_clock::now();
        floyd_warshall(graph, 0, n-1);
        stop_time = std::chrono::high_resolution_clock::now();
        duration_time_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
        cout << duration_time_nanoseconds.count() << ' ';
        file_1_f << n << "," << duration_time_nanoseconds.count() << endl;
        file_2_f << edges_count << "," << duration_time_nanoseconds.count() << endl;
        // PART 2
        file_full_graph_vertexes << "," << duration_time_nanoseconds.count();
        file_full_graph_edges << "," << duration_time_nanoseconds.count();

        start_time = std::chrono::high_resolution_clock::now();
        bellman_ford(graph, 0, n-1);
        stop_time = std::chrono::high_resolution_clock::now();
        duration_time_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
        cout << duration_time_nanoseconds.count() << '\n';
        file_1_b<< n << "," << duration_time_nanoseconds.count() << endl;
        file_2_b << edges_count << "," << duration_time_nanoseconds.count() << endl;
        // Пишем в 1_vetexes.csv - зависимость от кол-ва: Вершин (n)
        // Пишем в 1_edges.csv - зависимость от кол-ва: Ребер (edges_count)
        // PART 2
        file_full_graph_vertexes << "," << duration_time_nanoseconds.count() << endl;
        file_full_graph_edges << "," << duration_time_nanoseconds.count() << endl;
        graph.clear();
        // ----------------------------------------------------------------
    

        // ------------------------ СВЯЗНЫЕ ГРАФЫ (б) ------------------------
        edges_count = generateCompleteGraph(n, graph);
        start_time = std::chrono::high_resolution_clock::now();
        dijkstra(graph, 0, n-1);
        stop_time = std::chrono::high_resolution_clock::now();
        duration_time_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
        cout << duration_time_nanoseconds.count() << ' ';
        file_3_d << n << "," << duration_time_nanoseconds.count() << endl;
        file_4_d << edges_count << "," << duration_time_nanoseconds.count() << endl;
        // PART 2:
        file_connected_graph_vertexes << n << "," << duration_time_nanoseconds.count();
        file_connected_graph_edges << edges_count << "," << duration_time_nanoseconds.count();
        
        start_time = std::chrono::high_resolution_clock::now();
        floyd_warshall(graph, 0, n-1);
        stop_time = std::chrono::high_resolution_clock::now();
        duration_time_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
        cout << duration_time_nanoseconds.count() << ' ';
        file_3_f << n << "," << duration_time_nanoseconds.count() << endl;
        file_4_f << edges_count << "," << duration_time_nanoseconds.count() << endl;
        // PART 2:
        file_connected_graph_vertexes << "," << duration_time_nanoseconds.count();
        file_connected_graph_edges << "," << duration_time_nanoseconds.count();

        start_time = std::chrono::high_resolution_clock::now();
        bellman_ford(graph, 0, n-1);
        // Пишем в 1_vetexes.csv - зависимость от кол-ва: Вершин (n)
        // Пишем в 1_edges.csv - зависимость от кол-ва: Ребер (edges_count)
        stop_time = std::chrono::high_resolution_clock::now();
        duration_time_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
        cout << duration_time_nanoseconds.count() << '\n';
        file_3_b<< n << "," << duration_time_nanoseconds.count() << endl;
        file_4_b << edges_count << "," << duration_time_nanoseconds.count() << endl;
        // PART 2:
        file_connected_graph_vertexes << "," << duration_time_nanoseconds.count() << endl;
        file_connected_graph_edges << "," << duration_time_nanoseconds.count() << endl;
        
        // Пишем в 2_vetexes.csv - зависимость от кол-ва: Вершин (n)
        // Пишем в 2_edges.csv - зависимость от кол-ва: Ребер (edges_count)
        graph.clear();

        // ------------------------ РАЗРЕЖЕННЫЕ ГРАФЫ (в) ------------------------
        edges_count = generateSparseTree(n, graph); // Разреженные графы (деревья, обратите внимание, что граф должен быть связным) с числом вершин от 10 до 1010 (шаг 50)
        start_time = std::chrono::high_resolution_clock::now();
        dijkstra(graph, 0, n-1);
        stop_time = std::chrono::high_resolution_clock::now();
        duration_time_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
        cout << duration_time_nanoseconds.count() << ' ';
        file_5_d << n << "," << duration_time_nanoseconds.count() << endl;
        file_6_d << edges_count << "," << duration_time_nanoseconds.count() << endl;
        // PART 2
        file_sparse_graph_vertexes << n << "," << duration_time_nanoseconds.count();
        file_sparse_graph_edges << edges_count << "," << duration_time_nanoseconds.count();
        
        start_time = std::chrono::high_resolution_clock::now();
        floyd_warshall(graph, 0, n-1);
        stop_time = std::chrono::high_resolution_clock::now();
        duration_time_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
        cout << duration_time_nanoseconds.count() << ' ';
        file_5_f << n << "," << duration_time_nanoseconds.count() << endl;
        file_6_f << edges_count << "," << duration_time_nanoseconds.count() << endl;
        // PART 2
        file_sparse_graph_vertexes << "," << duration_time_nanoseconds.count();
        file_sparse_graph_edges << "," << duration_time_nanoseconds.count();

        start_time = std::chrono::high_resolution_clock::now();
        bellman_ford(graph, 0, n-1);
        stop_time = std::chrono::high_resolution_clock::now();
        duration_time_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
        cout << duration_time_nanoseconds.count() << '\n';
        file_5_b<< n << "," << duration_time_nanoseconds.count() << endl;
        file_6_b << edges_count << "," << duration_time_nanoseconds.count() << endl;
        // PART 2
        file_sparse_graph_vertexes << "," << duration_time_nanoseconds.count() << endl;
        file_sparse_graph_edges << "," << duration_time_nanoseconds.count() << endl;
        
        // Пишем в 3_vetexes.csv - зависимость от кол-ва: Вершин (n)
        // Пишем в 3_edges.csv - зависимость от кол-ва: Ребер (edges_count)
        graph.clear();

        std::cout << "---------------------------------------------\n\n";
        
////////////////////////////////////////////
        // вывод графа
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < graph[i].size(); j++) {
        //         cout << i << " " << graph[i][j].first << " " << graph[i][j].second << endl;
        //     }
        // }
////////////////////////////////////////////
    }

    file_1_d.close();
    file_2_d.close();
    file_3_d.close();
    file_4_d.close();
    file_5_d.close();
    file_6_d.close();

    file_1_f.close();
    file_2_f.close();
    file_3_f.close();
    file_4_f.close();
    file_5_f.close();
    file_6_f.close();

    file_1_b.close();
    file_2_b.close();
    file_3_b.close();
    file_4_b.close();
    file_5_b.close();
    file_6_b.close();

    file_full_graph_vertexes.close();
    file_connected_graph_vertexes.close();
    file_sparse_graph_vertexes.close();
    file_full_graph_edges.close();
    file_connected_graph_edges.close();
    file_sparse_graph_edges.close();

    return 0;
}

/*
В этом коде мы используем алгоритм Дейкстры с приоритетной очередью, чтобы искать кратчайший путь в графе. Функция `dijkstra` принимает список ребер `edges`, который представляет граф в виде вектора списков пар (`<номер соседней вершины, вес ребра>`), а также номера стартовой `start` и конечной `end` вершин для поиска пути. Если путь найден, функция возвращает список вершин, составляющих кратчайший путь от стартовой до конечной вершины
*/