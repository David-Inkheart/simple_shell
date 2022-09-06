### Variable Replacement :heavy_dollar_sign:

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

