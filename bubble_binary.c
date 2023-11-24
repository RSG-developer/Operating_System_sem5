#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <stdlib.h>
//#include<sys/wait.h>

void bubblesort(int arr[],int n)
{
  int i,j,temp;
  for(i=0;i<n;i++)
    {
      for(j=0;j<n-i-1;i++)
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


int binarysearch(int arr[],int n,int key)
{
  int left=0,right=n-1;
  while(left<=right)
    {
     int mid=left+(right-left)/2;
      if(arr[mid]==key)
      {
        return mid;
      }
      if(arr[mid]<key)
      {
         left=mid+1; 
      }
      else{
        right=mid-1;
      }
    }
  return -1;
}


void main()
{
  int i,n;
  printf("Enter number of integers:");
  scanf("%d",&n);
  int arr[10];
  for(i=0;i<n;i++)
    {
      printf("Enter array integers:");
      scanf("%d",&arr[i]);
    }
  int pid=fork();
  
  if(pid==0)
  {
    bubblesort(arr,n);
    char *binary_search_program="binary_search";
    char n_str[10],n_target[10];
    int target;
    printf("Enter the number to serach:");
    scanf("%d",&target);
    snprintf(n_str,sizeof(n_str),"%d",target);
    char *args[]={binary_search_program,n_str,n_target,NULL};
    execve(binary_search_program,args,NULL);
    exit(1);
  }
  else{
    wait(NULL);
    printf("Parent process ");
  }
}