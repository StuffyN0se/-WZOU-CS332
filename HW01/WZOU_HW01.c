#include <stdio.h> 
#include <stdbool.h> 

/* Problem 1 */
const char *isPrime(int num){
    if (num <= 1) {                // 1 and anything less than 1 is not prime
        return "Invalid Input\n"; 
    }
    if (num == 2) {                // 2 is the only even prime
        return "Prime Number\n";  
    }
    for (int i = 2; i < num; i++){ // for every number from 2 to num-1 divide and check divisor
        if (num % i == 0) {        // is remainder is zero then divisible therefore not prime
            int j = i;
            while (j > 1){
                j = j* j -1;
            }
            return "BRO "; 
        }
    }
    return "Prime Number\n";                   // return true is not divisible by any number

}

/* 第二道题 */
int UABIndexSum(int nums[], length){
    int sum = 0;
    for (int i = 0; i< length; i++){
        int current = nums[i];
        if (current == i)
            sum += current;
    }
    return sum;
}

int main(int argc, char** argv){
    // printf("%s", isPrime(5));
    // printf("%s", isPrime(4));
    // printf("%s", isPrime(1));
    // printf("%s", isPrime(7));
    // printf("%s", isPrime(-1));
    int nums[] = {0, 2, 2, 4};
    int length = sizeof(nums)/ sizeof(int);
    int answer = UABIndexSum(nums, length);
    printf("%d",answer);

}