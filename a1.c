#include <stdio.h>

// Name: Shaunak Sachdev
// Student ID: 301558905
// Computing ID: SSA516@SFU.CA

// Recursive helper function
unsigned int reverseAndShuffle(unsigned int number, unsigned int factor) {
    if (number == 0) {
        return 0;
    }

    unsigned int digit = number % 10;
    return digit * factor + reverseAndShuffle(number / 10, factor / 10);
}

// Main function
unsigned int shuffleDigitsRecursive(unsigned int number) {
    unsigned int factor = 1;
    unsigned int temp = number;

    // Calculating the factor to handle leading zeros
    while (temp >= 10) {
        factor *= 10;
        temp /= 10;
    }

    return reverseAndShuffle(number, factor);
}

// Test function
void checkAndPrintInts(unsigned int expected, unsigned int result) {
    if (expected == result) {
        printf("%u is the same as %u, PASS\n", expected, result);
    } else {
        printf("%u is not the same as %u, FAIL\n", expected, result);
    }
}

int main() {
    checkAndPrintInts(1, shuffleDigitsRecursive(1)); //should return 1
    checkAndPrintInts(321, shuffleDigitsRecursive(123)); //should return 321
    checkAndPrintInts(403, shuffleDigitsRecursive(30400)); //should return 403 (no leading zero)

    return 0;
}