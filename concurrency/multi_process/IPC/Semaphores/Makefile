all: shm_write.cpp shm_read.cpp
	g++ -o shm_write shm_write.cpp
	g++ -o shm_read shm_read.cpp

start:
	./shm_write &
	./shm_read &

stop:
	kill -9 `pidof shm_write`
	kill -9 `pidof shm_read`

clean:
	rm shm_read shm_write

.PHONY: start clean
