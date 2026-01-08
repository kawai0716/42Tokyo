# Variable Expansion Crash Investigation - 2025-07-05

## Problem
The command `echo $TEST ; exit` causes a segmentation fault/invalid free error when `$TEST` is undefined or empty.

## Root Cause
The crash is caused by an inconsistency in how empty WORD tokens are handled during parsing:

1. **Variable Expansion**: When `$TEST` is undefined, `expand_variable()` in `src/lexer3.c` returns an empty string (`ft_strdup("")`)
2. **Token Creation**: This creates a WORD token with an empty value
3. **Counting Mismatch**:
   - `count_words()` in `src/parse_command.c` skips empty WORD tokens (line 35: `current->value[0] != '\0'`)
   - `process_token()` in `src/parse_command.c` processes empty WORD tokens differently (line 76-77)
4. **Memory Corruption**: The argv array is allocated based on `count_words()` but filled by `process_token()`, causing array bounds issues

## Code Analysis

### In `src/parse_command.c`:
```c
// count_words skips empty tokens
if (current->type == WORD && current->value && current->value[0] != '\0')
{
    count++;
    current = current->next;
}

// But process_token handles them differently
else if ((*tokens)->type == WORD)
    *tokens = (*tokens)->next;  // Just advances without adding to argv
```

This causes the argv array to have incorrect indexing when empty tokens are present.

## Additional Findings
- The shell doesn't support semicolons (`;`) as command separators
- Semicolons are treated as regular word characters, not metacharacters
- The command `echo $TEST ; exit` is interpreted as echo with arguments "; exit"

## Recommended Fix
1. Make `count_words()` and `process_token()` consistent in handling empty WORD tokens
2. Either:
   - Skip empty tokens in both functions, or
   - Count and process them in both functions
3. Consider adding semicolon support as a command separator (bonus feature)

## Test Case
```bash
# This crashes:
echo $UNDEFINED_VAR ; exit

# This works:
echo hello ; exit  # But treats "; exit" as arguments to echo
```