all: project5.exe
# if want to delete the .o and .exe files, add "clean" behind project5.exe

project5.o: project5.cpp IntersectionSimulationClass.h random.h constants.h
		g++ -c project5.cpp -o project5.o

random.o: random.cpp random.h
	g++ -c random.cpp -o random.o

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp IntersectionSimulationClass.h SortedListClass.h SortedListClass.inl LinkedNodeClass.h LinkedNodeClass.inl FIFOQueueClass.h FIFOQueueClass.inl EventClass.h CarClass.h constants.h random.h
	g++ -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

CarClass.o: CarClass.cpp CarClass.h constants.h
	g++ -c CarClass.cpp -o CarClass.o

EventClass.o: EventClass.cpp EventClass.h constants.h
	g++ -c EventClass.cpp -o EventClass.o


project5.exe: project5.o random.o IntersectionSimulationClass.o CarClass.o EventClass.o
		g++ project5.o random.o IntersectionSimulationClass.o CarClass.o EventClass.o -o project5.exe

clean:
		rm -rf *.o *.exe