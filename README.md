0x16. C - Simple Shell

Simple Shell project will challenge you a lot about everything you have learn so far:

- Basics of programming
- Basics of C
- Basics of thinking like an engineer
- Group work
- and Learning how to learn

Learning Objectives:

- Who designed and implemented the original Unix operating system
- Who wrote the first version of the UNIX shell
- Who invented the B programming language (the direct predecessor to the C programming language)
- Who is Ken Thompson
- How does a shell work
- What is a pid and a ppid
- How to manipulate the environment of the current process
- What is the difference between a function and a system call
- How to create processes
- What are the three prototypes of main
- How does the shell use the PATH to find the programs
- How to execute another program with the execve system call
- How to suspend the execution of a process until one of its children terminates
- What is EOF / “end-of-file”?

Requirements:

- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory-
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to (why?)
- Write a README with the description of your project
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker

TASKS:

0. Betty would be proud

- Write a beautiful code that passes the Betty checks

1. Simple shell 0.1

Write a UNIX command line interpreter.
- Usage: simple_shell
Your Shell should:
- Display a prompt and wait for the user to type a command. A command line always ends with a new line.
- The prompt is displayed again each time a command has been executed.
- The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
- The command lines are made only of one word. No arguments will be passed to programs.
- If an executable cannot be found, print an error message and display the prompt again.
- Handle errors.
- You have to handle the “end of file” condition (Ctrl+D)
You don’t have to:
- use the PATH
- implement built-ins
- handle special characters : ", ', `, \, *, &, #
- be able to move the cursor
- handle commands with arguments
execve will be the core part of your Shell, don’t forget to pass the environ to it…

2. Simple shell 0.2

Simple shell 0.1 +
- Handle command lines with arguments

3. Simple shell 0.3

Simple shell 0.2 +
- Handle the PATH
- fork must not be called if the command doesn’t exist

4. Simple shell 0.4

Simple shell 0.3 +
- Implement the exit built-in, that exits the shell
- Usage: exit
- You don’t have to handle any argument to the built-in exit

5. Simple shell 1.0

Simple shell 0.4 +
- Implement the env built-in, that prints the current environment

Additional 11 Advanced tasks to be unlocked