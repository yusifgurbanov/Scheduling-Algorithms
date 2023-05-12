#include <stdio.h>
#include <stdbool.h>

void FCFS(int process[1000][3], int n){
    FILE* output = fopen("Group2_FCFS.txt", "w");

    // calculate waiting time, turnaround time
    int current_time = 0;
    int count = 0;
    
    int completion_time[n];
    int waiting_time[n];
    int turnaround_time[n];
    float avg_waiting = 0;
    float avg_turnaround = 0;
    float avg_cpu = 0;
    int cpu_time = 0;
    
    // logic
    for(int i = 0; i < n; i++){
        int process_id = process[i][0];
        int arrival_time = process[i][1];
        int running_time = process[i][2];
        int running_time_copy = process[i][2];
        
        // wait for the process to arrive
        if(current_time < arrival_time) {current_time = arrival_time;}
        
        while(running_time_copy > 0){
            fprintf(output, "time %d: running process: %d\n", count, process_id);
            count++;
            running_time_copy--;
            cpu_time++;
        }// while
        
        // avoid random numbers
        completion_time[i] = 0;
        waiting_time[i] = 0;
        turnaround_time[i] = 0;
        
        completion_time[i] = current_time + running_time;

        // wait = start - arrival time
        waiting_time[i] = current_time - arrival_time;

        // turnaround = finish - submission
        turnaround_time[i] = completion_time[i] - arrival_time;
        current_time = completion_time[i];
        
    }//for i
    
    fprintf(output, "\n");
    
    // average waiting and turnaround time
    for(int i = 0; i < n; i++){
        avg_waiting += waiting_time[i];
        avg_turnaround += turnaround_time[i];
    }// for
    avg_waiting /= n;
    avg_turnaround /= n;
    avg_cpu = (cpu_time / current_time) * 100;
    
    fprintf(output, "Average waiting time: %.2lf\n", avg_waiting);
    fprintf(output, "Average turnaround time: %.2lf\n", avg_turnaround);
    fprintf(output, "Average CPU usage: %.2lf\n", avg_cpu);
    fclose(output);

}// FCFS

void SRTF(int process[1000][3], int n){
    FILE* output = fopen("Group2_SRTF.txt", "w");

     // calculate waiting time, turnaround time
    int current_time = 0;
    int count = 0;
    
    int completion_time[n];
    int waiting_time[n];
    int turnaround_time[n];
    float avg_waiting = 0;
    float avg_turnaround = 0;
    float avg_cpu = 0;
    int cpu_time = 0;
    
    
    // logic

    int remaining_time[n];
    for(int i = 0; i<n; i++){
        remaining_time[i] = process[i][2];
    }
    
    // check whether process is completed
    bool status[n];
    for(int i = 0; i<n; i++){
       status[i] = false;
    }    
    
    int index;
    int min_time;
    while(1){
        index = -1;
        min_time = 100000;
        
        for(int i = 0; i < n; i++){
            if( process[i][1] <= current_time && !status[i] ){
                if(remaining_time[i] < min_time){
                    min_time = remaining_time[i];
                    index = i;
                }// nested if
            }// if
        }// for
        
        if(index == -1) { break; }
        
        int process_id = process[index][0];
        int arrival_time = process[index][1];
        int running_time = process[index][2];
        int running_time_copy = remaining_time[index];
        
        // wait for process to arrive
        if(current_time < arrival_time) current_time = arrival_time;

        fprintf(output, "time %d: running process: %d\n", count, process_id);
        count++;
        running_time_copy--;
        cpu_time++;
        
        if(running_time_copy == 0){
            status[index] = true;
            completion_time[index] = current_time + 1;
            waiting_time[index] = completion_time[index] - arrival_time - running_time;
            turnaround_time[index] = completion_time[index] - arrival_time;
        }// if
        remaining_time[index] = running_time_copy;
        current_time++;
        
    }// while
    
    fprintf(output, "\n");
    
    // average waiting and turnaround time
    for(int i = 0; i < n; i++){
        avg_waiting += waiting_time[i];
        avg_turnaround += turnaround_time[i];
    }// for

    avg_waiting /= n;
    avg_turnaround /= n;
    avg_cpu = (cpu_time / current_time) * 100;
    
    fprintf(output, "Average waiting time: %.2lf\n", avg_waiting);
    fprintf(output, "Average turnaround time: %.2lf\n", avg_turnaround);
    fprintf(output, "Average CPU usage: %.2lf\n", avg_cpu);
    fclose(output);
}// SRTF

