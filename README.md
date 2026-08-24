# 🐧 Operating Systems Practical Laboratory & Linux Learning Repository

A comprehensive, organized, and clean repository containing Linux Operating System practical implementations, POSIX system call programming, process synchronization, CPU scheduling algorithms, multithreading, and Linux terminal command cheatsheets.

---

## 📁 Repository Structure

```tree
.
├── Practical 1/
│   ├── commands.txt            # System calls, uname, free, ps, and /proc explanations
│   └── practical1.c            # C program exploring getpid, uname, and sysinfo
│
├── Practical 2/
│   ├── commands.txt            # Process creation, pstree, ps, top, strace explanations
│   ├── fork1.c                 # Process creation using fork() & wait()
│   ├── p1.c                    # Target binary called by execv()
│   ├── example.c               # Process replacement via execv()
│   ├── ex.c                    # Executing system binaries (/bin/ls) via execv()
│   └── build_system.c          # Multi-process build automation simulation
│
├── Practical 4/
│   ├── commands.txt            # CPU scheduling, priorities (nice/renice), and process states
│   ├── zombie.c                # Creation and lifecycle of a Zombie (defunct) process
│   ├── fcfs.c                  # First-Come First-Served CPU scheduling with Gantt chart
│   ├── sjf.c                   # Shortest Job First (Preemptive SRTF & Non-Preemptive)
│   ├── priority.c              # Priority CPU scheduling (Preemptive & Non-Preemptive)
│   └── round_robin.c           # Round Robin scheduling with configurable time quantum
│
└── Practical 5/
    ├── commands.txt            # POSIX threads, context switching, and /proc/task inspection
    ├── fork_vs_thread.c        # Demonstrates process memory space isolation vs threads
    ├── thread1.c               # Demonstrates shared global memory between threads
    ├── thread2.c               # Concurrent interleaved execution of multiple threads
    ├── thread3.c               # Array of thread handles and loop synchronization
    ├── exp_3.c                 # Thread scalability benchmarking (2, 4, 8, 16 threads)
    └── exp_1.c                 # Sequential vs Multithreaded execution time benchmark
```

---

## 🚀 Practicals Overview & Quick Run Guide

### 📘 [Practical 1: Linux System Calls & Kernel Interface Exploration](./Practical%201)
- **Concepts**: User-kernel space interface, POSIX system calls (`getpid()`, `getppid()`, `uname()`, `sysinfo()`), `/proc` virtual filesystem inspection (`/proc/self/status`, `/proc/version`, `/proc/meminfo`).
- **Compile & Run**:
  ```bash
  cd "Practical 1"
  gcc practical1.c -o practical1
  ./practical1
  ```

---

### 📙 [Practical 2: Process Creation, Program Execution & Synchronization](./Practical%202)
- **Concepts**: Process hierarchy, Parent-Child relationships, process states, `fork()`, `execv()`, `execvp()`, `wait()`, `waitpid()`, and build system automation.
- **Compile & Run**:
  ```bash
  cd "Practical 2"
  
  # Basic Fork & Wait
  gcc fork1.c -o fork1 && ./fork1
  
  # Process Image Replacement (execv)
  gcc p1.c -o p1
  gcc example.c -o example && ./example
  
  # Executing System Command (/bin/ls -l)
  gcc ex.c -o ex && ./ex
  
  # Build System Automation
  gcc build_system.c -o build_system && ./build_system
  ```

---

### 📗 [Practical 4: CPU Scheduling Algorithms & Process Control](./Practical%204)
- **Concepts**: Process scheduling algorithms (FCFS, SJF/SRTF, Priority, Round Robin), performance metrics ($WT$, $TAT$, $RT$, Throughput), process states (`R`, `S`, `Z`), priorities (`nice`, `renice`), real-time scheduling (`chrt`).
- **Compile & Run**:
  ```bash
  cd "Practical 4"
  
  # Zombie Process Simulation
  gcc zombie.c -o zombie && ./zombie &
  ps aux | grep 'Z'
  
  # Scheduling Simulators
  gcc fcfs.c -o fcfs && ./fcfs
  gcc sjf.c -o sjf && ./sjf
  gcc priority.c -o priority && ./priority
  gcc round_robin.c -o round_robin && ./round_robin
  ```

---

### 📕 [Practical 5: POSIX Thread Programming & Concurrency Analysis](./Practical%205)
- **Concepts**: Multithreading vs multiprocessing, POSIX thread APIs (`pthread_create`, `pthread_join`, `pthread_exit`), memory sharing vs process isolation, thread scalability, and performance benchmarking.
- **Compile & Run**:
  ```bash
  cd "Practical 5"
  
  # Process Memory Isolation vs Threads
  gcc fork_vs_thread.c -o fork_vs_thread && ./fork_vs_thread
  
  # Shared Memory in Threads
  gcc thread1.c -o thread1 -lpthread && ./thread1
  
  # Concurrent Execution
  gcc thread2.c -o thread2 -lpthread && ./thread2
  gcc thread3.c -o thread3 -lpthread && ./thread3
  
  # Scalability and Benchmarks
  gcc exp_3.c -o exp_3 -lpthread && ./exp_3
  gcc exp_1.c -o exp_1 -lpthread && ./exp_1
  ```

---

## 🛠️ Linux Commands Summary Cheat Sheet

| Practical | Key Commands | What They Inspect / Control |
|---|---|---|
| **Practical 1** | `uname -a`, `free -h`, `ps aux`, `cat /proc/version`, `cat /proc/meminfo` | Kernel release, hardware architecture, memory stats, `/proc` entries |
| **Practical 2** | `pstree -p`, `ps -ef`, `top`, `strace ./binary`, `cat /proc/<pid>/status` | Process tree hierarchy, system call tracing, parent-child PID mapping |
| **Practical 4** | `ps -eo pid,ni,pri,comm`, `nice -n <val>`, `renice`, `chrt -p <pid>`, `kill -9` | Process priority, niceness, real-time scheduling policies, signal handling |
| **Practical 5** | `ps -eLf`, `ps -T -p <pid>`, `top -H`, `ls /proc/<pid>/task/`, `time` | Lightweight processes (LWPs), per-thread CPU usage, execution timing |

---

## 💡 Notes for Git / GitHub

To push this repository to your GitHub account:
```bash
git init
git add .
git commit -m "Add organized OS practical files, C programs, and command guides"
git branch -M main
git remote add origin <YOUR_GITHUB_REPO_URL>
git push -u origin main
```
