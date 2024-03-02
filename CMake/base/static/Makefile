all: src/main.cpp src/test.cpp include/test.h

src/main.cpp: src
	@echo '#include "include/test.h"'                >> src/main.cpp
	@echo 'int main() {'                             >> src/main.cpp
	@echo '    debug(666);'                          >> src/main.cpp
	@echo '    return 0;'                            >> src/main.cpp
	@echo '}'                                        >> src/main.cpp
	@echo 'src/main.cpp file generation is complete'

src/test.cpp: src
	@echo '#include "include/test.h"'                >> src/test.cpp
	@echo 'void debug(int a) {'                      >> src/test.cpp
	@echo '    std::cout << "val: " << a << "\\n";'  >> src/test.cpp
	@echo '}'                                        >> src/test.cpp
	@echo 'src/test.cpp file generation is complete'

include/test.h: include
	@echo '#ifndef TEST_H_'                          >> include/test.h
	@echo '#define TEST_H_'                          >> include/test.h
	@echo ''                                         >> include/test.h
	@echo '#include <iostream>'                      >> include/test.h
	@echo 'void debug(int a);'                       >> include/test.h
	@echo ''                                         >> include/test.h
	@echo '#endif'                                   >> include/test.h
	@echo 'include/test.h file generation is complete'

start: build
	@cd build; cmake .. && cmake --build . && ./main

src:
	@mkdir src

include:
	@mkdir include

build:
	@mkdir build

clean:
	rm -rf src include build

.PHONY: all clean
