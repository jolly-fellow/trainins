#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

// Definition for a node.
class node_t {
public:
    int val;
    vector<node_t*> neighbors;
    node_t() {
        val = 0;
        neighbors = vector<node_t*>();
    }
    explicit node_t(int _val) {
        val = _val;
        neighbors = vector<node_t*>();
    }
    node_t(int _val, const vector<node_t*> & _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


unordered_map<node_t *, node_t *> m;

node_t *clone_graph(node_t *n) {

    if (n == nullptr) return nullptr;

    if (m.count(n)) {
        return m[n];
    }

    node_t * node_copy = new node_t(n->val);
    m[n] = node_copy;

    for (const auto &nb : n->neighbors) {
        node_copy->neighbors.push_back(clone_graph(nb));
    }
    return node_copy;
}



node_t * init_graph(const vector<vector<int>> & adjacent_list) {

    size_t al_size = adjacent_list.size();
    vector<node_t *> nodes(al_size);

    if(0 == al_size) {
        return new node_t(1);
    }

    for(int i = 1; i <= al_size; ++i ) {
        nodes[i - 1] = new node_t(i);
    }

    for(int i = 0; i < al_size; ++i ) {
        for(auto n: adjacent_list[i]) {
            nodes[i]->neighbors.push_back(nodes[n - 1]);
        }
    }
    return nodes[0];
}



void print_node(node_t * n) {
    cout << "\n Val: " << n->val;
    for(const auto nb: n->neighbors) {
        cout << " | " << nb->val;
    }
}

void  print_graph(node_t * n, vector<bool> & printed) {
    if (n == nullptr) { return; }
    print_node(n);
    printed[n->val] = true;
    for(const auto nb: n->neighbors) {
        if(!printed[nb->val]) {
            print_graph(nb, printed);
        }
    }
}

void print_graph_BFS(node_t * n, int nodes_number) {
    vector<bool> printed(nodes_number, false);

    print_graph(n, printed);
}

node_t* clone_graph_iterative(node_t* node) {
    if (node == nullptr) {
        return nullptr;
    }
    unordered_map<node_t*, node_t*> table;
    table[node] = new node_t(node->val);
    queue<node_t*> q;
    q.push(node);
    while (!q.empty()) {
        node_t* n = q.front();
        q.pop();
        for (node_t* nb : n->neighbors) {
            if (!table.count(nb)) {
                table[nb] = new node_t(nb->val);
                q.push(nb);
            }
            table[n]->neighbors.push_back(table[nb]);
        }
    }

    return table[node];
}


int main() {

    vector<vector<int>> vv {{2,4},{1,3},{2,4},{1,3}};

    node_t * graph = init_graph(vv);

    print_graph_BFS(graph, vv.size());

    cout << "\n Clone: \n";

    node_t * clone = clone_graph(graph);

    print_graph_BFS(clone, vv.size());

    return 0;
}
