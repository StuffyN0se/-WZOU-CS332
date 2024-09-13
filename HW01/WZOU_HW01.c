#include <stdio.h> 
#include <stdbool.h> 
#include <math.h>
#include <string.h>

/* Problem 1 */
const char* isPrime(int num){
    if (num <= 1) {                // 1 and anything less than 1 is not prime
        return "Invalid Input\n"; 
    }
    if (num == 2) {                // 2 is the only even prime
        return"Prime Number\n";  
    }
    for (int i = 2; i < num; i++){ 
        if (num % i == 0) {        
            int j = i;
            while (j > 1){
                j = j* j -1;
            }
            return "Factorial :"; 
            printf("%d\n", j);
        }
    }
    return "Prime Number\n";                   // return true is not divisible by any number

}

/* 第二道题 */
int UABIndexSum(int nums[], int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        int current = nums[i];
        if (current == i)
            sum += current;
    }
    return sum;
}

/* El problema 3 */
int* replaceEvenWithZero(int nums[], int length){
    for(int i=0; i < length; i++) {
        int current = nums[i];
        if (current%2 == 0){
            nums[i] = 0;
        }
    }
    return nums;
}

/* 他妈的第四道题*/
bool evenSquare(int x){
    if (x <= 1){
    return false;
    }
    int root = (int)sqrt(x);
    if (root *root == x){
        if (root %2 == 0){
        return true;
        }
        else
        return false;
    }
    else
        return false;
}

/* 终于要做完了 */
int countVowels(char str[]){
    int len = strlen(str);
    int counter = 0; 
    for (int i = 0; i < len; i++){
        if (str[i] == 'a' || str[i] == 'A' || str[i] == 'e' || str[i] == 'E' || str[i] == 'i' || str[i] == 'I' || str[i] == 'o' || str[i] == 'O' || str[i] == 'u' ||str[i] == 'U')
        counter++;
    }
    return counter;
}



int main(int argc, char** argv) {
/* Problem one */
    printf("%s", isPrime(5));
    printf("%s", isPrime(4));
    printf("%s", isPrime(1));
    printf("%s", isPrime(7));
    printf("%s", isPrime(-1));
    printf("\n");

/* 第二道题 */
    int nums1[] = {0, 2, 2, 4};
    int length1 = sizeof(nums1) / sizeof(int);  
    int answer1 = UABIndexSum(nums1, length1);   
    printf("%d\n", answer1);       

    int nums2[] = {3, 1, 0, 4};
    int length2 = sizeof(nums2) / sizeof(int);  
    int answer2 = UABIndexSum(nums2, length2);   
    printf("%d\n", answer2); 

    int nums3[] = {1, 2, 3, 3};
    int length3 = sizeof(nums3) / sizeof(int);  
    int answer3 = UABIndexSum(nums3, length3);   
    printf("%d\n", answer3);
    printf("\n");


/* El problema 3 */
    int test1[] = {1, 2, 3, 4};
    int testLen1 = sizeof(test1) / sizeof(int);
    replaceEvenWithZero(test1, testLen1);
    for (int i = 0; i < testLen1; i++) {
        printf("%d ", test1[i]);
    }
    printf("\n");

    int test2[] = {2, 4, 6};
    int testLen2 = sizeof(test2) / sizeof(int);
    replaceEvenWithZero(test2, testLen2);
    for (int i = 0; i < testLen2; i++) {
        printf("%d ", test2[i]);
    }
    printf("\n");

    int test3[] = {1,3,5};
    int testLen3 = sizeof(test3) / sizeof(int);
    replaceEvenWithZero(test3, testLen3);
    for (int i = 0; i < testLen3; i++) {
        printf("%d ", test3[i]);
    }
    printf("\n");

/* 他妈的第四道题*/
    printf("%d is a even square : %s\n", 16, evenSquare(16) ? "true" : "false");
    printf("%d is a even square : %s\n", 15, evenSquare(15) ? "true" : "false");
    printf("%d is a even square : %s\n", 25, evenSquare(25) ? "true" : "false");
    printf("%d is a even square : %s\n", 36, evenSquare(36) ? "true" : "false");
    printf("\n");

/* Problem 5 */
    printf("%d\n", countVowels("Hello World"));
    printf("%d\n", countVowels("UAB CS"));
    printf("%d\n", countVowels("Python"));
    printf("%d\n", countVowels("aeiou"));
}
