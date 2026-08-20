# Conway's Game of Life in C

A C implementation of **Conway's Game of Life**, developed progressively across six assignment levels.

The project models a square society of cells in which each cell is either alive or dead. The state of the society evolves over successive generations according to Conway's Game of Life rules.

This repository was created as part of a C programming assignment and demonstrates core C programming concepts including:

- Two-dimensional arrays
- Functions and procedures
- User input processing
- Simulation algorithms
- Array copying
- Population counting
- Stable sorting
- Incremental program development

## Game of Life Rules

Each cell has up to eight neighbouring cells.

For every generation:

1. A live cell with fewer than two live neighbours dies from underpopulation.
2. A live cell with two or three live neighbours survives.
3. A live cell with more than three live neighbours dies from overpopulation.
4. A dead cell with exactly three live neighbours becomes alive.

The program represents cells internally as integers:

```text
0 = dead
1 = alive
```

When displayed to the user:

```text
- = dead
* = alive
```

## Project Structure

The assignment was implemented incrementally, with each level introducing additional functionality.

| File | Functionality |
|---|---|
| `life1.c` | Read and display a society |
| `life2.c` | Add live population counting |
| `life3.c` | Perform one Game of Life evolution |
| `life4.c` | Perform multiple generations and detect stabilization |
| `life5.c` | Add row-by-row population census |
| `life6.c` | Add migration by population density |
| `life.c` | Complete implementation |

The original assignment specification is also included:

```text
Project 3 - Game of Life.pdf
```

## Level 1 — Creating the Society

The first level reads an `m × m` society from standard input.

The maximum supported size is:

```c
#define MAXSIZE 48
```

Input may contain whitespace, while only `*` and `-` are interpreted as cells.

The main functions introduced are:

```c
void read_soc(int soc[][MAXSIZE], int size);
void prt_soc(int soc[][MAXSIZE], int size);
```

The society is displayed inside an ASCII border.

Example:

```text
/ooooooooooo\
| - * * - * |
| - * - * - |
| * - * - * |
| - * * * - |
| - * - * - |
\ooooooooooo/
```

## Level 2 — Population Count

Level 2 adds the ability to count the number of live cells in the entire society.

```c
int population(int soc[][MAXSIZE], int size);
```

Example:

```text
The number of inhabitants is: 13.
```

## Level 3 — Evolution

Level 3 applies the Game of Life rules to every cell.

Two important functions are introduced:

```c
int destiny(int soc[][MAXSIZE], int row, int col);
int evolve_soc(int soc[][MAXSIZE], int size);
```

`destiny()` determines whether a particular cell will be alive or dead in the next generation.

`evolve_soc()` calculates the complete next generation and reports whether any cells changed.

A separate array is used to hold the next generation so that changes to one cell do not affect calculations for neighbouring cells during the same evolution.

## Level 4 — Multiple Generations

Level 4 allows the user to request multiple evolutions.

```c
void generate(int soc[][MAXSIZE], int size, int gen);
```

Evolution continues until either:

- The requested number of generations has been completed, or
- The society reaches a stable state where another evolution produces no change.

Example:

```text
Evolution continues after 5 evolutions.
```

or:

```text
The society stabilises at evolution 1.
```

## Level 5 — Population Census

Level 5 performs a population census for each row.

```c
void census(int soc[][MAXSIZE], int size, int pop[]);
```

For example:

```text
[ 3 2 3 2 1 ]
```

means:

```text
Row 0 -> 3 live cells
Row 1 -> 2 live cells
Row 2 -> 3 live cells
Row 3 -> 2 live cells
Row 4 -> 1 live cell
```

## Level 6 — Migration

The final level introduces **migration**.

Rows are rearranged so that rows with larger live populations move toward the top of the society, while rows with smaller populations move toward the bottom.

```c
void migrate(int soc[][MAXSIZE], int size, int pop[]);
```

For example, given census results:

```text
[ 3 3 4 0 0 ]
```

the row containing four live cells moves above the rows containing three live cells.

Rows with equal populations preserve their relative order, producing a stable descending ordering.

Example result:

