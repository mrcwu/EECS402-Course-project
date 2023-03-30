all: proj3.exe

project3.o: project3.cpp ColorClass.h ColorImageClass.h PatternClass.h constants.h questionForPath.h questionForColor.h questionForLoc.h printInvalidInNum.h inPatternCheck.h inPpmCheck.h
	g++ -c project3.cpp -o project3.o

# the classes
ColorClass.o: ColorClass.cpp ColorClass.h constants.h
	g++ -c ColorClass.cpp -o ColorClass.o

ColorImageClass.o: ColorImageClass.cpp ColorImageClass.h ColorClass.h PatternClass.h constants.h
	g++ -c ColorImageClass.cpp -o ColorImageClass.o

PatternClass.o: PatternClass.cpp PatternClass.h
	g++ -c PatternClass.cpp -o PatternClass.o

# the global functions
questionForPath.o: questionForPath.cpp questionForPath.h inPatternCheck.h inPpmCheck.h constants.h
	g++ -c questionForPath.cpp -o questionForPath.o

questionForColor.o: questionForColor.cpp questionForColor.h printInvalidInNum.h constants.h
	g++ -c questionForColor.cpp -o questionForColor.o

questionForLoc.o: questionForLoc.cpp questionForLoc.h printInvalidInNum.h ColorImageClass.h constants.h
	g++ -c questionForLoc.cpp -o questionForLoc.o

printInvalidInNum.o: printInvalidInNum.cpp printInvalidInNum.h
	g++ -c printInvalidInNum.cpp -o printInvalidInNum.o

inPatternCheck.o: inPatternCheck.cpp inPatternCheck.h
	g++ -c inPatternCheck.cpp -o inPatternCheck.o

inPpmCheck.o: inPpmCheck.cpp inPpmCheck.h constants.h
	g++ -c inPpmCheck.cpp -o inPpmCheck.o


proj3.exe: project3.o ColorClass.o ColorImageClass.o PatternClass.o questionForPath.o questionForColor.o questionForLoc.o printInvalidInNum.o inPatternCheck.o inPpmCheck.o
	g++ project3.o ColorClass.o ColorImageClass.o PatternClass.o questionForPath.o questionForColor.o questionForLoc.o printInvalidInNum.o inPatternCheck.o inPpmCheck.o -o proj3.exe

clean:
	rm -rf proj3.exe project3.o ColorClass.o ColorImageClass.o PatternClass.o questionForPath.o questionForColor.o questionForLoc.o printInvalidInNum.o inPatternCheck.o inPpmCheck.o