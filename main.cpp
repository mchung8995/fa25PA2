//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    //similar to huffman, returns -1 if there is no letters, if there is returns 0 if only 1 leaf exist
    //parent uses the left and right edge by convention
    if (nextFree == 0) {
        //no letters
        return -1;
    }
    if (nextFree == 1) {
        //only 1 letter
        return 0;
    }
    MinHeap heap;

    for (int i=0; i<nextFree; ++i) {
        //adds all the leaf nodes into the heap
        heap.push(i,weightArr);
    }

    int curr = nextFree;
    //index where the next new node will go

    while (heap.size>1 && curr<MAX_NODES) {
        int a = heap.pop(weightArr);
        //the smallest node
        int b = heap.pop(weightArr);
        //the second smallest node

        //creates a new parent node that adds a and b
        charArr[curr] = '\0';
        //internal node
        weightArr[curr] = weightArr[a] + weightArr[b];
        leftArr[curr] = a;
        //left branch ='0'
        rightArr[curr] = b;
        //right branch ='1'

        //puts the new node back into the heap
        heap.push(curr, weightArr);
        curr++;
    }

    if (heap.size==1) {
        //when the last remaining node is the root of the tree
        return heap.pop(weightArr);
    }
    return -1;
    //if something went wrong
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    //each path from the root to the leaf makes a code
    if (root==-1) {
        //if nothing to encode it just returns
        return;
    }

    if (leftArr[root] == -1 && rightArr[root]==-1) {
        //only when there is one type of character it makes sure something will still print
        codes[charArr[root]-'a'] = '0';
        return;
    }

    stack<pair<int,string>> st;
    st.push({root,""});
    //stacks holds a pair

    while (!st.empty()) {
        //takes the top item from the stack
        auto current = st.top();
        //gives us the top element
        st.pop();
        //removes it
        int node = current.first;
        //the node index in the array
        string path = current.second;
        //the path

        int L = leftArr[node];
        int R = rightArr[node];

        if (L==-1 && R==-1) {
            //stores the path as the characters code
            char ch = charArr[node];
            if (ch>='a' && ch<='z') {
                codes[ch - 'a'] = path.empty() ? "0" : path;
            }
        }
        else {
            //pushes right first so the left gets processed first
            if (R!=-1) {
                st.push({R, path+"1"});
            }
            if (L!=-1) {
                st.push({L, path+"0"});
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}