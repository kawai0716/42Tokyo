# Redirection Segfault Fix

## Issue
The minishell was segfaulting when processing commands with redirections like `grep hi <./test_files/infile`. The segfault occurred in the `count_words()` function during command parsing.

## Root Cause
In `src/parse_command.c`, the `count_words()` function had a logic error where it was advancing the `current` pointer twice in some cases:

1. When encountering a redirection token, it would advance `current` to check for the filename
2. If a filename was found, it would advance `current` again  
3. Then at the end of the loop, it would unconditionally advance `current` once more with `current = current->next;`

This caused a NULL pointer dereference when `current` was already NULL after processing the last token.

## Fix Applied
Modified the `count_words()` function to only advance the pointer within each conditional branch, removing the unconditional advance at the end of the loop:

```c
// Before (problematic):
while (current)
{
    if (current->type == WORD ...)
        count++;
    else if (is_redirection(current->type))
    {
        current = current->next;
        if (current && current->type == WORD)
            current = current->next;
        else
            break;
    }
    else
        break;
    current = current->next;  // This line caused the segfault
}

// After (fixed):
while (current)
{
    if (current->type == WORD ...)
    {
        count++;
        current = current->next;
    }
    else if (is_redirection(current->type))
    {
        current = current->next;
        if (current && current->type == WORD)
            current = current->next;
    }
    else
        break;
}
```

## Testing
Verified the fix with various redirection commands:
- `grep hi <./test_files/infile` - Works correctly
- `echo hello >output.txt` - Works correctly  
- `ls >file1 >file2` - Works correctly (multiple redirections)
- `cat <output.txt` - Works correctly

All tests pass without segfaults and produce expected output.

## Impact
This was a critical bug introduced in commit cb66a67 when the code was refactored to comply with 42 norm standards. The fix ensures proper handling of all redirection scenarios without causing memory access violations.