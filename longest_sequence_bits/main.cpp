#include <iostream>
#include <strings.h>
#include <bitset>

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
    if (N < 2) return 0;
    int max = 0, count = 0;

    while (N % 2 == 0) N = N / 2;
    while (N > 0) {
        if (N % 2 == 1) {
            if (count > max) max = count;
            count = 0;
            N = N / 2;
        }
        else {
            count++;
            N = N / 2;
        }
    }
    return max;
}


int main() {

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