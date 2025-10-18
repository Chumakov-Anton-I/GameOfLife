# GameOfLife

![Static Badge](https://img.shields.io/badge/Chumakov--Anton--I-GameOfLife-GameOfLife)
![GitHub top language](https://img.shields.io/github/languages/top/Chumakov-Anton-I/GameOfLife)
![GitHub License](https://img.shields.io/github/license/Chumakov-Anton-I/GameOfLife)
![GitHub Org's stars](https://img.shields.io/github/stars/Chumakov-Anton-I%2FGameOfLife)

The **Game of Life** simulator. See [Wikipedia page](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).

## Building

Before building make sure you have CMake version 3.10 or newer and Qt Toolkit 6.8 or newer.
Older versions of Qt can be used but they weren't tested.

Clone the repository
```
git clone git@github.com:Chumakov-Anton-I/GameOfLife.git
```
or
```
git clone https://github.com/Chumakov-Anton-I/GameOfLife.git
```
on your computer.

> [!NOTE]
> You can also use QtCreator to open the project and build it.

Now build the application
```
cd GameOfLife
cmake -S . -B <build-tree>
cmake --build <build-tree>
```
> [!WARNING]
> Type your path to `<build-tree>`.

> [!WARNING]
> If you are a Windows user, open the special prepared for Qt command line. This can be done on the Start menu.

## Using

Just start the `game.exe` file in your build directory (`<build-tree>').

