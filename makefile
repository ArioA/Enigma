#enigma: plugboard.o helper.o
#	g++ -g -Wall pb.o helper.o -o enigma



#plugboard.o: plugboard.cpp helper.cpp plugboard.h
#	g++ -g -Wall -c plugboard.cpp

#helper.o: helper.cpp helper.h
#	g++ -g -Wall -c helper.cpp



OBJ = enigma.o rotor.o reflector.o plugboard.o helper.o
SOR = $(OBJ:.o = .cpp)
HDR = $(OBJ:.o = .h)
EXE = enigma
CPPFLAGS = -g -Wall

all: $(SOR) $(HDR) $(EXE)

$(EXE): $(OBJ)
	g++ $(CPPFLAGS) $(OBJ) -o $(EXE)

%.o: %.cpp
	g++ $(CPPFLAGS) -c $<

