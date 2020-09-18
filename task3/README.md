## Task3
### The task
An array of 100'000 elements is declared and initialized so that a[i] = i.

- Write a program that creates a new array, where the following values will be stored: b [i] = (a [i-1] * a [i] * a [i + 1]) / 3.0

* Modify the original array (without creating a new one). The values are written to the central element of the "window": a [i] = (a [i-1] * a [i] * a [i + 1]) / 3.0

### Solution
Here implemented second point of the task. The calculation was made according to a slightly modified formula:
```
a [i] = (a [i-2] * a [i-1] * a [i]) / 3.0
```
![](https://github.com/ilkoch008/OpenMP_tasks/blob/master/task3/steps.png?raw=true)

The steps shown in green are performed at the beginning of the execution (that is synchronized), 
so the red steps do not affect the correctness of the calculation of the second thread.

As a result, we get the same array as in the original formula, but shifted by 1 element to the right.
