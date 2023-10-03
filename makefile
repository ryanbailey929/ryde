main_debug := build_debug/main.o
base_debug := build_debug/base/window.o build_debug/base/widget.o
widgets_debug := build_debug/widgets/main_area.o build_debug/widgets/tab.o
mw_debug := build_debug/main_window.o

glad := lib/glad/glad.c

CXX := g++-11
FLAGS_DEBUG := -std=c++20 -Wall -I lib/ -g
GL_FLAGS := -ldl -lglfw

#executables

bin/ryde_debug: $(main_debug) $(base_debug) $(widgets_debug) $(mw_debug)
	$(CXX) $(main_debug) $(glad) $(base_debug) $(widgets_debug) $(mw_debug) \
	-o bin/ryde_debug $(FLAGS_DEBUG) $(GL_FLAGS)

bin/create_shader_header: src/build_tools/create_shader_header.cpp
	$(CXX) src/build_tools/create_shader_header.cpp -o bin/create_shader_header \
	$(FLAGS_DEBUG)

#object files

build_debug/main.o: $(base_debug) $(mw_debug) src/main.cpp
	$(CXX) -c src/main.cpp -o $(main_debug) $(FLAGS_DEBUG)

build_debug/base/window.o: src/base/window.cpp src/base/window.hpp
	$(CXX) -c src/base/window.cpp -o build_debug/base/window.o $(FLAGS_DEBUG)

build_debug/base/widget.o: src/base/widget.cpp src/base/widget.hpp
	$(CXX) -c src/base/widget.cpp -o build_debug/base/widget.o $(FLAGS_DEBUG)

build_debug/main_window.o: src/main_window.cpp src/main_window.hpp src/colors.hpp
	$(CXX) -c src/main_window.cpp -o $(mw_debug) $(FLAGS_DEBUG)

build_debug/widgets/main_area.o: src/widgets/main_area.cpp src/widgets/main_area.hpp \
		src/colors.hpp src/shaders/headers/basic_vertex_shader.hpp \
		src/shaders/headers/main_area_fragment_shader.hpp
	$(CXX) -c src/widgets/main_area.cpp -o build_debug/widgets/main_area.o \
	$(FLAGS_DEBUG)

build_debug/widgets/tab.o: src/widgets/tab.cpp src/widgets/tab.hpp \
		src/colors.hpp src/shaders/headers/basic_vertex_shader.hpp \
		src/shaders/headers/tab_fragment_shader.hpp
	$(CXX) -c src/widgets/tab.cpp -o build_debug/widgets/tab.o $(FLAGS_DEBUG)

#shader headers

src/shaders/headers/basic_vertex_shader.hpp: src/shaders/glsl/basic.vert
	./bin/create_shader_header src/shaders/glsl/basic.vert

src/shaders/headers/basic_fragment_shader.hpp: src/shaders/glsl/basic.frag
	./bin/create_shader_header src/shaders/glsl/basic.frag

src/shaders/headers/tab_fragment_shader.hpp: src/shaders/glsl/tab.frag
	./bin/create_shader_header src/shaders/glsl/tab.frag

src/shaders/headers/main_area_fragment_shader.hpp: src/shaders/glsl/main_area.frag
	./bin/create_shader_header src/shaders/glsl/main_area.frag
