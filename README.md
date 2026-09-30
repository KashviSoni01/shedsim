# SchedSim — CPU Scheduling Simulator

## Project Description

SchedSim is a command-line CPU scheduling simulator written entirely in C.

In a multitasking operating system, multiple processes compete for access to the CPU. The operating system uses CPU scheduling algorithms to decide which process should execute, when it should execute, and for how long.

Different scheduling strategies can produce significantly different results in terms of waiting time, turnaround time, response time, and CPU utilization.

SchedSim aims to simulate this process in a controlled environment. Users will be able to create a set of processes, select a CPU scheduling algorithm, simulate their execution, visualize the execution timeline, and analyze the resulting scheduling metrics.

The project will implement multiple scheduling algorithms and provide a way to compare their behavior using the same set of processes.

---

## Problem Statement

CPU scheduling is a fundamental operating-system problem where multiple processes compete for a limited CPU resource.

Although scheduling algorithms can be studied mathematically, it can be difficult to understand how their decisions affect the actual execution of processes.

SchedSim addresses this by providing an interactive simulation environment where process scheduling can be observed step by step.

The simulator will model process arrival, execution, waiting, completion, and preemption where applicable. It will then calculate important scheduling metrics and present the results in a readable format.

---

## Goals

The main goals of SchedSim are:

1. Understand CPU scheduling through practical implementation in C.
2. Implement multiple CPU scheduling algorithms from scratch.
3. Simulate process execution over time.
4. Calculate important scheduling metrics.
5. Display process execution using terminal-based Gantt charts.
6. Compare the behavior of different scheduling algorithms on the same workload.
7. Practice C programming concepts such as structures, arrays, functions, pointers, queues, and file handling.
8. Build a well-structured C project suitable for use as a portfolio project.

---

## Specifications

### Process Information

Each process will contain information such as:

- Process ID
- Arrival Time
- Burst Time
- Priority
- Remaining Burst Time
- Completion Time
- Turnaround Time
- Waiting Time
- Response Time

### Scheduling Algorithms

The initial version of SchedSim will implement:

- First Come First Serve (FCFS)
- Shortest Job First (SJF)
- Round Robin (RR)

Additional algorithms may be added as future improvements.

### Scheduling Metrics

For each process, the simulator will calculate:

- Completion Time
- Turnaround Time
- Waiting Time
- Response Time

The simulator will also calculate average values across all processes.

### Visualization

The simulator will display the execution order of processes using a terminal-based Gantt chart.

Example:

```text
| P1 | P1 | P2 | P2 | P3 | P3 |
0    1    2    3    4    5    6