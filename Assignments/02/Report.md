# Results for Assignment 02

## Improvement Iterations

Here's a table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the _wall-clock time_ for a program run.

| Version | Time | Speedup | Memory (KB) | Changes |
| :-----: | ---- | :-----: | :------: | ------- |
| [01](01.cpp) | 10.08s | &mdash; | 1041332 | Initial version - no changes |
| 02 | 3.54s | 2.85x | 1041332 | Compiled with -O1 for basic optimization |
| 03 | 2.31s | 4.36x | 1041316 | Compiled with -O3 for most aggressive optimization

## Profiling Analysis

### Initial Review

By simply updating the compiler optimization settings, I was able to eventually get a 4.36 increase in performance/process speed, along with a decrease in memory usage by 16KB. The quality of the output was not affected or sacrificed as the resulitng smallest triangle did not change.
