# Embedded / Systems Placement Preparation Roadmap

**Duration:** 2 Months

**Target Roles:**
- Embedded Systems
- Firmware
- Systems Programming
- Mixed Hardware-Software Roles

---

## Preparation Philosophy

This roadmap is:
- Implementation-heavy
- Linux-focused
- Systems-oriented
- Debugging-oriented
- Low on passive theory
- Focused on engineering depth

**Main goals:**
- Strong C programming
- Linux fluency
- Systems programming confidence
- Debugging maturity
- Placement-level DSA
- Strong interview discussions

---

## Daily Time Target

**Average:** 3–4 hrs/day

**Structure:**
- 1.5 hrs — systems / Linux / embedded
- 1 hr — DSA + bit manipulation
- 1–1.5 hrs — implementation / debugging / project work

**Daily task structure:**
- Driver project tasks
- 2 bit-manipulation questions
- 2 DSA questions (C++ + STL)

Theory revision is self-directed (see [Theory Revision Policy](#theory-revision-policy)).

---

## Main Tracks

There are 6 parallel tracks:

1. C + Systems Programming
2. Linux Practical Skills
3. OS + Embedded Concepts
4. Bit Manipulation + Logic Building
5. Placement DSA
6. Linux Device Driver Project

---

## Weekly Plan

### Week 1 — Memory, Pointers, Linux, Debugging

**Goals**
- Become extremely comfortable with memory and pointers
- Build Linux workflow confidence
- Improve implementation fluency
- Start debugging seriously

**C / Systems Topics — Study + Implement**
- Memory layout
- Stack vs heap
- Pointer arithmetic
- Arrays vs pointers
- Dynamic memory
- Structs/unions
- Linked list internals
- File IO basics
- Makefiles

**Linux Topics — Practice Daily**
- gcc, gdb, valgrind
- Makefiles
- grep / find / xargs
- permissions
- ps / top / kill
- shell scripting
- vim basics

**Coding Implementations**

*Data structures (implement from scratch in C):*
- Dynamic vector
- Singly linked list
- Doubly linked list
- Stack
- Queue
- Circular buffer

*String/memory functions (implement):*
- memcpy, memmove, strtok, memset, calloc
- realloc simulation

*Linux/system utilities (build):*
- Mini grep
- Hex dump utility
- File copy utility
- Log parser

**Bit Manipulation**

Focus area — divide practice into:
1. Interview-style logic problems
2. Embedded/systems-oriented bit reasoning

Focus on: XOR reasoning, state transitions, bitwise optimization, packet/register parsing, encoding/decoding, greedy bit logic, masking-based algorithms.

Avoid spending too much time on: repetitive set/reset/toggle-only exercises.

*Topics:* XOR tricks, bit masks, field extraction, bit packing/unpacking, parity, power-of-2 logic, state compression, binary transformations, bitwise arithmetic, bitmap logic.

*Practice problems:* reverse bits, next power of 2, missing number using XOR, two non-repeating numbers, packet parsing, bitmap implementation, subset masks, maximum XOR pair, bitwise addition, Gray code, parity calculation, protocol/register decoding.

**Debugging Focus**

Use: gdb, valgrind.
Debug: segmentation faults, dangling pointers, double free, memory leaks.

---

### Week 2 — Processes, Threads, Synchronization

**Goals**
- Understand Linux execution model
- Build concurrency intuition
- Learn synchronization practically

**Systems Topics — Study + Implement**
- fork(), exec(), wait()
- pipes, signals
- pthreads, mutexes, semaphores
- race conditions, deadlocks

**Implementations — Build**
- Process tree creator
- Parent-child IPC
- Multithreaded counter
- Producer-consumer
- Thread-safe queue
- Command executor
- Parallel file processor

**Debugging Focus**
Debug: race conditions, deadlocks, thread synchronization bugs.
Use: gdb, valgrind, printf tracing.

**Bit Manipulation — Advanced Problems**
- Single Number II/III
- Bitwise addition without +
- Subset generation using bits
- Parity calculation
- Maximum XOR
- XOR partitioning
- Bitmask-based logic
- Bitwise state encoding

**DSA Focus**

Priority is understanding patterns incrementally.

*Phase 1:* arrays, strings, vectors, hash maps, hash sets, stacks, queues, linked lists, binary search, two pointers.

*Phase 2:* sliding window, interval problems, heap problems, DFS/BFS, recursion/backtracking basics.

*Phase 3:* graph patterns, monotonic deque, greedy reasoning, design-style interview questions.

> **Rule:** Do not move aggressively to Phase 2 or Phase 3 until Phase 1 patterns feel comfortable.

Do **NOT** optimize for: hardcore competitive programming, advanced DP-heavy problems, obscure STL/template tricks.

**DSA Learning Philosophy**

Goal: build pattern recognition gradually, learn interview problem families, use C++ STL comfortably.

Important:
- It is acceptable to study editorials initially.
- Pattern recognition is more important than independent solving in the beginning.
- Independence will naturally improve after repeated exposure.

Current focus: simpler questions solved independently; medium questions solved with hints/editorials; understanding patterns over memorizing solutions.

> The objective is not competitive programming — it's becoming comfortable with common placement interview patterns.

Emphasis: repetition over difficulty, pattern recognition over speed, STL familiarity over implementation from scratch.

Preferred problem categories: hashing, arrays, strings, stacks, queues, binary search, two pointers.

Progress to harder graph/heap/advanced problems only after these patterns feel natural.

---

### Week 3 — Advanced Linux Systems Programming + IPC + Debugging

**Goals**
- Become comfortable with real Linux APIs
- Improve systems design thinking

**Topics**
- Advanced Linux systems programming
- IPC (pipes, shared memory, message queues)
- File descriptor management
- Process and thread debugging
- Resource lifecycle management
- Continued DSA foundation building
- Advanced bit manipulation logic

**Implementations — Build**
- Multi-client chat server
- Async logger
- Terminal chat application

**Linux Topics — Learn**
- strace
- lsof
- process inspection

**Bit Manipulation — Embedded-Oriented Logic**
- CRC basics
- Bit packing/unpacking
- State-machine encoding

**DSA Topics**
- Stacks, queues
- Trees basics
- Binary search
- Sliding window

---

### Week 4 — OS + Embedded Systems + Interview-Oriented DSA

**Goals**
- Strengthen interview discussions
- Build systems intuition
- Connect embedded + OS concepts

**OS Topics — Study**
- Scheduling
- Virtual memory, paging, TLB
- Context switching
- Synchronization internals
- IPC
- Cache concepts

**Embedded Topics — Study**
- Interrupts, DMA
- Memory-mapped IO
- volatile
- Cache coherency basics
- RTOS scheduling
- UART/SPI/I2C/CAN
- Polling vs interrupts

**Implementations — Build**
- Memory pool allocator
- Simple scheduler simulation
- Interrupt/event simulation
- Protocol parser

**Debugging Focus**
- Heap corruption debugging
- Synchronization debugging
- Race-condition analysis

---

### Week 5 — Placement DSA + Systems Coding

**Goals**
- Become OA-capable
- Improve implementation speed
- Improve logic building

**DSA Topics** (ONLY placement-relevant)
- Arrays, strings, hashing
- Sliding window, binary search
- Stacks/queues
- Trees basics

NO hardcore competitive programming.

**Bit Manipulation — Tricky Problems**
- Maximum XOR pair
- Bitmask DP basics
- Subset masks
- Missing/repeating numbers
- Unique number problems
- Gray code
- Power set generation
- Packet/state encoding

**Systems Coding — Implement**
- LRU cache
- Memory tracker
- Command parser
- Configuration parser

---

### Weeks 6–8 — Linux Device Driver Project

**Goal:** Transition from Linux systems programming exercises to a substantial Linux kernel/device-driver project that can be showcased on a resume and discussed in embedded/firmware interviews. This project track gradually replaces daily standalone systems questions.

#### Phase 1: Kernel Module Fundamentals

**Objectives**
- Build and load Linux kernel modules
- Understand kernel logging and debugging
- Understand module lifecycle

**Topics**
- `module_init()`, `module_exit()`
- `printk()`
- `dmesg`, `insmod`, `rmmod`, `lsmod`

**Deliverable:** `hello_driver.ko`

#### Phase 2: Character Device Driver

**Objectives:** Create a character driver exposed through `/dev/mychardev`.

**Topics**
- `alloc_chrdev_region()`
- `cdev_init()`, `cdev_add()`
- `class_create()`, `device_create()`
- `file_operations`

**Operations:** `open()`, `release()`, `read()`, `write()`

**Deliverable:** A working character driver that supports:
```
echo "hello" > /dev/mychardev
cat /dev/mychardev
```

#### Phase 3: Advanced Character Driver Features

**Objectives:** Add user-kernel communication features.

**Topics**
- `copy_to_user()`, `copy_from_user()`
- `ioctl()`

**Features:** `SET_VALUE`, `GET_VALUE`, `CLEAR_BUFFER`

**Deliverable:** Character driver with ioctl support.

#### Phase 4: Synchronization Inside Drivers

**Objectives:** Learn how synchronization is performed inside kernel drivers.

**Topics**
- mutex
- spinlock (conceptual)
- wait queues

**Features:** blocking read, blocking write, synchronization between readers/writers

**Deliverable:** Thread-safe character driver.

#### Phase 5: poll()/select() Support

**Objectives:** Connect previous Linux systems knowledge with driver development.

**Topics**
- `poll()`, `select()`
- wait queues

**Features:** Applications should be able to `poll()` / `select()` on the driver.

**Deliverable:** Event-driven character driver.

#### Phase 6: Advanced Character Driver — Mini Kernel Subsystem

**Objectives:** Turn the existing character driver into a self-contained mini kernel subsystem demonstrating multi-client access, structured control, and observability — without requiring any hardware.

**Topics**
- Circular buffer design inside kernel space
- Multiple readers / multiple writers support
- `mutex` / `spinlock` selection and justification
- Extended `ioctl()` command set
- Driver-internal statistics tracking

**Features**
- `/dev/msgdrv` supporting concurrent open() from multiple processes
- Circular buffer with configurable size (`SET_BUFFER_SIZE`)
- `ioctl()` commands: `GET_STATS`, `CLEAR_STATS`, `SET_BUFFER_SIZE`, `RESET_DRIVER`
- Statistics tracked: bytes written, bytes read, read operations, write operations, blocking waits, dropped messages
- Backpressure handling when buffer is full (drop vs block, documented trade-off)

**Deliverable:** A thread-safe, multi-client character driver with configurable buffering and a stats/control interface via `ioctl()`.

#### Phase 7: Virtual Sensor Driver — Kernel Thread + Data Pipeline

**Objectives:** Build a driver that models a real sensor's data pipeline (producer thread → buffer → consumer) using simulated data, while keeping the kernel-side logic hardware-agnostic and swappable for real hardware later.

**Topics**
- `kthread_run()` — kernel thread lifecycle
- Producer-consumer pattern inside the kernel
- `poll_wait()`, `wait_event_interruptible()`, `wake_up_interruptible()`
- Timestamping samples
- Simple moving-average filtering

**Features**
- `/dev/tempsensor` backed by a kernel thread generating simulated readings (temperature/humidity/pressure) at a configurable interval
- `read()` returns the latest sample, blocking via wait queue when no new sample is available
- `poll()` support so userspace can `select()`/`epoll()` on new data
- `ioctl()` commands: `SET_INTERVAL`, `SET_NOISE`, `GET_STATS`, `RESET`
- Userspace monitoring application that polls and logs timestamped readings

**Deliverable:** A kernel-thread-driven virtual sensor driver with blocking reads, `poll()` support, and a userspace monitor — structured so the simulated sampling function can later be swapped for a real I2C/SPI read with no other code changes.

**Expected Outcomes** — by completion of this track:
- Comfortable with Linux kernel modules
- Comfortable with character drivers
- Understand driver synchronization mechanisms
- Understand multi-client driver design and statistics/control interfaces
- Understand kernel-thread-driven producer-consumer patterns and event-driven (`poll()`) drivers
- Possess a substantial embedded/Linux project suitable for firmware and embedded-systems interviews

**Project Requirements** — must include:
- Makefile
- README
- Modular code
- Debugging support
- Clean architecture

---

### Week 7 — Interview Preparation Phase

**Goals**
- Become interview comfortable
- Improve explanation ability
- Improve debugging confidence

**Practice Daily**

*Coding:* timed coding, implementation from scratch

*Interview topics:* OS questions, Linux questions, embedded questions, debugging scenarios

*Discussion practice — explain:* race conditions, mutexes, virtual memory, interrupts, volatile, synchronization

**Mock Discussions** — practice explaining:
- Your project
- Design decisions
- Debugging process
- Failures and fixes

---

### Week 8 — Final Revision + Polish

**Revise**

| Area | Topics |
|---|---|
| C | pointers, memory bugs, undefined behavior, function pointers |
| Linux | processes, threads, synchronization, sockets, debugging tools |
| Embedded | interrupts, DMA, protocols, RTOS basics |
| OS | scheduling, paging, deadlocks, synchronization |

**Final Practice**
- Mock interviews
- Debugging exercises
- Timed implementation
- Project walkthroughs

---

## Progress Notes (Consolidated)

> This section replaces the previously scattered, repeated progress comments with a single running summary, organized by status rather than by the order notes were added.

### Comfortable / Reliable
- Hashing-based DSA problems
- STL usage (no longer a bottleneck)
- Two-pointer patterns
- Binary-search interview problems
- Sliding-window problems (solvable without editorials)
- Register-style bit manipulation / field extraction
- Shared-memory synchronization (mutexes and semaphores)
- Producer-consumer synchronization (shared memory + semaphores)
- `select()` / `poll()` (treated as equivalent-level familiarity)
- Fixed-size memory pools / basic allocator design
- Multi-threaded synchronization patterns
- Monotonic stack patterns (now in reinforcement mode, not introduction)
- Binary Search on Answer (multiple common interview variants)
- Binary Trie and xor maximization based problems
- Foundational bit manipulation: XOR cancellation, XOR partitioning, power-of-two reasoning, bit masking, register extraction, bit scanning, bitwise arithmetic
- Shell project — feature-complete for placement purposes
- Prefix XOR
- Prefix State + HashMap patterns (Prefix XOR, Prefix Sum frequency counting)
- Linux character device registration
- Device-number allocation (major/minor)
- Linux file_operations interface
- Wait queues
- Blocking driver operations
- Basic character driver development (module lifecycle, registration, read/write, ioctl, wait queues, poll)
- Driver synchronization using mutexes
- Circular buffer design and wrap-around logic
- Basic C++ STL usage (sort, priority_queue, lower_bound, upper_bound)

### Introduced, Needs 1–2 Reinforcement Exercises
- Shared-memory IPC
- POSIX message queues (`mq_open` / `mq_send` / `mq_receive`)
- Monotonic deque
- Subset-mask based bit-manipulation problems
- Greedy + Monotonic Stack hybrid problems
- Condition variables / thread-pool style synchronization
- Linux kernel module
- ioctl-based driver interfaces
- Driver synchronization using mutexes
- ioctl-based driver interfaces
- poll()/select() callback implementation
- Linux TTY subsystem
- termios-based serial communication
- UART user-space programming
- Kernel dynamic memory management (kmalloc/kfree)
- Runtime driver reconfiguration via ioctl

### Active Focus Areas (Ongoing)
- Memory allocator design (expanded from pools to slab-style allocators)
- Character driver feature development
- Driver synchronization and wait queues

### General Notes
- New Linux APIs generally require one guided exposure before becoming comfortable.
- Edge-case handling and defensive programming should be emphasized in future exercises going forward.

### Adjust Emphasis Going Forward

**Reduce:**
- Sliding window (basics)
- Monotonic stack basics
- Basic binary-search-on-answer variants
- Simple register extraction / protocol parsing / basic bit-scanning (unless introducing a genuinely new concept)
- Foundational XOR-only drills (unless used for revision)

**Increase:**
- Prefix XOR
- Binary Trie counting problems
- Greedy reasoning problems
- State encoding
- Bitset algorithms
- Subset-mask reasoning
- Mathematical bit logic
- Contribution techniques
- Advanced interview bit-manipulation problems

> Progress to harder graph/heap/advanced DSA problems only after Phase 1/2 patterns feel natural.

---

## Priority Order

**Primary Focus:**
- C systems programming
- Linux practical skills
- Debugging
- Concurrency/synchronization
- OS and systems concepts
- Bitwise logic
- Interview-oriented DSA

**Reduced Priority:**
- Advanced networking
- Hardcore competitive programming
- Advanced kernel internals
- Excessive roadmap/theory hopping

---

## What to Avoid

Avoid spending too much time on:
- Advanced C++
- Competitive programming
- Advanced kernel internals
- Deep networking theory
- Excessive tutorials
- Roadmap hopping
- Implementing every DSA structure manually, repeatedly

Prioritize instead: systems thinking, Linux fluency, debugging, concurrency, interview-style logic problems.

---

## Theory Revision Policy

Theory revision is **not** scheduled daily. Instead, revisit theory:
- When a coding problem exposes a knowledge gap
- Before interview preparation rounds
- During dedicated revision weeks
- When project work requires deeper understanding

**Priority theory areas:**
- Operating Systems
- Computer Architecture
- Embedded Systems
- Linux Internals
- Synchronization
- Memory Management
- Communication Protocols
- RTOS Concepts

Implementation and problem-solving remain the primary learning method.

---

## Final Target

By placements, aim to become someone who can:
- Write robust C code
- Debug independently
- Work comfortably in Linux
- Understand concurrency
- Solve placement-level coding questions
- Explain systems concepts clearly
- Discuss engineering tradeoffs confidently
- Build small systems software independently

---

## Daily Question Tracker

### Day 1

#### C / Systems
- Reverse Array — Arrays / Pointers
- Palindrome String — Strings
- my_strlen — Strings / Pointers
- my_strcpy — Strings / Pointers
- my_strcmp — Strings / Pointers
- Linked List Insert/Delete — Linked Lists
- Max in Array — Arrays
- Circular Buffer — Buffers / Wraparound Logic
- Dynamic Vector — Dynamic Memory / Heap Management
- file_copy.c — Linux File IO / System Calls

#### Linux
- Linux Directory Structure Creation — Terminal Basics
- GCC Compilation — Build Workflow
- Makefile Creation — Build Systems
- Shell Script Build Automation — Shell Scripting
- Process Monitoring — ps/top/kill
- File Search / Filtering — grep/find/xargs
- fork() Example — Processes
- pipe() Example — IPC / Pipes
- pthread Counter Example — Threads / Race Conditions

#### Bit Manipulation
- Set/Clear/Toggle/Check nth Bit — Bit Operations
- Count Set Bits — Kernighan Algorithm
- Detect Power of 2 — Bit Logic
- Reverse Bits — Divide-and-Conquer Bit Manipulation
- Next Power of Two — Bit Reduction Logic
- Find Position of Set Bit — Bit Scanning
- Swap Odd/Even Bits — Bit Masks
- Integer Addition Without '+' — XOR + Carry Logic

#### DSA
- None yet

---

### Day 2

#### C / Systems
- Circular Buffer Upgrade — Robustness / Error Handling
- Dynamic Vector Upgrade — realloc / Heap Management
- file_copy Upgrade — Linux File IO / Robustness
- Producer Consumer — Threads / Synchronization
- Valid Parentheses — Stack Implementation
- Binary Search — Searching Algorithms

#### Linux
- fork + execlp Example — Process Control
- wait() Usage — Process Synchronization
- Multiple Child Processes — Scheduling / Process Hierarchy
- command_logger.sh — Shell Scripting / Logging

#### Bit Manipulation
- Bitfield Extraction — Register Parsing
- Bitmap Implementation — Bit Arrays
- Missing Number Using XOR — XOR Reduction Logic
- Two Non-Repeating Numbers — XOR Partitioning Logic

#### DSA
- Valid Parentheses — Stack
- Binary Search — Binary Search

---

### Day 3

#### C / Systems
- file_copy_stats.c — Advanced File IO / Statistics
- mini_wc.c — Low-Level File Processing
- file_permissions.c — Linux File APIs / stat/access
- Memory Pool Allocator — Custom Allocation
- my_calloc — Allocation Internals
- Reader Writer Problem — Synchronization
- Thread Pool — Worker Architecture
- Queue Using Two Stacks — Data Structure Design

#### Linux
- File Descriptor Handling — Linux File IO
- access() and stat() Usage — Linux APIs
- search_logs.sh — Linux Search Utilities

#### Bit Manipulation
- Skipped basic bit-manipulation exercises intentionally to focus more on logic-heavy/system-oriented problems

#### DSA
- Longest Substring Without Repeating Characters — Sliding Window
- Queue Using Two Stacks — Stack/Queue Logic

---

### Day 4

#### C / Systems
- Shared Memory Example — IPC / Shared Memory
- Shared Memory + Synchronization — Process Synchronization
- Signal Handling — UNIX Signals
- LRU Cache — Hashmap + Doubly Linked List

#### Linux
- Shared Memory APIs — shmget/shmat/shmctl
- Signal Registration — signal()
- Process Communication — IPC

#### Bit Manipulation
- Gray Code Generator — XOR State Transitions
- Maximum XOR Pair — Greedy Bitwise Logic

#### DSA
- Merge Intervals — Interval Merging
- Floyd Cycle Detection — Fast/Slow Pointer
- LRU Cache — Design Problem

---

### Day 5

#### C / Systems
- mini_shell.c — Process Execution / fork-exec-wait
- Deadlock Demonstration — Mutex Ordering / Concurrency
- Deadlock Fix — Lock Ordering Strategy

#### Linux
- execvp() Usage — Command Execution
- Shell Loop Implementation — Process Control
- Process Synchronization — wait()

#### Bit Manipulation
- Single Number II — Bitwise State Machine Logic

#### DSA
- Top K Frequent Elements — Heap + Hashmap
- Sliding Window Maximum — Monotonic Deque

---
### Day 6

#### C / Systems
- mini_shell Argument Parsing — Tokenization / execvp argv Handling
- mini_strace_logger.c — Syscall Logging / File Descriptor Awareness
- interrupt_handler.c — ISR Registration / Function Pointers

#### Linux
- execvp argv Handling — Process Execution
- System Call Observation — open/read/write/close
- File Descriptor Awareness — Linux IO Internals

#### Bit Manipulation
- Single Number III — XOR Partitioning Logic

#### DSA
- Number of Islands — DFS / Grid Traversal
- K Closest Elements — Binary Search + Two Pointers

---

### Day 7

#### C / Systems
- mini_shell_upgrade.c — Background Processes / Redirection / Process Lifecycle
- File Descriptor Redirection — dup2() / UNIX IO Model

#### Linux
- Background Execution (&) — Foreground vs Background Processes
- Zombie Cleanup — waitpid(..., WNOHANG)
- Output Redirection — open() + dup2()
- Process Lifecycle Management — fork/exec/wait Integration

#### Embedded / Concurrency
- Lock-Free Ring Buffer (Conceptual Revision) — Single Producer Single Consumer Design

#### Bit Manipulation
- Maximum XOR Using Binary Trie — Greedy Bitwise Traversal
- Detect Opposite Signs — Sign-Bit Reasoning / XOR Logic

#### DSA
- Course Schedule — Graph Cycle Detection / DFS
- Merge K Sorted Lists — Heap / Priority Queue

---
### Day 8

#### C / Systems
- mini_shell_v3.c — Command History / Circular Buffer Style State Management
- fd_inspector.c — File Descriptors / /proc Filesystem Exploration

#### Linux
- /proc/self/fd Exploration — Linux Process Introspection
- File Descriptor Lifecycle — open(), close(), opendir()
- Shell State Management — Command History Tracking

#### Embedded / Concurrency
- UART Packet Parser (Skipped) — Already comfortable with basic packet parsing and field extraction concepts

#### Bit Manipulation
- Find Element Appearing Odd Number of Times — XOR Cancellation Logic
- Count Total Set Bits from 1 to N — Kernighan Algorithm / Bit Counting Patterns

#### DSA
- Contains Duplicate — Hash Set Pattern
- Valid Anagram — Frequency Counting / Hash Map Pattern

---

### Day 9

#### C / Systems
- mini_shell_v4.c — Built-in Commands / Shell Architecture
- mini_logger.c — Modular Logging Utility / File Logging

#### Linux
- Built-in Shell Commands — cd / pwd / exit / history
- Process Environment vs Child Process Execution
- Log File Creation and Management
- File Descriptor Based Logging

#### Bit Manipulation
- Power Of Four Detection — Bit Pattern Recognition
- Rightmost Different Bit — XOR + Bit Extraction Logic

#### DSA
- Two Sum — Hash Map Lookup Pattern
- Merge Sorted Array — Two Pointer Technique

---
### Day 10

#### C / Systems
- mini_shell_v5.c — Pipes / Process Communication
- mini_diff.c — File Comparison Utility / File IO

#### Linux
- pipe() System Call
- dup2() with Pipes
- Inter-Process Communication (IPC)
- Multi-Process Data Flow

#### Bit Manipulation
- XOR Swap — XOR Properties
- Divide Without '/' — Bit Shifting / Binary Arithmetic

#### DSA
- Valid Parentheses — STL Stack Pattern
- Best Time To Buy And Sell Stock — Running Minimum Pattern
---

### Day 11

#### C / Systems
- mini_shell_v6.c — Background Job Tracking / Shell State Management
- mini_hexdump.c — Binary File Inspection Utility

#### Linux
- Background Process Tracking
- waitpid(..., WNOHANG) for Job Monitoring
- Binary File Processing
- File Formatting and Inspection Utilities

#### Bit Manipulation
- Count Trailing Zeros — Lowest Set Bit Logic
- Reverse 32-bit Integer — Hierarchical Bit Swapping

#### DSA
- Remove Duplicates From Sorted Array — Two Pointer Pattern
- Valid Palindrome — String Processing + Two Pointers

---

### Day 12

#### C / Systems
- mini_shell_v7.c — Command Execution Timing / Performance Measurement
- mini_tail.c — File Seeking / Reverse File Traversal

#### Linux
- clock_gettime()
- Execution Time Measurement
- File Positioning (fseek/ftell)
- Linux Utility Development

#### Bit Manipulation
- Next Power Of Two — Bit Propagation Technique
- Find Missing Number (Skipped — Previously Solved)

#### DSA
- Majority Element — Hash Map Frequency Counting
- Intersection Of Two Arrays — Hash Set Pattern

---
### Day 13

#### C / Systems
- mini_shell_v8.c — Conditional Execution (&&) / Exit Status Handling
- mini_wcl.c — Low-Level File Processing / Line Counting
- process_tree.c — Process Metadata Inspection via /proc

#### Linux
- Process Exit Status (WIFEXITED / WEXITSTATUS)
- /proc/<pid>/status Exploration
- Low-Level File IO (open/read/close)
- Linux Process Introspection

#### Bit Manipulation
- Count Bits For Every Number — Bit DP Pattern
- Single Number II — Bitwise State Machine Logic

#### DSA
- Valid Sudoku — Hashing + Matrix Validation
- First and Last Occurrence — Binary Search Variant

---

### Day 14

#### C / Systems
- mini_shell_v9.c — Logical OR (||) / Shell Command Chaining
- mini_cat.c — Low-Level File Display Utility
- fd_leak_demo.c — File Descriptor Lifecycle / Resource Leak Demonstration

#### Linux
- Logical Command Chaining
- Resource Leak Detection
- /proc/self/fd Monitoring
- Low-Level File Reading and Writing

#### Bit Manipulation
- Generate All Subsets Using Bitmasks — Bitmask Enumeration
- Find Two Missing Numbers — XOR Partitioning Logic

#### DSA
- Queue Using STL — STL Queue Familiarity
- Find Peak Element — Binary Search Pattern

---

### Day 15

#### C / Systems
- mini_shell_v10.c — Sequential Command Execution (;)
- mini_tee.c — Stream Duplication Utility

#### Linux
- Sequential Command Parsing
- STDIN / STDOUT Stream Handling
- File Descriptor Duplication Concepts
- Utility-Style Program Development

#### Bit Manipulation
- Binary Representation Palindrome Check
- Remainder Without Using *, /, %

#### DSA
- Move Zeroes — Two Pointer Pattern
- Longest Common Prefix — String Comparison Pattern

---

### Day 16

#### C / Systems
- mini_shell_v11.c — Quoted String Parsing / Shell Tokenization
- shared_counter.c — Shared Memory IPC / Parent-Child Communication

#### Linux
- Shared Memory APIs (shmget/shmat/shmdt/shmctl)
- Parent-Child Shared State
- Shell Parsing Strategies
- Command Tokenization

#### Bit Manipulation
- Binary Gap — Bit Scanning / State Tracking
- Modulo Bit Counting Logic (Single Number Variant)

#### DSA
- Valid Anagram (Frequency Array Version) — Character Counting
- Search Insert Position — Binary Search Variant

---

### Day 17

#### C / Systems
- mini_shell_v12.c — Append Redirection (>>)
- message_queue_demo.c — POSIX Message Queues / IPC

#### Linux
- POSIX Message Queue APIs
- mq_open / mq_send / mq_receive
- Append File Semantics (O_APPEND)
- IPC Mechanism Comparison

#### Bit Manipulation
- Parity Calculation Using XOR Folding
- Bitwise Majority Construction

#### DSA
- Search In Rotated Sorted Array — Pivot Detection + Binary Search

---

### Day 18

#### C / Systems
- mini_shell_v13.c — STDERR Redirection (2>)
- select_demo.c — I/O Multiplexing / select()

#### Linux
- STDERR vs STDOUT Redirection
- select() API
- FD Sets (FD_ZERO / FD_SET / FD_ISSET)
- Blocking vs Timed Waiting

#### Bit Manipulation
- XOR of Numbers From 1 to N — XOR Periodicity Pattern
- Count Different Bits Between Two Numbers — XOR Distance

#### DSA
- Next Greater Element — Monotonic Stack Introduction
- Minimum Size Subarray Sum — Sliding Window Pattern
---

### Day 19

#### C / Systems
- mini_shell_v14.c — Combined STDOUT/STDERR Redirection
- poll_demo.c — poll() Based I/O Multiplexing
- shared_counter_semaphore.c — Shared Memory + Semaphore Synchronization

#### Linux
- poll() API
- struct pollfd
- POLLIN Event Handling
- Process-Shared Semaphores
- Synchronization Using sem_wait / sem_post

#### Bit Manipulation
- Isolate Rightmost Consecutive Set-Bit Block — Mask Construction
- Count Numbers With Exactly One Set Bit — Power-of-Two Pattern

#### DSA
- Daily Temperatures — Monotonic Stack Reinforcement
- Longest Substring With At Most K Distinct Characters — Sliding Window + Hash Map
---

### Day 20

#### C / Systems
- mini_shell_v15.c — Input Redirection (<)
- shared_mem_producer_consumer.c — Shared Memory Producer Consumer

#### Linux
- STDIN Redirection
- Producer Consumer Synchronization
- Shared Memory Circular Buffers
- Semaphore-Based Resource Coordination

#### Bit Manipulation
- Extract Bit Field — Register Parsing
- Circular Bit Rotation — Hardware-Style Bit Operations

#### DSA
- Largest Rectangle In Histogram — Monotonic Stack
- Longest Repeating Character Replacement — Sliding Window + Frequency Tracking

---

### Day 21

#### C / Systems
- mini_shell_v16.c — Combined Input + Append Redirection
- shared_mem_producer_consumer_ring_buffer.c — Circular Buffer Producer Consumer

#### Linux
- Multiple File Descriptor Redirections
- Shared Memory Circular Buffer Design
- Producer Consumer Architecture
- Semaphore Protected Ring Buffers

#### Bit Manipulation
- Decode Packed Register — Firmware Register Parsing
- Count Trailing Ones — Bit State Scanning

#### DSA
- Sum Of Subarray Minimums — Monotonic Stack + Contribution Technique
- Longest Substring Without Repeating Characters (Revisited) — Sliding Window Reinforcement
---

### Day 22

#### C / Systems
- mini_shell_v17.c — Shell Robustness / Error Handling
- mini_mem_tracker.c — Memory Tracking and Leak Detection
- thread_pool.c — Thread Pool / Condition Variables

#### Linux
- Defensive Programming
- Condition Variables (pthread_cond_t)
- Worker Thread Architecture
- Task Queue Design

#### Bit Manipulation
- Maximum XOR Pair Using Binary Trie (Revisited)
- Count Pairs Differing By Exactly One Bit — Hamming Distance Logic

#### DSA
- Binary Search On Answer (Introduced)
- Sliding Window Maximum (Revisited)
---

### Day 23

#### C / Systems
- mem_pool_allocator.c — Fixed Size Memory Pool Allocator
- bounded_blocking_queue.c — Mutex + Condition Variable Queue

#### Linux
- Memory Pool Design
- Condition Variable Based Synchronization
- Blocking Queue Architecture
- Resource Lifecycle Management

#### Bit Manipulation
- Total XOR Of All Pairs — Contribution Technique
- Count Subsets With XOR = K — Subset Mask Enumeration

#### DSA
- Capacity To Ship Packages Within D Days — Binary Search On Answer
- Next Smaller Element — Monotonic Stack Reinforcement
---
### Day 24

#### C / Systems
- mem_pool_allocator_v2.c — Memory Pool Validation / Double-Free Protection
- delayed_task_scheduler.c — Event Scheduling / Timed Task Execution

#### Linux
- Event Loop Design
- Delayed Task Scheduling
- Priority Ordered Task Queues
- Allocator Robustness

#### Bit Manipulation
- Sum Of XOR Of All Pairs — Contribution Technique Reinforcement
- Maximum XOR Subarray — Prefix XOR + Binary Trie

#### DSA
- Split Array Largest Sum — Binary Search On Answer Reinforcement
- Stock Span Problem — Monotonic Stack Reinforcement
---

### Day 25

#### C / Systems
- slab_allocator.c — Multi-Slab Memory Allocation
- reader_writer_lock.c — Reader-Writer Synchronization

#### Linux
- Slab Allocator Design
- Multi-Pool Memory Management
- Reader-Preference Synchronization
- Concurrency Control

#### Bit Manipulation
- Count Subarrays With XOR = K — Prefix XOR + Hash Map
- Maximum XOR Pair Without Trie — Greedy Bit Construction

#### DSA
- Allocate Minimum Number Of Pages — Binary Search On Answer Reinforcement
- Next Greater Element Circular Array — Monotonic Stack + Circular Traversal
---

### Day 26

#### C / Systems
- multi_producer_single_consumer.c — Multi-Producer Queue Synchronization

#### Linux
- Multi-Producer Single-Consumer Design
- Semaphore + Mutex Coordination
- Queue Ownership and Synchronization

#### Bit Manipulation
- Count Triplets With XOR = 0 — Prefix XOR + Counting Logic
- Maximum XOR Between Two Subsets — XOR Reasoning / Mathematical Bit Logic

#### DSA
- Aggressive Cows — Binary Search On Answer Reinforcement
- Online Stock Span (Conceptually Reviewed) — Monotonic Stack Design Pattern
---

### Day 27

#### Bit Manipulation
- Count Subarrays With XOR Less Than K — Prefix XOR + Binary Trie Counting
- Minimum XOR Pair — Sorting + Bitwise Observation

#### DSA
- Painters Partition Problem — Binary Search On Answer Reinforcement
- Remove K Digits — Greedy + Monotonic Stack
---

### Day 28

#### Linux Device Driver Project
- hello_driver.c — First Linux Kernel Module
- Kernel Module Build Workflow
- printk() Logging
- module_init() / module_exit()
- insmod / rmmod / lsmod / dmesg

#### Driver Development
- Linux Kernel Module Lifecycle
- Kernel Logging Basics
- Out-of-Tree Module Compilation

#### Bit Manipulation
- Maximum XOR Of Prefix And Suffix — Prefix XOR + Binary Trie
- Count Pairs With XOR In Range [L, R] — Binary Trie Counting

#### DSA
- Minimize Maximum Distance Between Gas Stations — Binary Search On Answer
- Maximum Of Minimum For Every Window Size — Advanced Monotonic Stack
---

### Day 29

#### Linux Device Driver Project
- Character Device Registration
- alloc_chrdev_region()
- cdev_init()
- cdev_add()
- struct file_operations
- open() / release()
- Major and Minor Device Numbers

#### Driver Development
- Character Device Lifecycle
- Device Number Allocation
- VFS to Driver Dispatch Path
- Manual Device Node Creation (mknod)

#### Bit Manipulation
- Maximum XOR Of Two Non-Overlapping Subarrays — Prefix XOR + Binary Trie
- Count Triplets With XOR In Range [L, R] — Advanced Trie Counting

#### DSA
- Capacity To Ship Packages Within D Days (Revision)
- Largest Rectangle In Histogram (Revision)
---

### Day 30

#### Linux Device Driver Project
- Implemented read() and write() operations
- copy_to_user() and copy_from_user()
- Character Device Data Transfer
- Automatic Device Node Creation
- class_create()
- device_create()

#### Driver Development
- User Space ↔ Kernel Space Communication
- Character Device Buffer Management
- Device File Lifecycle

#### Bit Manipulation
- Count Subarrays With XOR = K (Reimplemented)
- Prefix XOR + HashMap Reinforcement

#### DSA
- Search In 2D Matrix
- Sum Of Subarray Minimums (Contribution Technique Revision)
---

### Day 31

#### Linux Device Driver Project
- Implemented ioctl() Support
- SET_VALUE / GET_VALUE / CLEAR_BUFFER Commands
- unlocked_ioctl Interface
- User-Space IOCTL Test Program

#### Driver Development
- IOCTL Based User ↔ Kernel Communication
- Driver Command Interfaces
- Device State Management

#### Bit Manipulation
- Count Subarrays With Equal 0s And 1s
- Prefix State + HashMap Reinforcement

#### DSA
- Find K Closest Elements
- Asteroid Collision
---

### Day 32

#### Linux Device Driver Project
- Driver Synchronization Using Mutex
- Blocking read() with Wait Queues
- wait_event_interruptible()
- wake_up_interruptible()

#### Driver Development
- Concurrent Character Driver
- Driver State Protection
- Blocking User-Space Communication

#### Bit Manipulation
- Count Subarrays With Sum Divisible By K
- Maximum XOR With Element Less Than M (Offline Queries + Binary Trie)

#### DSA
- Median Of Two Sorted Arrays (Editorial Study)
- Car Fleet (Editorial Study)
---

### Day 33

#### Linux Device Driver Project
- Added poll() Support
- poll_wait()
- POLLIN / POLLRDNORM Event Handling
- User-Space poll() Test Program

#### Driver Development
- Event-Driven Character Driver
- poll() / select() Integration
- Wait Queue Based Event Notification

#### Bit Manipulation
- Maximum XOR Of Strong Pair
- Wonderful Substrings (Bitmask State + Prefix Frequency)

#### DSA
- Search Suggestions System (Editorial Study)
- Task Scheduler (Editorial Study)
---

### Day 34

#### Linux Device Driver Project
- UART User-Space Terminal
- termios Configuration
- Baud Rate Configuration
- UART Loopback Communication
- Serial Port Programming

#### Driver Development
- Linux TTY Subsystem (Introduction)
- User-Space UART Communication
- UART Configuration using termios

#### Bit Manipulation
- Count Excellent Pairs (Popcount-Based Counting)
- Maximum AND Pair (Greedy Bit Construction)

#### DSA
- Merge Intervals (Revision)
- Meeting Rooms II (Priority Queue / Heap)
---

### Day 35

#### Linux Device Driver Project
- Circular Buffer Implementation
- Driver Statistics Collection
- GET_STATS ioctl Extension
- Driver Statistics Test Program

#### Driver Development
- Circular Buffer Design
- Driver Observability
- Buffer Overflow Handling Policy
- Multi-Operation Driver Validation

#### Bit Manipulation
- Count Pairs With Sum As Power Of Two
- Maximum Product Of Word Lengths (Bitmask Representation)

#### DSA
- Top K Frequent Elements (Priority Queue + STL)
- Insert Interval

#### C++ STL Reinforcement
- sort() and Custom Comparators
- priority_queue
- lower_bound() / upper_bound()
---

### Day 36

#### Linux Device Driver Project
- Dynamic Circular Buffer using kmalloc()/kfree()
- Runtime Buffer Resizing
- SET_BUFFER_SIZE ioctl
- RESET_DRIVER ioctl
- Driver Reset Validation Program

#### Driver Development
- Dynamic Kernel Memory Management
- Runtime Driver Reconfiguration
- Safe Buffer Migration During Resize

#### Bit Manipulation
- Shortest Subarray With OR At Least K
- Smallest Subarrays With Maximum Bitwise OR (Editorial Study)

#### DSA
- Merge K Sorted Lists (Priority Queue + Custom Comparator)
- Kth Largest Element In An Array
---



## Format to Follow

Problem Name — Subtopic

Example:
- Circular Buffer — Buffers / Arrays
- Producer Consumer — Threads / Synchronization
- Mini Grep — File IO / Linux
- Reverse Bits — Bit Manipulation
- Two Sum — Hashing