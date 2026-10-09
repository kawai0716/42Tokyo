# ディレクトリ操作関数

## getcwd

### プロトタイプ
```c
char *getcwd(char *buf, size_t size);
```

### ヘッダファイル
```c
#include <unistd.h>
```

### 説明
現在の作業ディレクトリの絶対パスを取得します。

### パラメータ
- `buf`: パスを格納するバッファ（NULLも可）
- `size`: バッファのサイズ

### 戻り値
- 成功時: bufのポインタ（bufがNULLの場合はmalloc()された文字列）
- 失敗時: NULL

### Minishellでの使用例

#### pwdコマンドの実装
```c
// src/builtin/builtin_pwd.c
int builtin_pwd(char **argv, t_shell *shell)
{
    char    *cwd;
    
    (void)argv;  // 引数は使用しない
    
    // カレントディレクトリを取得
    cwd = getcwd(NULL, 0);  // 自動的にメモリ割り当て
    if (!cwd)
    {
        perror("pwd");
        return (1);
    }
    
    // パスを出力
    ft_putendl_fd(cwd, STDOUT_FILENO);
    
    // メモリ解放
    free(cwd);
    
    return (0);
}
```

#### プロンプトでの使用（拡張例）
```c
// src/shell/prompt.c
char *get_prompt(t_shell *shell)
{
    char    cwd[PATH_MAX];
    char    *prompt;
    char    *home;
    
    // カレントディレクトリ取得
    if (!getcwd(cwd, sizeof(cwd)))
        strcpy(cwd, "?");
    
    // ホームディレクトリを~に置換
    home = get_env_value(shell->env_list, "HOME");
    if (home && strncmp(cwd, home, strlen(home)) == 0)
    {
        prompt = malloc(strlen(cwd) - strlen(home) + 3);
        sprintf(prompt, "~%s$ ", cwd + strlen(home));
    }
    else
    {
        prompt = malloc(strlen(cwd) + 3);
        sprintf(prompt, "%s$ ", cwd);
    }
    
    return (prompt);
}
```

### 注意点
- **バッファサイズ**: PATH_MAX（通常4096）を使用
- **NULL渡し**: `getcwd(NULL, 0)`で自動割り当て（GNU拡張）
- **メモリ管理**: NULL渡しの場合は返り値をfree()する

---

## chdir

### プロトタイプ
```c
int chdir(const char *path);
```

### ヘッダファイル
```c
#include <unistd.h>
```

### 説明
現在の作業ディレクトリを変更します。

### パラメータ
- `path`: 移動先のディレクトリパス

### 戻り値
- 成功時: 0
- 失敗時: -1（errnoが設定される）

### Minishellでの使用例

#### cdコマンドの実装
```c
// src/builtin/builtin_cd.c
int builtin_cd(char **argv, t_shell *shell)
{
    char    *path;
    char    *oldpwd;
    
    // 引数なしの場合はHOMEへ
    if (!argv[1])
    {
        path = get_env_value(shell->env_list, "HOME");
        if (!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return (1);
        }
    }
    else if (strcmp(argv[1], "-") == 0)
    {
        // cd - の場合はOLDPWDへ
        path = get_env_value(shell->env_list, "OLDPWD");
        if (!path)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
            return (1);
        }
        ft_putendl_fd(path, STDOUT_FILENO);
    }
    else
    {
        path = argv[1];
    }
    
    // 現在のディレクトリを保存
    oldpwd = getcwd(NULL, 0);
    
    // ディレクトリ変更
    if (chdir(path) == -1)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        perror(path);
        free(oldpwd);
        return (1);
    }
    
    // 環境変数を更新
    if (oldpwd)
    {
        set_env_value(&shell->env_list, "OLDPWD", oldpwd);
        free(oldpwd);
    }
    
    char *newpwd = getcwd(NULL, 0);
    if (newpwd)
    {
        set_env_value(&shell->env_list, "PWD", newpwd);
        free(newpwd);
    }
    
    return (0);
}
```

