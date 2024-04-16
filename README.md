# Simple Shell
This is a simple UNIX shell implemented in C, capable of handling various features such as command execution, built-in commands, file input, exit status handling, and more.

## Features
Command Execution: Execute commands entered by the user or read from files, works in interactive and non interactive mode.
Semicolon Separation: Commands can be separated by semicolons for sequential execution.
Aliases: Define and use custom command aliases.
Comments: Ignore lines starting with #.
Built-in Commands:
exit: Terminate the shell with a specified exit status or the status of the last command executed.
cd: Change the current working directory.
setenv: Set environment variables.
unsetenv: Unset environment variables.
printenv: Print environment variables.

## Getting Started
To build and run the simple shell, follow these steps:
```
git clone https://github.com/adeyemialameen04/simple_shell.git
```

```
gcc -Wall -Werror -Wextra -pedantic *.c -o shell
```

```
gcc -Wall -Werror -Wextra -pedantic *.c -o shell
```

## Usage
Once the shell is running, you can enter commands as you would in a regular shell. Here are some examples:
```
$ ls -l
total 72
-rw-r--r-- 1 user user  1971 Mar 15 10:36 builtin.c
-rw-r--r-- 1 user user  2975 Mar 15 10:36 exec.c
-rw-r--r-- 1 user user  1158 Mar 15 10:36 shell.h
-rw-r--r-- 1 user user 20584 Mar 15 10:36 shell.c
...
$ echo "Hello, world!"
Hello, world!
$ exit
```

## Contributing
Contributions are welcome! If you would like to contribute to the development of this project, please follow these steps:

Fork the repository.
Create a new branch (git checkout -b feature/your_feature_name).
Make your changes.
Commit your changes (git commit -am 'Add new feature').
Push to the branch (git push origin feature/your_feature_name).
Create a new pull request.

## License
This project is licensed under the MIT License - see the [LICENSE]("https://github.com/adeyemialameen04/simple_shell/blob/main/LICENSE") file for details.
