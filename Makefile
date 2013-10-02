all:
	g++ ./srct/*.cpp ./srct/Posix/*.cpp ./src/*.cpp vendasdescontosTestes.cpp -o testador
	g++ ./src/*.cpp vendasdescontos.cpp -o programadefato
