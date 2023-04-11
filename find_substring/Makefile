.PHONY: all main run clean
all: main

CFLAGS = -O2 -std=c++14
# c++14 необходим для для короткого for-а \
  при переборе элементов вектора

CC = g++

main:
	$(CC) main.cpp KMP_sophisticated_edges.cpp KMP_standart_edges.cpp z_function.cpp native_algo.cpp $(CFLAGS) -o main

run: main
	./main

clean:
	rm main