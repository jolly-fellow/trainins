#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <bitset>

using namespace std;

using cells_t = bitset<8>;

//    these convertion functions need only because
//    of input type is vector<int> which I can't change to pass the auto test on leetcode.com
//    But I'd prefer bitset<8> type everywhere because it is better describe the task
//    and because unordered_map doesn't work with vector<int> as a key directly

cells_t vector_to_bitset(const std::vector<int> & cells) {
    cells_t bits;
    for (auto i = 0; i < 8; ++i) {
        bits[i] = cells[i];
    }
    return bits;
}

std::vector<int> bitset_to_vector(const cells_t & bits) {
    vector<int> cells(8);
    for (auto i = 0; i < 8; ++i) {
        cells[i] = bits[i];
    }
    return cells;
}

vector<int> prisonAfterNDays(vector<int>& cells_vector, int N) {
    // because unordered_map has constant access complexity. O(1)
    unordered_map<cells_t, int> seen;

    cells_t cells = vector_to_bitset(cells_vector);

    while (N > 0) {
        cells_t cells2;

        seen[cells] = N--;

        for (int i = 1; i < 7; ++i) {
            cells2[i] = cells[i - 1] == cells[i + 1] ? 1 : 0;
        }

        cells = cells2;

        auto pair = seen.find(cells);

        if ( pair != seen.end()) {
            auto diff = pair->second - N;
            if(diff > 0) {
                N %= diff;
            }
        }

    }
    return bitset_to_vector(cells);
}

int main() {

    vector<int> cells = {1,0,0,1,0,0,1,0};
    vector<int> res = prisonAfterNDays(cells, 1000000000);

    cout << "Input: cells = [1,0,0,1,0,0,1,0], N = 1000000000" << endl <<
         "Expected: [0,0,1,1,1,1,1,0]" << endl <<
         "Actual output: ";

    for (auto i : res) {
        cout << i << " ";
    }

    return 0;
}