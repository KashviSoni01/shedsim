# SchedSim — CPU Scheduling Simulator

## 1. Project Description

**SchedSim** is a command-line CPU scheduling simulator developed in **C**. It simulates different CPU scheduling algorithms and calculates important scheduling metrics such as Completion Time, Turnaround Time, Waiting Time, and Response Time.

The simulator also generates a Gantt chart to visualize the order in which processes are executed.

---

## 2. Project Goals

The main goals of the project are:

- To understand how CPU scheduling works in operating systems.
- To implement common CPU scheduling algorithms in C.
- To understand preemptive and non-preemptive scheduling.
- To calculate and compare scheduling metrics.
- To visualize process execution using Gantt charts.
- To gain practical experience with modular C programming and Git.

---

## 3. Project Specifications

### Input

The user provides:

- Number of processes
- Arrival time
- Burst time
- Priority
- Scheduling algorithm
- Time quantum for Round Robin

For priority scheduling, a **smaller number means higher priority**.

### Output

The simulator displays:

- Gantt chart
- Completion Time
- Turnaround Time
- Waiting Time
- Response Time
- Average scheduling metrics

CPU idle periods are also represented in the Gantt chart.

---

## 4. Scheduling Algorithms

| Algorithm | Type | Preemptive |
|---|---|---|
| FCFS | First Come First Serve | No |
| SJF | Shortest Job First | No |
| Priority Scheduling | Priority Based | No |
| Priority Scheduling | Priority Based | Yes |
| SRTF | Shortest Remaining Time First | Yes |
| Round Robin | Time Sharing | Yes |

### Scheduling Metrics

```text
Turnaround Time = Completion Time - Arrival Time

Waiting Time = Turnaround Time - Burst Time

Response Time = First Start Time - Arrival Time
```

---

## 5. Project Design

The project uses a modular structure:

```text
schedsim/
│
├── include/
│   ├── process.h
│   └── scheduler.h
│
├── src/
│   ├── main.c
│   ├── process.c
│   └── scheduler.c
│
└── README.md
```

### Components

**`main.c`**
- Handles user input
- Displays the algorithm menu
- Runs the selected algorithm
- Displays results

**`process.h`**
- Defines the `Process` structure.

**`scheduler.h`**
- Contains scheduling and Gantt chart declarations.

**`scheduler.c`**
- Implements all six scheduling algorithms.
- Handles Gantt chart generation.

The `Process` structure stores information such as PID, arrival time, burst time, priority, remaining time, and scheduling metrics.

For preemptive algorithms, a `ScheduleSegment` structure is used to record the process ID, start time, and end time of each execution segment.

---

## 6. Example

### Input

```text
Number of processes: 4

P1: Arrival = 0, Burst = 8, Priority = 3
P2: Arrival = 1, Burst = 3, Priority = 1
P3: Arrival = 2, Burst = 2, Priority = 2
P4: Arrival = 4, Burst = 1, Priority = 4
```

Using **Preemptive Priority Scheduling**:

```text
P1 | P2 | P3 | P1 | P4
0    1    4    6    13   14
```

---

## 7. Compilation and Execution

### Compile

```bash
gcc src/main.c src/process.c src/scheduler.c -Iinclude -o schedsim
```

### Run on Windows

```powershell
.\schedsim.exe
```

### Run on Linux/macOS

```bash
./schedsim
```

---

## 8. Testing

The project was tested using different process configurations, including:

- Different arrival times
- Different burst times
- Different priorities
- CPU idle periods
- Preemptive scheduling
- Round Robin with different time quanta

The tests were used to verify Gantt charts and scheduling metrics.

---

## 9. Conclusion

SchedSim provides a practical way to understand and compare fundamental CPU scheduling algorithms.

The project combines Operating Systems concepts with C programming and demonstrates how different scheduling strategies affect process execution and performance.

---

## 10. Author

**Kashvi Soni**

Educational project developed to understand CPU scheduling and Operating Systems concepts.