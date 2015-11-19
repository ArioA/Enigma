#enigma: plugboard.o helper.o
#	g++ -g -Wall pb.o helper.o -o enigma



OBJ = enigma.o rotor.o reflector.o plugboard.o helper.o configuration.o
SOR = $(OBJ:.o = .cpp)
HDR = $(OBJ:.o = .h)
EXE = enigma
CPPFLAGS = -g -Wall

all: $(SOR) $(HDR) $(EXE)

$(EXE): $(OBJ)
	g++ $(CPPFLAGS) $(OBJ) -o $(EXE)

%.o: %.cpp %.h
	g++ $(CPPFLAGS) -c $<

.PHONY: clean

clean:
	-rm *.o
