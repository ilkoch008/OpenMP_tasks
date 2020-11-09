### Task 10

Here is considered boundary value problem of the form:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_1.png" width="">

It is necessary to solve this problem using quasi-linearization method, the Numerov approximation:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_2.png" width="">

And the method of cyclic reduction. 

The problem is: 

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_3.png" width="">

### Solution

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_4.png" width="">

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_5.png" width="">

Quasi-linearization method:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_6.png" width="">

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_7.png" width="">

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_8.png" width="">

Introduce the notation:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_9.png" width="">

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_10.png" width="">

The resulting system:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_11.png" width="">

In matrix form:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_12.png" width="">

Let's consider first three equations:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_13.png" width="">

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_14.png" width="">

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_15.png" width="">

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_16.png" width="">

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_17.png" width="">

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_18.png" width="">

Thus, we have eliminated variables with odd indices:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_19.png" width="">

In general:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_20.png" width="">

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_21.png" width="">

After the introduction of the appropriate designations:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_22.png" width="">

From here, we can go reverse:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_23.png" width="">

For example, for the last step of forward part:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_24.png" width="">

Where Y[0] and Y[N] are given as border conditions.

The considered algorithm is less efficient in terms of sequential execution than the sweep method.
But it allows to run in parallel.

### Testing
