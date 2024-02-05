# kite
A small toy OpenGL wrapper for simple 3D/2D graphics written in C++.

![example render](assets/example.png)

Kite was written as a small introductin to the OpenGL framework and graphics rendering pipelines and technique. It is not made for speed or efficiency.

Hopefully, in the future it will be able to serve as a full framework for games or visualizations, which has keyboard and controller input, as well as a fully fledged audio engine. 


## Compiling
Kite uses the following dependencies:
```
brew install glfw glew glm
```
When installed, compile and run the included example program with
```
make all
./kite
```

## Todo
* add input and audio api
* add support for .obj files
