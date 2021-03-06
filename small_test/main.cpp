
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <optional>
#include <sstream>
#include <memory>

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



#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

long countTriplets() { // (const vector<long>&, long ) {
    vector<long> arr {1, 2, 2, 4};
    long r = 2;
    long count = 0;
    // ratio: a, b=a*r, c=a*r*r
    unordered_map<long,long> b; // key=possible 2nd triplet members from values of a, value=count
    unordered_map<long,long> c; // key=possible 3rd triplet members from values of b, value=count
    for(const long i : arr) {
        const auto next = i * r;
        if(c.count(i) > 0) {
            count += c[i];
        }
        if(b.count(i) > 0) {
            c[next] += b[i];
        }
        ++b[next];
    }
    return count;
}
#endif

template<typename T>
void adl(T) {
    cout << "T";
}

struct S {

};

template<typename T>
void call_adl(T t) {
    adl(S());
    adl(t);
}

void adl(S) {
    cout << "S";
}

template<typename T>
class Foo {
    T tVar;
public:
    Foo() {}
    Foo(T t): tVar(t) {}
};

class FooDerived: public Foo<std::string> {

};




template<template<typename> class>
struct X {
    X() {
        cout << "1" ;
    }
};

template<typename>
struct Y {};

template<typename T>
using Z = Y<T>;

template<>
struct X<Y> {
    X() { cout << "2" ; }
};


struct A {
    A() { throw 2; }
};

struct B {
    B() {
        try {
            A a;
        }
        catch (int i) {
            cout << i;
        }
    }
};


int countPairs(vector<int> projectCosts, int target) {
    unordered_map<int, int> m;
    for (int i : projectCosts) {
        m[i]++;
    }

    int count = 0;

    for (auto i : m) {
        if ((i.second > 1) || (m.count(i.first + target))) {
            ++count;
        }
    }
    return count;

}

int findPairs(vector<int>& nums, int k) {
    unordered_map<int, int> m;
    for (int n : nums) m[n]++;
    int cnt = 0;
    for (auto p : m) {
        if ((!k && p.second > 1)
            || (k && m.count(p.first + k))) ++cnt;
    }
    return cnt;
}

int min_steps(string s, string t) {
    int mymap1[26] = { 0 };
    int mymap2[26] = { 0 };

    for (int i = 0; i < s.length(); i++) {
        mymap1[s[i] - 'a']++;
        mymap2[t[i] - 'a']++;
    }

    int count = 0;

    for (int i = 0; i < 26; i++) {
        if (mymap2[i] > mymap1[i])
            count += mymap2[i] - mymap1[i];
    }
    return count;
}

void f(vector<string> v, int n) {
    for(auto s: v) {
        int size_s = s.size();
        if(size_s < 1) { cout << -1; }
        if(size_s % 2 == 0) {
            string sub1 = s.substr(0,size_s / 2);
            string sub2 = s.substr(size_s / 2);
            cout << min_steps(sub1,sub2);
        }
    }
}

class asd {
public:
    int vvv = 5;
    void aaa() {

    }
};


int removeDuplicates(vector<int>& v) {
    int v_size = v.size();
    int p = 1, dups = 0;
    for(int i = 0; (i < v_size) && (p < v_size); ++i, ++p) {
        while( (v[i] == v[p]) && (p < v_size) ) {
            ++ p;
            ++ dups;
        }
        if(p < v_size) {
            v[i+1] = v[p];
        }
    }
    return v_size - dups;
}



using ppid_t = int;
using pid_t = int;

struct process_t {
    ppid_t ppid;
    pid_t pid;
    string name;
    vector<pid_t> children;
};

using processes_t = unordered_map<ppid_t, process_t>;

processes_t proc_map;

void parse_input() {

    process_t root;
    root.pid = 0;
    root.ppid = 0;
    root.name = "";
    proc_map.emplace(root.ppid, root);

    for (std::string line; std::getline(std::cin, line); ) {
        std::istringstream iss(line);
        process_t process;
        iss >> process.pid >> process.ppid >> process.name;

        if(proc_map.count(process.pid) == 0) {
            proc_map.emplace(process.pid, process);
            proc_map[process.ppid].children.push_back(process.pid);
        }
        else {
            cout << "error. It should never happens"; exit(1);
        }
    }
}

void print_proc(pid_t pid) {

    static string tabs;
    auto process = proc_map[pid];
    cout << tabs << "PPID: " << process.ppid << " PID: " << process.pid << " name: " <<  process.name << endl;
    for(auto p: process.children) {
        tabs.push_back('\t');
        print_proc(p);
        tabs.pop_back();
    }
}

