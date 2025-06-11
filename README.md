# Sushi Shell - Zhabatayev Damir

**Sushi Shell** is a custom Linux-like command-line shell written in C++. It mimics the functionality of popular shells such as Bash and Zsh, providing an interactive interface for executing commands, handling processes, and navigating the file system.

## Features

- Basic command execution (`ls`, `cd`, `pwd`, etc.)
- Input parsing with arguments
- Built-in commands (`exit`, `clear`, `help`, etc.)
- File system navigation
- Support for piping (`|`) and redirection (`>`, `<`)
- Process management with forking and execution
- Error handling and graceful exits

## Built With

- C++
- Linux system calls (`fork`, `exec`, `pipe`, `dup2`, etc.)
- POSIX API
