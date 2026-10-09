# Empty Variable Expansion Fix Analysis
**Date**: 2025-07-19
**Author**: Claude (AI Assistant)

## Problem Analysis
The minishell is incorrectly handling empty variable expansions:
- `echo $TEST $TEST` outputs " " (space) but should output nothing
- `echo    $TEST lol $TEST` outputs " lol" but should output "lol"

## Root Cause
In bash, unquoted empty variable expansions are completely removed during word splitting, not just replaced with empty strings. Our implementation:
1. Lexer expands `$TEST` to empty string ""
2. Creates separate tokens for each word
3. Parser builds argv from these tokens, including empty strings

## Attempted Solutions
1. **Modified token structure** - Added quoted field to track context (reverted due to complexity)
2. **Modified skip_empty_strings** - Removed ALL empty strings (broke quoted empty strings)
3. **Problem**: Cannot distinguish between:
   - `echo "" test` → should keep empty string
   - `echo $EMPTY test` → should remove empty string

## Current Architecture Limitation
The lexer performs variable expansion during tokenization, before the parser runs. This makes it impossible to distinguish between:
- Empty strings from quotes (should be preserved)
- Empty strings from unquoted variable expansion (should be removed)

## Possible Solutions
1. **Defer variable expansion** - Move expansion to parser or executor phase
2. **Track expansion context** - Add metadata to tokens about their origin
3. **Implement proper word splitting** - After variable expansion, re-split words based on IFS

## Next Steps
The issue requires architectural changes to properly implement bash-compatible word splitting.