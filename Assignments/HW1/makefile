# Example 7
EXE=HW1

# Main target
all: $(EXE)

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lfreeglut -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
HW1:HW1.o
	gcc -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)
