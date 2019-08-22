#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <bitset>

// Used "experimental" for compatibility with old compilers.
#include <experimental/optional>


using namespace std;
using namespace experimental;


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

int main() {

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

    return 0;
}