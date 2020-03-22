#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <chrono>
#include <climits>
#include <bitset>
#include <stack>
#include <unordered_set>
#include <random>
#include <utility>
#include <map>


using namespace std;

template < class T >
void swap(vector<T> & v,  size_t a, size_t b, size_t size ) {
    for(size_t i = 0; i < size; ++i) {
        T temp = v[a + i];
        v[a + i] = v[b + i];
        v[b + i] = temp;
    }
}

template < class T >
void reverse(vector<T> & v, size_t begin, size_t end) {
    while(begin < end) {
        auto temp = v[begin];
        v[begin] = v[end];
        v[end] = temp;
        begin++;
        end--;
    }
}

// Bentley is 4 times slower than the Reverse. The Swap is faster than the Reverse in 5-6 time
template < class T >
void left_rotate_swap(vector<T> & v, size_t rot_dist) {
    auto v_size = v.size();
    auto i = rot_dist, j = v_size - rot_dist;
    while (i != j) {
        if (i > j) {
            swap(v, rot_dist-i, rot_dist, j);
            i = i-j;
        }
        else {
            swap(v, rot_dist-i,rot_dist+j-i, i);
            j = j-i;
        }
    }
    swap(v, rot_dist-i, rot_dist, i);
}

template < class T >
void print(vector<T> v) {
    for (auto i: v) {
        cout << i << ", ";
    }
    cout <<  std::endl <<  std::endl;
}

template < class T >
void left_rotate_reverse(vector<T> & v, size_t rot_dist) {
    auto v_size = v.size();
    if( (v_size == 2) || (rot_dist == 0) || (rot_dist == v_size) ) { return; }
    if( v_size < rot_dist) { rot_dist -= v_size; }

    reverse(v, 0, rot_dist - 1);
    reverse(v, rot_dist, v_size-1);
    reverse(v, 0, v_size-1);
}

template < class T >
void right_rotate_reverse(vector<T> & v, size_t rot_dist) {
    auto v_size = v.size();
    if( (v_size < 2) || (rot_dist == 0)) { return; }
    if(( (rot_dist % v_size) == 0)) {
        return;
    }
    else if( v_size < rot_dist) {
        rot_dist %= v_size;
    }

    reverse(v, v_size - rot_dist, v_size-1);
    reverse(v, 0, v_size-1 - rot_dist);
    reverse(v, 0, v_size-1);
}


// Jon Bentley algorithm (Bentley is 4 times slower than the Reverse. The Swap is faster than the Reverse in 5-6 time
template < class T >
void left_rotate(vector<T> & v, size_t rot_dist) {
    const size_t v_size = v.size();
    const size_t GCD = gcd(rot_dist, v_size);
    for(size_t i = 0; i < GCD; ++i) {
        auto curr = i;
        auto temp = v[curr];
        while(true) {
            auto next = curr + rot_dist;
            if(next >= v_size) { next = next - v_size; }
            if(next == i ) { break; }
            v[curr] = v[next];
            curr=next;
        }
        v[curr] = temp;
    }
}

/*

A non-empty array A consisting of N integers is given. The array contains an odd number of elements, and each element
 of the array can be paired with another element that has the same value, except for one element that is left unpaired.

For example, in array A such that:
  A[0] = 9  A[1] = 3  A[2] = 9
  A[3] = 3  A[4] = 9  A[5] = 7
  A[6] = 9

        the elements at indexes 0 and 2 have value 9,
        the elements at indexes 1 and 3 have value 3,
        the elements at indexes 4 and 6 have value 9,
        the element at index 5 has value 7 and is unpaired.

Write a function:

    int solution(vector<int> &A);

that, given an array A consisting of N integers fulfilling the above conditions, returns the value of the unpaired element.

For example, given array A such that:
  A[0] = 9  A[1] = 3  A[2] = 9
  A[3] = 3  A[4] = 9  A[5] = 7
  A[6] = 9

the function should return 7, as explained in the example above.

Write an efficient algorithm for the following assumptions:

        N is an odd integer within the range [1..1,000,000];
        each element of array A is an integer within the range [1..1,000,000,000];
        all but one of the values in A occur an even number of times.
 */

int get_odd_occurrence(vector<int> & v) {
    const int v_size = v.size();
/*  non destructive solution
    int res = 0;
    for(auto i: v) {
        res ^= i;
    }
    return res;
*/

// destructive solution
    for(auto i = 1; i < v_size; ++i) {
        v[i] ^= v[i-1];
    }
    return v.back();
}

// Find missing element in a permutated sequence
/*
An array A consisting of N different integers is given. The array contains integers in the range [1..(N + 1)], which means that exactly one element is missing.

Your goal is to find that missing element.

Write a function:

    int solution(vector<int> &A);

that, given an array A, returns the value of the missing element.

For example, given array A such that:
  A[0] = 2
  A[1] = 3
  A[2] = 1
  A[3] = 5

the function should return 4, as it is the missing element.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [0..100,000];
        the elements of A are all distinct;
        each element of array A is an integer within the range [1..(N + 1)].
 */
