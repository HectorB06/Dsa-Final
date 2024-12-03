//
// Created by Hector Borjas on 12/2/2024.
//


#ifndef DSA_FINAL_MAX_HEAP_H
#define DSA_FINAL_MAX_HEAP_H

#include <iostream>
#include "student.h"

using namespace std;

class Max_heap{



    void heapify(int arr[], int size, int i){

        //keep track of indexes
        int root = i;
        int leftChild = 2*i +1;
        int rightChild = 2*i +2;

        if(leftChild < size && arr[leftChild] > arr[root]){
            root = leftChild;
        }
        if(rightChild < size && arr[rightChild] > arr[root]){
            root = rightChild;
        }

        if(root != i){
            swap(arr[i], arr[root]);
            heapify(arr, size, root);
        }
    }
};

#endif //DSA_FINAL_MAX_HEAP_H
