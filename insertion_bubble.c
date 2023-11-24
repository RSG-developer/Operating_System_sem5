#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
//#include<sys/wait.h>
void bubble(int arr[],int n)
{
  int i,j,temp;
  for(i=0;i<n;i++)
    {
      for(j=0;j<n-i-1;j++)
        {
          if(arr[j] > arr[j+1])
          {
            temp=arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=temp;
          }
        }
    } 
}

void insertion(int arr[],int n)
{
  int i,key,j;
  for(i=0;i<n;i++)
    {
      key=arr[i];
      j=i-1;
      while(j>=0 && arr[j]>key)
        {
          arr[j+1]=arr[j];
          j=j-1;
        }
      arr[j+1]=key;
    }
}


void main()
{
  int pid;
int arr[10],n;
printf("Enter number integers:");
scanf("%d",&n);
for(int i=0;i<n;i++)
{
  printf("Enter integers:");
  scanf("%d",&arr[i]);
}
  if(pid==0)
  {
    insertion(arr, n);
    printf("\nArray after insertion sort:\n");
    for(int i=0;i<n;i++){
      printf("%d\t",arr[i]);
    }
    printf("\n");
    sleep(5);
  }
  else
  {
    printf("\nParent process  %d\n ",getpid());
    bubble(arr, n);
    printf("Array after bubbble sort \n");
    for(int i=0;i<n;i++)
      {
        printf("%d\t",arr[i]);
      }
    printf("\n");
    sleep(2);
    wait(NULL);
  }
}