
#include <iostream>
#include <vector>
#include <algorithm>

#include <optional>

using namespace std;

#if 0

// it returns the second biggest number after the maximal item of the input array
// in case of incorrect input array size (0 or 1) returns an empty object.

optional<int> second_max(const vector<int> & input_array) {

    int max_element = 0;
    int result = 0;
    size_t array_length =  input_array.size();

    if( array_length < 2 ) {
        return nullopt;
    }

    if( array_length == 2 ) {
        return min(input_array[0],input_array[1]);
    }

    for( auto i: input_array) {

        if( i > max_element ) {
            result = max_element;
            max_element = i;
        }

    }

    return result;
}

void print_array(const vector<int> & input_array) {

    cout << "array length = " << input_array.size() << endl;
    cout << "array content {";
    for (auto i : input_array) {
        cout << i << " ";
    }
    cout << "}" << endl;
}

void test(const vector<int> & input_array) {

    auto result = second_max(input_array);

    if(result) {
        print_array(input_array);
        cout << "The second after max number is: " << *result << endl;
    }
    else {
        cout << "incorrect input array" << endl;
        print_array(input_array);
    }
}


bool solution2(vector<int> &v) {
    unsigned xorsum = 0;
    size_t v_size = v.size();
    for (size_t i = 0; i < v_size; i++) {
        xorsum = (i + 1) ^ static_cast<unsigned>(v[i]) ^ xorsum;
    }
    return xorsum == 0;
}

#include <algorithm>
int solution(vector<int> &v) {
    int v_size = v.size();
    auto min_max = std::minmax_element(v.begin(), v.end());

    int min_element = *min_max.first;

    if(min_element != 1) {
        return false;
    }

    int max_element = *min_max.second;

    // if this is a sequence then max - min + 1 elements must be equal to number of given elements
    if ( (max_element - min_element  + 1) != v_size) {
        return false;
    }

    // pass through the whole array
    for (int i = 0; i < v_size; ++i) {
        int j; // auxiliary index

        if (v[i] < 0) {
            j = -v[i] - min_element;
        }
        else {
            j = v[i] - min_element;
        }

        if (v[j] > 0) {
            v[j] = -v[j];
        }
        else {
            // if the value at index j is negative then it is repeated
            return false;
        }
    }
    // If we didn't meet a negative element then this is a sequence
    return true;
}

void calc(vector<int> q) {
    int ans = 0;
    for (int i = q.size() - 1; i >= 0; i--) {
        if (q[i] - (i + 1) > 2) {
            cout << "Too chaotic" << endl;
            return;
        }
        for (int j = max(0, q[i] - 2); j < i; j++)
            if (q[j] > q[i]) {
                ans++;
            }
    }
    cout << ans << endl;
}

/*
i   arr                         swap (indices)
0   [7, 1, 3, 2, 4, 5, 6]   swap (0,3)
1   [2, 1, 3, 7, 4, 5, 6]   swap (0,1)
2   [1, 2, 3, 7, 4, 5, 6]   swap (3,4)
3   [1, 2, 3, 4, 7, 5, 6]   swap (4,5)
4   [1, 2, 3, 4, 5, 7, 6]   swap (5,6)
5   [1, 2, 3, 4, 5, 6, 7]
*/
int minimumSwaps(vector<int> arr) {
    int count = 0;
    int i = 0;
    int v_size = arr.size();
    while (i < v_size) {
        if (arr[i]!=i+1){
            int temp = arr[i];
            arr[i] = arr[arr[i]-1];
            arr[temp-1] = temp;
            count ++;
        }
        else {
            i++;
        }
    }
    return count;
}

using query_t = std::tuple<int, int, int>;

using data_t = vector<query_t>;

int test(int N, int K, const data_t & data) {
    long int p,q,sum,i, max=0,x=0;

    vector<long int> a(N+1);

    for(i=0;i<K;i++) {
        std::tie(p, q, sum) = data[i];
        a[p]+=sum;
        if((q+1)<=N) a[q+1]-=sum;
    }

    for(i=1;i<=N;i++) {
        x=x+a[i];
        if(max<x) max=x;
    }
    return max;
}

int main() {

    vector<int> v {1,2,5,2};
    vector<int> v1 {1,1,5,1};
    vector<int> v2 {7, 1, 3, 2, 4, 5, 6};
    int N = 5, K = 3;
    data_t data {
            {1, 2, 100},
            {2, 5, 100},
            {3, 4, 100}
    };


    data_t data2{
            {1, 5, 3},
            {4, 8, 7},
            {6, 9, 1}
    };

    // cout << minimumSwaps(v2) << endl;
    // cout << test(N, K, data) << endl;
    // cout << test(10, K, data2) << endl;
    // calc(v2);


    // std::cout << std::boolalpha << solution2(v1);

/*
    const vector<int> incorrect_input_array1 = {};
    const vector<int> incorrect_input_array2 = {0};


    const vector<int> input_array0 = {0,1};
    const vector<int> input_array1 = {0,1,2,3,4,5,6,7,8,9,0};
    const vector<int> input_array2 = {0,0,0,0,0,0,0,0,0,0,0};
    const vector<int> input_array3 = {0,1,2,3,4,5,6,7,8,9,0};

    test({});
    test({0});
    test({0,1});
    test({0,1,2,3,4,5,6,7,8,9,0});
    test({0,0,0,0,0,0,0,0,0,0,0});
    test({9,8,7,6,5,4,3,2,1});
*/
    return 0;
}

#endif

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the checkMagazine function below.
void checkMagazine(vector<string> magazine, vector<string> note) {

/*
    unordered_map<string, int> words;

    for (auto &it: magazine) {
        words[it]++;
    }

    for (auto &it: note) {
        if (words[it]>0) {
            words[it]--;
        }
        else
            cout << "No";
        return;
    }
    cout << "Yes";
*/

    unordered_multiset<string> set(magazine.begin(), magazine.end());

    for (auto &word : note) {
        auto p = set.find(word);
        if (p != set.end()) {
            set.erase(p);
        } else {
            cout << "No";
            return;
        }
    }
    cout << "Yes";
}



int main()
{
    string mn_temp;
    getline(cin, mn_temp);

    vector<string> mn = split_string(mn_temp);

    int m = stoi(mn[0]);

    int n = stoi(mn[1]);

    string magazine_temp_temp;
    getline(cin, magazine_temp_temp);

    vector<string> magazine_temp = split_string(magazine_temp_temp);

    vector<string> magazine(m);

    for (int i = 0; i < m; i++) {
        string magazine_item = magazine_temp[i];

        magazine[i] = magazine_item;
    }

    string note_temp_temp;
    getline(cin, note_temp_temp);

    vector<string> note_temp = split_string(note_temp_temp);

    vector<string> note(n);

    for (int i = 0; i < n; i++) {
        string note_item = note_temp[i];

        note[i] = note_item;
    }

    checkMagazine(magazine, note);

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
