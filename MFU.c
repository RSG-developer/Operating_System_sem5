#include<stdio.h>
#include<stdlib.h>
#define MAX 100
void showPaging(int memery[],int frames)
{
    for(int i=0;i<frames;i++)
    {
        printf("%d |",memery[i]);
    }
    printf("\n");
}

void MFU(int page_reference[],int n,int frames)
{
    int memory[MAX];
    int page_frequency[MAX]={0};
    int page_fault=0;

    for(int i=0;i<frames;i++)
    {
        memory[i]=-1;
    }

    for(int i=0;i<n;i++)
    {
        int page_found=0;
        for(int j=0;j<frames;j++)
        {
            if(memory[j]==page_reference[i])
            {
                page_found=1;
                page_frequency[j]++;
                break;
            }
        }

        if(!page_found)
        {
            if(page_fault < frames)
            {
                int index=page_fault;
                memory[index]=page_reference[i];
                page_frequency[index]++;
            }
            else
            {
                int max_frequency_page=0;
                for(int j=1;j<frames;j++)
                {
                    if(page_frequency[j] < page_frequency[max_frequency_page])
                    {
                        max_frequency_page=j;
                    }
                }
                int index=max_frequency_page;
                memory[index]=page_reference[i];
                page_frequency[index]=1;
            }
            page_fault++;
            showPaging(memory,frames);
        }
    }
    printf("Total number of page faults are %d",page_fault);
}

void main()
{
    //int page_reference[]={8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2};
    int page_reference[]={3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6};
    int n=sizeof(page_reference)/sizeof(page_reference[0]);
    int frames;
    printf("Enter number of frames:");
    scanf("%d",&frames);
    MFU(page_reference,n,frames);
}