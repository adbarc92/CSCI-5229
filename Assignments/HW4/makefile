EXE=hw4
SRC=vector4d.cpp lib.cpp shapes.cpp objects.cpp scene.cpp effects.cpp particle.cpp particleSystem.cpp vector3d.cpp

CFLG=-O0 -Wall -g
CLEAN=rm -f $(EXE) $(EXE).exe *.o *.a
ifeq "$(OS)" "Windows_NT"
LIBS=-mwindows -mconsole -lmingw32 -lglew32 -lfreeglut -lglu32 -lopengl32 -lIL
else
LIBS=-lglut -lGLU -lGL -lGLEW -lm -lIL
endif

all: $(EXE)

.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

$(EXE):$(SRC:.cpp=.o) $(EXE).o
	g++ -O3 -o $@ $^ $(LIBS)

run: $(EXE)
	./$(EXE)

clean:
	$(CLEAN)