int find_missing_element(vector<int> &v) {
    auto v_size = v.size() + 1;
    auto sumOfAllElements = (v_size * (1 + v_size)) / 2; // of the sequence
    auto missingElement = sumOfAllElements - std::accumulate(v.begin(), v.end(), 0);
    return missingElement;
}

template<typename T>
void show_binrep(const T& a) {
    const char* beg = reinterpret_cast<const char*>(&a);
    const char* end = beg + sizeof(a);
    while(beg != end) {
        std::cout << std::bitset<CHAR_BIT>(*beg++) << ' ';
    }
    std::cout << endl;
}

/*
 Write a function:

    int solution(vector<int> &A);

that, given an array A, returns 1 if array A is a permutation and 0 if it is not.

For example, given array A such that:
    A[0] = 4
    A[1] = 1
    A[2] = 3
    A[3] = 2

the function should return 1.

Given array A such that:
    A[0] = 4
    A[1] = 1
    A[2] = 3

the function should return 0.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [1..100,000];
        each element of array A is an integer within the range [1..1,000,000,000].
 */
// vector<int> v = {4, 1, 3, 2};
bool is_permutation(vector<int> &v) {
    unsigned xorsum = 0;
    int v_size = v.size();
    std::cout << endl;
    for (int i = 0; i < v_size; ++i) {
        cout << "xorsum: " << xorsum << " ^ (i + 1): " << i+1 << " ^ v[i]: " << v[i]; // << "xorsum binary ";
//        show_binrep(xorsum);
        xorsum = (i + 1) ^ static_cast<unsigned>(v[i]) ^ xorsum;
        cout << " = " << xorsum  << endl;
    }
    return xorsum == 0;
}


/*
 A small frog wants to get to the other side of a river. The frog is initially located on one bank of the river
 (position 0) and wants to get to the opposite bank (position X+1). Leaves fall from a tree onto the surface of the river.
 You are given an array A consisting of N integers representing the falling leaves. A[K] represents the position where
 one leaf falls at time K, measured in seconds.

 The goal is to find the earliest time when the frog can jump to the other side of the river.
 The frog can cross only when leaves appear at every position across the river from 1 to X
 (that is, we want to find the earliest moment when all the positions from 1 to X are covered by leaves).
 You may assume that the speed of the current in the river is negligibly small, i.e. the leaves do not change their
 positions once they fall in the river.

 For example, you are given integer X = 5 and array A such that:
  A[0] = 1
  A[1] = 3
  A[2] = 1
  A[3] = 4
  A[4] = 2
  A[5] = 3
  A[6] = 5
  A[7] = 4

In second 6, a leaf falls into position 5. This is the earliest time when leaves appear in every position across the river.

Write a function:

    int solution(int X, vector<int> &A);

 that, given a non-empty array A consisting of N integers and integer X, returns the earliest time when the frog can
 jump to the other side of the river.

 If the frog is never able to jump to the other side of the river, the function should return −1.

 For example, given X = 5 and array A such that:
  A[0] = 1
  A[1] = 3
  A[2] = 1
  A[3] = 4
  A[4] = 2
  A[5] = 3
  A[6] = 5
  A[7] = 4

the function should return 6, as explained above.

Write an efficient algorithm for the following assumptions:

        N and X are integers within the range [1..100,000];
        each element of array A is an integer within the range [1..X].
 */

int frog_river_one(int x, vector<int> & v) {
    const int v_size = v.size();
    vector<bool> bitmap(v_size+1, false);
    if (v_size >= x) {
        auto total = x;
        for (int i = 0; i < v_size; i++) {
            if (!bitmap[v[i]]) {
                bitmap[v[i]] = true; total--;
                if (total == 0) return i;
            }
        }
    }
    return -1;
}


/*
You are given N counters, initially set to 0, and you have two possible operations on them:

increase(X) − counter X is increased by 1,
max counter − all counters are set to the maximum value of any counter.

A non-empty array A of M integers is given. This array represents consecutive operations:

if A[K] = X, such that 1 ≤ X ≤ N, then operation K is increase(X),
if A[K] = N + 1 then operation K is max counter.

For example, given integer N = 5 and array A such that:
A[0] = 3
A[1] = 4
A[2] = 4
A[3] = 6
A[4] = 1
A[5] = 4
A[6] = 4

the values of the counters after each consecutive operation will be:
(0, 0, 1, 0, 0)
(0, 0, 1, 1, 0)
(0, 0, 1, 2, 0)
(2, 2, 2, 2, 2)
(3, 2, 2, 2, 2)
(3, 2, 2, 3, 2)
(3, 2, 2, 4, 2)

The goal is to calculate the value of every counter after all operations.

Write a function:

vector<int> solution(int N, vector<int> &A);

that, given an integer N and a non-empty array A consisting of M integers, returns a sequence of integers representing the values of the counters.

Result array should be returned as a vector of integers.

For example, given:
A[0] = 3
A[1] = 4
A[2] = 4
A[3] = 6
A[4] = 1
A[5] = 4
A[6] = 4

the function should return [3, 2, 2, 4, 2], as explained above.

Write an efficient algorithm for the following assumptions:

N and M are integers within the range [1..100,000];
each element of array A is an integer within the range [1..N + 1].
*/