#### エラー処理の詳細
```c
// src/builtin/builtin_cd_utils.c
int handle_cd_error(const char *path)
{
    struct stat statbuf;
    
    if (stat(path, &statbuf) == -1)
    {
        if (errno == ENOENT)
            ft_putstr_fd("No such file or directory\n", 2);
        else if (errno == EACCES)
            ft_putstr_fd("Permission denied\n", 2);
    }
    else if (!S_ISDIR(statbuf.st_mode))
    {
        ft_putstr_fd("Not a directory\n", 2);
    }
    else
    {
        perror(path);
    }
    
    return (1);
}
```

### エラーコード
| errno | 意味 |
|-------|------|
| ENOENT | ディレクトリが存在しない |
| EACCES | アクセス権限がない |
| ENOTDIR | ディレクトリではない |
| ENAMETOOLONG | パス名が長すぎる |

---

## opendir

### プロトタイプ
```c
DIR *opendir(const char *name);
```

### ヘッダファイル
```c
#include <dirent.h>
```

### 説明
ディレクトリストリームを開きます。

### パラメータ
- `name`: 開くディレクトリのパス

### 戻り値
- 成功時: DIRポインタ
- 失敗時: NULL

### Minishellでの使用例

#### ワイルドカード展開
```c
// src/utils/wildcard.c
char **expand_wildcard(const char *pattern)
{
    DIR             *dir;
    struct dirent   *entry;
    char            **matches;
    int             count = 0;
    
    // カレントディレクトリを開く
    dir = opendir(".");
    if (!dir)
        return (NULL);
    
    // マッチするファイルを数える
    while ((entry = readdir(dir)))
    {
        if (match_pattern(entry->d_name, pattern))
            count++;
    }
    
    if (count == 0)
    {
        closedir(dir);
        return (NULL);
    }
    
    // 結果配列を割り当て
    matches = malloc(sizeof(char *) * (count + 1));
    
    // ディレクトリを再度読む
    rewinddir(dir);
    int i = 0;
    while ((entry = readdir(dir)))
    {
        if (match_pattern(entry->d_name, pattern))
            matches[i++] = ft_strdup(entry->d_name);
    }
    matches[i] = NULL;
    
    closedir(dir);
    return (matches);
}
```

---

## readdir

### プロトタイプ
```c
struct dirent *readdir(DIR *dirp);
```

### ヘッダファイル
```c
#include <dirent.h>
```

### 説明
ディレクトリストリームから次のエントリを読み込みます。

### パラメータ
- `dirp`: ディレクトリストリーム

### 戻り値
- 成功時: dirent構造体へのポインタ
- ストリーム終端またはエラー: NULL

### dirent構造体
```c
struct dirent {
    ino_t          d_ino;       // inode番号
    off_t          d_off;       // オフセット
    unsigned short d_reclen;    // レコード長
    unsigned char  d_type;      // ファイルタイプ
    char           d_name[256]; // ファイル名
};
```

### Minishellでの使用例

#### ワイルドカードマッチング
```c
// src/utils/wildcard_match.c
int match_wildcard(const char *pattern, const char *str)
{
    // * は0文字以上の任意の文字列にマッチ
    // ? は任意の1文字にマッチ
    
    while (*pattern && *str)
    {
        if (*pattern == '*')
        {
            // * の処理
            pattern++;
            if (!*pattern)
                return (1);  // 末尾の*は全てにマッチ
            
            // 次のパターンを探す
            while (*str)
            {
                if (match_wildcard(pattern, str))
                    return (1);
                str++;
            }
            return (0);
        }
        else if (*pattern == '?')
        {
            // ? は任意の1文字
            pattern++;
            str++;
        }
        else if (*pattern == *str)
        {
            // 通常の文字比較
            pattern++;
            str++;
        }
        else
        {
            return (0);
        }
    }
    
    // 残りの*を処理
    while (*pattern == '*')
        pattern++;
    
    return (!*pattern && !*str);
}

t_token *expand_wildcards_in_token(t_token *token)
{
    DIR             *dir;
    struct dirent   *entry;
    t_token         *result = NULL;
    t_token         *last = NULL;
    int             matched = 0;
    
    // ワイルドカード文字が含まれているか確認
    if (!strchr(token->value, '*') && !strchr(token->value, '?'))
        return (token);
    
    dir = opendir(".");
    if (!dir)
        return (token);
    
    while ((entry = readdir(dir)))
    {
        // 隠しファイルは明示的な指定以外はスキップ
        if (entry->d_name[0] == '.' && token->value[0] != '.')
            continue;
        
        if (match_wildcard(token->value, entry->d_name))
        {
            // マッチしたファイルをトークンに追加
            t_token *new_token = create_token(TOKEN_WORD, 
                                             ft_strdup(entry->d_name));
            
            if (!result)
                result = new_token;
            else
                last->next = new_token;
            
            last = new_token;
            matched = 1;
        }
    }
    
    closedir(dir);
    
    // マッチしなかった場合は元のトークンを返す
    if (!matched)
        return (token);
    
    // 元のトークンを解放
    free(token->value);
    free(token);
    
    return (result);
}
```

