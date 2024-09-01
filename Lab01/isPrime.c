#include <stdio.h> 
#include <stdbool.h> 

bool isPrime(int num) {

    if (num <= 1) {                // 1 and anything less than 1 is not prime
        return false; 
    }
    if (num == 2) {                // 2 is the only even prime
        return true;  
    }
    for (int i = 2; i < num; i++){ // for every number from 2 to num-1 divide and check divisor
        if (num % i == 0) {        // is remainder is zero then divisible therefore not prime
            return false; 
        }
    }
    return true;                   // return true is not divisible by any number
}

int main(int argc, char** argv) {
    int given_number;  // Declare an integer variable to store user input
    
    printf("Enter a number:\n");
    scanf("%d", &given_number);  // Store input in the variable 'num'
    
    if (isPrime(given_number)) {
        printf("The number %d is prime.\n", given_number);  
    } else {
        printf("The number %d is not prime.\n", given_number);  
    }
    
    return 0;
}