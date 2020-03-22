#include <iostream>
#include <strings.h>
#include <bitset>
#include <cmath>
#include <cstring>


void print_bits(unsigned n) {
    /* step 1 */
    if (n > 1)
        print_bits(n/2);

    /* step 2 */
    std::cout << n % 2;
}

unsigned set_bit(unsigned bit_fld, int n) {
    return bit_fld |= (1 << n);
}

unsigned clear_bit(unsigned bit_fld, int n) {
    return bit_fld &= ~(1 << n);
}

unsigned toggle_bit(unsigned bit_fld, int n) {
    return bit_fld ^= (1 << n);
}

unsigned test_bit(unsigned bit_fld, int n) {
    return bit_fld & (1 << n);
}


/*
 * The idea is based on the concept that if we AND a bit sequence with a shifted version of itself, we’re effectively
 * removing the trailing 1 from every sequence of consecutive 1s.

      11101111   (x)
    & 11011110   (x << 1)
    ----------
      11001110   (x & (x << 1))
        ^    ^
        |    |
   trailing 1 removed

    So the operation x = (x & (x << 1)) reduces length of every sequence of 1s by one in binary representation of x.
    If we keep doing this operation in a loop, we end up with x = 0. The number of iterations required to reach 0 is
    actually length of the longest consecutive sequence of 1s.
 */

const unsigned ALL_ONES = (unsigned)-1;

int longest_1bit_sequence(unsigned n) {
    if (n == 0) return 0;
    if (n == ALL_ONES) return 8*sizeof(n);
    int count = 0;

    while(n) {
        // This operation reduces length
        // of every sequence of 1s by one.
        n = (n & (n << 1));
        count++;
    }
    return count;
}

int longest_0bit_sequence(unsigned n) {
    if (n == 0) return 8*sizeof(n);
    if (n == ALL_ONES) return 0;
    int count = 1;
    // switch a last bit of each 0bit sequence to 1;
    n = (n | n << 1 | 1);

    while(n != ALL_ONES) {
        // This operation reduces length
        // of every sequence of 0s by one.
        n = (n | (n << 1));
        count++;
    }
    return count;
}

int last0bits(unsigned n) {
    return ffs(n) - 1;
}

int first0bits(unsigned n) {
    unsigned test = n & (1 << (8*sizeof(n)-1));
    int count = 0;
    while ( ! test ) {
        n <<= 1;
        test = n & (1 << 8*sizeof(n)-1);
        count++;
    }
    return count;
}

int max_binary_gap(unsigned N) {
    //if N < 2 it means we have the only bit which may be set to 1 so we can't have the gap here.
    if (N < 2) { return 0; }

    // Init counters of bits for a current gap and a longest gap
    int max = 0, count = 0;
    /* N % 2 != 0 only in case we have the first bit set to 1.

     Example:
     0000 0001 = 1
     0000 0011 = 3
     0000 0111 = 7
     0000 1111 = 15
     and so on.

     N % 2 == 0 only in case we have the first bit set to 0.

     Example:
     0000 0000 = 0
     0000 0010 = 2
     0000 0110 = 6
     0000 1110 = 14
     and so on.

     Division of N by 2 do the same as right shift operation that is move all the bits right to one position,
     but integer division operation exists in all programming languages when bit shift operations usually have
     low level languages only so division by 2 is more general solution.
     Thus this line means "repeat while the first bit is 0 right shift all the bits to one position.
    */
    while (N % 2 == 0) { N /= 2; }// Thus this line means "until the last bit is 0 right shift the bits to one position"

    // Repeat while we have 1th bits in the N variable
    while (N > 0) {

        // if the first bit of the N is 1 it means we reached the end of the current gap
        if (N % 2 == 1) {

            // if the current gap is bigger than the max gap make it the max
            if (count > max) { max = count; }

            // clean the counter to count the next gap length
            count = 0;
        }
        else {
            // if the first bit of the N is 0 just count the current bit to the current gap
            count++;
        }
        // right shift to work with a next bit
        N /= 2;
    }
    return max;
}

typedef struct _NODE
{
    struct _NODE	*node_next;
    int				key;
    char				*data;
} ITEM, *NODE, *LIST;

LIST AddKey(LIST list, int key, char* data) {
    // create and fill a new node
    NODE new_node = (NODE) malloc(sizeof(ITEM));

    if(!new_node) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    new_node->key = key;
    new_node->data = data;
    new_node->node_next = NULL;

    NODE current;

    // Special case for the head node
    if ( (list == NULL) || (list->key >= new_node->key) ) {
        new_node->node_next = list;
        list = new_node;
    }
    else {
        // Find a node before the point of insertion
        current = list;
        while ( (current->node_next != NULL) &&
                (current->node_next->key < new_node->key) ) {
            current = current->node_next;
        }
        new_node->node_next = current->node_next;
        current->node_next = new_node;
    }
    return list;
}




void print_nodes(LIST list) {
    for(LIST l = list; l != NULL; l = l->node_next) {
        std::cout << "key = " << l->key << std::endl;
        std::cout << "data = " << l->data << std::endl;
    }
}

char * SlowFunction2(char *output, char *input) {
    while (*input) {
        *output = toupper((unsigned char) *input);
        input++;
        output++;
    }
    *output = '\0';
    return output;
}

char *SlowFunction(char *output, char *input) {
    int i, j;

    for (i = 0, j = 0; input[i]; ++i) {
        if (input[i] >= 32 && input[i] < 97) {
            output[j++] = input[i];
        }
        if (input[i] >= 97 && input[i] <= 122) {
            output[j++] = input[i] - 32;
        }
        if (input[i] > 122 && input[i] < 127) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
}

char* SlowFunction3(char* output, char* input) {

    while(*input != '\0')
    {
        if( *input >= 'a' && *input <= 'z') {
            *output = *input - 32;
        }
        else {
            *output = *input;
        }
        input++;
        output++;
    }
    *output = '\0';
    return output;
}

int main() {

    LIST l = NULL;

    l = AddKey(l, 4, "4");
    l = AddKey(l, 1, "1");
    l = AddKey(l, 8, "8");
    l = AddKey(l, 3, "3");
    l = AddKey(l, 2, "2");
    l = AddKey(l, 1, "1");
    l = AddKey(l, 2, "2");
    l = AddKey(l, 3, "3");

    print_nodes(l);

    char output[100] = {0};
    char * input = "asdasdasdasddsfdfghjhghjhk23420904569     d f df s df sd f sd f s234453465";

    SlowFunction(output, input);
    std::cout << output << std::endl;

    memset(output, 0, 100);

    SlowFunction2(output, input);
    std::cout << output << std::endl;

    memset(output, 0, 100);

    SlowFunction3(output, input);
    std::cout << output << std::endl;


    int t = first0bits(128);
    std::cout << "number of first 0 bits: " << t << std::endl;
    t = last0bits(128);
    std::cout << "number of last 0 bits: " << t << std::endl;
    int n1 = 1041;
    int n0 = 1041;
    std::cout << "longest 1 bit sequence is: " << longest_1bit_sequence(n1) << std::endl;
    std::cout << "longest 0 bit sequence is: " << longest_0bit_sequence(n0) << std::endl;
    return 0;
}