---

## closedir

### プロトタイプ
```c
int closedir(DIR *dirp);
```

### ヘッダファイル
```c
#include <dirent.h>
```

### 説明
ディレクトリストリームを閉じます。

### パラメータ
- `dirp`: 閉じるディレクトリストリーム

### 戻り値
- 成功時: 0
- 失敗時: -1

### Minishellでの使用例

```c
// src/utils/directory_utils.c
int list_directory_contents(const char *path)
{
    DIR             *dir;
    struct dirent   *entry;
    
    dir = opendir(path);
    if (!dir)
    {
        perror(path);
        return (-1);
    }
    
    while ((entry = readdir(dir)))
    {
        // . と .. はスキップ
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;
        
        printf("%s\n", entry->d_name);
    }
    
    // 必ずクローズ
    if (closedir(dir) == -1)
    {
        perror("closedir");
        return (-1);
    }
    
    return (0);
}
```

## ディレクトリ操作のベストプラクティス

### 1. エラー処理

```c
DIR *dir = opendir(path);
if (!dir)
{
    if (errno == ENOENT)
        ft_putstr_fd("Directory not found\n", 2);
    else if (errno == EACCES)
        ft_putstr_fd("Permission denied\n", 2);
    else
        perror(path);
    return (-1);
}
```

### 2. リソース管理

```c
// RAII風の処理
int process_directory(const char *path)
{
    DIR *dir = opendir(path);
    if (!dir)
        return (-1);
    
    int result = do_something_with_dir(dir);
    
    // 必ずクローズ
    closedir(dir);
    
    return (result);
}
```

### 3. パス操作

```c
// パスの結合
char *join_path(const char *dir, const char *file)
{
    size_t  dir_len = strlen(dir);
    size_t  file_len = strlen(file);
    char    *path;
    
    // スラッシュの処理
    int need_slash = (dir_len > 0 && dir[dir_len - 1] != '/');
    
    path = malloc(dir_len + need_slash + file_len + 1);
    strcpy(path, dir);
    if (need_slash)
        strcat(path, "/");
    strcat(path, file);
    
    return (path);
}
```

### 4. ディレクトリの走査

```c
// 再帰的なディレクトリ走査
void traverse_directory(const char *path, int depth)
{
    DIR             *dir;
    struct dirent   *entry;
    struct stat     statbuf;
    char            *full_path;
    
    if (depth > MAX_DEPTH)
        return;
    
    dir = opendir(path);
    if (!dir)
        return;
    
    while ((entry = readdir(dir)))
    {
        if (entry->d_name[0] == '.')
            continue;
        
        full_path = join_path(path, entry->d_name);
        
        if (stat(full_path, &statbuf) == 0)
        {
            if (S_ISDIR(statbuf.st_mode))
            {
                // サブディレクトリを再帰的に処理
                traverse_directory(full_path, depth + 1);
            }
            else
            {
                // ファイルを処理
                process_file(full_path);
            }
        }
        
        free(full_path);
    }
    
    closedir(dir);
}
```