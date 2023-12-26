all: main.o
	ld main.o -o main \
		-plugin /usr/lib/gcc/x86_64-linux-gnu/9/liblto_plugin.so \
		-plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/9/lto-wrapper \
		-plugin-opt=-fresolution=/tmp/cciHb1aE.res \
		-plugin-opt=-pass-through=-lgcc_s \
		-plugin-opt=-pass-through=-lgcc \
		-plugin-opt=-pass-through=-lc \
		-plugin-opt=-pass-through=-lgcc_s \
		-plugin-opt=-pass-through=-lgcc \
		--build-id --eh-frame-hdr \
		-m elf_x86_64 --hash-style=gnu --as-needed \
		-dynamic-linker /lib64/ld-linux-x86-64.so.2 \
		-pie -z now \
		-z relro /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/Scrt1.o \
		/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/crti.o \
		/usr/lib/gcc/x86_64-linux-gnu/9/crtbeginS.o \
		-L/usr/lib/gcc/x86_64-linux-gnu/9 \
		-L/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu \
		-L/usr/lib/gcc/x86_64-linux-gnu/9/../../../../lib -L/lib/x86_64-linux-gnu \
		-L/lib/../lib \
		-L/usr/lib/x86_64-linux-gnu \
		-L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/9/../../.. \
		-lstdc++ -lm -lgcc_s -lgcc -lc -lgcc_s -lgcc \
		/usr/lib/gcc/x86_64-linux-gnu/9/crtendS.o \
		/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/crtn.o

main.o: main.s
	as -o main.o main.s

main.s: main.cpp
	g++ -S main.cpp

start:
	./main

clean:
	rm main.s && rm main.o && rm main

.PHONY: start clean
