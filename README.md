# **Code Description**
* This code is written in C language and can be used to perform various operations on files present in a directory.
The code uses several system libraries such as `stdio.h`, `string.h`, `sys/types.h`, `unistd.h`, `dirent.h`, `sys/stat.h`, `fcntl.h`, `sys/wait.h`, `and stdlib.h`.
* The code starts by checking if the correct number of arguments are passed in the command line arguments. If not, it will display the correct usage. Then, it opens a directory specified in the command line argument using `opendir()` and checks if it was successfully opened.
* The code then iterates through each file in the directory using readdir() and checks if it is a C file or not by calling the `verificareFisier()` function. If it is a C file, the code then creates a child process using `fork()` and executes different options passed as command line arguments using a switch case.
* The options available are:
* 'n' - prints the file name
* 'u' - prints the user ID
* 'a' - prints the access rights of the file
* 'd' - prints the file size in bytes
* 'c' - prints the number of hard links to the file
* 'g' - compiles the C file into an executable file
* After executing the options, the code checks if the size of the file is less than 100KB. If yes, then it creates a symbolic link to the file.

# **How to use**
* To use this code, follow the steps below:
1)* Copy the code into a file with the .c extension.
Compile the code using a C compiler.
Run the executable file using the command ./executable <directory> <options>.
Replace <directory> with the path of the directory you want to perform operations on.
Replace <options> with the options you want to execute. You can pass multiple options as a string, for example: ./executable /home/user/directory ndc.
The available options are explained above.
