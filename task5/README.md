## Task5
### Task

Create a parallel program that calculates the sum of a series (calculating the exponent).

The number of terms is set by the start argument

-- Calculation of a more complex series

### Solution 
Here I calculated pi number. Firstly, I calculated according this formula:

![](https://wikimedia.org/api/rest_v1/media/math/render/svg/80f5960de1f4ca7dee0c5850d656b08e647612ab)

But due to dividing by 4^k max number of terms is 32. It took some time to understand that fact. If you try to sum a longer series, the resulting amount will grow. 
So for this method sum_size=32 is optimal case.

After this fault I decided to calculate pi number according to next formula:

![](https://wikimedia.org/api/rest_v1/media/math/render/svg/1eb1e79d23f5bd7162177712dc1a088d649ece49)

This series converges much more slowly, which makes it possible to calculate a longer sum.

### Functions overview.

```c
long double long_sum(long int N);
```
-- first method I tried.
``` c
long double long_sum_it(long int k);
```
-- k-th term of the sum.
```c
long double Leibniz(long int N);
```
-- second method I tried.
```c
long double Leibniz_it(long int k);
```
-- k-th term of the sum.
```c
int comp(long double x, long double y);
```
-- comparator for qsort.
```c
long double pow_2(long int k);
```
-- fast raising of two to the k power.
```c
long double m_sum(const long double * x, int size);
```
-- getting the final result.
