# Embedded / Systems Placement Preparation Roadmap
## Duration: 2 Months
## Target Roles:
- Embedded Systems
- Firmware
- Systems Programming
- Mixed Hardware-Software Roles

---

# PREPARATION PHILOSOPHY

This roadmap is:
- implementation-heavy
- Linux-focused
- systems-oriented
- debugging-oriented
- low on passive theory
- focused on engineering depth

Main goals:
- strong C programming
- Linux fluency
- systems programming confidence
- debugging maturity
- placement-level DSA
- strong interview discussions

---

# DAILY TIME TARGET

Average:
- 3-4 hrs/day

Structure:
- 1.5 hrs systems/Linux/embedded
- 1 hr DSA + bit manipulation
- 1–1.5 hrs implementation/debugging/project work

Daily task structure:
- 3 systems/Linux questions
- 2 bit-manipulation questions
- 2 DSA questions (C++ + STL)

Theory revision is self-directed

---

# MAIN TRACKS

There are 6 parallel tracks:

1. C + Systems Programming
2. Linux Practical Skills
3. OS + Embedded Concepts
4. Bit Manipulation + Logic Building
5. Placement DSA
6. Systems Project

---

# WEEK 1 — Memory, Pointers, Linux, Debugging

## Goals
- Become extremely comfortable with memory and pointers
- Build Linux workflow confidence
- Improve implementation fluency
- Start debugging seriously

---

# C / Systems Topics

## Study + Implement
- memory layout
- stack vs heap
- pointer arithmetic
- arrays vs pointers
- dynamic memory
- structs/unions
- linked list internals
- file IO basics
- Makefiles

---

# Linux Topics

## Practice Daily
- gcc
- gdb
- valgrind
- Makefiles
- grep/find/xargs
- permissions
- ps/top/kill
- shell scripting
- vim basics

---

# Coding Implementations

## Data Structures
Implement from scratch in C:
- dynamic vector
- singly linked list
- doubly linked list
- stack
- queue
- circular buffer

---

# String/Memory Functions

Implement:
- memcpy
- memmove
- strtok
- memset
- calloc
- realloc simulation

---

# Linux/System Utilities

Build:
- mini grep
- hex dump utility
- file copy utility
- log parser

---

# Bit Manipulation

## Focus Area
Bit-manipulation practice should now be divided into:

1. Interview-style logic problems
2. Embedded/systems-oriented bit reasoning

Focus should be on:
- XOR reasoning
- state transitions
- bitwise optimization
- packet/register parsing
- encoding/decoding
- greedy bit logic
- masking-based algorithms

Avoid spending too much time on:
- repetitive set/reset/toggle-only exercises

---

## Topics
- XOR tricks
- bit masks
- field extraction
- bit packing/unpacking
- parity
- power-of-2 logic
- state compression
- binary transformations
- bitwise arithmetic
- bitmap logic

## Practice Problems
- reverse bits
- next power of 2
- missing number using XOR
- two non-repeating numbers
- packet parsing
- bitmap implementation
- subset masks
- maximum XOR pair
- bitwise addition
- Gray code
- parity calculation
- protocol/register decoding

---

# Debugging Focus

Use:
- gdb
- valgrind

Debug:
- segmentation faults
- dangling pointers
- double free
- memory leaks

---

# WEEK 2 — Processes, Threads, Synchronization

## Goals
- Understand Linux execution model
- Build concurrency intuition
- Learn synchronization practically

---

# Systems Topics

Study + Implement:
- fork()
- exec()
- wait()
- pipes
- signals
- pthreads
- mutexes
- semaphores
- race conditions
- deadlocks

---

# Implementations

Build:
- process tree creator
- parent-child IPC
- multithreaded counter
- producer-consumer
- thread-safe queue
- command executor
- parallel file processor

---

# Debugging Focus

Debug:
- race conditions
- deadlocks
- thread synchronization bugs

