# Sudoku
A sudoku solver written in C++.

# Requirements
Requires `jsoncpp`. The include files are expected at `<json/*.h>`, so make sure the files are at `/usr/include/json/`.

# Building
`make` should do the trick.

# Using
Inside the tools folder, there are three programs available.
* `create`: Creates a board interactively from user input. No arguments.
* `print [file.json]`: Prints a created board to the console. One optional argument: the file to read from (defaults to result.json)
* `solve <file.json>`: Solves a board. One required argument: the board to solve.
