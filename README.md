[![CircleCI](https://circleci.com/gh/ocarizr/OWI_sample.svg?style=svg)](https://circleci.com/gh/ocarizr/OWI_sample)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/d9cb9f6e95a04455963045310743b4a9)](https://www.codacy.com/manual/ocarizr/OWI_sample?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=ocarizr/OWI_sample&amp;utm_campaign=Badge_Grade)

# OWI Sample Project

The repository contains a solution (sln) with two projects who can be opened at one using VS2019:
-  A test Project,
-  The project with the algorithm

I used C++17 in the project.

### Design choices

The algorithm runs in a single thread
-  The main reason for that is because I want to save threads to run as much as possible boards at the same time.
-  The given algorithm has enough performance to attend to its requirements (I measured from 500ms to 1s to solve a 3x3 grid).

### Algorithm Purpose

The given project has the objective to solve a given board of puzzle
-  The board is inputted into the algorithm as a string.
-  The board is a square grid (nxn).
-  Each piece has only four sides.
-  A piece connects with its neighbor when its side is a lower character and its neighbor side is the same letter, but upper.

### Allowed behaviors

-  The pieces cannot flip, but they can be rotated.
-  The pieces can be moved to any position on the board.

### Some requirements

-  The algorithm needs to validate the input.
-  A solution is when all pieces are connected.
-  The algorithm needs to calculate all possible solutions of a given board of a maximum size of 3x3 at a reasonable time.

### Algorithm work

All the classes in the project exist to facilitate the calculation of the results.
-  board: resume functions about the board, like grab pieces, determine if a position is inside it, etc.
-  piece: has functions about the pieces, like rotation, verification if it's connected, etc.
-  position: has information about the piece position and functions to change the properties.
-  custom_comparison: only has a function to compare two matrixes.
-  puzzle_solver: in this class are all the algorithms to determine a solution, validation of input and all possible solutions.

The first function is input validation:
-  It needs to guarantee that the input forms a square grid.
-  The values for the sides of the pieces need to be allowed as mentioned above.
-  The input can only have 4 letters for the sides of the pieces, not more neither less.

The second function is to determine if a given input is a solution:
-  After validating the input it needs to verify if the input is a solution for the grid.

The third one is responsible to determine the number of solutions of the given input.
-  It simply uses the fourth function to get the size of the resulting collection.

The fourth function returns all possible solutions to the given input.
-  It iterates through a tree of possibilities, every time it finds that a branch doesn't have a solution it drops it and starts analyzing the next branch.
-  Inside each possible board, arrangement exists several possible rotation combinations for the pieces.
-  The focus of the algorithm is to analyze the minimum possibilities as possible to find all solutions for the board.
