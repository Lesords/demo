all: main.cpp
	g++ -o main main.cpp -D_FILE_OFFSET_BITS=64

start:
	@echo "hello world" >> example.txt
	./main

clean:
	rm ./main
	rm ./example.txt

.PHONY: start clean
