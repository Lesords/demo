all: src/main.cpp
	g++ -o main src/main.cpp -ldl

lib: src/func.cpp
	g++ -o libFunc.so src/func.cpp \
		-shared -fPIC

start:
	./main

auto: lib all start

clean:
	rm libFunc.so
	rm main

.PHONY: lib start auto clean
