#include <stdio.h>
#include <string.h>

int heap[500];  // Array to store heap elements (1-based index, heap[0] unused)
int sz = 1;     // Size of the heap (starts at 1 because heap[0] is unused)

// Function to move an element up the heap (used when inserting or updating)
void up(int idx) {
    int p = idx / 2;   // Calculate the parent index
    if (p == 0) return;  // Stop if at the root

    // If the current element is greater than its parent, swap them
    if (heap[p] < heap[idx]) {
        int tmp = heap[p];
        heap[p] = heap[idx];
        heap[idx] = tmp;
        up(p);  // Recursively move the parent element up
    }
}

// Function to move an element down the heap (used after deletion or updating)
void down(int idx) {
    int mx = idx;  // mx stores the index of the maximum element (current or its children)
    
    // Check if the left child exists and is greater than the current element
    if (idx * 2 < sz && heap[idx * 2] > heap[mx]) 
        mx = idx * 2;
    
    // Check if the right child exists and is greater than the current max (either the current element or left child)
    if (idx * 2 + 1 < sz && heap[idx * 2 + 1] > heap[mx]) 
        mx = idx * 2 + 1;

    // If a child is larger, swap it with the current element and continue moving it down
    if (mx != idx) {
        int tmp = heap[idx];
        heap[idx] = heap[mx];
        heap[mx] = tmp;
        down(mx);  // Recursively move the swapped element down
    }
}

// Function to insert a new value into the heap
void insert(int v) {
    heap[sz++] = v;  // Insert the new value at the end of the heap
    up(sz - 1);      // Move the inserted value up to maintain the max-heap property
}

// Function to update a specific element in the heap with a new value
void update(int target, int val) {
    // Iterate through the heap to find the element to be updated
    for (int i = 1; i < sz; i++) {
        if (heap[i] == target) {  // If the target value is found
            heap[i] = val;  // Update the element
            up(i);          // Ensure max-heap property by moving it up if necessary
            down(i);        // Ensure max-heap property by moving it down if necessary
        }
    }
    return;
}

// Function to delete the maximum element (root) from the heap
void del() {
    heap[1] = heap[sz - 1];  // Replace the root with the last element
    sz--;                    // Decrease the size of the heap
    down(1);                 // Move the new root down to maintain the max-heap property
}

int main() {
    char opt[30] = {};  // Array to store the input command (insert, update, delete, exit)
    
    // Continuously process commands from the input until 'exit' is entered
    while (scanf("%s", opt) == 1) {
        // Compare full string with strcmp to check for commands
        if (strcmp(opt, "exit") == 0) break;  // Exit the loop if the command is "exit"

        if (strcmp(opt, "insert") == 0) {     // Process the "insert" command
            int v;
            scanf("%d", &v);          // Read the value to be inserted
            insert(v);                // Insert the value into the heap
        }

        if (strcmp(opt, "update") == 0) {     // Process the "update" command
            int v1, v2;
            scanf("%d %d", &v1, &v2); // Read the target value and the new value
            update(v1, v2);           // Update the target value with the new value
        }

        if (strcmp(opt, "delete") == 0) {     // Process the "delete" command
            del();                    // Delete the maximum element (root) from the heap
        }
    }

    // After exiting the loop, print all elements in the heap
    for (int i = 1; i < sz; i++) 
        printf("%d ", heap[i]);       // Print each element in the heap
}
