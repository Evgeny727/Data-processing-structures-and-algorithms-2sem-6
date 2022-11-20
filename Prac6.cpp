#include <iostream>
#include <vector>
#include <queue>// поиск в ширину
#include <stack> //поиск в глубину

using namespace std;

struct Graph {
   vector<vector<bool>> smezhTable;
};

struct OstTree {
    int numNode;
    int status = 0; // 0-не обнаружена,1-обнаружена,2-пройдена
    vector<OstTree*> connects;
};

Graph createGraph() {
    cout << "Введите кол-во элементов графа: ";
    int graphSize;
    cin >> graphSize;
    Graph graph;
    for (int i = 0; i < graphSize; i++) {
        vector<bool> temp;
        cout << "Введите связи для " << i << "-ого элемента\n";
        bool num;
        for (int j = 0; j < graphSize; j++) {
            cin >> num;
            temp.push_back(num);
        }
        graph.smezhTable.push_back(temp);
    }
    return graph;
}

int searchDepth(Graph graph) {
    // таблица смежности
    //    0 1 1 0 1
    //    1 0 0 1 1
    //    1 0 0 1 1
    //    0 1 1 0 1
    //    1 1 1 1 0
    stack<int> Stack;
    vector<int> nodes;
    for (int i = 0; i < 7; i++)
        nodes.push_back(0);
    Stack.push(0);
    int height = -1;
    while (!Stack.empty()) {
        int node = Stack.top(); // извлекаем вершину
        Stack.pop();
        if (nodes[node] == 2) continue;
        nodes[node] = 2; // отмечаем ее как посещенную
        height++;
        for (int j = graph.smezhTable.size()-1; j >= 0; j--) { // проверяем для нее все смежные вершины
            if (graph.smezhTable[node][j] == 1 && nodes[j] != 2) { // если вершина смежная и не обнаружена
                Stack.push(j); // добавляем ее в cтек
                nodes[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
    }
    return height;
}

OstTree* searchInWidth(Graph graph) {
    queue<OstTree*> Queue;
    vector<OstTree*> nodes;
    for (int i = 0; i < graph.smezhTable.size(); i++) {
        OstTree* temp = new OstTree;
        temp->numNode = i;
        nodes.push_back(temp);
    }
    Queue.push(nodes[0]);
    OstTree* node;
    while (!Queue.empty()) {
        node = Queue.front();
        int index = node->numNode;
        Queue.pop();
        nodes[node->numNode]->status = 2;
        for (int i = 0; i < graph.smezhTable.size(); i++) {
            if (graph.smezhTable[node->numNode][i] == 1 and nodes[i]->status == 0) {
                Queue.push(nodes[i]);
                nodes[i]->status = 1;
                nodes[index]->connects.push_back(nodes[i]);
            }
        }
    }
    return nodes[0];
}

void printGraph(Graph graph) {
    cout << "Граф:\n";
    for (int i = 0; i < graph.smezhTable.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < graph.smezhTable[i].size(); j++) {
            cout << graph.smezhTable[i][j] << " ";
        }
        cout << endl;
    }
}

void print_Tree(OstTree* p, int level) {
    if (p) {
        if (level > 0) {
            for (int i = 0; i < level; i++) cout << "   ";
        }
        cout << p->numNode << endl;
        for (int i = 0; i < p->connects.size(); i++) {
            print_Tree(p->connects[i], level + 1);
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    Graph graph = createGraph();
    printGraph(graph);
    int h = searchDepth(graph);
    cout << "\nГлубина графа: " << h << endl;
    OstTree* root = searchInWidth(graph);
    cout << "\nОстовое дерево:\n";
    print_Tree(root, 0);
    return 0;
}