vector<int> max_counters(int n, vector<int> &v) {
    int max_current_counter = 0;
    int max_global_counter = 0;
    int counter_index; // index of the current counter in the counters array
    vector<int> counters(n, 0);
    int v_size = v.size();

    for(int i = 0; i < v_size; ++i) {
        counter_index = v[i] - 1;
        if(v[i] <= n && v[i] >= 1) {
            counters[counter_index] = max(max_global_counter, counters[counter_index]) + 1;
            max_current_counter = max(max_current_counter, counters[counter_index]);
        }
        else if(v[i] == n + 1) {
            max_global_counter = max_current_counter;
        }
    }

    int counters_size = counters.size();

    for(int i = 0; i < counters_size; ++i) {
        counters[i] = max(counters[i], max_global_counter);
    }
    return counters;
}

/*
 Write a function:

    int solution(vector<int> &A);

that, given an array A of N integers, returns the smallest positive integer (greater than 0) that does not occur in A.

For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.

Given A = [1, 2, 3], the function should return 4.

Given A = [−1, −3], the function should return 1.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [1..100,000];
        each element of array A is an integer within the range [−1,000,000..1,000,000].
 */

int miss_int(vector<int> &v) {
    int v_size = v.size();
    vector<bool> present(v_size+1, false);

    for (int i = 0; i < v_size; ++i) {
        if ( (v[i] > 0) && (v[i] <= v_size) ) {
            present[v[i]] = true;
        }
    }

    // Find the first element which didn't
    // appear in the original array
    for (int i = 1; i <= v_size; ++i) {
        if (!present[i]) {
            return i;
        }
    }
    // If the original array was of the
    // type {1, 2, 3} in its sorted form
    return v_size + 1;
}

/*
Compute number of integers divisible by k in range [a..b].
Write a function:
    int solution(int A, int B, int K);
that, given three integers A, B and K, returns the number of integers within the range [A..B] that are divisible by K, i.e.:
    { i : A ≤ i ≤ B, i mod K = 0 }
For example, for A = 6, B = 11 and K = 2, your function should return 3, because there are three numbers divisible by 2 within the range [6..11], namely 6, 8 and 10.

Write an efficient algorithm for the following assumptions:
        A and B are integers within the range [0..2,000,000,000];
        K is an integer within the range [1..2,000,000,000];
        A ≤ B.
 */

// B/K – (A – 1)/K

int count_div(int A, int B, int K) {
    int b = B/K, a = 0;

    if (A > 0) {
        a = (A - 1) / K;
    }
    else {
        // If A == 0 we need to count it in because 0 is divisible by any positive number
        b++;
    }
    return b - a;
}

int min_avg_two_slice(vector<int> &v) {
    size_t v_size = v.size();
    // The minimal average of the first slice
    double min_avg_value = (v[0] + v[1]) / 2.0;
    // The start position of the first
    // slice with minimal average    
    size_t min_avg_pos = 0;

    for (size_t i = 0; i < v_size - 2; ++i) {
        // Try the next 2-element slice
        double min_avg_slice_2 = (v[i] + v[i + 1]) / 2.0;
        if (min_avg_value > min_avg_slice_2) {
            min_avg_value = min_avg_slice_2;
            min_avg_pos = i;
        }
        // Try the next 3-element slice
        double min_avg_slice_3 = (v[i] + v[i + 1] + v[i + 2]) / 3.0;
        if (min_avg_value > min_avg_slice_3) {
            min_avg_value = min_avg_slice_3;
            min_avg_pos = i;
        }
    }
    // Try the last 2-element slice
    double min_avg_last_slice = (v[v_size - 2] + v[v_size - 1]) / 2.0;
    if (min_avg_value > min_avg_last_slice) {
        min_avg_pos = v_size - 2;
    }
    return min_avg_pos;
}

// Implementation of the same algorithm but without divisions and floating point variables.
// because divisions and operations with floating point nombers are significantly slower than
// work with integer numbers

