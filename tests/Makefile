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

SOURCES  = $(wildcard *.cpp)
OBJECTS  = $(SOURCES:.cpp=.o)
LIBS += -L../lib/ -lGlutFramework

all: $(OBJECTS)

%.o: %.cpp
	@echo
	$(CC) $(CCFLAGS) $(INCLUDES) $^ -o $(subst .o,,$@) $(LIBS) $(FRAMEWORKS)
	
clean:
	rm -f $(subst .o,,$(OBJECTS)) *.*~ *~
