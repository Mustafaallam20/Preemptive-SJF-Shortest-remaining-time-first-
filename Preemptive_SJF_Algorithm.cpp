#include <iostream>
#include <windows.h>
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int main () {
int aT[10],bT[10],x[10]; // Arrays for arrivalTime, burstTime adn x, which will be used as copy of burst time
int waiting[10],turnaround[10], completion[10];
int i,j,smallest,count1 = 0,time,numOfProc;
int color = 48; // We will need this later for changing colors
double average = 0;
double tt = 0;  //turnaroundtime
double end1;
int index = 0;
int GanttChart [100];


cout << "\nEnter the number of Processes " ;
cin >> numOfProc;
for (i=0; i<numOfProc; i++) {
    cout << "\nEnter arrival time of process " << i+1 << ": "; //input;
    cin>>aT[i];
}
for (i=0; i<numOfProc; i++) {
    cout << "\nEnter burst time of process " << i+1 << ": ";
    cin>>bT[i];
}

for (i=0;i<numOfProc;i++) x[i]=bT[i];
bT[9]=9999;

for (time=0; count1 != numOfProc; time++) {
    smallest = 9;
    for (i=0; i<numOfProc; i++) {
        if (aT[i]<=time && bT[i]<bT[smallest] && bT[i]>0) smallest = i;
    }
    GanttChart[index]=smallest;
    index++;
    bT[smallest]--;

    if (bT[smallest]==0) {
        count1++;
        end1=time+1;
        completion[smallest] = end1;
        waiting[smallest] = end1 - aT[smallest] - x[smallest];
        turnaround[smallest] = end1 - aT[smallest];
    }
}



cout << "\n\n Gantt Chart representation of processes: \n ";
for (i = 0; i<index+1; i++) cout << "-- ";
cout << endl << "|" ;
SetConsoleTextAttribute(h,color);
int changer = 0;

for (int f = 0; f<index; f++) {
     if (GanttChart[f]==9) cout << "   ";
     else {
     SetConsoleTextAttribute(h,color);
     cout << GanttChart[f]+1 << "  " ;

     switch(changer){
     case 0 : if (GanttChart[f]!=GanttChart[f+1] && changer==0)   {
                  color = 64;
                  changer++;
               }
      break;
     case 1 : if (GanttChart[f]!=GanttChart[f+1] && changer==1)   {
                  color = 32;
                  changer++;
              }
      break;
     case 2 : if (GanttChart[f]!=GanttChart[f+1] && changer==2)   {
                  color = 48;
                  changer++;
              }
      break;
      case 3 : if (GanttChart[f]!=GanttChart[f+1] && changer==3)   {
                  color = 80;
                  changer=0;
               }
      break;
  }
 }
}
color = 7;
SetConsoleTextAttribute(h,color); // Taking back to default color
cout << " |" << endl << " ";
for (i = 0; i<index+1; i++) cout << "-- ";

cout << endl ;
for (i = 0; i<index+1; i++)
        if (i<10) cout << " " << i << " ";
        else cout << " " << i;
//End of GanttChart representation

cout << "\n\n" << "Process" << "\t\t" << "burst-time" << "\t" << "arrival-time" << "\t" <<"waiting-time" << "\t" << "turnaround-time" <<   "\t" << "completion-time" << endl;

for (i=0; i<numOfProc;i++) {
cout << "p" <<i+1<< "\t\t" << x[i] << "\t\t" << aT[i] <<"\t\t" << waiting[i] << "\t\t" << turnaround[i]<<"\t\t" <<completion[i] << endl;
average+=waiting[i];
tt+=turnaround[i];
}

cout << "\n\nAverage waiting time " << average/numOfProc;
cout << "  Average turnaround time =" <<tt/numOfProc <<endl;

return 0;
}