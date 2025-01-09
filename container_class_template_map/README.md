# CS 540 Programming Assignment 2: Container
CS 440/540 Fall 2020: **Assignment-2** [*Implement a container class template named Map similar to the std::map class from the C++ Standard Library*] 

Implement a container class template named Map similar to the std::map class from the C++ Standard Library. Such containers implement key-value pairs, where key and value may be any types, including class types. (In the following, the value will be referred to as the mapped type or mapped object, and the term value will used to designate the entire pair. This is so as to be consistent with the terminology in the standard library.) Note that C++ terminology uses object even for fundamental types such as ints. Your Map class template will have two type parameters, Key_T and Mapped_T, denoting the key type and the mapped type, respectively. As in std::map, the mapped type values themselves must be in your map, not pointers to the values.
[Read More](http://www.cs.binghamton.edu/~kchiu/cs540/prog/2/)
<br /><br />
The development of the program was done in multiple parts referencing the requirements given in the assignment and the functionality of std::maps class from the C++ Standard Library.
<br /><br />
Please Note that I have been able to successfully execute all the following test cases given <br />[ [Test 1](http://www.cs.binghamton.edu/~kchiu/cs540/prog/2/tests/test-kec.cpp), [Test 2](http://www.cs.binghamton.edu/~kchiu/cs540/prog/2/tests/test.cpp), [Minimal](http://www.cs.binghamton.edu/~kchiu/cs540/prog/2/tests/minimal.cpp), [Morse Code Example](http://www.cs.binghamton.edu/~kchiu/cs540/prog/2/tests/morseex.cpp), [Performance Test](http://www.cs.binghamton.edu/~kchiu/cs540/prog/2/tests/test-scaling.cpp) ]

## Compile
```bash
make
# Test-1.cpp is the test-kec.cpp labelled
g++ -std=c++11 -Wall -Wextra -pedantic Test-1.cpp Map.hpp -o test-1
Compiled file test-1 successfully !
# Test-2.cpp is the test.cpp labelled
g++ -std=c++11 -Wall -Wextra -pedantic Test-2.cpp Map.hpp -o test-2
Compiled file test-2 successfully !
# minimal.cpp is the minimal.cpp labelled
g++ -std=c++11 -Wall -Wextra -pedantic minimal.cpp Map.hpp -o minimal
Compiled file minimal successfully !
# morseex.cpp is the morseex.cpp labelled
g++ -std=c++11 -Wall -Wextra -pedantic morseex.cpp Map.hpp -o morseex
Compiled file morseex successfully !
# performance.cpp is the test-scaling.cpp labelled
g++ -std=c++11 -Wall -Wextra -pedantic -O performance.cpp Map.hpp -o performance
Compiled file performance successfully !
```

## Execution
To demonstrate the execution of the requirement of the assignment please use the following command. <br />
```bash

./test-1
# program executes printing the result of of Test-1.cpp, i.e. test-kec.cpp on screen

./test-2
# program executes printing the result of Test-3.cpp, i.e. test.cpp on screen

./minimal
# program executes printing the result of minimal.cpp on screen

./morseex
# program executes printing the result of morseex.cpp on screen

time ./performance
# program executes printing the result of performance.cpp, i.e. test-scaling.cpp on screen and 
# also prints the time taken
# real    0m44.598s
# user    0m43.736s
# sys     0m0.850s
# *Please Note: this is my system time, actual result may slightly vary.*
```

## Post Execution
This will clean the files generated at compile time.
```bash
make clean

rm test-1
Executable file ./test-1 deleted successfully !
rm test-2
Executable file ./test-2 deleted successfully !
rm minimal
Executable file ./minimal deleted successfully !
rm morseex
Executable file ./morseex deleted successfully !
rm performance
Executable file ./performance deleted successfully !
```

## References
The code has been developed taking inspiration from the following sources - <br />

1. Implement Skip List - https://www.sanfoundry.com/cpp-program-implement-skip-list/
2. How to write Template - https://en.cppreference.com/w/cpp/language/type_alias
3. Use of Function Templates - https://www.cplusplus.com/doc/oldtutorial/templates/
4. Naming Conventions Standard - https://stackoverflow.com/questions/3136594/naming-convention-underscore-in-c-and-c-sharp-variables#:~:text=In%20general%2C%20you%20are%20not,t%20frown%20on%20leading%20underscores
5. Map Class Member functions have been inspired from - https://github.com/andrewmwilliams/cs440map
6. Purpose of Random Number Generator - https://cseweb.ucsd.edu/classes/fa15/cse100-a/lectures-c/Lec07_ann_DS.pdf
7. RAND_MAX Value purpose - http://www.cplusplus.com/reference/cstdlib/RAND_MAX/
8. typdef specifier use- https://en.cppreference.com/w/cpp/language/typedef
9. Exception Handling in sophisticated way - https://en.cppreference.com/w/cpp/language/try_catch
10. Optimizations usage - https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
11. Include Guards - https://en.wikipedia.org/wiki/Include_guard
