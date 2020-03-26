#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<iomanip>
using namespace std;
int checkarrival(int t[50][3],int n)
{
    int i;
    while(i<n-1)
    {
        if(t[i][1]!=t[i+1][1])
            break;
        i++;
    }
    if(i==n-1)
        return 1;
    else
        return 0;
}
void fcfs(int tab[50][3],int n)
{
    int wt[n],tat[n];
    int samearrival;
    samearrival=checkarrival(tab,n);
    if(samearrival==1)
    {
       wt[0]=0;
       for(int k=1;k<n;k++)
       {
           wt[k]=wt[k-1]+tab[k-1][2];
           tat[k]=(wt[k]+tab[k][2])-tab[k][1];
       }
    }
    else
    {
        int time=tab[0][2];
        for(int i=0;i<n;i++)
        for(int j=0;j<n-i-1;j++)
        {
            if(tab[j][1]>tab[j+1][1])
            {
                swap(tab[j][0],tab[j+1][0]);
                swap(tab[j][1],tab[j+1][1]);
                swap(tab[j][2],tab[j+1][2]);
            }
        }

        wt[0]=0;
        tat[0]=tab[0][2];
        for(int m=1;m<n;m++)
        {
           if(time<tab[m][1])
           {
               while(time==tab[m][1])
                    time++;
                wt[m]=0;
           }
           else
           {
                wt[m]=time-tab[m][1];
                time=time+tab[m][2];
           }
           tat[m]=time-tab[m][1];
        }
    }
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"process      arrival      burst      waiting-time      turnaround-time"<<endl;
    cout<<"----------------------------------------------------------------------"<<endl;
    for(int a=0;a<n;a++)
        cout<<left<<setw(13)<<tab[a][0]<<left<<setw(13)<<tab[a][1]<<left<<setw(11)<<tab[a][2]<<left<<setw(18)<<wt[a]<<setw(15)<<tat[a]<<endl;
    cout<<"----------------------------------------------------------------------"<<endl;
    int twt=0,tt=0;
    for(int i=0;i<n;i++)
    {
        twt=twt+wt[i];
        tt=tt+tat[i];
    }
    cout<<endl<<"Average waiting time:"<<(float)twt/(float)n<<endl<<endl<<"Average turn-around time:"<<(float)tt/(float)n<<endl;
}
int main()
{
    int n;
    cout<<"Enter the number of processes:";
    cin>>n;
    int table[n][3];
    for(int i=0;i<n;i++)
    {
       table[i][0]=i;
    }
    cout<<"Enter the arrival times of the processes"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P["<<i<<"]=";
        cin>>table[i][1];
    }
    cout<<"Enter the burst times:"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P["<<i<<"]=";
        cin>>table[i][2];
    }
    fcfs(table,n);
}
