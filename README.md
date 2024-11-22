# **Conway's Game of Life - 2D Finite Implementation**

## **Overview**
This project is an implementation of Conway's Game of Life in a finite 2D grid. The Game of Life is a cellular automaton invented by mathematician John Horton Conway in 1970. It is a zero-player game, meaning its evolution is determined by its initial state and progresses based on a set of simple rules.

The uniqueness of this implementation lies in its finite grid representation, where the world has fixed dimensions, and cells along the edges have neighbors only within the defined bounds.

---

## **Rules of the Game**
1. **Grid and Cells**: 
   - The game is played on a 2D grid of cells, where each cell is either alive (`*`) or dead (` `).
   - The grid has fixed dimensions, meaning it is finite, and cells along the edges do not wrap around.

2. **State Updates**:
   - At each step (generation), the state of the cells evolves based on the following rules:
     1. **Survival**: A living cell with 2 or 3 live neighbors remains alive.
     2. **Overpopulation**: A living cell with more than 3 live neighbors dies.
     3. **Underpopulation**: A living cell with fewer than 2 live neighbors dies.
     4. **Reproduction**: A dead cell with exactly 3 live neighbors becomes alive.

3. **Edge Handling**:
   - Cells at the edges of the grid interact only with their neighbors within the bounds of the finite grid.
   - Cells outside the bounds are considered dead.

4. **Iterations**:
   - The game evolves for a fixed number of generations or until all cells are dead, resulting in an empty world.

---

## **How to Use**
1. **Initialize the World**:
   - You can provide an initial state through a `.txt` file, where each row represents a grid row, and each character (`*` or ` `) represents a cell.
   - Example file for a 10x5 grid:
     ```
     **********
     *        *
     *   **   *
     *        *
     **********
     ```
   - The `glider/` folder contains `.txt` files for various glider patterns, such as:
    - **Glider**: A small pattern that moves diagonally across the grid.
    - **Lightweight Spaceship (LWSS)**: A larger pattern that moves horizontally.

You can easily test these patterns by loading them as input files.

2. **Run the Simulation**:
   - The program reads the input file, initializes the grid, and iterates through generations based on the rules.

3. **Output**:
   - The current state of the grid is displayed in the console at each generation.
   - The final state of the grid is saved to a file for later use or analysis.
