#include<stdio.h>
#include<stdlib.h>

void main()
{
	int n;
	printf("Enter the number of processes: ");
	scanf("%d",&n);
	int process_id[n];
	int at[n];
	int bt[n];
	int ct[n];
	int tat[n];
	int wt[n];
	for(int j=1;j<=n;j++)
	{
    	process_id[j-1]=j;
	}
	printf("enter arrival time for process 1 to %d\n",n);
	for(int i=0;i<n;i++)
	{
    	scanf("%d",&at[i]);
	}
	printf("enter the burst time for process 1 to %d\n",n);
	for(int i=0;i<n;i++)
	{
    	scanf("%d",&bt[i]);
	}

	int temp;
	int temp2=0;
	for(int i=0;i<n;i++)
	{
    	for(int j=i+1;j<n;j++)
    	{
        	if(at[i]>at[j])
        	{
            	temp=at[i];
            	at[i]=at[j];
            	at[j]=temp;
            	temp2=bt[i];
            	bt[i]=bt[j];
            	bt[j]=temp2;
        	}
    	}
	}

	int sum=0;
	for(int i=0;i<n;i++)
	{
    	if(at[i]>sum)
    	{
        	sum=sum+(at[i]-ct[i-1]);
    	}
    	sum+=bt[i];
    	ct[i]=sum;
	}
	for(int i=0;i<n;i++)
	{
    	tat[i]=ct[i]-at[i];
    	wt[i]=tat[i]-bt[i];
	}
	printf("process_ID\tAT\tBT\tCT\tTAT\tWT\n");
	for(int i=0;i<n;i++)
	{
    	printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",process_id[i],at[i],bt[i],ct[i],tat[i],wt[i]);
	}
	float tatavg;
	float wtavg;
	int s2=0;
	int s=0;
	for(int i=0;i<n;i++)
	{
    	s+=tat[i];
    	s2+=wt[i];
	}
	tatavg=(float)s/n;
	wtavg=(float)s2/n;
	printf("avg turnaround time: %f\n",tatavg);
	printf("avg waiting time: %f\n",wtavg);
}
