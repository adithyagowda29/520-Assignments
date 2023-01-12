//Import required libraries
#include<stdio.h>

void main(){
    // Defining variables needed
    int array_len=0;
    int i;
    int array1[15];

    // Take length of array as input 
    printf("Input the number of elements to store in the array (max 15) : ");
    scanf("%d",&array_len);
    
    // Take array elements as input one by one
    printf("Input 5 number of elements in the array :\n");
    for(i=0;i<array_len;i++){
        printf("element - %d : ",i+1);
        scanf("%d",&array1[i]);
    }

    // Print out array elements in reverse order one by one
    printf("The elements of array in reverse order are :");
    for(int i=array_len;i>0;i--){
        printf("element - %d : %d ",i,array1[i-1]);
    }

}