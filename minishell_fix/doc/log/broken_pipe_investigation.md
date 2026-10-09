# Broken Pipe Investigation - Test 70 and 123

## Date: 2025-07-05

## Summary

The minishell_tester shows warning (⚠️) on tests 70 and 71 because minishell doesn't report "Broken pipe" errors like bash does when SIGPIPE occurs in pipelines.

## Test Details

### Test 70 (Line 70 in all tests)
```bash
echo <"./test_files/infile_big" | echo <"./test_files/infile"
```

### Test 71
```bash
echo hi | cat <"./test_files/infile"
```

### Test 123 (Initially mentioned but actually different)
```bash
echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02
```

## Issue Analysis

### What Happens

1. In a pipeline like `echo hi | cat <file`:
   - The first `echo hi` tries to write "hi\n" to the pipe
   - The second command (`cat <file`) reads from file, not from stdin (the pipe)
   - Since no one is reading from the pipe, the first echo gets SIGPIPE
   - When SIGPIPE is trapped (with `trap "" PIPE`), bash's echo reports: "bash: line 1: echo: write error: Broken pipe"
   - Minishell's echo doesn't report this error

2. The tester detects this by:
   - Running commands with `trap "" PIPE` to prevent SIGPIPE from terminating the process
   - Capturing stderr and extracting error messages
   - Comparing bash and minishell error outputs
   - Showing ⚠️ when outputs match but error messages differ

### Root Cause

1. **Minishell's echo builtin** (`src/builtin/builtin_echo.c`):
   - Uses `ft_putstr_fd()` and `ft_putchar_fd()` to write output
   - These functions don't check the return value of `write()`
   - When write() fails due to SIGPIPE, no error is reported

2. **Bash's behavior**:
   - Bash's echo builtin checks for write errors
   - When write() returns -1 with errno=EPIPE, it prints "write error: Broken pipe" to stderr

3. **Signal handling**:
   - Minishell only handles SIGINT and SIGQUIT (in `src/signal.c`)
   - SIGPIPE is not explicitly handled, so it uses default behavior

## Test Results

Running the tester shows:
- Test 70: ✅⚠️ (passes but with warning about different error messages)
- Test 71: ✅⚠️ (same issue)
- Test 123: ✅ (no warning - this test has different behavior)

The warning appears because:
- Bash error message: "Broken pipe"
- Minishell error message: (empty)

## Recommendation

To fix this issue and achieve 100% compatibility:

1. Modify `ft_putstr_fd()` and `ft_putchar_fd()` to check write() return value
2. In echo builtin, detect write errors and report them to stderr
3. Specifically handle EPIPE errors with the message "write error: Broken pipe"

This is a minor compatibility issue that doesn't affect functionality but shows up in the tester's strict error message comparison.