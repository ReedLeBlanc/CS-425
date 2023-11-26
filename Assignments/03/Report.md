# Results for Assignment 03

## Improvement Iterations

Here's a table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the entire process loading time.

| Version | Time | Speedup | Changes |
| :-----: | ---- | :-----: | ------- |
| [01](server(original).cpp) | 41.02s | Base Time | Initial version - no changes |
| [02](server02.cpp) | 43.49 | Slower(however allows for multiple connections) | Covered incoming connections into a thread |
| 03 | N/A | N/A | Attempted to run with thread pool with dynamic task distribution

## Analysis

### Initial Review



