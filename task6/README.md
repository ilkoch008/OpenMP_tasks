## Task6
### Task

Write a parallel program that calculates the number of primes from 1 to N.
-- N is given by the startup argument

-- Solve the problem without using simple enumeration, i.e. apply optimized search methods (with justification in the text of the program or comments to the task)

### Solution 

Let us use the Least Prime Divisor Theorem of a composite number.
According to this theorem, the segment [0,*sqrt(N)*] contains the smallest prime divisor of the composite number *N*.
Therefore, first, using the sequential algorithm (sieve of Eratosthenes), 
we find the prime numbers in the segment [0,*sqrt(N)*], 
and then, using the parallel algorithm, 
we check the remaining numbers using the prime numbers found in the first part of the program.

#### Small remark
This is probably happening because of small number of executors, but in my tests sieve of Eratosthenes showed better efficiency.

### Functions and structs overview.

```c
struct number {
    int value;
    int is_prime;
} number;
```
-- allows you to label prime numbers
```c
struct starter_pack {
    int * prime_nums;
    int size;
} starterPack;
```
-- storage for prime numbers from a segment [0,*sqrt(N)*]
```c
struct starter_pack sieve_of_Eratosthenes(struct number * numbers, int size);
```
-- uses sieve of Eratosthenes and returns prime numbers from a segment *numbers*[0,*size*]
```c
int is_not_prime(int x, struct starter_pack pack);
```
-- checks a number *x* for divisibility using numbers from pack
