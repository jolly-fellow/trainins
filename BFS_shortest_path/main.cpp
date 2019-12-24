#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <tuple>
#include <cstring>

/*
Shortest path in a Binary Maze
Given a MxN matrix where each element can either be 0 or 1. We need to find the shortest path between a given source cell to a destination cell.
The path can only be created out of a cell if its value is 1.
*/

using namespace std;

struct node_t {
	int row = 0, col = 0, distance = 0;
	bool operator==(const node_t & r) const {
		return (row == r.row) && (col == r.col);
	}

};

class item_t {
	int value = 0;
	bool visited = false;
public:
	item_t(int v) : value(v) {};
	int get_value() const { return value; }
	void set_value(int v) { value = v; }
	bool is_visited() const { return visited; }
	void set_visited(bool v) { visited = v; }
};

using matrix_t = vector<vector<item_t>>;

vector<node_t> expand(const matrix_t & m, const node_t & p) {
    vector<node_t> res;
    int rows = m.size();
    int cols = m[0].size();


   // For vertical and horizontal neighbors only
    vector<int> row_dir = { -1,  0, 1, 0 };
    vector<int> col_dir = {  0, -1, 0, 1 };

/*
    // For all 8 neighbors
    vector<int> row_dir = { -1,  0, 1, 0, -1, +1, -1,  1 };
    vector<int> col_dir = {  0, -1, 0, 1, -1, +1,  1, -1 };
*/

    for (auto i = 0; i < row_dir.size(); ++i) {
        int new_row = p.row + row_dir[i];
        int new_col = p.col + col_dir[i];

        if (new_row < 0 || new_row >= rows || new_col < 0 || new_col >= cols) {
            continue;
        }
        res.emplace_back(node_t{ new_row, new_col });
    }
    return res;
}

std::optional<int> BFS_ri(matrix_t & matrix, queue<node_t> & q, const node_t & dest) {

    if (q.empty()) {
        return nullopt;
    }
    node_t node = q.front();
    if (node == dest) {
        return node.distance + 1;
    }
    q.pop();
    for (auto child : expand(matrix, node)) {
        auto & n = matrix[child.row][child.col];
        if ((n.is_visited() == false) && (n.get_value() == 1)) {
            n.set_visited(true);
            child.distance = node.distance + 1;
            q.push(child);
        }
    }
    return BFS_ri(matrix, q, dest);
}



std::optional<int> BFS_r(matrix_t & matrix, const node_t & start, const node_t & dest) {
    if ((0 == matrix[start.row][start.col].get_value()) || (0 == matrix[dest.row][dest.col].get_value())) {
        return nullopt;
    }
    matrix[start.row][start.col].set_visited(true);
    queue<node_t> q;
    q.push(start);

    return BFS_ri(matrix, q, dest);

}

std::optional<int> BFS(matrix_t & matrix, const node_t & start, const node_t & dest) {

    item_t s = matrix[start.row][start.col];
    item_t d = matrix[dest.row][dest.col];
    if ((0 == s.get_value()) || (0 == d.get_value())) {
        return nullopt;
    }

    queue<node_t> q;
    s.set_visited(true);
    q.push(start);
    while (!q.empty()) {
        node_t node = q.front();
        if (node == dest) {
            return node.distance + 1;
        }
        q.pop();
        for (auto child : expand(matrix, node)) {
            auto & n = matrix[child.row][child.col];
            if (!n.is_visited() && (n.get_value() == 1)) {
                n.set_visited(true);
                child.distance = node.distance + 1;
                q.push(child);
            }
        }
    }
    return nullopt;
}

void print(const vector<vector<item_t>> & m) {
    cout << endl;
    for (const auto& x : m) {
        for (auto y : x) {
            cout << y.get_value() << ", ";
        }
        cout << endl;
    }
    cout << endl;
}


void InitArray(int* array, int array_length)
{
    int i = 0;

    while (i < array_length)
    {
        array[i] = i;
        i++;
    }
}

int main() {

    int asd[10] = {};

//    char* test =
    InitArray(asd, 10);
//    cout << "Shortest path = " << test << endl;

    matrix_t matrix =
            {
                      { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                      { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
                      { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                      { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
                      { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                      { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                      { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
                      { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                      { 1, 1, 0, 0, 0, 0, 1, 0, 0, 1 }
            };

    print(matrix);

    node_t start = { 0, 0 };
    node_t dest = { 8, 0 };

    auto dist = BFS(matrix, start, dest);

    if (dist)
        cout << "Shortest path = " << *dist; // the distance is counted from zero!
    else
        cout << "Shortest path doesn't exist";

    return 0;
}