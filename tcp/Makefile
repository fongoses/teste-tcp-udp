CC = gcc
FLAGS = -Wall 

all: testecli testecli2 testesrv testesrv2

testecli: testecli.cpp
	$(CC) testecli.cpp -lc -o testecli $(FLAGS) 

testecli2: testecli2.cpp
	$(CC) testecli2.cpp -lc -o testecli2 $(FLAGS) 


testesrv: testesrv.cpp 
	$(CC) testesrv.cpp -lc -o testesrv $(FLAGS) 

testesrv2: testesrv2.cpp 
	$(CC) testesrv2.cpp -lc -o testesrv2 $(FLAGS) 

clean:
	rm testecli testesrv 
