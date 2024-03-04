all: main.cpp

main.cpp:
	@echo '#include <iostream>'                 >> main.cpp
	@echo 'int main() {'                        >> main.cpp
	@echo '    std::cout << "hello world\\n";'  >> main.cpp
	@echo '    return 0;'                       >> main.cpp
	@echo '}'                                   >> main.cpp
	@echo 'main.cpp file generation is complete'

start: build
	cd build; cmake .. && mv ./compile_commands.json ..

build:
	mkdir build

clean:
	rm main.cpp compile_commands.json
	rm -rf build

.PHONY: all clean
