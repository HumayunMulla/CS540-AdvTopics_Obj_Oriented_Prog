all:
	g++ -g -std=c++11 -c -o SharedPtr_test.o SharedPtr_test.cpp -ldl -Wall -Wextra -pedantic
	@echo "Compiled file SharedPtr_test.o successfully !"

	g++ -o test SharedPtr_test.o -pthread -Wl,--no-as-needed -ldl
	@echo "Linked executable file ./test created successfully !"

clean:
	rm test
	rm SharedPtr_test.o
	@echo "Executable file ./test deleted successfully !"