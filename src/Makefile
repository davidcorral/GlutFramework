LIB = libGlutFramework.a

CC = clang++
LD = clang++

CCFLAGS += -Wall

OS = Darwin

###############################################################################

# OpenGl
ifeq ($(OS),Linux)
    INCLUDES += -I/usr/include/GL/
    LIBS     += -lGL -lGLU -lglut -lGLEW
endif

# OpenGl
ifeq ($(OS),Darwin)
    INCLUDES  += -I/opt/local/include 
    FRAMEWORKS = -framework GLUT -framework OpenGL
    LIBS += -lGLEW
endif

###############################################################################

INCLUDES += -I../include/
SOURCES   = $(wildcard *.cpp)
OBJECTS   = $(SOURCES:.cpp=.o)

$(LIB): $(OBJECTS)
	@echo
	@mkdir -p ../private
	@mkdir -p ../lib
	ar vrs ../lib/$@ $(addprefix ../private/,$^)

%.o: %.cpp
	@echo
	@mkdir -p ../private
	$(CC) $(CCFLAGS) -c $^ $(INCLUDES) -o ../private/$@
	
clean:
	rm -f ../lib/$(LIB) ../private/*.o *.*~ *~
