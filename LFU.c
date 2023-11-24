#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 100

// Structure to represent a page in memory
typedef struct {
    int page_number;
    int frequency;
} Page;

// Initialize memory frames
void initialize_memory(Page memory[], int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        memory[i].page_number = -1;
        memory[i].frequency = 0;
    }
}

// LFU Page Replacement Algorithm
int LFU_page_replacement(int reference_string[], int num_pages, int num_frames) {
    Page memory[MAX_FRAMES];
    int page_faults = 0;

    initialize_memory(memory, num_frames);

    for (int i = 0; i < num_pages; i++) {
        int page = reference_string[i];
        int found = 0;
        
        // Check if the page is already in memory
        for (int j = 0; j < num_frames; j++) {
            if (memory[j].page_number == page) {
                memory[j].frequency++;
                found = 1;
                break;
            }
        }

        // If the page is not in memory, find a slot to replace
        if (!found) {
            page_faults++;
            int min_frequency = memory[0].frequency;
            int min_index = 0;

            for (int j = 1; j < num_frames; j++) {
                if (memory[j].frequency < min_frequency) {
                    min_frequency = memory[j].frequency;
                    min_index = j;
                }
            }

            memory[min_index].page_number = page;
            memory[min_index].frequency = 1;
        }
    }

    return page_faults;
}

int main() {
    int reference_string[] = {3, 4, 5, 4, 3, 4, 7, 2, 4, 5, 6, 7, 2, 4, 6};
    int num_pages = sizeof(reference_string) / sizeof(reference_string[0]);
    int num_frames ;  // Number of memory frames
    printf("Enter number of frames:");
    scanf("%d",&num_frames);
    int page_faults = LFU_page_replacement(reference_string, num_pages, num_frames);

    printf("Reference String: ");
    for (int i = 0; i < num_pages; i++) {
        printf("%d ", reference_string[i]);
    }
    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}
