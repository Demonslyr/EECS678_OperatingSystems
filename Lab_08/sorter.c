#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct proc_line
{
    int pid;
    int at;
    int pri;    

} proc_line;

int arrtime(const void * a, const void * b)
{
    const proc_line * elemA = a;
    const proc_line * elemB = b;
	return ( elemA->at - elemB->at );
}

int priority(const void * a, const void * b)
{
    const proc_line * elemA = a;
    const proc_line * elemB = b;
    if(elemB->pri == elemA->pri)
    {
        if(elemA->at> elemB->at)
        {
            return(0);
            return ( elemA->pri - elemB->pri );
        }
        return(1);
        return ( elemB->pri - elemA->pri );    
    }
	return ( elemB->pri - elemA->pri );
}


//typedef int (*compar) (int a, int b);

int num_elem;

int main (int argc, char *argv[])
{
int proc_arr[7][3];
proc_line proc_line_arr[7];
FILE *input = fopen("process.txt","r");

char buff[255];

if(input == NULL)
{
    printf("Can't open file\n");
    exit(1);
}

int row =0;

while(fgets(buff,sizeof buff,input)!=NULL)
{
    char *token;
    token = strtok(buff,",");
    proc_line_arr[row].pid = atoi(token);
    token = strtok(NULL,",");
    proc_line_arr[row].at = atoi(token);
    token = strtok(NULL,",");
    proc_line_arr[row].pri = atoi(token);
    row++;
}
    int i =0;
    while(i<7)
    {
        printf("Row # %d: %d, %d, %d\n",i,proc_line_arr[i].pid,proc_line_arr[i].at,proc_line_arr[i].pri);
        i++;
    }


qsort(&proc_line_arr, (7), sizeof(proc_line_arr[0]),arrtime);
printf("\n\nArrival Time:\n");
    i =0;
    while(i<7)
    {
        printf("Row # %d: %d, %d, %d\n",i,proc_line_arr[i].pid,proc_line_arr[i].at,proc_line_arr[i].pri);
        i++;
    }
    
qsort(&proc_line_arr, (7), sizeof(proc_line_arr[0]),priority);

printf("\n\nPriority\n");
    i =0;
    while(i<7)
    {
        printf("Row # %d: %d, %d, %d\n",i,proc_line_arr[i].pid,proc_line_arr[i].at,proc_line_arr[i].pri);
        i++;
    }


}



