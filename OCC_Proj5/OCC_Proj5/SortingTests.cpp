//
//  SortingTests.cpp
//  OCC_Proj5
//
//  Created by Anna Li on 11/24/18.
//  Copyright © 2018 Anna Li. All rights reserved.
//

#include "SortingTests.hpp"
#include <fstream>
#include <iostream>
#include <chrono>
using namespace std::chrono;

/*
 helper function that swaps two diff ints in array
 */
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/*
 @post Sorts an array in ascending order using the selection sort algorithm.
 @param a the array to sort
 @param size the number of elements in a
 */
void selectionSort(int a[], size_t size) {
    int i, j, minimum_idx;
    
    // Loop through unsorted array
    for (i = 0; i < size-1; i++)
    {
        // Find the smallest element of the unsorted array
        minimum_idx = i;
        for (j = i+1; j < size; j++)
            if (a[j] < a[minimum_idx])
                minimum_idx = j;
        
        // Swap smallest element with first
        swap(&a[minimum_idx], &a[i]);
    }
}

/*
 tester function for selectionSort/insertionSort

void printArray(int arr[], int size)
{
    for (int i=0; i < size; i++)
        std::cout << arr[i] << std::endl;
    std::cout << "\n" << std::endl;
}
*/
void insertionSort(int a[], size_t size)
{
    int i, key, j;
    
    //loop through unsorted array
    for (i = 1; i < size; i++)
    {
        key = a[i];
        j = i-1;
        
        //move elements that are greater than ahead
        while (j >= 0 && a[j] > key)
        {
            a[j+1] = a[j];
            j = j-1;
        }
        
        //set element to key
        a[j+1] = key;
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    
    int num_1 = m - l + 1;
    int num_2 =  r - m;
  
    //make temporary arrays
    int *left = new int[num_1];
    int *right = new int[num_2];
    
    //copy unsorted array to temporary ones
    for (i = 0; i < num_1; i++)
        left[i] = arr[l + i];
    for (j = 0; j < num_2; j++)
        right[j] = arr[m + 1+ j];
    
    //re-merge
    j = 0;
    i = 0;
    k = l;
    while (i < num_1 && j < num_2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    
    //copy remaining elements back into right
    while (j < num_2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
    
   //copy remaining elements back into left
    while (i < num_1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    
    
}

/* l is for left index and r is right index of the
 sub-array of arr to be sorted */
void mergeSort(int a[], int from, int to)
{
    if (from < to)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = from+(to-from)/2;
        
        // Sort first and second halves
        mergeSort(a, from, m);
        mergeSort(a, m+1, to);
        
        merge(a, from, m, to);
    }
}

/**
 @post Populates values with randomly generated numbers in range size
 @param values the array to populate
 @param size of the array to be populated
 */
void generateRandomArray(int values[], size_t size)
{
    values[size] = {};
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < size; i++) {
        values[i] = rand() % size;
    }
}

/**
 @post Populates values with integers in ascending order
 @param values the array to populate
 @param size of the array to be populated
 */
void generateAscendingArray(int values[], size_t size) {
    values[size] = {};
    for (int i = 0; i < size; i++) {
        values[i] = i;
    }
}

/**
 @post Populates values with integers in descending order
 @param values the array to populate
 @param size of the array to be populated
 */
void generateDescendingArray(int values[], size_t size) {
    values[size] = {};
    int counter = 0;
    for (int i = int(size); i > 0; i--) {
        values[counter] = i;
        counter++;
    }
}

/**
 @post Populates values with integers in ascending order except for the last 10 that are randomly generated
 @param values the array to populate
 @param size of the array to be populated
 */
void generateLastTenRandomArray(int values[], size_t size)
{
    values[size] = {};
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < int(size)-10; i++) {
        values[i] = i;
    }
    for (int i = int(size)-10; i < size; i++) {
        values[i] = rand() % size;
    }
}

/**
 @post Populates values with integers in randomly generated in range size/10
 @param values the array to populate
 @param size of the array to be populated
 */
void generateFewRandomArray(int values[], size_t size)
{
    int new_size = int(size)/10;
    values[new_size] = {};
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < new_size; i++) {
        values[i] = rand() % new_size;
    }
}

/**
 @post Sorts values in ascending order and averages its runtime over 10 runs
 @param sortingFunction the function used to sort the array
 @param values the array to sort
 @param size of the array to sort
 @return the average runtime in microseconds
 */
double sortTest(void (*sortingFunction)(int a[], size_t size), int values[], size_t size)
{

    //declares sum variable used for averaging durations
    duration<float, std::micro> runtime_sum = duration<float, std::micro>(0);
    
    for (int i = 0; i < 10; i++) {
        //create new array for run
        int * new_array = new int[size];
        
        //dynamically copying array
        for (int i = 0; i < size; i++)
        {
            new_array[i] = values[i];
        }
        
        auto start_time = high_resolution_clock().now();
        sortingFunction(new_array, size);
        auto end_time = high_resolution_clock().now();
        
        //gets duration of function's runtime
        duration<float, std::micro> run_time = duration_cast<microseconds>(end_time - start_time);
        runtime_sum = runtime_sum + duration<float, std::micro>(run_time.count());
    }
    
    double average = runtime_sum/duration<float, std::micro>(10);
    return average;
}

/**
 @post Sorts values in ascending order using mergeSort and averages its runtime over 10 runs
 @param values the array to sort
 @param size of the array to sort
 @return the average runtime in microseconds
 */
double mergeSortTest(int values[], size_t size)
{
    //declares sum variable used for averaging durations
    duration<float, std::micro> runtime_sum = duration<float, std::micro>(0);
    
    for (int i = 0; i < 10; i++) {
        //create new array for run
        int * new_array = new int[size];
        
        //dynamically copying array
        for (int i = 0; i < size; i++)
        {
            new_array[i] = values[i];
        }
        
        auto start_time = high_resolution_clock().now();
        mergeSort(new_array, 0, int(size)-1);
        auto end_time = high_resolution_clock().now();
        
        //gets duration of function's runtime
        duration<float, std::micro> run_time = duration_cast<microseconds>(end_time - start_time);
        runtime_sum += duration<float, std::micro>(run_time.count());
    }
    
    double average = runtime_sum/duration<float, std::micro>(10);
    return average;
}
