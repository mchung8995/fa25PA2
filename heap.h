//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // inserts a new index into the heap and restore the heap order
        if (size>=64) {
            //Make sure it doesnt overflow
            return;
        }
        int i = size++;
        data[i] = idx;
        //inserts it at the end
        upheap(i, weightArr);
        //restores the min heap
    }

    int pop(int weightArr[]) {
        // removes and returns the smallest index
        if (size==0) {
            //returns -1 if the heap is empty
            return -1;
        }
        int root = data[0];
        //the smallest element
        data[0] = data[size-1];
        //replaces the root with the last element
        size--;
        //makes the heap size smaller
        if (size > 0) {
            downheap(0, weightArr);
            //pushes the new root down
        }
        return root;
    }

    void upheap(int pos, int weightArr[]) {
        //the uphead moves an element up until it is in the correct order
        while (pos > 0) {
            int parent = (pos-1)/2;
            // compares if it is equal or not and uses index to check based on weights
            bool smaller = (weightArr[data[pos]]<weightArr[data[parent]])||(weightArr[data[pos]]==weightArr[data[parent]]
                && data[pos]< data[parent]);
            if (smaller) {
                //swaps the child and the parent
                int t = data[pos];
                data[pos] = data[parent];
                data[parent] = t;
                pos = parent;
                //the new element moves up in the heap
            }
            else {
                break;
                //breaks when in the correct position
            }
        }

    }

    void downheap(int pos, int weightArr[]) {
        // moves the element down until each of the children are larger than the parent
        while (true) {
            int left = 2*pos+1;
            int right = 2*pos+2;
            int smallest = pos;

            auto lessIdx = [&](int a, int b) {
                //helper lambda to compare the position of each child
                if (weightArr[data[a]] != weightArr[data[b]]) {
                    return weightArr[data[a]] < weightArr[data[b]];
                }
                return data[a] < data[b];
                //tiebreaker, makes sure it has a consistent method when two nodes are equal
            };
            if (left<size&&lessIdx(left, smallest)) {
                smallest = left;
            }
            if (right<size&&lessIdx(right,smallest)) {
                smallest = right;
            }
            //checks the parent and kids and finds the smallest one
            if (smallest!=pos) {
                //swaps the parent with the smaller child
                int t = data[pos];
                data[pos] = data[smallest];
                data[smallest] = t;
                pos = smallest;
            }
            else {
                break;
                //when heap property is restored it breaks
            }
        }
    }
};

#endif