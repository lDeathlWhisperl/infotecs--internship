all: prog_1 prog_2
	g++ main_1.o functions_1.o Args.o -o pr_1
	g++ main_2.o functions_2.o Serv.o -o pr_2
	rm *.o
#	clear

prog_1:
	g++ -c Prog_1/main_1.cpp
	g++ -c Prog_1/functions_1.cpp
	g++ -c Prog_1/Args.cpp
	
prog_2:
	g++ -c Prog_2/main_2.cpp
	g++ -c Prog_2/functions_2.cpp
	g++ -c Prog_2/Serv.cpp