const string IsOneEditAway(string s1, string s2) {

    int s1_size = s1.size();
    int s2_size = s2.size();

    if(s1 == s2) {
        return "NOTHING";
    }

    if (s2_size == 0 || s1_size == 0) {
        return "IMPOSSIBLE";
    }

    if ((s1_size - s2_size) > 1 || (s2_size - s1_size) > 1  ) {
        return "IMPOSSIBLE";
    }

    int i = 0, j = 0;
    int diff = 0;
    while (i < s1_size && j < s2_size) {
        char f = s1[i];
        char s = s2[j];
        if (f != s) {
            diff++;
            if (s1_size > s1_size)
                i++;
            if (s1_size > s1_size)
                j++;
            if (s1_size == s1_size)
                i++; j++;
        }
        else{
            i++; j++;
        }
        if (diff > 1) {
            return "IMPOSSIBLE";
        }
    }

    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    if (diff == 1 && s1 == s2) {
        return "MOVE";
    }

    if (diff == 1 && s1_size != s2_size) {
        return "REMOVE";
    }

    return "INSERT";

}


void merge(int A[], int m, int B[], int n) {
    int p = m-1, q = n-1, i = m+n-1;
    while ( q>=0 ) {
        if ( p<0 || B[q] >= A[p] )
            A[i--] = B[q--];
        else
            A[i--] = A[p--];
    }
}

void merge(vector<int>& v1, int s1, vector<int>& v2, int s2) {

    int v1_size = v1.size() - 1;
    --s1, --s2;

    while( s2 >= 0) {
        if ( s1 < 0 || v2[s2] >= v1[s1] )
            v1[v1_size--] = v2[s2--];
        else
            v1[v1_size--] = v1[s1--];
    }
}

void print_vector(const vector<int> & v) {
    for (auto const& i : v) {
        std::cout << i << ' ';
    }
}

void print_vector(const vector<string> & v) {
    for (auto const& i : v) {
        std::cout << i << ' ';
    }
}

class Solution {
public:
    struct TrieNode {
        vector<TrieNode*> child;
        string word;
        explicit TrieNode() : child(26, nullptr) {}
    };

    static TrieNode* buildTrie(vector<string>& words) {
        auto * root = new TrieNode();
        for (const string& w : words) {
            TrieNode * curr = root;
            for (char c : w) {
                int i = c - 'a';
                if (curr->child[i] == nullptr) { curr->child[i] = new TrieNode(); }
                curr = curr->child[i];
            }
            curr->word = w;
        }
        return root;
    }

    static vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        int board_x_size = board.size();
        int board_y_size = board[0].size();
        TrieNode* root = buildTrie(words);
        for(int i = 0; i < board_x_size; ++i) {
            for (int j = 0; j < board_y_size; ++j) {
                dfs(board, i, j, root, result);
            }
        }
        return result;
    }

    static void dfs(vector<vector<char>>& board, int i, int j, TrieNode* curr, vector<string>& out) {
        char c = board[i][j];
        if(c == '#' || curr->child[c - 'a'] == nullptr) return;
        curr = curr->child[c - 'a'];
        if (!curr->word.empty()) {
            out.push_back(curr->word);
            curr->word.clear();
        }
        board[i][j] = '#';
        if(i > 0) dfs(board, i - 1, j , curr, out);
        if(j > 0) dfs(board, i, j - 1, curr, out);
        if(i < board.size() - 1) dfs(board, i + 1, j, curr, out);
        if(j < board[0].size() - 1) dfs(board, i, j + 1, curr, out);
        board[i][j] = c;
    }
};


class Solution2 {
public:
    struct TrieNode {
        vector<unique_ptr<TrieNode>> links;
        string word;
        TrieNode() : links(26) {}

        bool has_key(char ch) const {
            return links[ch -'a'] != nullptr;
        }

        void put(char ch, unique_ptr<TrieNode> node) {
            links[ch -'a'] = move(node);
        }

        void make_node(char ch) {
            links[ch -'a'] = make_unique<TrieNode>();
        }


        [[nodiscard]] const unique_ptr<TrieNode> & get_node(char ch) const  {
            return links.at(ch -'a');
        }

    };

    static const unique_ptr<TrieNode> buildTrie(vector<string>& words) {
        auto root = make_unique<TrieNode>();
        for (const string& w : words) {
            TrieNode * curr = root.get();
            for (char c : w) {
                if( ! curr->has_key(c)) { curr->make_node(c); }
                curr = curr->get_node(c).get();
            }
            curr->word = w;
        }
        return root;
    }