```text
Before migration

| - * * * - |
| - * * * - |
| * * - * * |
| - - - - - |
| - - - - - |

Census

[ 3 3 4 0 0 ]
```

After migration:

```text
| * * - * * |
| - * * * - |
| - * * * - |
| - - - - - |
| - - - - - |
```

## Building

A C compiler such as GCC or Clang is sufficient.

Compile the full implementation with:

```bash
gcc life.c -o life
```

or:

```bash
gcc life6.c -o life6
```

You can enable additional compiler warnings with:

```bash
gcc -Wall -Wextra -pedantic life.c -o life
```

## Running

Run the compiled executable:

```bash
./life
```

The program first asks for the size of the society:

```text
Read the boundary size:
```

Enter a value between `1` and `48`.

For example:

```text
5
```

Then enter the rows of the society:

```text
- * * - *
- * - * -
* - * - *
- * * * -
- * - * -
```

The program displays the initial society, population, evolved society, requested generations, census, and migration result.

## Example

Example input:

```text
5
- * * - *
- * - * -
* - * - *
- * * * -
- * - * -
3
```

Initial society:

```text
/ooooooooooo\
| - * * - * |
| - * - * - |
| * - * - * |
| - * * * - |
| - * - * - |
\ooooooooooo/

The number of inhabitants is: 13.
```

After one evolution:

```text
/ooooooooooo\
| - * * * - |
| * - - - * |
| * - - - * |
| * - - - * |
| - * - * - |
\ooooooooooo/

The number of inhabitants is: 11.
```

Further generations are then calculated until either the requested number of evolutions has been reached or the society stabilizes.

## Main Functions

The complete implementation is organized around the following functions:

```c
int read_size(void);
int read_evolutions(void);

void read_soc(int soc[][MAXSIZE], int size);
void prt_soc(int soc[][MAXSIZE], int size);

int population(int soc[][MAXSIZE], int size);

int destiny(int soc[][MAXSIZE], int row, int col);
int evolve_soc(int soc[][MAXSIZE], int size);
void generate(int soc[][MAXSIZE], int size, int gen);

void census(int soc[][MAXSIZE], int size, int pop[]);
void print_census(int pop[], int size);

void migrate(int soc[][MAXSIZE], int size, int pop[]);
```

## Concepts Demonstrated

This project is particularly useful as an exercise in several fundamental programming ideas.

### Two-dimensional arrays

The society is stored as:

```c
int grid[MAXSIZE][MAXSIZE];
```

Each array element represents one cell.

### Simultaneous state updates

A Game of Life generation cannot safely modify the original grid while neighbouring cells are still being calculated.

The program therefore calculates the next generation in a temporary array before copying it back into the current society.

### Neighbour traversal

For each cell, the surrounding positions are examined using row and column offsets:

```text
(-1,-1) (-1,0) (-1,+1)
( 0,-1)  CELL   ( 0,+1)
(+1,-1) (+1,0) (+1,+1)
```

This provides up to eight neighbours per cell.

### Stable migration

The migration stage sorts rows according to their live-cell population.

Rows with equal populations retain their original relative ordering, as required by the assignment.

## Assignment Progression

One interesting feature of the project is that the final program was not written all at once.

Instead, the assignment builds the solution incrementally:

```text
Input / Output
      ↓
Population Count
      ↓
Single Evolution
      ↓
Multiple Evolutions
      ↓
Stabilization Detection
      ↓
Population Census
      ↓
Migration
```

This structure demonstrates how a larger programming problem can be decomposed into smaller independently testable stages.

## Background

Conway's Game of Life is a cellular automaton devised by mathematician **John Horton Conway**.

Despite its simple rules, different starting configurations can produce complex behaviour including:

- Stable structures
- Oscillators
- Moving patterns
- Expanding populations
- Complete extinction

The simulation is therefore a useful programming exercise for learning about arrays, state transitions, algorithms, and emergent behaviour.

## Repository

This project is available at:

`https://github.com/channico/c_programming_game_of_life`

## Acknowledgements

The implementation is based on the **Project 3 — Game of Life** programming assignment included in this repository.

The assignment describes a six-level progression from reading and displaying an initial society through Game of Life evolution, stabilization detection, population census, and migration.
