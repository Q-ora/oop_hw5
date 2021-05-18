all: main

main: main.cpp Mixed.cpp Mixed.h
	g++ main.cpp Mixed.cpp -o main

clean: main
	rm main