    static vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        int board_x_size = board.size();
        int board_y_size = board[0].size();
        auto root = buildTrie(words);
        for(int i = 0; i < board_x_size; ++i) {
            for (int j = 0; j < board_y_size; ++j) {
                dfs(board, i, j, root.get(), result);
            }
        }
        return result;
    }

    static void dfs(vector<vector<char>>& board, int i, int j, TrieNode * curr, vector<string>& out) {
        char c = board[i][j];
        if(c == '#' || (!curr->has_key(c)) ) { return; }
        curr = curr->get_node(c).get();
        if (!curr->word.empty()) {
            out.push_back(curr->word);
            curr->word.clear();
        }
        board[i][j] = '#';
        if(i > 0) dfs(board, i - 1, j , curr, out);
        if(j > 0) dfs(board, i, j - 1, curr, out);
        if(i < board.size() - 1) dfs(board, i + 1, j, curr, out);
        if(j < board[0].size() - 1) dfs(board, i, j + 1, curr, out);
        board[i][j] = c;
    }
};


class Trie {
/*
    struct TrieNode {
        bool end = false;
        vector<TrieNode*> links;
        TrieNode() : links(26, nullptr) {}

        bool has_key(char ch) {
            return links[ch -'a'] != nullptr;
        }

        void put(char ch, TrieNode * node) {
            links[ch -'a'] = node;
        }

        TrieNode * get(char ch) {
            return links[ch -'a'];
        }
        void setEnd() {
            end = true;
        }
        bool isEnd() {
            return end;
        }
    } root;
*/
    struct TrieNode {
        bool end = false;
        unordered_map<char, unique_ptr<TrieNode>> links;

        void put(char ch, unique_ptr<TrieNode> node) {
            links.emplace(ch, move(node));
        }

        bool has_key(char ch) {
            return links.count(ch); // if contains then count > 0;
        }

        TrieNode * get(char ch) {
            return links[ch].get();
        }
        void setEnd() {
            end = true;
        }
        bool isEnd() {
            return end;
        }
    } root;

    // search a prefix or whole key in trie and
    // returns the node where search ends
    TrieNode * searchPrefix(const string & word) {
        TrieNode * node = &root;
        for (int i = 0; i < word.length(); i++) {
            char curLetter = word[i];
            if (node->has_key(curLetter)) {
                node = node->get(curLetter);
            }
            else {
                return nullptr;
            }
        }
        return node;
    }

public:
    /** Initialize your data structure here. */
    Trie() {
    }

    /** Inserts a word into the trie. */
    void insert(const string & word) {

        TrieNode * node = &root;

        for (int i = 0; i < word.length(); i++) {
            char ch = word[i];
            if (!node->has_key(ch)) {
                node->put(ch, std::make_unique<TrieNode>());
            }
            node = node->get(ch);
        }
        node->setEnd();
    }

    /** Returns if the word is in the trie. */
    bool search(const string & word) {
        TrieNode * node = searchPrefix(word);
        return node != nullptr && node->isEnd();
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(const string & prefix) {
        TrieNode * node = searchPrefix(prefix);
        return node != nullptr;
    }
};


int main() {

/*
    Trie trie;
    trie.insert("apple");
    cout << trie.search("apple") << endl;   // return True
    cout << trie.search("app") << endl;     // return False
    cout << trie.startsWith("app") << endl; // return True
    trie.insert("app");
    cout << trie.search("app") << endl;     // return True
*/
    vector<vector<char>> board {{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}};
    vector<string> words {"oath","pea","eat","rain"};
    auto result = Solution2::findWords(board, words);

    print_vector(result);

//    parse_input();
//    print_proc(0);

// ----------
    vector<int> v1{1,2,3,0,0,0};
    vector<int> v2{2,5,6};

//    merge(v1, 3, v2, 3);
//    print_vector(v1);

//    cout << removeDuplicates(v) << endl;

/*
    float g = 10;
    void *ptr=&g;
    float f=*(float *)ptr;

    cout << f;

    int x=10, a=-3;
    x=+a;
    printf("%d",x);

    cout << endl;



    ofstream fout(getenv("OUTPUT_PATH"));

    string nr_temp;
    getline(cin, nr_temp);

    vector<string> nr = split(rtrim(nr_temp));

    int n = stoi(nr[0]);

    long r = stol(nr[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<long> arr(n);

    for (int i = 0; i < n; i++) {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }
*/

//    long ans = countTriplets(arr, r);
//    long ans = countTriplets();

//    fout << ans << "\n";

//    fout.close();

    return 0;
}
/*
string ltrim(const string &str) {
    string s(str);

    s.erase(
            s.begin(),
            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
            find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
            s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
*/