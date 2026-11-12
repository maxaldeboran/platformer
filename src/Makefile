CXX=g++
RAYLIB_SRC=raylib/src
CXXFLAGS=-std=c++23 -ggdb -Wall -Wextra -pedantic-errors -I$(RAYLIB_SRC)
LIBS=-lm -lX11

.PHONY: clean cleanraylib cleanall

plat: obj/main.o $(RAYLIB_SRC)/libraylib.a
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

obj/%.o: %.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c -o $@ $^

$(RAYLIB_SRC)/libraylib.a: $(RAYLIB_SRC)/*.c $(RAYLIB_SRC)/*.h
	$(MAKE) -C $(RAYLIB_SRC) TARGET_PLATFORM=PLATFORM_DESKTOP_GLFW

clean:
	rm -rf plat obj

cleanraylib:
	$(MAKE) -C $(RAYLIB_SRC) clean

cleanall: clean cleanraylib
