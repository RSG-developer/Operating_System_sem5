#include<stdio.h>
#include<stdlib.h>

typedef struct process
{
    char name[10];
    int at,bt,ct,tat,tbt,wt,priority;
}process;

process p[10];
int processcnt,currenttime;
float totalwt,totaltat,avgtat,avgwt;

void readprocess()
{
    int i;
    printf("Enter number of process:");
    scanf("%d",&processcnt);
    for(i=0;i<processcnt;i++)
    {
        printf("Enter process name:");
        scanf("%s",&p[i].name);
        printf("Enter the arrival time:");
        scanf("%d",&p[i].at);
        printf("Enter the burst time:");
        scanf("%d",&p[i].bt);
        printf("Enter the priority :");
        scanf("%d",&p[i].priority);

        p[i].tbt=p[i].bt;
    }
}

int getprocess()
{
    int i=0,min=999,p1=-1;
    for(i=0;i<processcnt;i++)
    {
        if(p[i].at <=currenttime  && p[i].tbt!=0)
        {
            if(p[i].priority <min)
            {
                min=p[i].priority;
                p1=i;
            }
        }

    }
    return p1;
}

void scheduleprocess()
{
    int i,cnt=0;
    printf("Gannt Chart");
    printf("\n-----------------------------------\n");
    while(1)
    {
        i=getprocess();
        if(i==-1)
        {
            printf("%d ",currenttime);
            currenttime=p[cnt].at;
            printf("%d |",currenttime);
        }
        else
        {
            printf("%d",currenttime);
            p[i].wt=currenttime-p[i].at;
            currenttime=currenttime+p[i].bt;
            p[i].ct=currenttime;
            p[i].tat=p[i].wt+p[i].bt;
            p[i].tbt=0;
            totaltat+=p[i].tat;
            totalwt+=p[i].wt;
            printf("%s ",p[i].name);
            printf("%d |",currenttime);
            i++;
            cnt++;
            if(cnt==processcnt)
                break;

        }

    }
    avgtat=totaltat/processcnt;
    avgwt=totalwt/processcnt;
}

void displayprocess()
{
    int i;
    printf("\n-----------------------------------------");
    printf("\nName\tArrival\tBurst\tCPU\tTUrnaround\tWaiting\n");
    for(i=0;i<processcnt;i++)
    {
        printf("\n%s\t%d\t%d\t%d\t%d\t%d",p[i].name,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    printf("\nTota; Turn Around Time is %f",totaltat);
    printf("\nTotal waiting time  is %f",totalwt);
    printf("\nAverage turn aroundtime is %f",avgtat);
    printf("\nAverage woting time is %f",avgwt);
}

void main()
{
    readprocess();
    scheduleprocess();
    displayprocess();
}