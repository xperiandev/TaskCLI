# TaskCLI
### A simple todo list app made in C++

TaskCLI (pronounced as task-c-l-i) is a todo app made in C++ as a passion project.

## Commands
### view
- gives a list of all tasks within todo.txt file.
### add "task"
- adds the task specified within the double-quotes to the todo.txt file.
### delete
- gives a list of tasks and prompts the user for an index of that task to delete.

> [!NOTE]
> all these actions will create a "todo.txt" file if not found, in the same location as the binary.

## Compiling
run make
```bash
make
```
defaults to g++. if using clang++ use 
```bash
make CXX=clang++
```

## Contributing
- feel free to add any changes and make a pull request, we'll discuss.

## Requirements
- g++/clang++ to compile
- no other third party libraries

## LICENSE
licensed under GNU GPL v3