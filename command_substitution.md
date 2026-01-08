# Command Substitution and Pipes

This note explains the difference between two similar-looking commands.

## Examples

```sh
echo `ls` | grep 42
```

- `ls` runs first and its output is substituted into `echo`.
- `echo` prints the list as a single line (newlines are turned into spaces).
- The pipe to `grep 42` happens **after** `echo`, so `grep` sees one long line.
- `grep` is writing to the terminal here, so it may color matches.

```sh
echo `ls | grep 42`
```

- The pipe is **inside** command substitution.
- `ls | grep 42` runs first and filters the list.
- The filtered result is substituted into `echo` and printed as one line.
- `grep` output is captured by the shell, so it is not writing to a terminal
  and usually does not color matches.

## Recommended form

Use `$(...)` instead of backticks for readability:

```sh
echo "$(ls | grep 42)"
```

If you only want the filtered list, just use:

```sh
ls | grep 42
```
