all: main.cpp
	g++ -o main main.cpp -lrt

start:
	echo "hello world" > test.txt
	./main

clean:
	rm ./test.txt
	rm ./main

.PHONY: start clean
