// A Recursive C program to solve minimum sum partition
// problem.
#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <limits>
#include <numeric>
using namespace std;

using bitmatrix_t = vector<vector<bool>>;


// this is a very easy and understandable solution of the set partition problem
// it calls Karmarkar - Karp Partition
/*
 эвристический алгоритм — метод наибольшей разности (МНР, en:Largest Differencing Method, LDM)[6],
 который называется эвристическим методом Кармаркара–Карпа[2], по имени учёных, опубликовавших метод в 1982[7].
 МНР имеет две фазы. Первая фаза алгоритма берёт два наибольших числа из входа и заменяем их разностью.
 Повторяем операцию, пока не останется одно число. Замена представляет решение разместить два числа в разные
 подмножества, но в какие множества эти числа размещаются, решение не принимается. В конце первой фазы оставшееся
 единственное число является разностью двух сумм подмножеств. На втором этапе строится актуальное решение[1].

 Разностный эвристический алгоритм работает лучше, чем жадный алгоритм, но остаётся плохим для задач,
 в которых числа экспоненционально зависят от размера множества[1].
 */

int find_min2(vector<int> &v) {
    // create max heap
    std::priority_queue<int> heap{v.begin(), v.end()};

    while(heap.size() > 1) {
        int val1 = heap.top();
        heap.pop();
        int val2 = heap.top();
        heap.pop();
        heap.push(val1 - val2);
    }
    return heap.top();
}

// This is correct solution of the task but it doesn't take to the Knapsack problem.
int find_min3(vector<int> &v) {
    int v_size = v.size();
    int left_sum = 0;

    int minimal = std::numeric_limits<int>::max();

    int right_sum = std::accumulate(v.begin(), v.end(), 0);

    for (int i = 1; i < v_size; i++) {
        int val = v[i - 1];

        left_sum  += val;
        right_sum -= val;

        int diff = std::abs(left_sum - right_sum);

        if (minimal > diff) {
            minimal = diff;
        }
    }
    return minimal;
}

// Solution of the Knapsack problem by Dynamic programming
// Returns the minimum value of the difference of the two sets.
int find_min(vector<int> &v) {
    // Calculate sum of all elements
    auto v_size = v.size();
    int sum = 0;
//    int minimal = 0;

    // Create a matrix to store solution table
    bitmatrix_t bitmatrix(v_size+1, vector<bool>(1, true));
/*
    for (int i = 0; i < v_size; ++i) {
        minimal = min(v[i], minimal);
    }

    if(minimal < 0 ) {
        for (int i = 0; i < v_size; ++i) {
            v[i] -= minimal;
        }
    }
*/
    for (int i = 0; i < v_size; ++i) {
        sum += v[i];
    }

    int half_sum = sum/2;

    bitmatrix[0].resize(half_sum, false);

    for (int i=1; i<=v_size; i++) {
        bitmatrix[i].resize(half_sum, false);
        for (int j=1; j<=half_sum; j++) {
            // If i'th element is excluded
            bitmatrix[i][j] = bitmatrix[i-1][j];
            // If i'th element is included
            if (v[i-1] <= j) {
                bitmatrix[i][j] = bitmatrix[i][j] || bitmatrix[i - 1][j - v[i - 1]];
            }
        }
    }

    // print the matrix
    for (int j = 0; j <= half_sum; j++) {
        for (int i=0; i<=v_size; i++) {
            cout << bitmatrix[i][j] << ", ";
        }
        cout << endl;
    }

    // Initialize difference of two sums.
    int diff = std::numeric_limits<int>::max();

    // Find the largest j such that dp[n][j]
    // is true where j loops from sum/2 t0 0
    for (int j=half_sum; j >= 0; j--)
    {
        // Find the
        if (bitmatrix[v_size][j] == true) {
            diff = sum-2*j;
            break;
        }
    }
    return diff;
}


// Returns the minimum value of the difference of the two sets.
int findMin(int arr[], int n)
{
    // Calculate sum of all elements
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];

    // Create an array to store results of subproblems
    bool dp[n+1][sum+1];

    // Initialize first column as true. 0 sum is possible
    // with all elements.
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;

    // Initialize top row, except dp[0][0], as false. With
    // 0 elements, no other sum except 0 is possible
    for (int i = 1; i <= sum; i++)
        dp[0][i] = false;

    // Fill the partition table in bottom up manner
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=sum; j++)
        {
            // If i'th element is excluded
            dp[i][j] = dp[i-1][j];

            // If i'th element is included
            if (arr[i-1] <= j)
                dp[i][j] |= dp[i-1][j-arr[i-1]];
        }
    }

    // print the matrix
/*
    cout << "  | ";
    for (int j=0; j<=sum; j++) { cout << j << ", "; }
    cout << endl;
*/
    for (int i=0; i<=n; i++) {
//        cout << arr[i] << " | ";
        for (int j = 0; j <= sum; j++) {
            cout << dp[i][j] << ", ";
        }
        cout << endl;
    }

    // Initialize difference of two sums.
    int diff = INT_MAX;

    // Find the largest j such that dp[n][j]
    // is true where j loops from sum/2 t0 0
    for (int j=sum/2; j>=0; j--)
    {
        // Find the
        if (dp[n][j] == true)
        {
            diff = sum-2*j;
            break;
        }
    }
    return diff;
}

// Driver program to test above function
int main()
{
    vector<int> v1 = {-1000, 1000};
    int arr[] = {5, 6, 2, 4, 1}; // expected 4
    vector<int> v = {7, 5, 3, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    //auto res = findMin(arr, n);
    auto res = find_min(v);
    cout << "The minimum difference between 2 sets is " << res;
    return 0;
}
