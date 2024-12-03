//
// Created by Hector Borjas on 12/3/2024.
//

#ifndef DSA_FINAL_MIN_HEAP_H
#define DSA_FINAL_MIN_HEAP_H

#include <iostream>
#include <vector>
#include "student.h"



using namespace std;

class Min_heap{
public:

    vector<Student> heap;

    Min_heap()= default;

    void heapify(int size, int i){

        //keep track of indexes
        int root = i;
        int leftChild = 2*i +1;
        int rightChild = 2*i +2;

        if(leftChild < size && heap[leftChild].getID() < heap[root].getID()){
            root = leftChild;
        }
        if(rightChild < size && heap[rightChild].getID() < heap[root].getID()){
            root = rightChild;
        }

        if(root != i){
            swap(heap[i], heap[root]);
            heapify(size, root);
        }
    }

    void buildHeap() {
        int n = heap.size();

        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(n, i);
        }
    }
};


#endif //DSA_FINAL_MIN_HEAP_H
