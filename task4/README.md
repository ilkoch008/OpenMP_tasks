## Task4
### Task
Create a parallel program that multiplies matrices whose values are given by random numbers.

* Adapt the program for multiplying large matrices (> 1000x1000). Use dynamic load balancing methods, analyze efficiency.

### Solution
Processor: Intel Core i5 7300HQ 2.5 GHz 4 cores

Matrix has size 1500x1500 (might be changed).

Let's consider all implementations of multiplication separately:
```c
void matrixMult_def(double ** matrixA, double ** matrixB, double ** matrixC, int size);
```
-- sequential computation
```c
void matrixMult_stat_str(double ** matrixA, double ** matrixB, double ** matrixC, int size);
```
-- static load balancing with rows
```c
void matrixMult_dyn_str(double ** matrixA, double ** matrixB, double ** matrixC, int size);
```
-- dynamic load balancing with rows
```c
void matrixMult_guided_str(double ** matrixA, double ** matrixB, double ** matrixC, int size);
```
-- guided load balancing with rows
```c
void matrixMult_static_all(double ** matrixA, double ** matrixB, double ** matrixC, int size);
```
-- static load balancing with separate elements.
```c
void matrixMult_dyn_all(double ** matrixA, double ** matrixB, double ** matrixC, int size);
```
-- dynamic load balancing with separate elements.
```c
void matrixMult_guided_all(double ** matrixA, double ** matrixB, double ** matrixC, int size);
```
-- guided load balancing with separate elements.

Here you can see the results of execution:

![](https://github.com/ilkoch008/OpenMP_tasks/raw/master/task4/images/exec_time.png)


![](https://github.com/ilkoch008/OpenMP_tasks/raw/master/task4/images/speed-up.png)

Speed-up for dynamic load balancing may be increased with increasing of minimal block.
For example, with minimal block = 1000 time of execution on 4 threads equals 11.6 seconds.

### Bonus

Let's try the same but with *-Ofast* flag of compilation.


![](https://github.com/ilkoch008/OpenMP_tasks/raw/master/task4/images/exec_time_O.png)


![](https://github.com/ilkoch008/OpenMP_tasks/raw/master/task4/images/speed-up_O.png)

It can be pointed out that speed-up has decreased.

In general all computations lasted three times less.

To be honest, I expected that speed-up in comparison with no optimization mode will be less.
