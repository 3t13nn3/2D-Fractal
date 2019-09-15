# Fractal-2D
A simple program that allow you to play with some 2D fractals

This project aims at learn the foundation of fractals and then play with some.

I invite you to check code comments if you are interested in fractal conception (particulary in GLSL here).

## Prerequisites

- [GLFW](https://www.glfw.org/)
- [OpenGL Mathematics (GLM)](https://glm.g-truc.net/0.9.9/index.html)
  
***Note that the project will not compile if you are missing one of these libraries.***

## How to use - *Linux Project*

### Compilation

Compile the program with ```make```.

### Utilisation

Lauch the binary as ```./fractal fragmentShader.fs```.

***Note that if you don't use the argmument thing to select a shader, it will automaticly select the ```Shaders/mandel.fs``` shader.***

### Use

Inputs:
- *```Arrows (UP & DOWN)```* Zoom
- *```Z```* Forward
- *```S```* Backward
- *```Q```* Left
- *```D```* Right

### Clean files

Clean object files by ```make clean```.
Clean object files and binary by ```make cleanall```.

## Available fractales

### Mandelbrot

You could use the program with the ```Shaders/mandel.fs``` to play with the Mandelbrot fractal.

### Julia

As the Mandelbrot fractal, you must use the ```Shaders/mandel.fs``` because the Julia one is a derivative of the Mandelbrot fractal.
To move the Mandelbrot fractal into Julia, you have to use the conditional inclusion set as ```Julia``` by uncommenting the ```#define Julia``` line.

Furthermore, you could change Julia's component (```realJulia``` and ```imaginaryJulia``` variables) value to get an other result (I advice you the [Julia Set Wikipedia page at the "Quadratic polynomials"](https://en.wikipedia.org/wiki/Julia_set) to got some reactives values).

## Visual Effect

By uncommenting the the conditional inclusion ```#define Move``` line, you could make the fractal move smoothly through the current time and sinus/cosinus function, try it!.

Finaly, you could tweak the ```finalColor``` `vec4` to get some other colors to the fractal. Actually, colors change in function of time, iterations and cosinus function.
## Exemple of Execution

Here are some pictures that illustrate execution:

- ***Mandelbrot Fractal***

![*Mandelbrot Fractal](https://github.com/3t13nn3/Fractal-2D/blob/master/Screen/4.png)

- ***Julia Fractal Empty***

![*Mandelbrot Fractal](https://github.com/3t13nn3/Fractal-2D/blob/master/Screen/2.png)

- ***Julia Fractal Stars***

![*Mandelbrot Fractal](https://github.com/3t13nn3/Fractal-2D/blob/master/Screen/3.png)

- ***Julia Fractal Storm***

![*Mandelbrot Fractal](https://github.com/3t13nn3/Fractal-2D/blob/master/Screen/1.png)

## Author

* **Etienne PENAULT** - *Personal Work*
