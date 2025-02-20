#include <stdio.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int id, arrival, burst, priority;
    int remaining, completion, turnaround, waiting;
} Process;

void displayResults(Process p[], int n) {
    float totalWT = 0, totalTAT = 0;
    printf("\nID   AT   BT   PR   CT   WT   TAT\n");
    for (int i = 0; i < n; i++) {
        printf("%02d   %02d   %02d   %02d   %02d   %02d   %02d\n", p[i].id, p[i].arrival, p[i].burst, p[i].priority, p[i].completion, p[i].waiting, p[i].turnaround);
        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void fcfs(Process p[], int n) {
    sortByArrival(p, n);
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        p[i].completion = time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        time = p[i].completion;
    }
    displayResults(p,n);
}

void sjf(Process p[], int n) 
{
    int completed = 0, time = 0, minIdx;
    int isCompleted[MAX] = {0}; 
    sortByArrival(p, n);
    while (completed < n) {
        minIdx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && !isCompleted[i]) {
                if (minIdx == -1 || p[i].burst < p[minIdx].burst)
                    minIdx = i;
            }
        }

        if (minIdx == -1) {
            time++; 
            continue;
        }
        time += p[minIdx].burst;
        p[minIdx].completion = time;
        p[minIdx].turnaround = p[minIdx].completion - p[minIdx].arrival;
        p[minIdx].waiting = p[minIdx].turnaround - p[minIdx].burst;
        isCompleted[minIdx] = 1; 
        completed++;
    }
    displayResults(p, n);
}

void srtf(Process p[], int n) {
    int time = 0, completed = 0, minIdx = -1;
    int remainingProcesses = n; 
    while (completed < n) {
        minIdx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (minIdx == -1 || p[i].remaining < p[minIdx].remaining)
                    minIdx = i;
            }
        }
        if (minIdx == -1) {
            time++; 
            continue;
        }
        p[minIdx].remaining--;
        time++;
        if (p[minIdx].remaining == 0) {
            completed++;
            p[minIdx].completion = time;
            p[minIdx].turnaround = p[minIdx].completion - p[minIdx].arrival;
            p[minIdx].waiting = p[minIdx].turnaround - p[minIdx].burst;
        }
    }
    displayResults(p, n);
}

void priorityPreemptive(Process p[], int n) {
    int time = 0, completed = 0, highestIdx;
    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        p[i].completion = 0;
    }

    while (completed < n) {
        highestIdx = -1;
        int minPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (p[i].priority < minPriority) {
                    minPriority = p[i].priority;
                    highestIdx = i;
                }
            }
        }

        if (highestIdx == -1) {
            int minArrival = INT_MAX;
            for (int i = 0; i < n; i++) {   
                if (p[i].remaining > 0 && p[i].arrival < minArrival)
                    minArrival = p[i].arrival;
            }
            time = minArrival;
            continue;
        }

        p[highestIdx].remaining--;
        time++;

        if (p[highestIdx].remaining == 0) {
            completed++;
            p[highestIdx].completion = time;
            p[highestIdx].turnaround = p[highestIdx].completion - p[highestIdx].arrival;
            p[highestIdx].waiting = p[highestIdx].turnaround - p[highestIdx].burst;
        }
    }

    displayResults(p, n);
}

void priorityNonPreemptive(Process p[], int n) {
    int completed = 0, time = 0;
    for (int i = 0; i < n; i++) {
        p[i].completion = 0;
    }

    while (completed < n) {
        int highestIdx = -1;
        int minPriority = 1e9; 

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].completion == 0) {
                if (p[i].priority < minPriority) {
                    minPriority = p[i].priority;
                    highestIdx = i;
                }
            }
        }

        if (highestIdx == -1) {
            int minArrival = 1e9;
            for (int i = 0; i < n; i++) {
                if (p[i].completion == 0 && p[i].arrival < minArrival)
                    minArrival = p[i].arrival;
            }
            time = minArrival;
            continue;
        }

        time += p[highestIdx].burst;
        p[highestIdx].completion = time;
        p[highestIdx].turnaround = p[highestIdx].completion - p[highestIdx].arrival;
        p[highestIdx].waiting = p[highestIdx].turnaround - p[highestIdx].burst;
        completed++;
    }

    displayResults(p, n);
}


void roundRobin(Process p[], int n, int quantum) {
    int time = 0, completed = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0 && p[i].arrival <= time) {
                if (p[i].remaining > quantum) {
                    time += quantum;
                    p[i].remaining -= quantum;
                } else {
                    time += p[i].remaining;
                    p[i].remaining = 0;
                    p[i].completion = time;
                    p[i].turnaround = p[i].completion - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    completed++;
                }
            }
        }
    }
    displayResults(p,n);
}

int main() {
    int n, choice, quantum;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival, burst time, priority: ");
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].remaining = p[i].burst;
    }

    do{
    printf("1. FCFS\n2. SJF\n3. SRTF\n4. Priority (Preemptive)\n5. Priority (Non-Preemptive)\n6. Round Robin\n7. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(p, n);
            break;
        case 2:
            sjf(p, n);
            break;
        case 3:
            srtf(p, n);
            break;
        case 4:
            priorityPreemptive(p, n);
            break;
        case 5:
            priorityNonPreemptive(p, n);
            break;
        case 6:
            printf("Enter quantum: ");
            scanf("%d", &quantum);
            roundRobin(p, n, quantum);
            break;
        case 7:
            printf("\nThank You");
        default:
            printf("Invalid choice!\n");
    }
    }while(choice!=7);

    return 0;
}