all:
	g++ -o main main.cpp

start:
	./main &
	@echo "hhh" >> /tmp/aa
	@cat /tmp/aa
	@chmod u+x /tmp/aa
	@rm /tmp/aa

stop:
	kill -9 `pidof ./main`

clean:
	rm ./main

.PHONY: start stop clean
