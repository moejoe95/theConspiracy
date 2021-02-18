# theConspiracy

theConspiracy is a simple 2D metroidvania-style game written in C++.

This project is done as the second assignment for the course *703807 Advanced C++ programming* at UIBK. 
The project follows loosely the specification given [here](https://git.uibk.ac.at/c7031162/703807-advanced-cxx/blob/master/assignment2/metroidvania_specification.md). A customized specification is given in the [specifications](specification.md) file.


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

## Known Issues



## Acknowledgements

This project was created with the help of:

- [Tiled](https://www.mapeditor.org/): design of rooms
- [Freesound.org](https://www.freesound.org): sound effects
- [gameartpartners.com](https://gameartpartners.com/): characters, weapons, etc.
