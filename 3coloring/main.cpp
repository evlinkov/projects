#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>

using namespace std;

class Graph {

private:

    int size;
    vector < vector <int> > edges;
    bool canThreeColoring;
    vector <int> colour;

public:

    Graph() { }

    Graph(int size) {
        this->size = size;
        edges.resize(size);
    }

    int getSize() {
        return size;
    }

    void setSize (int size) {
        this->size = size;
        edges.resize(size);
    }

    void addEdge(int a, int b) {
        --a;
        --b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    void addEdge(pair <int, int> e) {
        int a = e.first - 1;
        int b = e.second - 1;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    vector<int> & getEdgesOfVertex (int i) {
        return edges[i];
    }

    ~Graph() {
        for (int i = 0; i < size; ++i) {
            edges[i].clear();
        }
        edges.clear();
    }

    void updateThreeColoringSets() {
        canThreeColoring = false;
        vector <int> used;
        used.resize(size);
        for (int i = 0; i < size; ++i) {
            used[i] = -1;
        }
        maximalIndependentSets(used);
    }

    bool getCanThreeColoring() {
        return canThreeColoring;
    }

    int getMinimumDegreeVertex (vector <int> &used) {
        int numberOfVertex = -1, numberOfNeighbors = -1, cnt;
        for (int i = 0; i < size; ++i) {
            if (used[i] == -1) {
                cnt = 0;
                for (auto element : edges[i]) {
                    if (used[element] == -1) {
                        cnt++;
                    }
                }
                if (cnt > numberOfNeighbors) {
                    numberOfVertex = i;
                    numberOfNeighbors = cnt;
                }
            }
        }
        return numberOfVertex;
    }

    void dfs(int vertex, vector <int> &used, bool & can, int colour) {
        used[vertex] = colour;
        for (auto element : edges[vertex]) {
            if (used[element] == colour) {
                can = false;
            }
            if (used[element] == 0) {
                dfs(element, used, can, 5 - colour);
            }
        }
    }

    void maximalIndependentSets(vector <int> &used) {
        int numberOfVertex = getMinimumDegreeVertex(used);
        if (numberOfVertex == -1) {
            bool can = true;
            for (int i = 0; i < size; ++i) {
                if (used[i] == 0) {
                    dfs(i, used, can, 2);
                }
            }
            if (can) {
                canThreeColoring = true;
                colour.resize(size);
                for (int i = 0; i < size; ++i) {
                    colour[i] = used[i];
                }
            }
            for (int i = 0; i < size; ++i) {
                if (used[i] != 1) {
                    used[i] = 0;
                }
            }
        } else {
            vector <int> neigborsElement;
            neigborsElement.push_back(numberOfVertex);
            for (auto element : edges[numberOfVertex]) {
                if (used[element] == -1) {
                    neigborsElement.push_back(element);
                }
            }
            for (auto element : neigborsElement) {
                vector <int> neigborsVertex;
                neigborsVertex.push_back(element);
                for (auto vertex : edges[element]) {
                    if (used[vertex] == -1) {
                        neigborsVertex.push_back(vertex);
                    }
                }
                for (auto paintable : neigborsVertex) {
                    used[paintable] = (paintable == element) ? 1 : 0;
                }
                maximalIndependentSets(used);
                for (auto paintable : neigborsVertex) {
                    used[paintable] = -1;
                }
            }
        }
    }

    void updateThreeColoringFullBust() {
        canThreeColoring = false;
        vector <int> used;
        used.resize(size);
        paint(used, 0);
    }

    void paint(vector <int> &used, int number) {
        if (number == size) {
            bool can = true;
            for (int i = 0; i < size; ++i) {
                for (auto to : edges[i]) {
                    if (used[i] == used[to]) {
                        can = false;
                    }
                }
            }
            if (can) {
                canThreeColoring = true;
            }
        } else {
            for (int colour = 1; colour <= 3; ++colour) {
                used[number] = colour;
                paint(used, number + 1);
            }
        }
    }

    void printVector(vector <int> &used) {
        for (auto colour : used) {
            cout << colour << " ";
        }
        cout << "\n";
    }

    void printAnswer() {
        if (!canThreeColoring) return;
        for (auto x : colour) {
            cout << x << " ";
        }
        cout << "\n";
    }

    void printGraph() {
        for (int i = 0; i < size; ++i) {
            for (auto vertex : edges[i]) {
                if (i < vertex) {
                    cout << i << " " << vertex << "\n";
                }
            }
        }
    }
};

void readInputData(Graph &graph) {
    int n, m, a, b;
    cin >> n >> m;
    graph.setSize(n);
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        graph.addEdge(a, b);
    }
}

void solveTask() {
    Graph graph;
    readInputData(graph);
    graph.updateThreeColoringSets();
    cout << graph.getCanThreeColoring() << endl;
    if (graph.getCanThreeColoring()) {
        graph.printAnswer();
    }
}

void testThreeColoringCorrect() {
    int times = 100;
    int N = 8;
    vector < pair <int, int> > edges;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            edges.push_back(make_pair(i, j));
        }
    }
    bool checkSets, checkFullBust;
    for (int i = 0; i < times; ++i) {
        Graph graph(N);
        int numberOfEdges = rand()%(edges.size());
        random_shuffle(edges.begin(), edges.end());
        for (int j = 0; j < numberOfEdges; ++j) {
            graph.addEdge(edges[j]);
        }
        graph.updateThreeColoringSets();
        checkSets = graph.getCanThreeColoring();
        graph.updateThreeColoringFullBust();
        checkFullBust = graph.getCanThreeColoring();
        if (checkSets != checkFullBust) {
            cout << "ERROR" << "\n";
            exit(0);
        }
    }
    cout << "Correct is ok" << "\n";
}

void testThreeColoringTimer() {
    int N = 30;
    int times = 10;
    vector < pair <int, int> > edges;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            edges.push_back(make_pair(i, j));
        }
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    for (int i = 0; i < times; ++i) {
        Graph graph(N);
        int numberOfEdges = rand()%(edges.size());
        random_shuffle(edges.begin(), edges.end());
        for (int j = 0; j < numberOfEdges; ++j) {
            graph.addEdge(edges[j]);
        }
        graph.updateThreeColoringSets();
    }

    end = std::chrono::system_clock::now();
    cout << "Time for " << times << " times and " << N << " vertices : ";
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
}

int main()
{
    testThreeColoringCorrect();
    testThreeColoringTimer();
    solveTask();
    return 0;
}