int min_avg_two_slice_optimized(vector<int> &v) {
    int v_size = v.size();
    if (v_size == 2) return 0;

    int min_slice_2 = v[0] + v[1];
    int min_slice_2_pos = 0;

    int min_slice_3 = INT_MAX;
    int min_slice_3_pos = 0;

    for (int i = 2; i < v_size; i++) {
        int slice_2 = v[i - 1] + v[i];
        if (slice_2 < min_slice_2) {
            min_slice_2 = slice_2;
            min_slice_2_pos = i - 1;
        }

        int slice_3 = slice_2 + v[i - 2];
        if (slice_3 < min_slice_3) {
            min_slice_3 = slice_3;
            min_slice_3_pos = i - 2;
        }
    }
    int avg_min_2 = min_slice_2 * 3;
    int avg_min_3 = min_slice_3 * 2;

    if (avg_min_2 == avg_min_3) {
        return min(min_slice_2_pos, min_slice_3_pos);
    }
    else {
        return avg_min_2 < avg_min_3 ? min_slice_2_pos : min_slice_3_pos;
    }
}

int min_avg_two_slice2(vector<int> &v) {

    // Find prefix sum.
    int N = v.size();
    vector<int> ps(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        ps[i] = v[i - 1] + ps[i - 1];
    }

    int lft_idx, min_lft_idx;
    double avg_here, min_avg, avg_of_two, avg_with_prev;

    // Initialize variables at the first possible slice (v[0:1]).
    lft_idx = min_lft_idx = 0;
    avg_here = min_avg = (v[0] + v[1]) / 2.0;

    // Find min average of every slice that ends at ith element,
    // starting at i = 2.
    for (int i = 2; i < N; i ++) {

        // average of v[lft_idx : i]
        int sum = ps[i + 1] - ps[lft_idx];
        avg_with_prev = ((double) sum) /
                        (i - lft_idx + 1);

        // average of v[i - 1 : i]
        avg_of_two = (v[i - 1] + v[i]) / 2.0;

        // Find minimum and update lft_idx of slice
        // (previous lft_idx or i - 1).
        if (avg_of_two < avg_with_prev) {
            avg_here = avg_of_two;
            lft_idx = i - 1;
        }
        else
            avg_here = avg_with_prev;

        // Keep track of minimum so far and its left index.
        if (avg_here < min_avg) {
            min_avg = avg_here;
            min_lft_idx = lft_idx;
        }
    }
    return min_lft_idx;
}

int min_avg_two_best(vector<int> &v) {
    // keep current sum of the processed elements here
    int sum = v[0] + v[1];
    int v_size = v.size();
    int left_index, min_left_index;
    double avg_here, min_avg, avg_of_two, avg_with_prev;

    // Initialize variables at the first possible slice (v[0:1]).
    left_index = min_left_index = 0;
    min_avg = (v[0] + v[1]) / 2.0;

    // Find min average of every slice that ends at ith element,
    // starting at i = 2.
    for (int i = 2; i < v_size; ++i) {
        sum += v[i];

        // average of v[left_index : i]
        avg_with_prev = ((double) sum) / (i - left_index + 1);

        // average of v[i - 1 : i]
        avg_of_two = (v[i - 1] + v[i]) / 2.0;

        // Find minimum and update left_index of slice
        // (previous left_index or i - 1).
        if (avg_of_two < avg_with_prev) {
            avg_here = avg_of_two;
            left_index = i - 1;
            sum = v[i - 1] + v[i];
        }
        else {
            avg_here = avg_with_prev;
        }

        // Keep track of minimum so far and its left index.
        if (avg_here < min_avg) {
            min_avg = avg_here;
            min_left_index = left_index;
        }
    }
    return min_left_index;
}

/*
A non-empty array A consisting of N integers is given. The consecutive elements of array A represent consecutive cars on a road.
Array A contains only 0s and/or 1s:
    • 0 represents a car traveling east,
    • 1 represents a car traveling west.
The goal is to count passing cars. We say that a pair of cars (P, Q), where 0 ≤ P < Q < N, is passing when P is traveling to the east and Q is traveling to the west.
For example, consider array A such that:
A[0] = 0 A[1] = 1 A[2] = 0 A[3] = 1 A[4] = 1
We have five pairs of passing cars: (0, 1), (0, 3), (0, 4), (2, 3), (2, 4).
Write a function:
int solution(vector<int> &A);
that, given a non-empty array A of N integers, returns the number of pairs of passing cars.
The function should return −1 if the number of pairs of passing cars exceeds 1,000,000,000.
For example, given:
A[0] = 0 A[1] = 1 A[2] = 0 A[3] = 1 A[4] = 1
the function should return 5, as explained above.
Write an efficient algorithm for the following assumptions:
    • N is an integer within the range [1..100,000];
    • each element of array A is an integer that can have one of the following values: 0, 1.
 */

int get_pairs_passed_by(vector<int> &v) {
    size_t v_size = v.size();
    size_t pairs_passed_by = 0;
    size_t zeroes = 0;

    for(size_t i = 0; i < v_size; ++i) {
        if(0 == v[i]) {
            ++zeroes;
        }
        else if(1 == v[i]) {
            pairs_passed_by += zeroes;
            if(pairs_passed_by > 1'000'000'000) {
                return -1;
            }
        }
    }
    return pairs_passed_by;
}

