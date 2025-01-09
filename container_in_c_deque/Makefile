all:
	g++ -g -std=c++11 -c -o test.o test.cpp -ldl -Wall -Wextra -pedantic
	@echo "Compiled file test.o successfully !"

	g++ -o test test.o -ldl
	@echo "Linked executable file ./test created successfully !"

clean:
	rm test
	rm test.o
	@echo "Executable file ./test deleted successfully !"