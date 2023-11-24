#include<stdio.h>
#include<stdlib.h>

void showPaging(int memory[],int frames)
{
    for(int i=0;i<frames;i++)
    {
        printf("%d  |",memory[i]);
    }
    printf("\n");
}
void LRU(int page_reference[] , int n,int frames)
{
    int memory[frames];
    int recent_index[frames];
    int page_faults=0;

    for(int i=0;i<frames;i++)
    {
        memory[i]=-1;
        recent_index[i]=0;
    }

    for(int i=0;i<n;i++)
    {
        int page_found=0;
        int index=-1;
        for(int j=0;j<frames;j++)
        {
            if(memory[j]==page_reference[i])
            {
                page_found=1;
                index=j;
                break;
            }
        }

        if(!page_found)
        {
            int least_recently_used=0;
            for(int j=0;j<frames;j++)
            {
                if(recent_index[j]< recent_index[least_recently_used])
                {
                    least_recently_used=j;
                }
            }
            memory[least_recently_used]=page_reference[i];
            recent_index[least_recently_used]=i+1;
            page_faults++;
            showPaging(memory,frames);
        }
        else{
            recent_index[index]=i+1;
        }
    }
    printf("Total number of page faults %d",page_faults);
}

void main()
{
    int page_reference[]={ 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2};
    int n=sizeof(page_reference)/sizeof(page_reference[0]);
    int frames;
    printf("Enter the number of frames:");
    scanf("%d",&frames);
    LRU(page_reference,n,frames);
}