Use:
- gdb
- valgrind
- printf tracing

---

# Bit Manipulation

## Advanced Problems
- single number II/III
- bitwise addition without +
- subset generation using bits
- parity calculation
- maximum XOR
- XOR partitioning
- bitmask-based logic
- bitwise state encoding

---

# DSA Focus

Priority is understanding patterns incrementally.

Phase 1:
- arrays
- strings
- vectors
- hash maps
- hash sets
- stacks
- queues
- linked lists
- binary search
- two pointers

Phase 2:
- sliding window
- interval problems
- heap problems
- DFS/BFS
- recursion/backtracking basics

Phase 3:
- graph patterns
- monotonic deque
- greedy reasoning
- design-style interview questions

Rule:
Do not move aggressively to Phase 2 or Phase 3 until Phase 1 patterns feel comfortable.

Do NOT optimize for:
- hardcore competitive programming
- advanced DP-heavy problems
- obscure STL/template tricks

# DSA LEARNING PHILOSOPHY

Goal:
- Build pattern recognition gradually.
- Learn interview problem families.
- Use C++ STL comfortably.

Important:
- It is acceptable to study editorials initially.
- Pattern recognition is more important than independent solving in the beginning.
- Independence will naturally improve after repeated exposure.

Current Focus:
- Simpler questions solved independently.
- Medium questions solved with hints/editorials.
- Understanding patterns over memorizing solutions.

Remember:
The objective is not competitive programming.
The objective is becoming comfortable with common placement interview patterns.

Current DSA Progress:

Phase 1 is still the primary focus.

Emphasis:
- repetition over difficulty
- pattern recognition over speed
- STL familiarity over implementation from scratch

Preferred problem categories:
- hashing
- arrays
- strings
- stacks
- queues
- binary search
- two pointers

Current Progress:
- Shared-memory IPC has been introduced and should receive additional practice.
- Binary-search variants are becoming more comfortable but still require repetition.
- Shell project now covers most core interview-worthy shell features.
- Hashing-based DSA problems are becoming comfortable.
- STL usage is no longer a major bottleneck.
- Edge-case handling and defensive programming should be emphasized in future exercises.
- Two-pointer patterns are becoming increasingly comfortable.
- Bit manipulation should now focus on logic and state-encoding problems rather than basic XOR exercises.

Bit Manipulation Progress:

Foundational bit-manipulation patterns are becoming comfortable:
- XOR cancellation
- XOR partitioning
- power-of-two reasoning
- bit masking
- register extraction
- bit scanning
- bitwise arithmetic

Future bit-manipulation practice should emphasize:
- advanced logic problems
- embedded-oriented register/protocol problems
- state encoding problems
- bitset-based algorithms
- tricky interview questions

Avoid repeating foundational XOR-only exercises unless used for revision.

Progress to harder graph/heap/advanced problems only after these patterns feel natural.

---

# WEEK 3 — Advanced Linux Systems Programming + IPC + Debugging

## Goals
- Become comfortable with real Linux APIs
- Improve systems design thinking

---

# Topics
- Advanced Linux Systems Programming
- IPC (Pipes, Shared Memory, Message Queues)
- File Descriptor Management
- Process and Thread Debugging
- Resource Lifecycle Management
- Continued DSA Foundation Building
- Advanced Bit Manipulation Logic

---

# Implementations

Build:
- multi-client chat server
- async logger
- terminal chat application

---

# Linux Topics

Learn:
- strace
- lsof
- process inspection

---

# Bit Manipulation

## Embedded-Oriented Bit Logic
Practice:
- register field extraction
- status register parsing
- protocol packet parsing
- CRC basics
- bit packing/unpacking
- packet decoding
- state-machine encoding

---

# DSA

Topics:
- stacks
- queues
- trees basics
- binary search
- sliding window

---

# WEEK 4 — OS + Embedded Systems + Interview-Oriented DSA

