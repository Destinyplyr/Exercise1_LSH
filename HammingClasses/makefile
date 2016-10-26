# In order to execute this "makefile" just type "make"

OBJS 	= mainSample.o MathFunctions.o
SOURCE	= mainSample.cpp MathFunctions.cpp
HEADER  = EuclideanList.h EuclideanManager.h Hash.h HashFunctions.h ListData.h ListsFunctions.h mainSample.h MathFunctions.h Node.h NodeFunctions.h TrickList.h TrickFunctions.h
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


# clean 
clean:
	rm -f $(OBJS) $(OUT)

#accounting
count:
	wc $(SOURCE) $(HEADER)