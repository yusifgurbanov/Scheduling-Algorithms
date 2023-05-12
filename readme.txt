The given code implements three CPU scheduling algorithms:

First Come First Serve (FCFS), Shortest Remaining Time First (SRTF), and Round Robin (RR). The code takes input in the form of an array 'process' that stores the process id, arrival time, and burst time of 'n' processes.

The FCFS algorithm simply schedules the processes in the order in which they arrive. 
The SRTF algorithm schedules the process with the shortest remaining time to complete first. 
The RR algorithm uses time quantum 'tq' to schedule the processes. Each process is given 'tq' units of time to execute before it is preempted and added back to the end of the ready queue. The scheduler continues to execute processes in a circular manner until all processes are executed.

The implemented code prints the CPU execution details of each process in a separate text file and calculates the average waiting time, average turnaround time, and average CPU usage for each algorithm.
To run the code, "the process.txt" file, which is input file, should be in the location of the "program.c" file