## Goals
- Strengthen interview discussions
- Build systems intuition
- Connect embedded + OS concepts

---

# OS Topics

Study:
- scheduling
- virtual memory
- paging
- TLB
- context switching
- synchronization internals
- IPC
- cache concepts

---

# Embedded Topics

Study:
- interrupts
- DMA
- memory-mapped IO
- volatile
- cache coherency basics
- RTOS scheduling
- UART/SPI/I2C/CAN
- polling vs interrupts

---

# Implementations

Build:
- memory pool allocator
- simple scheduler simulation
- interrupt/event simulation
- protocol parser

---

# Debugging Focus

Practice:
- heap corruption debugging
- synchronization debugging
- race-condition analysis

---

# WEEK 5 — Placement DSA + Systems Coding

## Goals
- Become OA-capable
- Improve implementation speed
- Improve logic building

---

# DSA Topics

ONLY placement-relevant topics:
- arrays
- strings
- hashing
- sliding window
- binary search
- stacks/queues
- trees basics

NO hardcore competitive programming.

---

# Bit Manipulation

## Tricky Problems
Practice:
- maximum XOR pair
- bitmask DP basics
- subset masks
- missing/repeating numbers
- unique number problems
- Gray code
- power set generation
- packet/state encoding

---

# Systems Coding

Implement:
- LRU cache
- memory tracker
- command parser
- configuration parser

---

# WEEK 6 — Main Systems Project

# Build ONE Strong Project

Recommended options:

## Option 1 — Mini Shell
Features:
- command execution
- pipes
- redirection
- background jobs
- signal handling
- history

---

## Option 2 — Multi-threaded Logger
Features:
- thread-safe logging
- async writes
- configurable levels
- log rotation

---

## Option 3 — Multi-client Chat Server
Features:
- sockets
- multiple clients
- polling/select
- message broadcasting

---

# Project Requirements

Must include:
- Makefile
- README
- modular code
- debugging support
- clean architecture

---

# WEEK 7 — Interview Preparation Phase

## Goals
- Become interview comfortable
- Improve explanation ability
- Improve debugging confidence

---

# Practice Daily

## Coding
- timed coding
- implementation from scratch

## Interview Topics
- OS questions
- Linux questions
- embedded questions
- debugging scenarios

## Discussion Practice
Explain:
- race conditions
- mutexes
- virtual memory
- interrupts
- volatile
- synchronization

---

# Mock Discussions

Practice explaining:
- your project
- design decisions
- debugging process
- failures and fixes

---

# WEEK 8 — Final Revision + Polish

## Revise

### C
- pointers
- memory bugs
- undefined behavior
- function pointers

### Linux
- processes
- threads
- synchronization
- sockets
- debugging tools

### Embedded
- interrupts
- DMA
- protocols
- RTOS basics

### OS
- scheduling
- paging
- deadlocks
- synchronization

---

# Final Practice

- mock interviews
- debugging exercises
- timed implementation
- project walkthroughs

---

# IMPORTANT PRIORITY ORDER

Current preparation emphasis:

Primary Focus:
- C systems programming
- Linux practical skills
- debugging
- concurrency/synchronization
- OS and systems concepts
- bitwise logic
- interview-oriented DSA

Reduced Priority:
- advanced networking
- hardcore competitive programming
- advanced kernel internals
- excessive roadmap/theory hopping

---

# WHAT TO AVOID

Avoid spending too much time on:
- advanced C++
- competitive programming
- advanced kernel internals
- deep networking theory
- excessive tutorials
- roadmap hopping
- implementing every DSA structure manually repeatedly

Prioritize:
- systems thinking
- Linux fluency
- debugging
- concurrency
- interview-style logic problems

---

# THEORY REVISION POLICY

Theory revision is not scheduled daily.

Instead, theory should be revised:
- when a coding problem exposes a knowledge gap
- before interview preparation rounds
- during dedicated revision weeks
- when project work requires deeper understanding

