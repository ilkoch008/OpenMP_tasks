## Laboratory work

#### HW & SW

* Processor: Intel Core i5-7300HQ 2.50GHz (4-core)
* OS: Microsoft Windows [Version 10.0.18363.1198]
* MPI: MS-MPI v10.1.2

### Task 1

The task was to remake ```void compute_solo(double ** a)``` from ```main.c``` 
into parallel version.
```c
void compute_solo(double ** a) {
    int i, j;
    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
        }
    }
    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = sin(0.00001 * a[i][j]);
        }
    }
}
```
#### Functions summary

* ```void compute_cycle_master(double ** a, int world_size)``` - function for master-process.
It sends rows to slave processes to compute. Then it waits for result from any process.
After gathering the result it returns a new work to sender.

* ```void compute_first_cycle_slave(double * a_i)``` - function for slave processes. 
It gathers the row to compute, computes it (first cycle from ```void compute_solo(double ** a)```) and sends back. This continues until 
getting the message with ```TAG_STOP```.

* ```void compute_second_cycle_slave(double * a_i)``` - function for slave processes. 
It gathers the row to compute, computes it (second cycle from ```void compute_solo(double ** a)```) and sends back. This continues until 
getting the message with ```TAG_STOP```.

* ```void compute_two_cycles_slave(double * a_i)``` - function for slave processes. 
It does the same thing as previous two functions but in one cycle.

* ```void print_ff(FILE * ff, double ** a)``` - prints ```a``` into ```ff```.

* ```void compute_solo(double ** a)``` - does the computations on one process.

#### Results

Measurement table:

![]

Speedups graph:

![]

Here was only loop-independent dependencies. 
So we didn't think a lot about how to parallelize.
Let's move on to second task.

### Task 2

Here was another ```void compute_solo(double ** a)``` from ```2d.c```.
Here it is:

```c
void compute_solo(double **a) {
    int i, j;
    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
        }
    }
    for (i = 8; i < ISIZE; i++) {
        for (j = 0; j < JSIZE - 3; j++) {
            a[i][j] = sin(0.00001*a[i-8][j+3]);
        }
    }
}
```

Here we can see loop-carried dependency. Let's look at it closely and 
define distance vector and direction vector:

![]

So we can parallelize inner cycle with cashing necessary data. And also we can
parallelize outer cycle but only for 8 or less processes. For 3 slave processes 
it will be look like this:

![]

Each of the arrows represents a task for one processor.

#### Functions summary

```void compute_cycle_master(double ** a, int world_size)``` - the same as in previous task.

```void compute_sin_cycle_master(double ** a, int world_size)``` - function for master process.
Distributes tasks between processes.

```void compute_sin_cycle_master_lt(double ** a, int world_size)``` - the same as 
the previous one, but it transfers data less.

```void compute_first_cycle_slave(double * a_i)``` - the same as in Task 1.

```void compute_second_cycle_slave(double * a_i, double * a_i_8)``` - function for slave processes.
Reply part for ```void compute_sin_cycle_master_lt(double ** a, int world_size)```.

```void compute_second_cycle_slave_lt(double * a_i, double * a_i_8)``` - the same as previous,
but it transfers data less.

```void print_ff(FILE * ff, double ** a)``` - the same as in Task 1.

```void compute_solo(double ** a)``` - described above.

#### Results

Measurement table:

![]

Speedups graph:

![]

It can be noted that due to the complication of the data exchange structure 
and due to the lack of the ability to use all processors during the execution 
of the program, the acceleration rates decreased.

In theory, the best performance should be achieved with 9 processors.
