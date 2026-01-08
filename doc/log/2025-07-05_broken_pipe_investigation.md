# Broken Pipe Investigation - Test Case 70

**Date**: 2025-07-05
**Issue**: Test case 70 (`echo <"./test_files/infile_big" | echo <"./test_files/infile"`) - bash reports "Broken pipe" but minishell doesn't

## Summary

The issue involves SIGPIPE signal handling and how echo behaves in pipelines when it has input redirection.

## Key Findings

### 1. Understanding the Test Case

The command `echo <file1 | echo <file2` creates a pipeline where:
- First `echo` has input redirection from file1 (but echo ignores stdin)
- Second `echo` has input redirection from file2 (also ignores stdin)
- Neither echo reads from the pipe, causing a broken pipe condition

### 2. SIGPIPE Behavior

When bash runs with `trap "" PIPE` (SIGPIPE ignored):
```bash
$ bash -c 'trap "" PIPE; echo <file1 | echo <file2'
bash: line 1: echo: write error: Broken pipe
```

The first echo attempts to write to stdout (the pipe), but since the second echo never reads from stdin, the pipe breaks and write() returns EPIPE error.

### 3. Minishell's Current Behavior

Minishell doesn't report the "Broken pipe" error in the same situation. Investigation shows:

1. **Echo implementation** (`src/builtin/builtin_echo.c`):
   - DOES check for write errors
   - DOES print "echo: write error: Broken pipe" when write() fails
   - Implementation is correct

2. **Signal handling** (`src/signal.c`):
   - Only handles SIGINT and SIGQUIT
   - Does NOT explicitly handle SIGPIPE
   - No signal(SIGPIPE, SIG_IGN) found in codebase

### 4. Root Cause Analysis

The issue appears to be that:
1. The readline library or some other initialization might be setting SIGPIPE to SIG_IGN
2. Child processes inherit this signal disposition
3. When SIGPIPE is ignored, processes get EPIPE error instead of being terminated

However, minishell's echo builtin should still detect the write error and report it.

### 5. Test Results

Created test programs to verify:
- C program simulating the pipeline behavior confirms EPIPE error occurs
- Bash with trapped SIGPIPE consistently reports the error
- Minishell doesn't report the error despite having error checking code

## Possible Solutions

1. **Ensure SIGPIPE is not ignored in child processes**:
   - Add `signal(SIGPIPE, SIG_DFL)` in child processes after fork
   - This would match bash behavior

2. **Debug why echo's write error checking isn't triggering**:
   - Add debug output to verify write() is actually failing
   - Check if the error path is being reached

3. **Verify readline isn't setting SIGPIPE to SIG_IGN**:
   - Some readline versions might ignore SIGPIPE
   - Check signal disposition at startup

## Recommendation

The most likely fix is to ensure SIGPIPE has default behavior in child processes. This can be done by adding `signal(SIGPIPE, SIG_DFL)` after fork() in the command execution code.

## Test Commands Used

```bash
# Test with bash (shows error)
bash -c 'trap "" PIPE; echo <"./test_files/infile_big" | echo <"./test_files/infile"'

# Test with minishell (no error shown)
echo 'echo <"minishell_tester/test_files/infile_big" | echo <"minishell_tester/test_files/infile"' | ./minishell
```

## Files Examined

- `src/builtin/builtin_echo.c` - Echo implementation (has error checking)
- `src/signal.c` - Signal handling (no SIGPIPE handling)
- `src/executor/ex_pipeline.c` - Pipeline execution
- Test files created for investigation