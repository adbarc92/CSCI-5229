EXE=hw2
SRC=objects.cpp lib.cpp
all: $(EXE)

CFLG=-O3 -Wall
CLEAN=rm -f $(EXE) *.o *.a
ifeq "$(OS)" "Windows_NT"
LIBS=-mwindows -mconsole -lmingw32 -lglew32 -lfreeglut -lglu32 -lopengl32
else
LIBS=-lglut -lGLEW -lGLU -lGL -lm
endif

game: $(EXE)

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
$(EXE):$(SRC:.cpp=.o) $(EXE).o
	g++ -O3 -o $@ $^   $(LIBS)

run:
	./$(EXE)

#  Clean
clean:
	$(CLEAN)