Priority theory areas:
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

# FINAL TARGET

By placements, aim to become someone who can:
- write robust C code
- debug independently
- work comfortably in Linux
- understand concurrency
- solve placement-level coding questions
- explain systems concepts clearly
- discuss engineering tradeoffs confidently
- build small systems software independently

---

# DAILY QUESTION TRACKER

## Day 1

### C / Systems
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

### Linux
- Linux Directory Structure Creation — Terminal Basics
- GCC Compilation — Build Workflow
- Makefile Creation — Build Systems
- Shell Script Build Automation — Shell Scripting
- Process Monitoring — ps/top/kill
- File Search / Filtering — grep/find/xargs
- fork() Example — Processes
- pipe() Example — IPC / Pipes
- pthread Counter Example — Threads / Race Conditions

### Bit Manipulation
- Set/Clear/Toggle/Check nth Bit — Bit Operations
- Count Set Bits — Kernighan Algorithm
- Detect Power of 2 — Bit Logic
- Reverse Bits — Divide-and-Conquer Bit Manipulation
- Next Power of Two — Bit Reduction Logic
- Find Position of Set Bit — Bit Scanning
- Swap Odd/Even Bits — Bit Masks
- Integer Addition Without '+' — XOR + Carry Logic

### DSA
- None yet

---

## Day 2

### C / Systems
- Circular Buffer Upgrade — Robustness / Error Handling
- Dynamic Vector Upgrade — realloc / Heap Management
- file_copy Upgrade — Linux File IO / Robustness
- Producer Consumer — Threads / Synchronization
- Valid Parentheses — Stack Implementation
- Binary Search — Searching Algorithms

### Linux
- fork + execlp Example — Process Control
- wait() Usage — Process Synchronization
- Multiple Child Processes — Scheduling / Process Hierarchy
- command_logger.sh — Shell Scripting / Logging

### Bit Manipulation
- Bitfield Extraction — Register Parsing
- Bitmap Implementation — Bit Arrays
- Missing Number Using XOR — XOR Reduction Logic
- Two Non-Repeating Numbers — XOR Partitioning Logic

### DSA
- Valid Parentheses — Stack
- Binary Search — Binary Search

---

## Day 3

### C / Systems
- file_copy_stats.c — Advanced File IO / Statistics
- mini_wc.c — Low-Level File Processing
- file_permissions.c — Linux File APIs / stat/access
- Memory Pool Allocator — Custom Allocation
- my_calloc — Allocation Internals
- Reader Writer Problem — Synchronization
- Thread Pool — Worker Architecture
- Queue Using Two Stacks — Data Structure Design

### Linux
- File Descriptor Handling — Linux File IO
- access() and stat() Usage — Linux APIs
- search_logs.sh — Linux Search Utilities

### Bit Manipulation
- Skipped basic bit-manipulation exercises intentionally to focus more on logic-heavy/system-oriented problems

### DSA
- Longest Substring Without Repeating Characters — Sliding Window
- Queue Using Two Stacks — Stack/Queue Logic

---

## Day 4

### C / Systems
- Shared Memory Example — IPC / Shared Memory
- Shared Memory + Synchronization — Process Synchronization
- Signal Handling — UNIX Signals
- LRU Cache — Hashmap + Doubly Linked List

### Linux
- Shared Memory APIs — shmget/shmat/shmctl
- Signal Registration — signal()
- Process Communication — IPC

### Bit Manipulation
- Gray Code Generator — XOR State Transitions
- Maximum XOR Pair — Greedy Bitwise Logic

### DSA
- Merge Intervals — Interval Merging
- Floyd Cycle Detection — Fast/Slow Pointer
- LRU Cache — Design Problem

---

## Day 5

### C / Systems
- mini_shell.c — Process Execution / fork-exec-wait
- Deadlock Demonstration — Mutex Ordering / Concurrency
- Deadlock Fix — Lock Ordering Strategy

