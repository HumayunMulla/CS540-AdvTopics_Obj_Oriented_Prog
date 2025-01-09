# Assignment-3 - Shared Pointer
CS 440/540 Fall 2020: **Assignment-3** [*Implement a non-intrusive, thread-safe, exception-safe, reference-counting smart pointer named cs540::SharedPtr*] 

All classes should be in the cs540 namespace. Your code must work with test classes that are not in the cs540 namespace, however. Your code should not have any memory errors or leaks as reported by valgrind. Your code should compile and run on the remote.cs.binghamton.edu cluster. Your code must not have any hard-coded, arbitrary limits or assumptions about maximum sizes, etc. Your code should compile without warning with -Wall -Wextra -pedantic. Special exemptions to this may be requested in advance. [Read More](http://www.cs.binghamton.edu/~kchiu/cs540/prog/3/)
<br /><br />
I developed the program following the test case given [Shared Pointer Test](http://www.cs.binghamton.edu/~kchiu/cs540/prog/archive/SharedPtr/SharedPtr_test.cpp). 

# Implementation
The program was developed in multiple parts based on the test case given and also by understanding the working of [std::shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)

## Compile
```bash
make
# g++ -g -std=c++11 -c -o SharedPtr_test.o SharedPtr_test.cpp -ldl -Wall -Wextra -pedantic
# Compiled file SharedPtr_test.o successfully !
# g++ -o test SharedPtr_test.o -pthread -Wl,--no-as-needed -ldl
# Linked executable file ./test created successfully !

```
## Execution
To demonstrate the execution of the requirement of the assignment please use the following command. <br />
```bash
./test 
# program executes printing the result on screen

time ./test
# program executes printing the result on screen and also prints the time taken
# real    0m14.241s
# user    0m41.577s
# sys     0m10.154s
# *Please Note: this is my system time, actual result may slightly vary.*
```
## Post Execution
This will clean the files generated at compile time.
```bash
make clean
# rm test
# rm SharedPtr_test.o
# Executable file ./test deleted successfully !
```

## References
The code has been developed taking inspiration from the following sources - <br />
1. Shared Pointer - Member Functions - https://en.cppreference.com/w/cpp/memory/shared_ptr
2. Registering(this) to an observer - https://stackoverflow.com/questions/56683430/shared-pointer-using-this-registering-to-an-observer
3. Writing your shared_ptr - https://medium.com/analytics-vidhya/c-shared-ptr-and-how-to-write-your-own-d0d385c118ad
4. Using Default Arguments - https://codereview.stackexchange.com/questions/166395/custom-stdshared-ptrt-implementation
5. Solving errors with const has been inspired from https://github.com/AvocadosConstant/university-work/tree/master/courses/cs440/sharedptr
6. Partial Type Erasure - https://stackoverflow.com/questions/20896618/a-simple-implementation-of-smart-pointer-class
7. Understanding shared_ptr logic - https://docs.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-shared-ptr-instances?view=msvc-160
8. Mutex - https://en.cppreference.com/w/cpp/thread/mutex
9. Working with pthreads - https://man7.org/linux/man-pages/man7/pthreads.7.html
10. Include Guards - https://en.wikipedia.org/wiki/Include_guard
11. Certain aspects of the proram are also inspired from the testing code give, i.e. test.cpp - http://www.cs.binghamton.edu/~kchiu/cs540/prog/archive/SharedPtr/SharedPtr_test.cpp