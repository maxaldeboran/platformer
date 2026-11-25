CXX=g++
RAYLIB_SRC=raylib/src
CXXFLAGS=-std=c++23 -Wall -Wextra -pedantic-errors -I$(RAYLIB_SRC) -ggdb
LIBS=-lm -lX11

OBJS=\
     obj/globals.o \
     obj/actor.o \
     obj/solid.o \
     obj/level.o \
     obj/player.o \
     obj/main.o

.PHONY: all clean cleanraylib cleanall

all: plat

plat: $(OBJS) $(RAYLIB_SRC)/libraylib.a
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

obj/%.o: %.cpp *.h
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(RAYLIB_SRC)/libraylib.a: $(RAYLIB_SRC)/*.c $(RAYLIB_SRC)/*.h
	$(MAKE) -C $(RAYLIB_SRC) TARGET_PLATFORM=PLATFORM_DESKTOP_GLFW

clean:
	rm -rf plat obj

cleanraylib:
	$(MAKE) -C $(RAYLIB_SRC) clean

cleanall: clean cleanraylib
