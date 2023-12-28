all: server.cpp client.cpp
	g++ -o server server.cpp
	g++ -o client client.cpp

start:
	./server &
	./client &

clean:
	rm ./server
	rm ./client

.PHONY: start clean