### Linux
- execvp() Usage — Command Execution
- Shell Loop Implementation — Process Control
- Process Synchronization — wait()

### Bit Manipulation
- Single Number II — Bitwise State Machine Logic

### DSA
- Top K Frequent Elements — Heap + Hashmap
- Sliding Window Maximum — Monotonic Deque

---
## Day 6

### C / Systems
- mini_shell Argument Parsing — Tokenization / execvp argv Handling
- mini_strace_logger.c — Syscall Logging / File Descriptor Awareness
- interrupt_handler.c — ISR Registration / Function Pointers

### Linux
- execvp argv Handling — Process Execution
- System Call Observation — open/read/write/close
- File Descriptor Awareness — Linux IO Internals

### Bit Manipulation
- Single Number III — XOR Partitioning Logic

### DSA
- Number of Islands — DFS / Grid Traversal
- K Closest Elements — Binary Search + Two Pointers

---

## Day 7

### C / Systems
- mini_shell_upgrade.c — Background Processes / Redirection / Process Lifecycle
- File Descriptor Redirection — dup2() / UNIX IO Model

### Linux
- Background Execution (&) — Foreground vs Background Processes
- Zombie Cleanup — waitpid(..., WNOHANG)
- Output Redirection — open() + dup2()
- Process Lifecycle Management — fork/exec/wait Integration

### Embedded / Concurrency
- Lock-Free Ring Buffer (Conceptual Revision) — Single Producer Single Consumer Design

### Bit Manipulation
- Maximum XOR Using Binary Trie — Greedy Bitwise Traversal
- Detect Opposite Signs — Sign-Bit Reasoning / XOR Logic

### DSA
- Course Schedule — Graph Cycle Detection / DFS
- Merge K Sorted Lists — Heap / Priority Queue

---
## Day 8

### C / Systems
- mini_shell_v3.c — Command History / Circular Buffer Style State Management
- fd_inspector.c — File Descriptors / /proc Filesystem Exploration

### Linux
- /proc/self/fd Exploration — Linux Process Introspection
- File Descriptor Lifecycle — open(), close(), opendir()
- Shell State Management — Command History Tracking

### Embedded / Concurrency
- UART Packet Parser (Skipped) — Already comfortable with basic packet parsing and field extraction concepts

### Bit Manipulation
- Find Element Appearing Odd Number of Times — XOR Cancellation Logic
- Count Total Set Bits from 1 to N — Kernighan Algorithm / Bit Counting Patterns

### DSA
- Contains Duplicate — Hash Set Pattern
- Valid Anagram — Frequency Counting / Hash Map Pattern

---

## Day 9

### C / Systems
- mini_shell_v4.c — Built-in Commands / Shell Architecture
- mini_logger.c — Modular Logging Utility / File Logging

### Linux
- Built-in Shell Commands — cd / pwd / exit / history
- Process Environment vs Child Process Execution
- Log File Creation and Management
- File Descriptor Based Logging

### Bit Manipulation
- Power Of Four Detection — Bit Pattern Recognition
- Rightmost Different Bit — XOR + Bit Extraction Logic

### DSA
- Two Sum — Hash Map Lookup Pattern
- Merge Sorted Array — Two Pointer Technique

---
## Day 10

### C / Systems
- mini_shell_v5.c — Pipes / Process Communication
- mini_diff.c — File Comparison Utility / File IO

### Linux
- pipe() System Call
- dup2() with Pipes
- Inter-Process Communication (IPC)
- Multi-Process Data Flow

### Bit Manipulation
- XOR Swap — XOR Properties
- Divide Without '/' — Bit Shifting / Binary Arithmetic

### DSA
- Valid Parentheses — STL Stack Pattern
- Best Time To Buy And Sell Stock — Running Minimum Pattern
---

## Day 11

### C / Systems
- mini_shell_v6.c — Background Job Tracking / Shell State Management
- mini_hexdump.c — Binary File Inspection Utility

