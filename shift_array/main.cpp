#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <chrono>

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
/*  non destructive solution
    int res = 0;
    for(auto i: v) {
        res ^= i;
    }
    return res;
*/

// destructive solution
    for(auto i = 1; i < v.size(); ++i) {
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


int main() {
    const auto N = 100000;
    vector<int> v0 = {};
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v = {1, 2, 3, 4, 5, 7, 8, 9};
    vector<int> v2 = {9, 3, 9, 3, 9, 7, 9};

//    vector<int> test_v(100000, 9);



    print(v1);
/*
    for (auto i = 0; i < 42; ++i) {
        right_rotate_reverse(v1, i);
        cout << "i = " << i << endl;
        print(v1);
    }
*/

    cout << "Odd number is " << get_odd_occurrence(v2) << endl;

    cout << "missing element is " << find_missing_element(v);
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