/*
A DNA sequence can be represented as a string consisting of the letters A, C, G and T, which correspond to the types of
 successive nucleotides in the sequence. Each nucleotide has an impact factor, which is an integer. Nucleotides of types
 A, C, G and T have impact factors of 1, 2, 3 and 4, respectively. You are going to answer several queries of the form:
 What is the minimal impact factor of nucleotides contained in a particular part of the given DNA sequence?

The DNA sequence is given as a non-empty string S = S[0]S[1]...S[N-1] consisting of N characters. There are M queries,
which are given in non-empty arrays P and Q, each consisting of M integers. The K-th query (0 ≤ K < M) requires you to
 find the minimal impact factor of nucleotides contained in the DNA sequence between positions P[K] and Q[K] (inclusive)

For example, consider string S = CAGCCTA and arrays P, Q such that:
    P[0] = 2    Q[0] = 4
    P[1] = 5    Q[1] = 5
    P[2] = 0    Q[2] = 6

The answers to these M = 3 queries are as follows:

        The part of the DNA between positions 2 and 4 contains nucleotides G and C (twice), whose impact factors
        are 3 and 2 respectively, so the answer is 2.
        The part between positions 5 and 5 contains a single nucleotide T, whose impact factor is 4, so the answer is 4.
        The part between positions 0 and 6 (the whole string) contains all nucleotides, in particular nucleotide
        A whose impact factor is 1, so the answer is 1.

Write a function:

    vector<int> solution(string &S, vector<int> &P, vector<int> &Q);

that, given a non-empty string S consisting of N characters and two non-empty arrays P and Q consisting of M integers,
 returns an array consisting of M integers specifying the consecutive answers to all queries.

Result array should be returned as a vector of integers.

For example, given the string S = CAGCCTA and arrays P, Q such that:
    P[0] = 2    Q[0] = 4
    P[1] = 5    Q[1] = 5
    P[2] = 0    Q[2] = 6

the function should return the values [2, 4, 1], as explained above.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [1..100,000];
        M is an integer within the range [1..50,000];
        each element of arrays P, Q is an integer within the range [0..N − 1];
        P[K] ≤ Q[K], where 0 ≤ K < M;
        string S consists only of upper-case English letters A, C, G, T
 */

vector<int> DNA_impact(const string &s, vector<int> &p, vector<int> &q) {

    enum impact_t { A = 1, C = 2, G = 3, T = 4 };
    struct counters_t { int A = 0; int C = 0; int G = 0; };

    size_t dna_len = s.length();
    size_t p_size = p.size();
    vector<int> result(p_size, 0);
    vector<counters_t> cumulative_sums;
    cumulative_sums.reserve(dna_len+1);
    counters_t counters = counters_t();

    for(size_t i = 0; i <= dna_len; ++i) {
        cumulative_sums.push_back(counters);
        switch (s[i]) {
            case 'A': { counters.A++; break; }
            case 'C': { counters.C++; break; }
            case 'G': { counters.G++; break; }
        }
    }

    for(size_t i = 0; i < p_size; ++i) {
        int from = p[i], to = q[i]+1;

        // If the number of A is increased throughout the query the it contains A
        if(cumulative_sums[to].A - cumulative_sums[from].A > 0) {
            result[i] = impact_t::A;
        }
        // the same for C and other nucleotides with higher impact factor
        else if(cumulative_sums[to].C - cumulative_sums[from].C > 0) {
            result[i] = impact_t::C;
        }
        else if(cumulative_sums[to].G - cumulative_sums[from].G > 0) {
            result[i] = impact_t::G;
        }
        else { // one of the counters must be changed, so it is the T
            result[i] = impact_t::T;
        }
    }
    return result;
}

/*
MaxProductOfThree

Maximize A[P] * A[Q] * A[R] for any triplet (P, Q, R).

Description:

A non-empty array A consisting of N integers is given. The product of triplet (P, Q, R) equates to A[P] * A[Q] * A[R] (0 ≤ P < Q < R < N).
For example, array A such that:
A[0] = -3 A[1] = 1 A[2] = 2 A[3] = -2 A[4] = 5 A[5] = 6
contains the following example triplets:
    • (0, 1, 2), product is −3 * 1 * 2 = −6
    • (1, 2, 4), product is 1 * 2 * 5 = 10
    • (2, 4, 5), product is 2 * 5 * 6 = 60
Your goal is to find the maximal product of any triplet.
Write a function:

int solution(vector<int> &A);

that, given a non-empty array A, returns the value of the maximal product of any triplet.
For example, given array A such that:
A[0] = -3 A[1] = 1 A[2] = 2 A[3] = -2 A[4] = 5 A[5] = 6
the function should return 60, as the product of triplet (2, 4, 5) is maximal.
Write an efficient algorithm for the following assumptions:
    • N is an integer within the range [3..100,000];
    • each element of array A is an integer within the range [−1,000..1,000]
*/

