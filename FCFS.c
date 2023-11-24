#include<stdio.h>
#include<stdlib.h>

typedef struct process
{
    char name[10];
    int at,bt,wt,tat,ct;
}process;

process p[10];
int processcnt,currenttime;
float avgtat,avgwt,totalwt,totaltat;

void sort()
{
    int i,j;
    process temp;
    for(i=0;i<processcnt;i++)
    {
        for(j=0;j<(processcnt-i-1);j++)
        {
            if(p[j].at > p[j+1].at)
            {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void readprocess()
{
    int i;
    printf("Enter number of process:");
    scanf("%d",&processcnt);
    for(i=0;i<processcnt;i++)
    {
        printf("Enter name of process:");
        scanf("%s",&p[i].name);
        printf("Enter arrival time:");
        scanf("%d",&p[i].at);
        printf("Enter burst time:");
        scanf("%d",&p[i].bt);
    }
    sort();
}

void scheduleprocess()
{
    int i=0,cnt=0;
    printf("Gantt Chart");
    printf("\n_______________________________\n");
    while(1)
    {
        if(currenttime < p[i].at)
        {
            printf("%d idle",currenttime);
            currenttime=p[i].at;
            printf("%d |",currenttime);
        }
        else{
            printf("%d ",currenttime);
            p[i].wt=currenttime+p[i].at;
            currenttime=currenttime+p[i].bt;
            p[i].ct=currenttime;
            p[i].tat=p[i].wt+p[i].bt;
            totaltat+=p[i].tat;
            totalwt+=p[i].wt;
            printf("%s  ",p[i].name);
            printf("%d  |",currenttime);
            i++;
            cnt++;
            if(cnt==processcnt)
                break;
        }
    }
    avgwt=totalwt/processcnt;
    avgtat=totaltat/processcnt;
}

void displayprocess()
{
    int i;
    printf("\n");
    printf("\nName\tArrival\tBurst\tCPU\tWaiting\tTurnAround\n");
    for(i=0;i<processcnt;i++)
    {
        printf("\n%s\t%d\t%d\t%d\t%d\t%d",p[i].name,p[i].at,p[i].bt,p[i].ct,p[i].wt,p[i].tat);
    }
    printf("\nTotal turnAround Time is %f",totaltat);
    printf("\nAverage turnAround time is %f",avgtat);
    printf("\nTotal Witing time is %f",totalwt);
    printf("\nAverage Waiting time is %f",avgwt);
}

void main()
{
    readprocess();
    scheduleprocess();
    displayprocess();
}