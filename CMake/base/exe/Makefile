all: main.cpp

main.cpp:
	@echo '#include <iostream>'                 >> main.cpp
	@echo 'int main() {'                        >> main.cpp
	@echo '    std::cout << "hello world\\n";'  >> main.cpp
	@echo '    return 0;'                       >> main.cpp
	@echo '}'                                   >> main.cpp
	@echo 'main.cpp file generation is complete'

start:
	mkdir build
	cd build; cmake .. && cmake --build . && ./main

clean:
	rm ./main.cpp
	rm -rf build

.PHONY: all clean
