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

Quasi-linearization method (we will repeat this with the resulting Y, then over and over again until we reach the required accuracy):

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

For example, for the first step of reverse part:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_24.png" width="">

Where Y[0] and Y[N] are given as border conditions.

The considered algorithm is less efficient in terms of sequential execution than the sweep method.
But it allows to run in parallel.

### Testing

First, let's test it on something easier. Just to be sure that all done in right way. For example:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_25.png" width="">

'''
h = 0.000019073486328125 = 20/2^20
N = 1048576 = 2^20
'''

For a = 1:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_26.png" width="">

For a = -1:

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_27.png" width="">

Seems like everything's alright. Let's move on to our task, that is 

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_3.png" width="">

'''
a = 100
h = 0.000019073486328125 = 20/2^20
N = 1048576 = 2^20
'''

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_28.png" width="">

And something is already wrong here. It is seen that the function is not smooth. Also the '''check_sum''' which is 

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_29.png" width="">

is pretty big: '''check_sum = 1.9907030992811863'''. For test examples this value was much less than one. Let's try smaller '''h''':

'''
N = 16777216 = 2^24
h = 0.0000011920928955078125 = 20/2^24
'''

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_30.png" width="">

And nothing had changed. Even '''check_sum = 1.9917383597402347'''.

Let's try big '''a''':

'''
a = 1000000
N = 16777216 = 2^24
h = 0.0000011920928955078125 = 20/2^24
'''

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_31.png" width="">

'''
check_sum = 198.3996323916111600
'''

'''check_sum''' had become even bigger. We can see that Y quickly approaches a one (trivial solution of equation).

### This is not the end

Small research with '''wolframalpha''' showed that for '''y(0) > 0.99704''' solution is nonperiodic and monotonic. But for '''y(0): 0 < y(0) < 0.99704''' solution is periodic. So we can try to find a solution for our problem using another border conditions.

Let's take '''y(-10) = y(10) = 0.997, y(x != -10, 10) = 0''' because for '''y > 0''' solution approaches to one. And other parameters:
'''
N = 4194304 = 2^22
h = 0.00000476837158203125 = 20/2^22
a = 1000000
'''

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_32.png" width="">

Finally, after the first step we can see the periodic structure. With huge '''check_sum = 418172.10879999999'''. After some iterations solution begins to approach to 1 (or to -1). Let's try some other values of '''a''':

'''
a = 500000 :
'''

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_33.png" width="">

'''
a = 100000 :
'''

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_34.png" width="">

'''
a = 10000 :
'''

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_35.png" width="">

'''
a = 1000 :
'''

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_36.png" width="">

'''
a = 100 :
'''

<img src="https://raw.githubusercontent.com/ilkoch008/OpenMP_tasks/master/task10/misc/Screenshot_37.png" width="">

The dependence of the period on the coefficient '''a''' is clearly seen.
