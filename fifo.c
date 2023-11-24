#include<stdio.h>
#include<stdlib.h>

void showpaging(int memory[],int frames)
{
    int i;
    for(i=0;i<frames;i++)
    {
        printf("%d |",memory[i]);
    }
    printf("\n");
}

void fifo(int page_reference[] ,int n, int frames)
{
    int memory[frames];
    int page_faults=0;
    int front=0,rear=0;

    for(int i=0;i<n;i++)
    {
        int page_found=0;
        for(int j=0;j<frames;j++)
        {
            if(memory[j]==page_reference[i])
            {
                page_found=1;
                break;
            }
        }

        if(!page_found)
        {
            if(rear< frames)
            {
                memory[rear++]=page_reference[i];
            }
            else
            {
                memory[front]=page_reference[i];
                front=(front+1)% frames;
            }

            page_faults++;
            showpaging(memory,frames);
        }
    }
    printf("Total number of page faults are %d",page_faults);
}

void main()
{
   int page_reference[] ={3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6 };
    
    int n=sizeof(page_reference)/sizeof(page_reference[0]);

    int frames;
    printf("Enter the number of frames:");
    scanf("%d",&frames);
    fifo(page_reference,n,frames);
}