### Linux
- Background Process Tracking
- waitpid(..., WNOHANG) for Job Monitoring
- Binary File Processing
- File Formatting and Inspection Utilities

### Bit Manipulation
- Count Trailing Zeros — Lowest Set Bit Logic
- Reverse 32-bit Integer — Hierarchical Bit Swapping

### DSA
- Remove Duplicates From Sorted Array — Two Pointer Pattern
- Valid Palindrome — String Processing + Two Pointers

---

## Day 12

### C / Systems
- mini_shell_v7.c — Command Execution Timing / Performance Measurement
- mini_tail.c — File Seeking / Reverse File Traversal

### Linux
- clock_gettime()
- Execution Time Measurement
- File Positioning (fseek/ftell)
- Linux Utility Development

### Bit Manipulation
- Next Power Of Two — Bit Propagation Technique
- Find Missing Number (Skipped — Previously Solved)

### DSA
- Majority Element — Hash Map Frequency Counting
- Intersection Of Two Arrays — Hash Set Pattern

---
## Day 13

### C / Systems
- mini_shell_v8.c — Conditional Execution (&&) / Exit Status Handling
- mini_wcl.c — Low-Level File Processing / Line Counting
- process_tree.c — Process Metadata Inspection via /proc

### Linux
- Process Exit Status (WIFEXITED / WEXITSTATUS)
- /proc/<pid>/status Exploration
- Low-Level File IO (open/read/close)
- Linux Process Introspection

### Bit Manipulation
- Count Bits For Every Number — Bit DP Pattern
- Single Number II — Bitwise State Machine Logic

### DSA
- Valid Sudoku — Hashing + Matrix Validation
- First and Last Occurrence — Binary Search Variant

---

## Day 14

### C / Systems
- mini_shell_v9.c — Logical OR (||) / Shell Command Chaining
- mini_cat.c — Low-Level File Display Utility
- fd_leak_demo.c — File Descriptor Lifecycle / Resource Leak Demonstration

### Linux
- Logical Command Chaining
- Resource Leak Detection
- /proc/self/fd Monitoring
- Low-Level File Reading and Writing

### Bit Manipulation
- Generate All Subsets Using Bitmasks — Bitmask Enumeration
- Find Two Missing Numbers — XOR Partitioning Logic

### DSA
- Queue Using STL — STL Queue Familiarity
- Find Peak Element — Binary Search Pattern

---

## Day 15

### C / Systems
- mini_shell_v10.c — Sequential Command Execution (;)
- mini_tee.c — Stream Duplication Utility

### Linux
- Sequential Command Parsing
- STDIN / STDOUT Stream Handling
- File Descriptor Duplication Concepts
- Utility-Style Program Development

### Bit Manipulation
- Binary Representation Palindrome Check
- Remainder Without Using *, /, %

### DSA
- Move Zeroes — Two Pointer Pattern
- Longest Common Prefix — String Comparison Pattern

---

## Day 16

### C / Systems
- mini_shell_v11.c — Quoted String Parsing / Shell Tokenization
- shared_counter.c — Shared Memory IPC / Parent-Child Communication

### Linux
- Shared Memory APIs (shmget/shmat/shmdt/shmctl)
- Parent-Child Shared State
- Shell Parsing Strategies
- Command Tokenization

### Bit Manipulation
- Binary Gap — Bit Scanning / State Tracking
- Modulo Bit Counting Logic (Single Number Variant)

### DSA
- Valid Anagram (Frequency Array Version) — Character Counting
- Search Insert Position — Binary Search Variant

---


# FORMAT TO FOLLOW

Problem Name — Subtopic

Example:
- Circular Buffer — Buffers / Arrays
- Producer Consumer — Threads / Synchronization
- Mini Grep — File IO / Linux
- Reverse Bits — Bit Manipulation
- Two Sum — Hashing