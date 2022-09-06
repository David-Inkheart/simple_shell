# unixhell - Simple Shell :skull:

A simple UNIX command interpreter written as part of the low-level programming project, at ALX.

## Description :pencil:

> - **unixhell** is a simple UNIX command language interpreter that reads commands from either a file or standard input(i.e stdin) and executes them.

### How to run `unixhell` :runner:

> - To run **unixhell**, compile all `.c` files in the repository and run the resulting executable:

```
gcc *.c -o unixhell
./unixhell
```

**unixhell** can be invoked both interactively and non-interactively. If **unixhell** is invoked with standard input not connected to a terminal, it reads and executes received cammands in order.

Example:
```
$ echo "echo 'hello'" | ./unixhell
'hello'
$
```

If **unixhell** is invoked with standard input connected to a terminal, an *interactive* shell is opened. When executing interactively, **unixhell** displays the prompt `:)` when it is ready to read a command.

Example:
```
$./unixhell
:)
```

Alternatively, if command line arguments are supplied upon invocation, **unixhell** treats the first argument as a file from which to read commands. The supplied file should contain one command per line. **unixhell** runs each of the commands contained in the file in order before exiting.

Example:
```
$ cat test_file
echo 'hello'
$ ./unixhell test_file
'hello'
$
```

### Environment :desert_island:

Upon invocation, **unixhell** receives and copies the environment of the parent process in which it was executed. This environment is an array of strings in the form *name=value*. Some examples of environmental variables are:

#### HOME
The home directory of the current user and the default directory argument for the **cd** builtin command.

```
$ echo "echo $HOME" | ./unixhell
/home/vagrant
```
#### PWD
The current working directory as set by the **cd** command.

```
$ echo "echo $PWD" | ./unixhell
/home/vagrant/alx-learning/simple_shell
```

#### OLDPWD
The previous working directory as set by the **cd** command.

```
$ echo "echo $OLDPWD" | ./unixhell
/home/vagrant/alx-learning/printf
```

#### PATH
A colon-separated list of directories in which the shell looks for commands. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directory.

```
$ echo "echo $PATH" | ./unixhell
/home/vagrant/.cargo/bin:/home/vagrant/.local/bin:/home/vagrant/.rbenv/plugins/ruby-build/bin:/home/vagrant/.rbenv/shims:/home/vagrant/.rbenv/bin:/home/vagrant/.nvm/versions/node/v10.15.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/vagrant/.cargo/bin:/home/vagrant/workflow:/home/vagrant/.local/bin
```

### Command Execution :arrow_forward:
After receiving a command, **unixhell** tokenizes it into words using `" "` as a delimiter. The first word is considered the command and all remaining words are considered arguments to that command. **unixhell** then proceeds with the following actions:
1. If the first character of the command is neither a slash (`\`) nor dot (`.`), the shell searches for it in the list of shell builtins. If there exists a builtin by that name, the builtin is invoked.
2. If the first character of the command is none of a slash (`\`), dot (`.`), nor builtin, **unixhell** searches each element of the **PATH** environmental variable for a directory containing an executable file by that name.
3. If the first character of the command is a slash (`\`) or dot (`.`) or either of the above searches was successful, the shell executes the named program with any remaining given arguments in a separate execution environment.

### Exit Status :wave:
**unixhell** returns the exit status of the last command executed, with zero indicating success and non-zero indicating failure.

If a command is not found, the return status is `127`; if a command is found but is not executable, the return status is 126.

All builtins return zero on success and one or two on incorrect usage (indicated by a corresponding error message).

### Signals :satellite:
While running in interactive mode, **unixhell** ignores the keyboard input `Ctrl+c`. Alternatively, an input of end-of-file (`Ctrl+d`) will exit the program.

User hits `Ctrl+d` in the third line.
```
$ ./unixhell
:) ^C
:) ^C
$
eplacement :heavy_dollar_sign:

**unixhell** interprets the `$` character for variable replacement.

#### $PWD
`PWD` is substituted with its value.

Example:
```
$ echo "echo $PWD" | ./unixhell
/home/vagrant/alx/simple_shell
```

#### $?
`?` is substitued with the return value of the last program executed.

Example:
```
$ echo "echo $?" | ./unixhell
0
```

#### $$
The second `$` is substitued with the current process ID.

Example:
```
$ echo "echo $$" | ./unixhell
6494
```

