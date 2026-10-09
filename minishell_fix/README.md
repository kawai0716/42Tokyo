# minishell

## Evaluation test cases

Assume the prompt is `minishell$ `. Some items require interactive key presses.

### Compile
```sh
make -n
make
make
```

### Simple command and globals
```sh
/bin/ls
<Enter>
<Space><Enter>
<Tab><Enter>
```
- Global variable should only hold last received signal number.

### Arguments
```sh
/bin/ls -a
/bin/ls -l .
/bin/echo hello world
/bin/pwd -L
```

### echo
```sh
echo
echo hello
echo -n hello
echo -n hello world
```

### exit
```sh
exit
exit 0
exit 42
exit 1 2
```

### Return value
```sh
/bin/ls
echo $?
/bin/ls filethatdoesntexist
echo $?
nosuchcmd
echo $?
echo $? $?
echo $?$?
```

### Signals
Empty prompt:
- Press Ctrl-C -> new line and prompt.
- Press Ctrl-\ -> nothing.
- Press Ctrl-D -> minishell exits (relaunch).

After typing some text:
- Type text then Ctrl-C -> new line and prompt, buffer cleared.
- Type text then Ctrl-\ -> nothing.
- Type text then Ctrl-D -> nothing.

Blocking command:
```sh
cat
```
Then press Ctrl-C, Ctrl-\, Ctrl-D in separate runs.

### Double quotes
```sh
echo "hello world"
echo "cat lol.c | cat > lol.c"
echo "  spaced   out "
echo "mix $USER and text"
```

### Single quotes
```sh
echo 'hello world'
echo ''
echo '$USER'
echo 'a | b > c < d'
echo '   spaced   '
```

### env
```sh
env
```

### export
```sh
export TEST=hello
env | grep TEST
export TEST=world
env | grep TEST
export NEWVAR=
env | grep NEWVAR
export A=1
export Z=1
export
```

### unset
```sh
unset TEST
env | grep TEST
unset PATH
env | grep PATH
```

### cd
```sh
pwd
cd /
pwd
cd ..
pwd
cd .
pwd
cd ~
pwd
cd nosuchdir
pwd
```

### pwd
```sh
pwd
cd /
pwd
cd ..
pwd
```

### Relative path
```sh
../minishell
./minishell
.././../bin/ls
```

### Environment PATH
```sh
ls
unset PATH
ls
export PATH=/bin:/usr/bin
ls
```

PATH order check:
```sh
mkdir -p /tmp/ms1 /tmp/ms2
printf '#!/bin/sh\necho ONE\n' > /tmp/ms1/foo
printf '#!/bin/sh\necho TWO\n' > /tmp/ms2/foo
chmod +x /tmp/ms1/foo /tmp/ms2/foo
export PATH=/tmp/ms1:/tmp/ms2
foo
export PATH=/tmp/ms2:/tmp/ms1
foo
```

### Redirection
```sh
echo hello > out.txt
cat < out.txt
echo world >> out.txt
cat < out.txt
echo hi > out1.txt > out2.txt
cat < out2.txt
cat < nosuchfile
cat << EOF
hello
world
EOF
```

### Pipes
```sh
cat file | grep bla | wc -l
ls filethatdoesntexist | grep bla | wc -l
<Up>/<Down>  # ヒストリ確認
dsbksdgbksdghsd
cat | cat | ls
echo a b c d e f g h i j k l m n o p q r s t

echo $USER
echo "$USER"
echo "$USER test"
```