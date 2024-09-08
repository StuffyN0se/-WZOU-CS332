#include <stdio.h> 
#include <stdbool.h> 

int main(int argc, char** argv) {
    int numElements, elements;  // Declare an integer variable to store number of elements
    
    printf("How many numbers are you entering? :\n");
    scanf("%d", &numElements);  // Stores size of array '
    int numArray[numElements];
    
    for(int i = 0; i < numElements; i++){
        printf("Please enter the %d number :\n", i +1);
        scanf("%d", &elements);
        numArray[i] = elements;
    }

    printf("The given array is: [");

    for (int i=0; i<numElements -1; i++){
        printf("%d, ", numArray[i]);
    }
    printf("%d]\n", numArray[numElements-1]);

    // InsertionSort
    int temp, current;
    for (int i=1; i<numElements; i++){
        current = i;
        while (current > 0 && numArray[current-1] > numArray[current]){
            temp = numArray[current];
            numArray[current] = numArray[current-1];
            numArray[current-1] = temp;
            current--;
            }
    }
    // Display

    printf("The sorted array is: [ ");
    for (int i=0; i<numElements-1; i++){
        printf("%d, ", numArray[i]);
    }
    printf("%d]\n", numArray[numElements-1]);
    
    return 0;
}