void RR(int process[1000][3], int n){
    FILE* output = fopen("Group2_RR.txt", "w");

    int tq = 1; // time quantum
    int cnt, j, t, remain, flag = 0;
    int wt = 0, tat = 0, at[10], bt[10], rt[10];
    int cpu_time = 0;
    
    remain = n;
    for (cnt = 0; cnt < n; cnt++){
        at[cnt] = process[cnt][1];
        bt[cnt] = process[cnt][2];
        rt[cnt] = bt[cnt];
    }// for

    //logic
    for (t = 0, cnt = 0; remain != 0;){
        if (rt[cnt] <= tq && rt[cnt] > 0){
            fprintf(output, "time %d: running process: %d\n", t, process[cnt][0]);
            t += rt[cnt];
            cpu_time += rt[cnt];
            rt[cnt] = 0;
            flag = 1;
        }
        else if (rt[cnt] > 0){
            rt[cnt] -= tq;
            fprintf(output, "time %d: running process: %d\n", t, process[cnt][0]);
            t += tq;
            cpu_time += tq;
        }
        if (rt[cnt] == 0 && flag == 1){
            remain--;
            wt += t - at[cnt] - bt[cnt];
            tat += t - at[cnt];
            flag = 0;
        }
        if (cnt == n - 1) cnt = 0;
        else if (at[cnt + 1] <= t) cnt++;
        else cnt = 0;
    }// end for

    fprintf(output, "\n");
    fprintf(output, "Average waiting time: %.2lf\n", wt * 1.0 / n);
    fprintf(output, "Average turnaround time: %.2lf\n", tat * 1.0 / n);
    fprintf(output, "Average CPU usage %.2lf\n", ((float) cpu_time / t)* 100);
    fclose(output);
}// RR

int main(){
    FILE* myfile = fopen("process.txt", "r");
    int n = 0;
    int process[1000][3];

    char buffer[100];
    fgets(buffer, 100, myfile); // ignore the first line

    // take 3 numbers in a single row and collect them into array
    while(fscanf(myfile, "%d, %d, %d", &process[n][0], &process[n][1], &process[n][2]) == 3){ n++; }
    fclose(myfile);
    
    // sort process by arrival time, then by running time
    for(int i = 0; i< n; i++){
        for(int j = i+1; j<n; j++){
            
            // arrival time
            if(process[i][1] > process[j][1]){
                // swap process 
                int temp[3]; 
                temp[0] = process[i][0];
                temp[1] = process[i][1];
                temp[2] = process[i][2];
                
                process[i][0] = process[j][0];
                process[i][1] = process[j][1];
                process[i][2] = process[j][2];
                
                process[j][0] = temp[0];
                process[j][1] = temp[1];
                process[j][2] = temp[2];
            }// if
            
            //running time
            else if(process[i][1] == process[j][1]){
                if(process[i][2] > process[j][2]){
                    // swap process
                    int temp1[3];
                    temp1[0] = process[i][0];
                    temp1[1] = process[i][1];
                    temp1[2] = process[i][2];
                    
                    process[i][0] = process[j][0];
                    process[i][1] = process[j][1];
                    process[i][2] = process[j][2];
                    
                    process[j][0] = temp1[0];
                    process[j][1] = temp1[1];
                    process[j][2] = temp1[2];
                }// if
            }// else if
        }// for j
    }// for i

    // run the algorithms
    FCFS(process, n);
    SRTF(process, n);
    RR(process, n);
}// main
