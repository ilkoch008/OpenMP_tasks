## Task 1
This program starts N threads, each one of them prints its own id.

Threads print their id numbers in reverse order. This is implemented with 

``` C
omp_set_lock (& lock)
```
Threads use check number to recognize which one of threads should print now. 
If check number equals to id of some thread then this thread locks other threads, prints it's id, reduses check number and unlocks other threads.