int max_product_of_three(vector<int> &v) {
    vector<int> max_num(3,-1000);
    vector<int> min_neg(2,0);

    const int v_size = v.size();

    for (auto i = 0; i < v_size; ++i) {
        if (v[i] < min_neg[0] ) {
            min_neg[1]=min_neg[0];
            min_neg[0]=v[i];
        }
        else if (v[i] < min_neg[1]) {
            min_neg[1]=v[i];
        }
        if (v[i] > max_num[0]) {
            max_num[2]=max_num[1];
            max_num[1]=max_num[0];
            max_num[0]=v[i];
        }
        else if (v[i] > max_num[1]) {
            max_num[2]=max_num[1];
            max_num[1]=v[i];
        }
        else if (v[i] > max_num[2]) {
            max_num[2]=v[i];
        }
    }

    auto res_neg = max_num[0] * min_neg[0] * min_neg[1];
    auto res_pos = max_num[0] * max_num[1] * max_num[2];

    return max (res_pos, res_neg);
}

/*
Write a function

    int solution(vector<int> &A);

that, given an array A consisting of N integers, returns the number of distinct values in array A.

For example, given array A consisting of six elements such that:
 A[0] = 2    A[1] = 1    A[2] = 1
 A[3] = 2    A[4] = 3    A[5] = 1

the function should return 3, because there are 3 distinct values appearing in array A, namely 1, 2 and 3.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [0..100,000];
        each element of array A is an integer within the range [−1,000,000..1,000,000].
*/
int count_distinct(vector<int> &v) {
    std::unordered_set<int> hash;
    int res = 0;
    for (auto i: v) {
        if (hash.find(i) == hash.end()) {
            hash.insert(i);
            res++;
        }
    }
    return res;
}

/*
An array A consisting of N integers is given. A triplet (P, Q, R) is triangular if 0 ≤ P < Q < R < N and:

        A[P] + A[Q] > A[R],
        A[Q] + A[R] > A[P],
        A[R] + A[P] > A[Q].

For example, consider array A such that:
  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 20

Triplet (0, 2, 4) is triangular.

Write a function:

    int solution(vector<int> &A);

that, given an array A consisting of N integers, returns 1 if there exists a triangular triplet for this array and returns 0 otherwise.

For example, given array A such that:
  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 20

the function should return 1, as explained above. Given array A such that:
  A[0] = 10    A[1] = 50    A[2] = 5
  A[3] = 1

the function should return 0.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [0..100,000];
        each element of array A is an integer within the range [−2,147,483,648..2,147,483,647]
*/

int find_triangle(vector<int> &v) {
    const int v_size = v.size();
    if(v_size < 3) { return 0; }

    std::sort(v.begin(), v.end());

    for (auto i = 2; i < v_size; ++i) {
        if (v[i - 2] > v[i] - v[i - 1]) {
            return 1;
        }
    }
    return 0;
}

/*
We draw N discs on a plane. The discs are numbered from 0 to N − 1. An array A of N non-negative integers, specifying
the radiuses of the discs, is given. The J-th disc is drawn with its center at (J, 0) and radius A[J].

We say that the J-th disc and K-th disc intersect if J ≠ K and the J-th and K-th discs have at least one common point
(assuming that the discs contain their borders).

The figure below shows discs drawn for N = 6 and A as follows:
  A[0] = 1
  A[1] = 5
  A[2] = 2
  A[3] = 1
  A[4] = 4
  A[5] = 0

There are eleven (unordered) pairs of discs that intersect, namely:

        discs 1 and 4 intersect, and both intersect with all the other discs;
        disc 2 also intersects with discs 0 and 3.

Write a function:

    int solution(vector<int> &A);

that, given an array A describing N discs as explained above, returns the number of (unordered) pairs of intersecting discs.
The function should return −1 if the number of intersecting pairs exceeds 10,000,000.

Given array A shown above, the function should return 11, as explained above.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [0..100,000];
        each element of array A is an integer within the range [0..2,147,483,647].
*/

