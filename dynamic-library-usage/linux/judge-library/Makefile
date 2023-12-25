all: src/main.cpp
	g++ -o main src/main.cpp -ldl

lib: src/func.cpp
	g++ -o libdebug.so src/func.cpp \
		-shared -fPIC

err: src/func.cpp
	g++ -o libdebug.so src/func.cpp \
		-shared -fPIC -DLIB_ERROR

start:
	./main

auto: lib all start

auto_err: err all start

clean:
	rm ./main
	rm ./libdebug.so

.PHONY: lib err start auto auto_err clean
