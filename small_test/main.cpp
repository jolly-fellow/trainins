
#include <iostream>
#include <vector>
#include <algorithm>

#include <optional>

using namespace std;

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



int main() {

    vector<int> v {1,2,5,2};
    vector<int> v1 {1,1,5,1};
    std::cout << std::boolalpha << solution2(v1);

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