int number_of_disc_intersections3(vector<int> &v) {

    const auto MAX_INTERSECTIONS = 10000000;
    int pairs = 0;

    const int v_size = v.size();

    // create an array of pairs, each containing the start and end indices of a disk
    multimap<int64_t, int64_t> segments;

    // Add the pairs to the array
    for (int64_t i = 0; i < v_size; ++i) {
        int64_t radius = v[i];
        // If radius of the circle is bigger than distance to the origin of the coordinate axis or
        // the radius is bigger than length of the given array
        // add this segment to the first point or to the last point.
        // We do it to avoid of scanning from MIN_INT to MAX_INT
        // because the task defines the range started from 0 to end of the given array.
        // We don't need to work outside of this range
//        int64_t begin = max(0L, i - radius);
//        int64_t end = min(v_size - 1, i + radius);
        int64_t begin = i - radius;
        int64_t end = i + radius;

        segments.insert({begin, end});
    }

//    for(auto i = 0; i < v_size; ++i ) {
    for (int i = 0; i < v_size; ++i) {
//        for(auto e : segments) {
// # for each disk in order of the *starting* position of the disk, not the centre

// # find the end position of that disk from the array of tuples
//        auto disk_end = segments.find(i); // intervals[i][1]

// # find the index of the rightmost value less than or equal to the interval-end
// # this finds the number of disks that have started before disk i ends
        // count = bisect_right(starts, disk_end )
        auto it = segments.upper_bound(i);

        auto count = distance(segments.begin(), it);
/*
        # subtract current position to exclude previous matches
        # this bit seemed 'magic' to me, so I think of it like this...
        # for disk i, i disks that start to the left have already been dealt with
        # subtract i from count to prevent double counting
        # subtract one more to prevent counting the disk itself
        count -= (i+1)
        pairs += count
        if pairs > 10000000:
            return -1
 */
        count -= (i+1);
        pairs += count;
        if (pairs > MAX_INTERSECTIONS) {
            return -1;
        }
    }
    return pairs;
}

int number_of_disc_intersections_sort(vector<int> &v) {

    using segment = std::pair<int, int>;
    const auto MAX_INTERSECTIONS = 10000000;
    int intersections = 0;

    size_t v_size = v.size();

    // create an array of pairs, each containing the start and end indices of a disk
    vector<segment> segments;
    // reserve the memory for all the pairs to avoid of many allocations
    segments.reserve(v_size);

    // Add the pairs to the array
    for (size_t i = 0; i < v_size; ++i) {
        int radius = v[i];
        // If radius of the circle is bigger than distance to the origin of the coordinate axis or
        // the radius is bigger than length of the given array
        // add this segment to the first point or to the last point.
        // We do this to avoid of scanning from MIN_INT to MAX_INT
        // because the task defines the range started from 0 to end of the given array.
        // We don't need to work outside of this range
        int begin = max(0, static_cast<int>(i) - radius);
        int end = min(v_size - 1, i + radius);
        segments.emplace_back(begin, end);
    }

    // sort the array by the first entry of each pair: the disk start indices
    sort(segments.begin(), segments.end());

    for (size_t i = 0; i < v_size; ++i) {
        // for each disk in order of the *starting* position of the disk, not the centre
        // find the end position of that disk from the array of tuples
        auto disk_end = segments[i].second;
        // find the index of the rightmost value less than or equal to the interval-end
        // this finds the number of disks that have started before disk i ends
        auto it = upper_bound(segments.begin(), segments.end(), make_pair(disk_end, 0),
                              [](segment lhs, segment rhs) -> bool { return lhs.first < rhs.first; });

        auto count = distance(segments.begin(), it);

        // subtract current position to exclude previous matches
        // for disk i, i disks that start to the left have already been dealt with
        // subtract i from count to prevent double counting
        // subtract one more to prevent counting the disk itself
        count -= (i + 1);
        intersections += count;
        if (intersections > MAX_INTERSECTIONS) {
            return -1;
        }
    }
    return intersections;
}

int number_of_disc_intersections(vector<int> &v) {
    const auto MAX_INTERSECTIONS = 10000000;
    size_t v_size = v.size();

    vector<int> start(v_size, 0), end(v_size, 0);

    // Assume circles as segments on the coordinate axis.
    // Count all start and end points of the segments intersects on each point of the axis
    for (size_t i = 0; i < v_size; ++i) {
        // If radius of the circle is bigger than distance to the origin
        // of the coordinate axis or
        // the radius is bigger than length of the given array
        // add this segment to the first point or to the last point.
        // We do this to avoid of scanning from MIN_INT to MAX_INT
        // because the task defines the range started from 0 to end of the given array.
        // We don't need to work outside of this range
        start[max(0, static_cast<int>(i) - v[i])]++;
        end[min(v_size - 1, i + v[i])]++;
    }

     // Number of "active" segments that is segments which intersect at the point i
    int active = 0;
     // Total number of intersections.
    int intersections = 0;
    for (size_t i = 0; i < v_size; i++) {
/*
 Walk by the array and count the segments which contain the current point “i” on the axis.
 Whenever a new segment starts at location “i”, it intersects with all existing segment (disks) at that location.
 That's why we have “active * start[i]” part in the formula. We also need to add the number of intersections for all
 the segments that just started at location “i”, i.e., the number of intersections within themselves excluding whatever
 already existed “(start[i] * (start[i] - 1)) / 2”.  For example if started 5 segments (disks) in one point,
 it will increased by (1+2+3+4+5 intersections, or 5*(5-1) / 2.
 */
        intersections += active * start[i] + (start[i] * (start[i] - 1)) / 2;
        if (intersections > MAX_INTERSECTIONS) {
            return -1;
        }
        active += start[i] - end[i];
    }
    return intersections;
}


