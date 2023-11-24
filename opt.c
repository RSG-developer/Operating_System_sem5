#include<stdio.h>
#include<stdlib.h>

#define max_frames 100

void initialize_memory(int memory[], int num_frames)
{
	int i;
	for(i=0;i<num_frames;i++)
	{
		memory[i]=-1;
	}
}

int OPT_page_replacement(int reference_string[], int num_pages, int num_frames)
{
	int i,j,k;
	int future_use;
	int memory[max_frames];
	int page_faults=0;
	int next_use[max_frames];
	
	initialize_memory(memory, num_frames);
	
	for(i=0;i<num_pages;i++)
	{
		int page=reference_string[i];
		int found=0;
		
		for(j=0;j<num_frames;j++)
		{
			if(memory[j]==page)
			{
				found=1;
				break;
			}
		}
		if(!found)
		{
			if(page_faults<num_frames)
			{
				memory[page_faults]=page;
			}
			else
			{
				int index=-1;
				for(j=0;j<num_frames;j++)
				{
					future_use=num_pages;
					for(k=i+1;k<num_pages;k++)
					{
						if(reference_string[k]==memory[j])
						{
							future_use=k;
							break;
						}
					}
					if(future_use>next_use[j])
					{
						next_use[j]=future_use;
						index=j;
					}
				}
				memory[index]=page;
			}
			page_faults++;	
		}
		printf("\nScheduling: ");
		for(j=0;j<num_frames;j++)
		{
			printf("%d ",memory[j]);
		}	
	}
	return page_faults;
}
void main()
{
	int i;
	int reference_string[]={8,5,7,8,5,7,2,3,7,5,9,4,6,2};
	int num_pages=sizeof(reference_string)/sizeof(reference_string[0]);
	int num_frames;
	printf("Enter number of frames: ");
	scanf("%d",&num_frames);
	int page_faults=OPT_page_replacement(reference_string, num_pages,num_frames);
	printf("Reference String: \n");
	for(i=0;i<num_pages;i++)
	{
		printf("%d ",reference_string[i]);
	}
	printf("\n\nTotal Page Faults: %d\n",page_faults);
}
