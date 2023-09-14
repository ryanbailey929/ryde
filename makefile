main_debug := build_debug/main.o
base_debug := build_debug/base/window.o build_debug/base/widget.o
widgets_debug := build_debug/widgets/main_area.o
mw_debug := build_debug/main_window.o

glad := lib/glad/glad.c

CXX := g++-11
FLAGS_DEBUG := -std=c++20 -Wall -I lib/ -g
GL_FLAGS := -ldl -lglfw

bin/ryde_debug: $(main_debug) $(base_debug) $(widgets_debug) $(mw_debug)
	$(CXX) $(main_debug) $(glad) $(base_debug) $(widgets_debug) $(mw_debug) \
	-o bin/ryde_debug $(FLAGS_DEBUG) $(GL_FLAGS)

build_debug/main.o: $(base_debug) $(mw_debug) src/main.cpp
	$(CXX) -c src/main.cpp -o $(main_debug) $(FLAGS_DEBUG)

build_debug/base/window.o: src/base/window.cpp src/base/window.hpp
	$(CXX) -c src/base/window.cpp -o build_debug/base/window.o $(FLAGS_DEBUG)

build_debug/base/widget.o: src/base/widget.cpp src/base/widget.hpp
	$(CXX) -c src/base/widget.cpp -o build_debug/base/widget.o $(FLAGS_DEBUG)

build_debug/main_window.o: src/main_window.cpp src/main_window.hpp src/colors.hpp
	$(CXX) -c src/main_window.cpp -o $(mw_debug) $(FLAGS_DEBUG)

build_debug/widgets/main_area.o: src/widgets/main_area.cpp src/widgets/main_area.hpp \
		src/colors.hpp
	$(CXX) -c src/widgets/main_area.cpp -o build_debug/widgets/main_area.o \
	$(FLAGS_DEBUG)

.PHONY: objects_debug
objects_debug: $(main_debug) $(base_debug) $(widgets_debug) $(mw_debug)
