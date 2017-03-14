# définition des variables utilise pour la compilation
CXX= g++
#SOURCE2= test.cpp
SOURCE= partie1.cpp
EXEC= testexec
#EXEC2=expexec 
SUP=rm -rf
CXXFLAGS=-lopencv_core -lopencv_highgui -lopencv_imgproc -std=c++11 -lpthread
all:	

	$(CXX) -Wall $(SOURCE) -o $(EXEC) $(CXXFLAGS)
	
#compile:
	#$(CXX) -Wall $(SOURCE2) -o $(EXEC2) $(CXXFLAGS)

	#./testexec

mrproper:clean
	$(SUP) *.o
clean:
	 $(SUP) *.o

