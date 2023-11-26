# Results for Assignment 03

## Improvement Iterations

Here's a table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the entire process loading time.

| Version | Time | Speedup | Changes |
| :-----: | ---- | :-----: | ------- |
| [01](server(original).cpp) | 41.02s | Base Time | Initial version - no changes |
| [02](server(threaded).cpp) | N/A | N/A | Attempted to increase performance by running portion of code in separate thread
| [03](server02.cpp) | 43.49 | Slower(however allows for multiple connections) | Allows for threaded connection so multiple connections will be faster

## Analysis


### Initial Review



