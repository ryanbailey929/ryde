# RyDE

An opinionated text editor. Currently under construction.

Only developed for Linux.

It's possible that the code may be easily portable to Windows and Mac in it's current state, but if so, know that may change anytime.

# Compilation (Linux)

**Note:** The program will run, but it cannot be used as a text editor yet. The only use case I can imagine for compiling it in it's current state is if you're a potential employer who wants to confirm I write code that isn't gibberish.

1. Create the following directories (the paths are relative to the directory this file is in):

    - bin/
    - lib/
    - build_debug/
    - build_debug/base/
    - build_debug/widgets/
    - src/shaders/headers/

    (`mkdir bin/ lib/ build_debug/ build_debug/base/ build_debug/widgets/ src/shaders/headers/`)

2. Install make, glfw3 and glm (if they are not already installed).

3. Make sure you have a version of gcc installed that can compile for C++20 (I use gcc 11).

4. To invoke the gcc C++ compiler on my system I call g++-11. If you don't, and instead call just g++ or some other package or alias, go into the makefile (it's in this directory) and you'll find a line near the top that says "CXX := g++-11". Replace "g++-11" with whatever you use.

5. Next you'll need to download the GL loader. Go to https://glad.dav1d.de/<br>
There should be a bunch of options. If not already selected:
    1. For Language, select C/C++.
    2. For Specification, select OpenGL.
    3. For gl (Under API), select Version 3.3.
    4. For Profile, select Core.
    5. Generate a loader should be selected, but Omit KHR and Local Files shouldn't be.<br>
    6. With those options set (don't worry about the others), click GENERATE.<br>
    7. Some files should appear for you to choose to download. Download glad.zip

6. Extract glad.zip and you should see 2 directories: include and src.<br>
(To distinguish between the src/ directory in glad.zip and this directory, from now I'll call the one in glad.zip: glad.zip/src/.)<br>
    1. Place both the folders inside the include/ directory (glad/ and KHR/) into lib/ (the directory you created in this directory).<br>
    2. Place the file that's inside the glad.zip/src/ directory (glad.c) into lib/glad/, so that that the file's location relative to this directory is lib/glad/glad.c<br>
lib/ should now look like this:<br>
~~~
lib/
| \
|  glad/
|  | \
|   \ glad.c
|    \
 \    glad.h
  \
   KHR/
   (The contents of KHR should be exactly as they were when downloaded.)
~~~

7. There's a program as a part of this software that's used in the build process of the main program. It needs to be built first.<br>
In a terminal inside this directory, run: `make bin/create_shader_header`<br> 
(What the program does is it converts the shaders for the project from glsl files to std::strings inside C++ headers.)<br>
8. Now run `make bin/ryde_debug`

(There is no release build as the program is still under construction.)

# Running the Program
The compiled program is bin/ryde_debug.<br>
To run: Open a terminal in this directory and run: `./bin/ryde_debug`