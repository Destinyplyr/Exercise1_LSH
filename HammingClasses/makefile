# In order to execute this "makefile" just type "make"

OBJS 	= mainSample.o MathFunctions.o EuclideanList.o EuclideanManager.o HashFunctions.o ListsFunctions.o NodeFunctions.o TrickFunctions.o
SOURCE	= mainSample.cpp MathFunctions.cpp EuclideanList.cpp EuclideanManager.cpp HashFunctions.cpp ListsFunctions.cpp NodeFunctions.cpp TrickFunctions.cpp
HEADER  = Hash.h ListData.h mainSample.h MathFunctions.h Node.h TrickList.h 
OUT  	= lsh
CC	= g++
FLAGS   = -g -c 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)


# create/compile the individual files
mainSample.o: mainSample.cpp
	$(CC) $(FLAGS) mainSample.cpp 

MathFunctions.o: MathFunctions.cpp
	$(CC) $(FLAGS) MathFunctions.cpp	

EuclideanList.o: EuclideanList.cpp
	$(CC) $(FLAGS) EuclideanList.cpp

EuclideanManager.o: EuclideanManager.cpp
	$(CC) $(FLAGS) EuclideanManager.cpp

HashFunctions.o: HashFunctions.cpp
	$(CC) $(FLAGS) HashFunctions.cpp

ListsFunctions.o: ListsFunctions.cpp
	$(CC) $(FLAGS) ListsFunctions.cpp

NodeFunctions.o: NodeFunctions.cpp
	$(CC) $(FLAGS) NodeFunctions.cpp

TrickFunctions.o: TrickFunctions.cpp
	$(CC) $(FLAGS) TrickFunctions.cpp

# clean 
clean:
	rm -f $(OBJS) $(OUT)

#accounting
count:
	wc $(SOURCE) $(HEADER)