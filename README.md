# **Code Description**
* This code is written in C language and can be used to perform various operations on files present in a directory.
The code uses several system libraries such as `stdio.h`, `string.h`, `sys/types.h`, `unistd.h`, `dirent.h`, `sys/stat.h`, `fcntl.h`, `sys/wait.h`, `and stdlib.h`.
* The code starts by checking if the correct number of arguments are passed in the command line arguments. If not, it will display the correct usage. Then, it opens a directory specified in the command line argument using `opendir()` and checks if it was successfully opened.
* The code then iterates through each file in the directory using readdir() and checks if it is a C file or not by calling the `verificareFisier()` function. If it is a C file, the code then creates a child process using `fork()` and executes different options passed as command line arguments using a switch case.
* The options available are:


