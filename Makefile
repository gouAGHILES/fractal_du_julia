# définition des variables utilise pour la compilation
CXX= g++

SOURCE= partie11.cpp
EXEC= testexec

SUP=rm -rf
CXXFLAGS=-lopencv_core -lopencv_highgui -lopencv_imgproc -std=c++11 -lpthread

all:	

	$(CXX) -Wall $(SOURCE) -o $(EXEC) $(CXXFLAGS)
	

mrproper:clean
	$(SUP) *.o
clean:
	 $(SUP) *.o

