### Task 6

Create a parallel program that solves the heat equation for the steady state of a rectangular region for a given accuracy 𝜀.

- Area size: 𝑀 ∗ 𝑁
- Initial conditions: see attached document
- Keep track of program execution time on threads and total
- Possibility of outputting changes in temperature distribution at each iteration

### Solution

My solution diligently pretends that it computes everything in mathematically correct way. But this is not true.

The program calculates the average value for each cell by walking through the array in different directions. Тeighbors are taken to calculate the average.

When you start the program you will see something like this:

![](https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task7/example.bmp)

All sides are kept hot except for the top.

#### Launch parameters 

```
task7.exe fpd 200 res 1000 500 tnum 4
```
```fpd``` sets number of frames that are will be calculated between drawing pictures.

```res``` sets resolution

```tnum``` sets number of threads to calculate the task
