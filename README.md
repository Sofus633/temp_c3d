*This project has been created as part of the 42 curriculum by cascrizz, rueapen.*

# cub3D

## Description

cub3D is a small first-person 3D engine written in C with the MiniLibX graphics library. It
renders the inside of a maze as a "realistic" 3D view, in the spirit of the first-person
shooter Wolfenstein 3D.

The rendering uses **raycasting**: for every vertical column of the window, a ray is cast
from the player's position into the map. The distance to the first wall hit determines the
height of the wall slice drawn on screen, so nearby walls look tall and far walls look short.
The walls are found with a DDA (Digital Differential Analyzer) grid traversal, which steps
from one grid cell to the next without testing every point along the ray.

The goal of the project is to explore raycasting and the basics of graphics programming
(windows, colors, events, shapes and images) while keeping the code robust: the program must
never crash, and every misconfigured scene file must be rejected with a clear error.

### Features

- Textured walls, with a different texture for each side: north, south, east and west.
- Configurable floor and ceiling colors (RGB).
- Movement with **W**, **A**, **S**, **D**, and looking left and right with the **left** and
  **right arrow** keys.
- **ESC** or clicking the red cross of the window closes the program cleanly.
- Scenes are described in `.cub` files: texture paths, colors and the map.

## Instructions

### Dependencies

- A C compiler (`cc`) and `make`.
- The X11 development libraries (`libx11-dev`, `libxext-dev` on Debian/Ubuntu), needed by
  MiniLibX.
- The MiniLibX sources are in `lib/mlx_linux`, and the `libft` sources are in `libft/`.
  Both are built automatically by the Makefile.

### Compilation

```sh
make            # builds the cub3D binary (and libft, MiniLibX)
make clean      # removes object files
make fclean     # removes object files, the binary and the libraries
make re         # fclean + make
```

The Makefile is built with `-Wall -Wextra -Werror` and does not relink when nothing changed.
The output name and object directory can be overridden, for example `make NAME=cub3D_test`.

### Execution

```sh
./cub3D maps/valid/subject_example.cub
```

The program takes exactly one argument: a scene description file with the `.cub` extension.
The sample maps in `maps/valid/` need the texture files `./textures/north.xpm`,
`./textures/south.xpm`, `./textures/west.xpm` and `./textures/east.xpm`, relative to the
directory you run the program from.

### Controls

| Key             | Action                              |
|-----------------|-------------------------------------|
| `W` / `S`       | Move forward / backward             |
| `A` / `D`       | Strafe left / right                 |
| Left / Right    | Turn the view left / right          |
| `ESC`           | Close the window and quit           |
| Red cross       | Close the window and quit           |

### Scene file format (`.cub`)

A scene file has two parts. The first part contains one element per line, in any order, with
one or more empty lines allowed between elements and one or more spaces between the fields.
The map is always the last part of the file.

| Identifier | Meaning                          | Example                    |
|------------|----------------------------------|----------------------------|
| `NO`       | Path to the north wall texture   | `NO ./textures/north.xpm`  |
| `SO`       | Path to the south wall texture   | `SO ./textures/south.xpm`  |
| `WE`       | Path to the west wall texture    | `WE ./textures/west.xpm`   |
| `EA`       | Path to the east wall texture    | `EA ./textures/east.xpm`   |
| `F`        | Floor color, R,G,B in `[0,255]`  | `F 220,100,0`              |
| `C`        | Ceiling color, R,G,B in `[0,255]`| `C 225,30,0`               |

The map uses these characters only:

- `0`: empty space
- `1`: wall
- `N`, `S`, `E`, `W`: the player's start position and initial orientation (exactly one)
- spaces: outside the map, or unknown cells. Spaces are valid map content.

The map must be closed: every floor cell (`0`, or a player start) must be enclosed by walls
(`1`). If the map is open, the program reports an error.

Example:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111111111
100000000001
100000N00001
100000000001
111111111111
```

### Error handling

If the scene file is invalid (wrong extension, missing or duplicated element, bad color,
missing texture, an open map, a map without a player, an unknown character, ...), the program
prints an error and exits without crashing:

```
Error
<explicit message describing the problem>
```

The test maps in `maps/invalid/` each contain one specific mistake. They can be checked with
`tests/run_tests.sh` (see below).

### Tests

```sh
tests/run_tests.sh ./cub3D
```

The script runs every map in `maps/invalid/` and checks for the `Error` output, runs every map
in `maps/valid/` under `valgrind` for 3 seconds (it needs a display, `$DISPLAY`), and reports
memory errors. It also checks wrong argument counts, a directory and a non-existent file.

## Resources

### References

- Lode's Computer Graphics Tutorial, Raycasting: https://lodev.org/cgtutor/raycasting.html
- MiniLibX documentation (42 docs): https://harm-smits.github.io/42docs/libs/minilibx
- Permadi, Ray-Casting Tutorial: https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
- Wolfenstein 3D (id Software, 1992), the game that inspired the project.

### AI usage

AI (Claude, by Anthropic) was used during this project for these tasks: reviewing the code
against the subject and the evaluation sheet, producing the to-do list of remaining work,
explaining the DDA algorithm used for raycasting, and helping to write and refactor the
raycasting, rendering and parsing code (including error handling for malformed scene files),
the Makefile (MiniLibX build), the test maps and the test script. All AI-generated code and
text was reviewed, tested and understood by the team before being kept.