### Comments :speech_balloon:

**unixhell** ignores all words and characters preceeded by a `#` character on a line.

Example:
```
$ echo "echo 'hello' #this will be ignored!" | ./unixhell
'hello'
```

### Operators :arrow_right:

**unixhell** specially interprets the following operator characters:

#### ; - Command separator
Commands separated by a `;` are executed sequentially.

Example:
```
$ echo "echo 'David' ; echo 'Philip'" | ./unixhell
'David'
'Philip'
```

#### && - AND logical operator
`command1 && command2`: `command2` is executed if, and only if, `command1` returns an exit status of zero.

Example:
```
$ echo "error! && echo 'hello'" | ./unixhell
./unixhell: 1: error!: not found
$ echo "echo 'all good' && echo 'hello'" | ./unixhell
'all good'
'hello'
```

#### || - OR logical operator
`command1 || command2`: `command2` is executed if, and only if, `command1` returns a non-zero exit status.

Example:
```
$ echo "error! || echo 'but still runs'" | ./unixhell
./unixhell: 1: error!: not found
'but still runs'
```

The operators `&&` and `||` have equal precedence, followed by `;`.

### unixhell Builtin Commands :wrench:

#### cd
  * Usage: `cd [DIRECTORY]`
  * Changes the current directory of the process to `DIRECTORY`.
  * If no argument is given, the command is interpreted as `cd $HOME`.
  * If the argument `-` is given, the command is interpreted as `cd $OLDPWD` and the pathname of the new working directory is printed to standad output.
  * If the argument, `--` is given, the command is interpreted as `cd $OLDPWD` but the pathname of the new working directory is not printed.
  * The environment variables `PWD` and `OLDPWD` are updated after a change of directory.

Example:
```
$ ./unixhell
:) pwd
/home/vagrant/alx/simple_shell
:) cd ../
:) pwd
/home/vagrant/alx
:) cd -
:) pwd
/home/vagrant/alx/simple_shell
```

#### alias
  * Usage: `alias [NAME[='VALUE'] ...]`
  * Handles aliases.
  * `alias`: Prints a list of all aliases, one per line, in the form `NAME='VALUE'`.
  * `alias NAME [NAME2 ...]`: Prints the aliases `NAME`, `NAME2`, etc. one per line, in the form `NAME='VALUE'`.
  * `alias NAME='VALUE' [...]`: Defines an alias for each `NAME` whose `VALUE` is given. If `name` is already an alias, its value is replaced with `VALUE`.

Example:
```
$ ./unixhell
:) alias show=ls
:) show
env.c	helpers.c	func.c	vim.h	create.md	super.c	link.c	add.c	test.c	lib.h
```

#### exit
  * Usage: `exit [STATUS]`
  * Exits the shell.
  * The `STATUS` argument is the integer used to exit the shell.
  * If no argument is given, the command is interpreted as `exit 0`.

Example:
```
$ ./unixhell
:) exit
$
```

#### env
  * Usage: `env`
  * Prints the current environment.

Example:
```
$ ./unixhell
:) env
NVM_DIR=/home/vagrant/.nvm
...
```

#### setenv
  * Usage: `setenv [VARIABLE] [VALUE]`
  * Initializes a new environment variable, or modifies an existing one.
  * Upon failure, prints a message to `stderr`.

Example:
```
$ ./unixhell
:) setenv NAME Philip
:) echo $NAME
Philip
:)
```

#### unsetenv
  * Usage: `unsetenv [VARIABLE]`
  * Removes an environmental variable.
  * Upon failure, prints a message to `stderr`.

Example:
```
$ ./unixhell
:) setenv NAME David
:) unsetenv NAME
:) echo $NAME

:)
```

## Authors :ledger:

* Philip Ukanwoke <[Kaditcuy](https://github.com/Kaditcuy)>
* David Okolie <[David-Inkheart](https://github.com/David-inkheart)>


## Acknowledgements ::

**unixhell** emulates basic functionality of the **sh** shell. This README borrows from the Linux man pages [sh(1)](https://linux.die.net/man/1/sh) and [dash(1)](https://linux.die.net/man/1/dash).

This project was written as part of the curriculum for Alx_learning. Alx software engineering programme is an online-based full-stack software engineering program that prepares students for careers in the tech industry using project-based peer learning. For more information, visit [this link](https://www.alxafrica.com/).
