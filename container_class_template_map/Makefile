#	Makefile
all:
	# Test-1.cpp is the test-kec.cpp labelled
	g++ -std=c++11 -Wall -Wextra -pedantic Test-1.cpp Map.hpp -o test-1
	@echo "Compiled file test-1 successfully !"

	# Test-2.cpp is the test.cpp labelled
	g++ -std=c++11 -Wall -Wextra -pedantic Test-2.cpp Map.hpp -o test-2
	@echo "Compiled file test-2 successfully !"

	# minimal.cpp is the minimal.cpp labelled
	g++ -std=c++11 -Wall -Wextra -pedantic minimal.cpp Map.hpp -o minimal
	@echo "Compiled file minimal successfully !"

	# morseex.cpp is the morseex.cpp labelled
	g++ -std=c++11 -Wall -Wextra -pedantic morseex.cpp Map.hpp -o morseex
	@echo "Compiled file morseex successfully !"

	# performance.cpp is the test-scaling.cpp labelled
	g++ -std=c++11 -Wall -Wextra -pedantic -O performance.cpp Map.hpp -o performance
	@echo "Compiled file performance successfully !"

clean:
	rm test-1
	@echo "Executable file ./test-1 deleted successfully !"
	rm test-2
	@echo "Executable file ./test-2 deleted successfully !"
	rm minimal
	@echo "Executable file ./minimal deleted successfully !"
	rm morseex
	@echo "Executable file ./morseex deleted successfully !"
	rm performance
	@echo "Executable file ./performance deleted successfully !"