#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

#include <list>
#include <forward_list>
#include <climits>

using namespace std;

std::list<int> asd { 7, 5, 16, 8 };

std::forward_list<int> asd2;

void ttt() {
    asd.erase(asd.begin());
    asd2.erase_after(asd2.begin());
}


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

// Fibonacci simple recursion

int fibonacci1(int n) {
    if( n == 0) {
        return 0;
    }
    else if( n == 1 || n == 2) {
        return 1;
    }
    else {
        return fibonacci1(n - 1) + fibonacci1(n - 2);
    }
}

// Fibonacci cached recursion

int fibonacci2(int n) {

    static vector<int> cache (n, 0);

    if(cache[n] == 0) {
        if (n == 0) {
            return 0;
        } else if (n == 1 || n == 2) {
            return 1;
        } else {
            return fibonacci1(n - 1) + fibonacci1(n - 2);
        }
    }
}

struct Node_DLL {
    Node_DLL * prev;
    Node_DLL * next;
    int data;
};

struct Node_SLL {
    Node_SLL * next;
    int data;
};

Node_SLL * make_sl_list(const vector<int> & list) {

    size_t list_size = list.size();

    if(list_size == 0) { return nullptr; }

    Node_SLL * head = new Node_SLL;

    head->next = nullptr;
    head->data = list[0];

    Node_SLL * tail = head;

    for(int i = 1; i < list_size; ++i ) {
        Node_SLL * node = new Node_SLL;
        tail->next = node;
        node->data = list[i];
        tail = node;
    }
    return head;
}


Node_DLL * make_dl_list(const vector<int> & list) {

    size_t list_size = list.size();

    if(list_size == 0) { return nullptr; }

    Node_DLL * head = new Node_DLL;

    head->prev = nullptr;
    head->next = nullptr;
    head->data = list[0];

    Node_DLL * tail = head;

    for(int i = 1; i < list_size; ++i ) {
        Node_DLL * node = new Node_DLL;
        tail->next = node;
        node->prev = tail;
        node->data = list[i];
        tail = node;
    }
    return head;
}

void print_list(Node_DLL * list) {
    while(list != nullptr) {
        cout << list->data << " ";
        list = list->next;
    }
}

void print_list(Node_SLL * list) {
    while(list != nullptr) {
        cout << list->data << " ";
        list = list->next;
    }
}


void remover_dll(Node_DLL * list, int to_remove, bool remove_one = false) {
    if(list == nullptr) { return; }

    do {
        Node_DLL * curr = list;
        if(curr->data == to_remove) {
            if(curr->prev != nullptr) {
                curr->prev->next = curr->next;
            }

            if(curr->next != nullptr) {
                curr->next->prev = curr->prev;
            }
            list = curr->next;
            delete curr;
            if(remove_one == true) {
                return;
            }
        }
        else {
            list = list->next;
        }
    } while(list != nullptr);
}

Node_SLL * remover_sll(Node_SLL * head, int to_remove, bool remove_one = false) {

    Node_SLL * curr = head;
    Node_SLL * prev = nullptr;
/*
    while(curr != nullptr) {
        if(curr->data == to_remove) {
            Node_SLL * temp = curr;
            if(prev == nullptr) { // this is a head
                curr = curr->next;
                delete temp;
            }
            else {
            prev->next = curr->next;
            delete curr;
            curr = prev;
            if(remove_one == true) {
                return;
            }
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    */

}

int min_pair(const vector<int> & v) {
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    int min1_id = 0;
    int min2_id = 0;

    int v_size = v.size();

    for (int i = 0; i < v_size; ++i) {
        if(v[i] < min1) {
            min2 = min1;
            min2_id = min1_id;
            min1 = v[i];
            min1_id = i;
        }
        else if(v[i] > min1 && v[i] < min2 && (i - min2_id) > 1 ) {
            min2 = v[i];
            min2_id = i;
        }
    }
    return min1 + min2;
}

int main() {

    cout << min_pair({5,2,4,6,3,7}) << endl;

/*
    Node_DLL * n = make_dl_list({1, 2, 3, 3, 3, 4, 5, 5, 5});

    print_list(n);

    cout << endl << "remove element with data = 5" << endl;

    remover_dll(n, 5);

    print_list(n);

    cout << endl;
*/
    Node_SLL * sll = make_sl_list({1, 2, 3, 3, 3, 4, 5, 5, 5});

    print_list(sll);

    cout << endl << "remove element with data = 5" << endl;

    remover_sll(sll, 5);

    print_list(sll);

    cout << endl;


    for(int i = 0; i < 30; ++i) {
        cout << fibonacci1(i) << " ";
    }

    cout << endl;


    vector<vector<int>> vv {{2,4},{1,3},{2,4},{1,3}};

    node_t * graph = init_graph(vv);

    print_graph_BFS(graph, vv.size());

    cout << "\n Clone: \n";

    node_t * clone = clone_graph(graph);

    print_graph_BFS(clone, vv.size());

    return 0;
}
