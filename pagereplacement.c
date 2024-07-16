#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to check if a page is present in memory
int isPresent(int memory[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (memory[i] == page) {
            return 1;
        }
    }
    return 0;
}

// Function to find the index of the least recently used page
int findLRU(int time[], int n) {
    int minimum = time[0], index = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < minimum) {
            minimum = time[i];
            index = i;
        }
    }
    return index;
}

// FIFO Page Replacement Algorithm
int fifo(int pages[], int n, int capacity) {
    int memory[capacity]; // Array to store pages in memory frames
    int pageFaults = 0; // Counter for page faults
    int next = 0; // Pointer to the next frame to replace

    // Initialize memory array to -1 (indicating empty frame)
    for (int i = 0; i < capacity; i++) {
        memory[i] = -1;
    }

    // Traverse through each page in the reference string
    for (int i = 0; i < n; i++) {
        // Check if the page is already present in memory
        if (!isPresent(memory, capacity, pages[i])) {
            // If memory is not full, place the page in the next available frame
            if (next < capacity) {
                memory[next] = pages[i];
                next++;
            }
            // If memory is full, replace the oldest page (FIFO principle)
            else {
                memory[next % capacity] = pages[i];
                next++;
            }
            pageFaults++; // Increment page fault count
        }
    }

    return pageFaults; // Return total number of page faults
}

// Optimal Page Replacement Algorithm
int optimal(int pages[], int n, int capacity) {
    int memory[capacity];
    int pageFaults = 0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (!isPresent(memory, capacity, pages[i])) {
            if (count < capacity) {
                memory[count++] = pages[i];
            } else {
                int farthest = i + 1, index = -1;
                for (int j = 0; j < capacity; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (memory[j] == pages[k]) {
                            if (k > farthest) {
                                farthest = k;
                                index = j;
                            }
                            break;
                        }
                    }
                    if (k == n) {
                        index = j;
                        break;
                    }
                }
                memory[index] = pages[i];
            }
            pageFaults++;
        }
    }

    return pageFaults;
}

// LRU Page Replacement Algorithm
int lru(int pages[], int n, int capacity) {
    int memory[capacity];
    int time[capacity];
    int pageFaults = 0;
    int count = 0;
    int timer = 0;

    for (int i = 0; i < n; i++) {
        if (!isPresent(memory, capacity, pages[i])) {
            if (count < capacity) {
                memory[count] = pages[i];
                time[count] = timer++;
                count++;
            } else {
                int lruIndex = findLRU(time, capacity);
                memory[lruIndex] = pages[i];
                time[lruIndex] = timer++;
            }
            pageFaults++;
        } else {
            for (int j = 0; j < capacity; j++) {
                if (memory[j] == pages[i]) {
                    time[j] = timer++;
                }
            }
        }
    }

    return pageFaults;
}

int main() {
    /*int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,3 };
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;*/
    int n,capacity;
    int pages[100];
    printf("Enter the amount of pages:\n");
    scanf("%d",&n);
    printf("Enter the page sequence:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&pages[i]);
    printf("Enter the amount of frames:\n");
    scanf("%d",&capacity);

    int fifo_faults = fifo(pages, n, capacity);
    int optimal_faults = optimal(pages, n, capacity);
    int lru_faults = lru(pages, n, capacity);

    printf("FIFO Page Faults: %d\n", fifo_faults);
    printf("Optimal Page Faults: %d\n", optimal_faults);
    printf("LRU Page Faults: %d\n", lru_faults);
}
