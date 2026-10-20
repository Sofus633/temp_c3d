# change.md — cub3D mandatory part

All changes made on 2026-10-10 by Claude (main session + 3 parallel agents). Nothing was committed.

## Foundation (main session)

- `lib/object/raycast.c` (new): DDA `cast_ray` + static helpers `ray_delta`, `init_ray`, `is_wall_cell`, `run_dda`. Norm-compliant.
- `lib/object/player.c`: removed old step-based `cast_ray` and unused `direction_vector`.
- `lib/object/player.h`: added `t_ray` struct, removed `direction_vector` prototype.
- `parsing/` (old root duplicate of `lib/parsing`): deleted (still in git history).
- `lib/parsing/libft/` -> `libft/` (git mv). Includes in `lib/parsing/*.c` and `parsing.h` changed to `#include "libft.h"`.
- `libft/SRC/libft/ft_calloc.c` (new) + prototype in `libft/Includes/libft.h` (needed: `calloc` is forbidden).
- `libft/Makefile`: `wildcard` replaced by an explicit source list.
- `lib/parsing/main.c`, `lib/parsing/Makefile`, `lib/parsing/cub3D`: test harness removed.
- `lib/mlx_linux`: was a git submodule entry without `.gitmodules` (empty on clone) -> untracked so it can be added as normal files. Removed its `.github/` CI folder.
- Untracked build artifacts from git (`*.o`, `*.d`, `*.a`, binaries, `minilibx-linux.tgz`).
- `game.h`: added `int map_width`.
- `lib/parsing/free.c` (new): `free_parsing(t_game *)`, prototype in `parsing.h`.
- `lib/parsing/parse_utils.c`: `check_player` now stores `player_x`/`player_y` (cells) instead of writing `player.pos`.
- `Makefile`: rewritten — binary `cub3D`, `OBJ_DIR`/`NAME` overridable, objects in `obj/`, no relink, `SRC_ENGINE` / `SRC_PARSING` lists, `-std=gnu99` (mlx.h uses old-style `int (*)()` prototypes that break under C23), MLX built through `Makefile.mk`.

## Engine (ENGINE agent)

All engine files were rewritten to the 42 Norm (42 header `sofus`, tabs, no comments, no ternaries, <= 25 lines / 5 vars / 4 params / 5 functions). norminette: OK on every engine file.

### Headers

