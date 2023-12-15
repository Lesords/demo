all: client server

client: client.cpp
	g++ -o client client.cpp

server: server.cpp
	g++ -o server server.cpp

start:
	./server &
	./client &

stop:
	kill -9 `pidof server`
	kill -9 `pidof client`

help:
	@echo "Usage:"
	@echo "    make all    - to compile client and server code"
	@echo "    make client - to compile client code"
	@echo "    make server - to compile server code"
	@echo "    make start  - to run server and client"
	@echo "    make stop   - to kill server and client"
	@echo "    make clean  - to clean all generated files"

clean:
	rm ./client ./server
	rm /tmp/fifo_twoway

.PHONY: start stop help clean
