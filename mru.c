#include <stdio.h>
#include <stdlib.h>

#define max_frames 100

void initialize_memory(int memory[], int num_frames)
{
    int i;
    for (i = 0; i < num_frames; i++)
    {
        memory[i] = -1;
    }
}

int MRU_page_replacement(int reference_string[], int num_pages, int num_frames)
{
    int i, j;
    int memory[max_frames];
    int page_faults = 0;
    int counter[max_frames] = {0};

    initialize_memory(memory, num_frames);

    for (i = 0; i < num_pages; i++)
    {
        int page = reference_string[i];
        int found = 0;
        for (j = 0; j < num_frames; j++)
        {
            if (memory[j] == page)
            {
                counter[j]++;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            if (page_faults < num_frames)
            {
                memory[page_faults] = page;
                counter[page_faults] = 1;
            }
            else
            {
                int max_counter = 0;
                for (j = 1; j < num_frames; j++)
                {
                    if (counter[j] > counter[max_counter])
                    {
                        max_counter = j;
                    }
                }
                memory[max_counter] = page;
                counter[max_counter] = 1;
            }
            page_faults++;
        }
        else
        {
            for (j = 0; j < num_frames; j++)
            {
                if (memory[j] != page)
                {
                    counter[j] = 0; // Reset counters for pages that are not the current page
                }
            }
        }

        printf("\nScheduling: ");
        for (j = 0; j < num_frames; j++)
        {
            printf("%d ", memory[j]);
        }
    }
    return page_faults;
}

void main()
{
    int i;
    int reference_string[] = {8,5,7,8,5,7,2,3,7,3,5,9,4,6,2};
    int num_pages = sizeof(reference_string) / sizeof(reference_string[0]);
    int num_frames;
    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);
    int page_faults = LRU_page_replacement(reference_string, num_pages, num_frames);
    printf("\n\nREFERENCE STRING: ");
    for (i = 0; i < num_pages; i++)
    {
        printf("%d ", reference_string[i]);
    }
    printf("\nTOTAL PAGE FAULTS: %d\n", page_faults);
}
