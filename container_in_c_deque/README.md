# Assignment-1 - Container in C 
CS 440/540 Fall 2020: **Assignment-1** [*Macro to implement a 'template' for a double-ended queue container*] 

The topic of the assignment is how to do containers in C. This will give you some understanding of what goes in behind-the-scenes in C++, and also serve as a good review of C. A secondary goal of this assignment is to give you experience in a form of test-driven development. I do not tell you exactly what to write, but rather I give you a piece of code (the test) that you must conform to. The assignment is not to be completed in strict C, but rather more like C++ without classes. You may not use any C++ classes, inheritance, templates, member functions, virtual member functions, dynamic_cast, etc. Also do not use any of the standard C++ containers such as std::vector or std::list. You will need to use C++ references. You must compile with g++, not gcc.You do not need to handle any error conditions not explicitly specified. For example, you may assume that the iterator returned by end() is never incremented. If the user does increment this, then this will cause undefined behavior.
[Read More](http://www.cs.binghamton.edu/~kchiu/cs540/prog/1/)
<br /><br />
The development of the program was done in two phases. Firstly, phase one contained developing the program using structures as a normal C++ program without classes and in phase two the code was converted into a MACO.
<br />
*Please note that certain aspects(code, functions,etc.) were modified and updated during the transition from phase one to phase two of the Macro program translation*


## Compile
```bash
make
# g++ -g -std=c++11 -c -o test.o test.cpp -ldl -Wall -Wextra -pedantic
# Compiled file test.o successfully !
#
# g++ -o test test.o -ldl
# Linked executable file ./test created successfully !

```

## Execution
To demonstrate the execution of the requirement of the assignment please use the following command. <br />
```bash
./test 
# program executes printing the result on screen

time ./time
# program executes printing the result on screen and also prints the time taken
# real    0m2.400s
# user    0m2.226s
# sys     0m0.120s
# *Please Note: this is my system time, actual result may slightly vary.*
```
## Post Execution
This will clean the files generated at compile time.
```bash
make clean
# rm test
# rm test.o
# Executable file ./test deleted successfully !
```



## References
The code has been developed taking inspiration from the following sources - <br />
1. Deque - Container operations- https://en.cppreference.com/w/cpp/container/deque
2. Memcpy - https://man7.org/linux/man-pages/man3/memcpy.3.html
3. Memmove - https://man7.org/linux/man-pages/man3/memmove.3.html
4. Memmove Usage reason - https://vgable.com/blog/2008/05/24/memcopy-memmove-and-speed-over-safety/
5. Sorting() This function has been inspired from https://github.com/rukumar333/cs440/tree/master/assignments/Assignment_1
6. QuickSort Usage reason - https://medium.com/human-in-a-machine-world/quicksort-the-best-sorting-algorithm-6ab461b5a9d0
7. QuickSort - http://www.cplusplus.com/reference/cstdlib/qsort/
8. MACRO implementation inspired from - http://www.cs.binghamton.edu/~kchiu/cs540/prog/1/example.cpp
9. Multiline MACRO inspiration - https://www.gnu.org/software/emacs/manual/html_node/ccmode/Multiline-Macro-Symbols.html
10. Include Guards - https://en.wikipedia.org/wiki/Include_guard
11. Certain aspects of the proram are also inspired from the testing code give, i.e. test.cpp - http://www.cs.binghamton.edu/~kchiu/cs540/prog/1/solution/test.cpp