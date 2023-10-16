# Results for Assignment 02

## Improvement Iterations

Here's a table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the _wall-clock time_ for a program run.

| Version | Time | Speedup | Changes |
| :-----: | ---- | :-----: | ------- |
| [01](lychrel.cpp.orig) | 17.494s | Base Time | Initial version - no changes |
| [02](lychrel_multi_threaded.cpp) | 15.940s | 1.0975 | Multi-Threaded to process chunks in parallel |
| [03](lychrel.cpp) | N/A | N/A | Attempted to run with thread pool with dynamic task distribution

## Analysis

### Initial Review

Was able to get the process multithreaded and running. Minimal increase in run time after testing the updated lychel.cpp.  
From there I tried to implement dynamic scheduling but for whatever reason the code will compile and execute but run indefinitely?  
Still working on coming up with a solution
