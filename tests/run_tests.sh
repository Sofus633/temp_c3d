#!/bin/bash
# cub3D test runner.
#
# Usage: tests/run_tests.sh [path/to/cub3D]   (default: ./cub3D)
#
# Builds nothing. Runs:
#   - every maps/invalid/* file, plus: no argument, two arguments, a directory,
#     a non-existent file. PASS if the program exits with a non-zero code other
#     than valgrind's 42 (memory error) and its first output line is exactly "Error".
#   - every maps/valid/* file under valgrind for 3 seconds (the program opens a
#     window, so $DISPLAY is required). PASS if it is killed by timeout (exit 124)
#     and valgrind reported no invalid read or write.
# CUB3D_NO_VALGRIND=1 skips valgrind (the memory checks), for machines where it cannot run.
# Exit status: 0 if every test passed, 1 otherwise.

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)" || exit 1

BIN_ARG="${1:-./cub3D}"
if [ ! -x "$BIN_ARG" ]; then
	echo "Error: '$BIN_ARG' is not an executable file (build it first, e.g. make)." >&2
	exit 1
fi
BIN="$(realpath "$BIN_ARG")"

cd "$ROOT_DIR" || exit 1

WORK_DIR="$(mktemp -d)" || exit 1
trap 'rm -rf -- "$WORK_DIR"' EXIT
mkdir -p "$WORK_DIR/dir.cub"

VALGRIND_OPTS=(--leak-check=full --errors-for-leak-kinds=definite,indirect --error-exitcode=42 -q)

# CUB3D_NO_VALGRIND=1 runs the binary directly (no memory checks), for machines
# where valgrind cannot start. Without it, valgrind is required.
if [ "${CUB3D_NO_VALGRIND:-0}" = "1" ]; then
	RUNNER=()
	MEMCHECK="skipped"
	echo "Note: CUB3D_NO_VALGRIND=1, running without valgrind (memory checks skipped)."
else
	RUNNER=(valgrind "${VALGRIND_OPTS[@]}")
	MEMCHECK="checked"
	if ! valgrind -q /bin/true > /dev/null 2>&1; then
		echo "Warning: valgrind cannot start on this system, so every case will fail." >&2
		echo "         Fix the valgrind install or run with CUB3D_NO_VALGRIND=1." >&2
	fi
fi

pass_count=0
fail_count=0

print_header()
{
	printf '%-6s  %-8s  %-40s  %s\n' "RESULT" "CATEGORY" "CASE" "DETAIL"
	printf '%-6s  %-8s  %-40s  %s\n' "------" "--------" "----------------------------------------" "------"
}

record()
{
	# record RESULT CATEGORY CASE DETAIL
	printf '%-6s  %-8s  %-40s  %s\n' "$1" "$2" "$3" "$4"
	if [ "$1" = "PASS" ]; then
		pass_count=$((pass_count + 1))
	else
		fail_count=$((fail_count + 1))
	fi
}

# check_error_case CATEGORY CASE_NAME ARGS...
# Runs the binary under valgrind with the given arguments and expects an error.
check_error_case()
{
	local category="$1" name="$2" out rc first
	shift 2
	out="$WORK_DIR/out.txt"
	"${RUNNER[@]}" "$BIN" "$@" > "$out" 2>&1
	rc=$?
	first="$(head -n 1 "$out")"
	if [ "$rc" -ne 0 ] && [ "$rc" -ne 42 ] && [ "$first" = "Error" ]; then
		record PASS "$category" "$name" "exit=$rc"
	else
		record FAIL "$category" "$name" "exit=$rc first_line='$first'"
	fi
}

# check_valid_case MAP
# Runs the binary on a valid map for 3 seconds under valgrind.
check_valid_case()
{
	local map="$1" name out rc invalid
	name="$(basename "$map")"
	out="$WORK_DIR/out.txt"
	timeout 3 "${RUNNER[@]}" "$BIN" "$map" > "$out" 2>&1
	rc=$?
	if grep -q -E "Invalid (read|write)" "$out"; then
		invalid="invalid read/write"
	else
		invalid="no invalid access ($MEMCHECK)"
	fi
	if [ "$rc" -eq 124 ] && ! grep -q -E "Invalid (read|write)" "$out"; then
		record PASS valid "$name" "timeout, $invalid"
	else
		record FAIL valid "$name" "exit=$rc, $invalid"
	fi
}

print_header

for file in maps/invalid/*; do
	[ -f "$file" ] || continue
	check_error_case invalid "$(basename "$file")" "$file"
done

check_error_case args "no_arguments"
check_error_case args "two_arguments" maps/valid/minimal.cub maps/valid/minimal.cub
check_error_case args "directory" "$WORK_DIR/dir.cub"
check_error_case args "nonexistent_file" tests/does_not_exist.cub

for file in maps/valid/*; do
	[ -f "$file" ] || continue
	check_valid_case "$file"
done

echo
echo "Summary: $pass_count passed, $fail_count failed, $((pass_count + fail_count)) total"

if [ "$fail_count" -ne 0 ]; then
	exit 1
fi
exit 0
