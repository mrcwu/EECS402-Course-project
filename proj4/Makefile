all: project4.exe
# if want to delete the .o and .exe files, add clean behind project4.exe

project4.o: project4.cpp
		g++ -c project4.cpp -o project4.o

LinkedNodeClass.o: LinkedNodeClass.cpp LinkedNodeClass.h
		g++ -c LinkedNodeClass.cpp -o LinkedNodeClass.o

SortedListClass.o: SortedListClass.cpp SortedListClass.h
		g++ -c SortedListClass.cpp -o SortedListClass.o

LIFOStackClass.o: LIFOStackClass.cpp LIFOStackClass.h
		g++ -c LIFOStackClass.cpp -o LIFOStackClass.o

FIFOQueueClass.o: FIFOQueueClass.cpp FIFOQueueClass.h
		g++ -c FIFOQueueClass.cpp -o FIFOQueueClass.o

project4.exe: project4.o LinkedNodeClass.o SortedListClass.o LIFOStackClass.o FIFOQueueClass.o
		g++ project4.o LinkedNodeClass.o SortedListClass.o LIFOStackClass.o FIFOQueueClass.o -o project4.exe

clean:
		rm -rf *.o *.exe