template< class Iter >
void fill_with_random_int_values( Iter start, Iter end, int min, int max) {
    static std::random_device rd;    // you only need to initialize it once
    static std::mt19937 mte(rd());   // this is a relative big object to create

    std::uniform_int_distribution<int> dist(min, max);

    std::generate(start, end, [&] () { return dist(mte); });
}

int main() {
//    const auto N = 100000;
    vector<int> v0 = {};
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v = {4,2,2,5,1,5,8};
//    vector<int> v = {4, 1, 3, 2};
    vector<int> v2 = {9, 3, 9, 3, 9, 7, 9};
    vector<int> v3 = {1,3,1,4,2,3,5,4};
    vector<int> v4 = {3,4,4,6,1,4,4};
    vector<int> v5 = {1, 3, 6, 4, 1, 2};
    vector<int> v6 = {10, 10, 10};
    vector<int> v7 = {0, 1, 0, 1, 1};
//    vector<int> v8(1000000, 0);
//    fill_with_random_int_values(v8.begin(), v8.end(), -100, 100);

    vector<int> v8 = {-5, 5, -5, 4}; // 125
//    vector<int> v8 = {-3, 1, 2, -2, 5, 6}; // 60
//    vector<int> v8 = {4, 5, 1, 0}; // 20
//    vector<int> v8 = {-10, -2, -4}; // -80

//    vector<int> test_v(100000, 9);

    vector<int> v9 = {2, 1, 1, 2, 3, 1};
    vector<int> v10 = {10, 2, 5, 1, 8, 20};
    // vector<int> v11 = {1,5,2,1,4,0}; // expected 11
    vector<int> v11 = {1, 2147483647, 0}; // expected 2

    vector<int> p = {0};
    vector<int> q = {0};

    cout << "number_of_disc_intersections is " <<  number_of_disc_intersections2(v11)  << endl;
    cout << "find_triangle is " <<  find_triangle(v10)  << endl;
    cout << "count_distinct is " <<  count_distinct(v9)  << endl;
    cout << "max_product_of_three is " <<  max_product_of_three(v8)  << endl;

    cout << "DNA_impact result:  " << endl;
    print(DNA_impact("C", p, q));

    cout << "get_pairs_passed_by is " <<  get_pairs_passed_by(v7)  << endl;

    cout << "min_avg_two_slice is " <<  min_avg_two_slice(v)  << endl;
    cout << "min_avg_two_slice_optimized is " <<  min_avg_two_slice_optimized(v)  << endl;
    cout << "min_avg_two_slice2 is " <<  min_avg_two_slice2(v6)  << endl;
    cout << "min_avg_two_best is " <<  min_avg_two_best(v6)  << endl;

    print(v5);
    cout << "miss_int " << miss_int(v5) << endl;

    cout << "counters vector: "  << endl;
    print(max_counters(5, v4));

    cout << endl << "frog_river_one = " << frog_river_one(5, v3) << endl;
/*
    for (auto i = 0; i < 42; ++i) {
        right_rotate_reverse(v1, i);
        cout << "i = " << i << endl;
        print(v1);
    }
*/

    cout << "count_div is " <<  count_div(0, 0, 11)  << endl;
    cout << "Odd number is " << get_odd_occurrence(v2) << endl;

    cout << "missing element is " << find_missing_element(v) << endl;

    cout << "array is" << ((is_permutation(v)) ? "" : " NOT") <<  " a permutation";
/*
    auto t0 = std::chrono::high_resolution_clock::now();
    for(auto i = 0; i < N; ++i) {
        left_rotate(test_v, 60000);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    auto ticks_per_iteration = (t1 - t0)/N;
    cout << "Bentley " << ticks_per_iteration.count() << endl;

    t0 = std::chrono::high_resolution_clock::now();
    for(auto i = 0; i < N; ++i) {
        left_rotate_reverse(test_v, 60000);
    }
    t1 = std::chrono::high_resolution_clock::now();
    ticks_per_iteration = (t1 - t0)/N;
    cout << "Left Reverse " << ticks_per_iteration.count() << endl;


    t0 = std::chrono::high_resolution_clock::now();
    for(auto i = 0; i < N; ++i) {
        right_rotate_reverse(test_v, 60000);
    }
    t1 = std::chrono::high_resolution_clock::now();
    ticks_per_iteration = (t1 - t0)/N;
    cout << "Right Reverse " << ticks_per_iteration.count() << endl;


    t0 = std::chrono::high_resolution_clock::now();
    for(auto i = 0; i < N; ++i) {
        left_rotate_swap(test_v, 60000);
    }
    t1 = std::chrono::high_resolution_clock::now();
    ticks_per_iteration = (t1 - t0)/N;
    cout << "Swap " << ticks_per_iteration.count() << endl;
*/

    return 0;
}