### Task 8

Create a parallel program that implements the Quick Sort mechanism for a one-dimensional array.

- Array size: up to 10000 elements, value of elements: within the int32_t type
- Implement the ability to enter an array through a file
- Implement the ability to enter an array from the keyboard
* * Modify the original array without creating new ones (memory limit)

### Solution

#### sequential algorithm

taken from wikipedia and looks like 
```
 algorithm quicksort(A, low, high) is
    if low < high then
        p:= partition(A, low, high)
        quicksort(A, low, p - 1)
        quicksort(A, p + 1, high)
```

partition takes three values from the given section, the first, from the middle of the section and the last. Selects the average from these three values and moves it to the end of the segment (let's call it the reference). Then a cycle begins, which from the left end of the section searches for elements larger than the reference. If such is found, the second cycle begins, which from the right end searches for elements less than the reference one. When found, the found items are swapped. At some point, the cycles will converge on one element (on average, in the middle of the section). This element is interchanged with the reference element, which is at the end of the section. The location of the reference is returned.

#### parallel algorithm

the parallel algorithm is a modification of the sequential algorithm. First, the whole array is executed by one thread. Then the two resulting parts are executed by two threads. The resulting four parts are executed on four threads with a sequential algorithm.

#### Launch parameters 

```
task8.exe -i input.txt -o output.txt
```
```-i``` sets the name of input file.

```-o``` sets the outut file.

By default, input and output is done using the command line.
