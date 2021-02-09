# theConspiracy

theConspiracy is a simple 2D metroidvania-style game written in C++.

This project is done as the second assignment for the course *703807 Advanced C++ programming* at UIBK. 
The project followes loosely the specification given [here](https://git.uibk.ac.at/c7031162/703807-advanced-cxx/blob/master/assignment2/metroidvania_specification.md). A more specific specification will be posted here soon.

## Build

```
cmake -B build
make -C build
./build/theConspiracy
```

Some settings can be configured in 'settings.ini'.

## Controlls

- `wasd` for player control
- `space` for shooting
- `ESC` for open menu


## Dependencies

- nlohmann-json
- boost (boost program options)
- SDL2 (image, mixer, ttf)
- spdlog
