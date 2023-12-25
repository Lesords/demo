all: src/main.cpp
	g++ -o main src/main.cpp \
		-L. -lFunc -Wl,-rpath,.

lib: src/func.cpp
	g++ -o libFunc.so src/func.cpp \
		-shared -fPIC

start:
	./main

auto: lib all start

clean:
	rm libFunc.so
	rm main

.PHONY: lib start clean auto
