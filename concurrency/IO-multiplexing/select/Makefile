all: server.cpp client.cpp
	g++ -o server server.cpp
	g++ -o client client.cpp

start:
	./server &
	./client one &
	./client two &
	./client three &

clean:
	kill -9 `pidof server`
	rm ./server
	rm ./client

.PHONY: start clean