- `game.h` (rewritten): guard `GAME_H`. `t_image` moved here (from `graphic.h`). New structs `t_player` (pos, dir, plane in cell units), `t_ray`, `t_hit` (dist, wall_x, side, step_x, step_y), `t_column`. `t_game`: `t_image buffer` (was a malloc'd pointer), `t_image tex[4]`, `int keys[KEY_COUNT]` (was `key_release[65536]`), `last_time`, `floor_color`, `ceil_color`. Defines `K_W..K_RIGHT`, `TEX_NO/SO/WE/EA`. Parsing fields unchanged (same names and types).
- `cub3d.h` (rewritten): guard `CUB3D_H`, includes `<X11/keysym.h>`, `<sys/time.h>`, `mlx.h`, `libft.h`, `game.h`, `parsing.h`. Defines WIDTH 1024, HEIGHT 768, MOVE_SPEED, ROT_SPEED, MARGIN, PLANE_LEN, MAX_DT. Removed CELL_SIZE, PLAYER_SIZE, AZERTY key defines, FRICTION, FOV, NB_RAY, COLOR_1, DEBUG. All engine prototypes live here.
- `lib/vector/vector2.h` (rewritten): `t_vector2` kept, `t_vec2` alias removed, only `v_rotate` declared.
- Deleted: `lib/graphics/graphic.h`, `lib/object/player.h`, `lib/key_handling/key_handling.h`, `lib/collision/clipping.h` (prototypes moved into `cub3d.h`, which avoids the circular include tangle).

### Sources

- `main.c` (rewritten): `main` checks argc == 2 (prints "Error\nUsage..." and returns 1), `ft_bzero`s the game, calls `init_map` before any mlx call, converts floor/ceiling colors, then `init_mlx` (mlx_init, window, image buffer), `load_textures`, `init_player`, `init_hooks` (KeyPress, KeyRelease, DestroyNotify 17 = red cross, loop hook), `mlx_loop`. Old `loop` / `init_game` (2D debug view, malloc'd map / vision) removed.
- `lib/exit/exit.c` (new): `destroy_images` (static), `clean_exit(t_game *, int)` (destroys textures, buffer, window, display, frees mlx, `free_parsing`, `exit`), `engine_error(t_game *, char *)` ("Error\n<msg>\n" on stderr + clean_exit(1)), `close_window` (red cross hook).
- `lib/graphics/image_manip.c` (rewritten): `put_pixel` (bounds-checked), `tex_pixel` (clamped texel read), `rgb_to_int`. Removed `t_new_image`, `my_mlx_pixel_put`, `my_mlx_pixel_get`, `clean_buffer`.
- `lib/graphics/texture.c` (new): `texture_error` (static), `load_texture` (static, mlx_xpm_file_to_image + mlx_get_data_addr, error + clean exit on failure), `load_textures`.
- `lib/graphics/shapes.c`: deleted (`draw_line`, `dis_rec` were only used for the 2D debug view).
- `lib/key_handling/key_handling.c` (rewritten): `key_index` (static, maps XK_w/s/a/d/Left/Right to an index or -1), `key_press` (ESC -> clean_exit(0), sets flag), `key_release`. Removed `event_on_keys` (movement moved to `update_player`). Keys are QWERTY now (were AZERTY z/q/s/d).
- `lib/object/player.c` (rewritten): `set_vectors` (static), `init_player` (pos = cell + 0.5, dir from N/S/E/W, plane = right vector * 0.66), `rotate_player` (static, rotates dir and plane), `update_player(t_game *, double dt)` (W/S forward/back, A/D strafe, arrows rotate, frame-time based). Removed `update_player` velocity/friction version, `cast_all_rays`, `display_player`, vision[].
- `lib/collision/clipping.c` (rewritten): `is_wall` (out of bounds or map != 0 -> wall, bounds from map_width/map_height), `is_blocked` (static, 4 corners of a MARGIN box), `move_player` (per-axis move so the player slides along walls). Removed `wall_on`, `set_clipping`, `display_clip`, `is_clipping`.
- `lib/object/raycast.c` (rewritten): DDA in cell units, `init_ray` now builds the ray from dir + plane * camera_x, `run_dda` uses `is_wall` (dynamic map bounds), `cast_ray(t_game *, int x)` returns `t_hit` (perpendicular distance, side, step, wall_x). No more WIDTH/HEIGHT/CELL_SIZE map bounds.
- `lib/render/render.c` (new): `pick_texture` (static), `compute_tex_x` (static), `setup_column` (static), `draw_column` (static), `render_frame`. Per screen column: ceiling color, textured wall slice, floor color.
- `lib/render/loop.c` (new): `get_time_us` (gettimeofday), `game_loop` (dt clamp, update_player, render_frame, one mlx_put_image_to_window per frame).
- `lib/vector/vector2.c` (rewritten): `v_rotate`. Removed `v_add`, `v_mul_scal`, `v_dist` (unused).

### Texture / side mapping

- Ray going north (side 1, step_y < 0) -> NO texture; south (side 1, step_y > 0) -> SO; east (side 0, step_x > 0) -> EA; west (side 0, step_x < 0) -> WE. So looking north you see the NO texture.
- texture x is flipped for side 0 with step_x < 0 and side 1 with step_y > 0 so no wall is mirrored (verified with screenshots: letters N/S/E and the top-left marker read correctly).

### Textures

- `textures/north.xpm`, `south.xpm`, `west.xpm`, `east.xpm` (new): 64x64 XPM3, 4 colors each. North = red bricks + "N", south = blue horizontal stripes + "S", west = green vertical stripes + "W", east = yellow checker + "E"; each has a white square in the top-left corner to check orientation. Generated by a script in the scratchpad (not in the repo).

### Makefile

- Only `SRC_ENGINE` edited: removed `lib/graphics/shapes.c`, added `lib/exit/exit.c`, `lib/graphics/texture.c`, `lib/render/loop.c`, `lib/render/render.c`.

# Parsing changes (lib/parsing, SRC_PARSING in Makefile)

Design: parse functions return an error string (NULL on success) instead of exiting, so parse_file can close the fd, drain gnl and free the line before error_exit(game, msg) prints "Error\n<msg>\n" on stderr, calls free_parsing and exit(1).
Colour format choice: "R,G,B", exactly 2 commas, spaces around each number allowed ("220, 100, 0"), each number 1-3 digits, 0-255 (leading zeros accepted, no sign).
Whitespace-only lines before the map are ignored; inside the map they count as empty lines (end of map, only blank lines may follow). Identifier lines may have leading spaces; separators are spaces only (no tabs). Texture paths cannot contain spaces.

- init.c: rewritten. init_map = init_defaults + .cub extension check + parse_file + build_map_grid. build_map_grid now allocates [map_height][map_width] with ft_calloc (1 = wall/space/padding, 0 = '0' or player), no HEIGHT/CELL_SIZE, no libc calloc, errors through error_exit(game, ...).
- parse_file.c (new): parse_file (open, read-error check for directories, read loop that keeps draining gnl after an error, close, then validation) and validate.
- parse_line.c (new, replaces old parse_line in parse_utils.c): line state machine (blank lines, identifiers, map start only after the 6 identifiers, empty line inside map, content after map), is_map_line, all_ids_found.
- parse_texture.c (new): NO/SO/WE/EA parsing; duplicate, missing path, extra tokens, file must open and be readable (open/read 0/close). No leaks on duplicate.
- parse_utils.c: now colour parsing only (strict, overflow-safe via 3-digit limit, split always freed). Removed debug printf.
- parse_map.c: add_map_line (ft_calloc'd array, no leak on failure, tracks map_width, \n/\r stripped before), find_player (exactly one), is_player. Removed debug printf.
- parse_walls.c (new): closed-map check using ft_strlen bounds on every neighbour row (no read past short rows).
- parse_check.c (new): has_cub_extension, check_identifiers (missing messages), validate_map (map exists, player, walls).
- utils.c: error_exit(game, msg) to stderr + free_parsing; free_split; is_number (1-3 digits); skip_spaces; strip_eol (\n and optional \r).
- find_char.c (new): find_char helper, because libft/Includes declares ft_strchr but libft has no implementation (link error). Libft owner could add ft_strchr.
- free.c: added 42 header; frees textures, map_lines, map (map_height rows), NULL-safe.
- includes/parsing.h: norm-style guards, new prototypes, includes game.h directly (not cub3d.h, which includes parsing.h circularly and broke t_game ordering).
- gnl/*: functions renamed gnl_* to stop clashing with libft ft_strlen/ft_strjoin/ft_strrchr (different semantics), header made standalone and norm-compliant, malloc-failure leaks fixed (stash freed), stash freed when empty.
- Makefile: SRC_PARSING list updated only.

# Build / docs / tests changes

## Makefile (top level; SRC_ENGINE / SRC_PARSING blocks untouched)

- Root cause of the MLX "Error 2": the parent's command-line `NAME=cub3D` (and `OBJ_DIR`) are
  inherited by the MLX sub-make through MAKEFLAGS. `lib/mlx_linux/Makefile.mk` then builds an
  archive called `cub3D` instead of `libmlx.a`, so the `$(MLX)` target is never produced and
  make fails. The same leak hits `libft/Makefile` (`NAME = libft.a`).
- `MLX_FLAGS` replaced by `MLX_MAKE`, which passes `NAME=libmlx.a OBJ_DIR=obj` explicitly
  (explicit sub-make arguments override the inherited ones; verified). `-f Makefile.mk`,
  `INC` and `CFLAGS` are kept as before.
- Removed the `libs` phony target and the `> /dev/null 2>&1` that hid MLX errors. Sub-libraries
  are now file rules `$(LIBFT): FORCE` and `$(MLX): FORCE`: their own Makefiles decide what to
  rebuild, and `$(NAME)` only relinks when an archive's mtime changes (no unnecessary relink).
- libft is always called with `NAME=libft.a` (for build, clean and fclean).
- `clean`: removes objects and libft objects. `fclean`: also removes `$(NAME)`, libft archive,
  and MLX objects/archives (`$(MLX_MAKE) clean`).
- `all` is now `all: $(NAME)`; `.PHONY` updated (`libs` removed, `FORCE` added).
- Verified in a scratch copy: `make fclean; make` builds everything; a second `make` prints
  nothing (no relink); `make re`, `make clean`, `make NAME=cub3D_x` work. The link of the
  current tree fails only because of undefined symbols from the PARSING agent's in-progress code.

## .gitignore (new)

- Ignores `obj/`, `.obj_*/`, `*.o`, `*.d`, `*.a`, `cub3D`, `cub3D_*`, the MLX generated files
  (`lib/mlx_linux/obj/`, `Makefile.gen`, `test/makefile.gen`, `test/mlx-test`) and `*.tgz`.
  `changes/` is not ignored.
- `git ls-files` contains no artifacts, so nothing was untracked with `git rm --cached`.
  Note: `lib/mlx_linux/` as a whole is untracked (`??`), so a fresh clone does not contain the
  MLX sources yet. That is a git-staging decision, not done here.

## Accidental side effect (fixed)

- While debugging, a few MLX sub-make commands were run in the real tree by mistake
  (`lib/mlx_linux/`). They created `lib/mlx_linux/cub3D` and `lib/mlx_linux/.obj_build/`, and
  re-created `libmlx_Linux.a` (content identical to `libmlx.a`). The first two were removed; the
  copy is the same as before.

## README.md (new)

- Root README in English. First line is the italic 42 line with `cascrizz, rueapen` (to be
  confirmed by the team). Sections: Description (raycasting/DDA, goal, features), Instructions
  (dependencies, make targets, NAME override, execution, controls, `.cub` format with example
  and error behavior, tests), Resources (lodev, 42 MiniLibX docs, Permadi, Wolfenstein 3D) with
  the AI usage paragraph.

## maps/valid/ (new, 10 files)

- subject_example.cub (subject example, textures replaced by ./textures/*.xpm), minimal.cub,
  spaces_in_map.cub, order_shuffled.cub (shuffled identifiers, extra spaces, multiple empty
  lines), trailing_newlines.cub, each_direction_{N,S,E,W}.cub, big.cub (60x40, closed).

## maps/invalid/ (new, 25 files, one error each)

- open_map_top, open_map_side, open_map_space_hole, no_player, two_players, bad_char,
  missing_NO, missing_C, duplicate_SO, duplicate_F, unknown_identifier, color_out_of_range,
  color_negative, color_letters, color_too_few, color_too_many, color_trailing_comma,
  map_not_last, empty_line_in_map, empty_file, only_identifiers, texture_missing_path,
  texture_nonexistent_file, wrong_extension.txt, map.cub.txt. Directory and non-existent
  file cases are created/handled in tests/run_tests.sh (no files needed).
- Generated with a scratchpad script (not part of the project).

## tests/run_tests.sh (new, executable)

- Usage `tests/run_tests.sh [binary]` (default ./cub3D), builds nothing. Invalid maps and
  argument cases run under valgrind (exit != 0 and != 42, first line "Error"); valid maps run
  under `timeout 3 valgrind` (exit 124, no "Invalid read/write"). PASS/FAIL table + summary,
  exit 1 on any FAIL.
- Added `CUB3D_NO_VALGRIND=1` (opt-in): runs without valgrind, memory check reported as
  "skipped". Needed because valgrind 3.25 cannot start on this machine (see report).
- Temporary directory via mktemp, removed on exit.

## Final integration (main session)

- `libft/Includes/libft.h`: removed the `ft_strchr` prototype (declared but never implemented; parsing uses its own `find_char.c`).
- Verified: `make fclean && make` builds with `-Wall -Wextra -Werror`, second `make` does not relink.
- Verified: norminette OK on main.c, cub3d.h, game.h, lib/** (except mlx_linux) and libft.
- Verified: `tests/run_tests.sh` with an AddressSanitizer/UBSan build: 38/39 pass (all invalid maps, arg cases, valid maps). Only failure: `maps/valid/subject_example.cub` (see open decision below).
- Removed agent build leftovers (`.obj_*`, `cub3D_*`).

## Follow-up (2026-10-11)

- `lib/mlx_linux/.github/`: restored from `minilibx-linux.tgz` (it had been deleted during the foundation step). `lib/mlx_linux` sources are identical to the tarball; only build outputs (`obj/`, `libmlx*.a`, `Makefile.gen`) differ.
- 42 headers of the 26 files written this session: login changed from `sofus` to `cascrizz` (engine files, headers) and `rueapen` (`lib/parsing/**`). README logins confirmed: `cascrizz, rueapen`.
- `lib/collision/clipping.c`, `lib/exit/exit.c`: had been reformatted to clang-format style (2 spaces, brace on the same line) after the norm check; re-indented to the Norm, code unchanged.
- Verified again: norminette OK everywhere, build OK, tests 38/39.

## Open decisions

- `subject_example.cub`: the subject's own example has floor cells that touch the void but are unreachable from the player; the strict wall check rejects it.
- `lib/mlx_linux/` is untracked: run `git add lib/mlx_linux` before committing or a fresh clone won't build.
