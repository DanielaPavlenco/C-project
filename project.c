#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int verificareFisier(struct dirent * fisier){
   
    if((fisier->d_name[strlen(fisier->d_name)-1] == 'c') && (fisier->d_name[strlen(fisier->d_name) - 2] == '.')) 
        return 1;
    else return 0;
}

int main(int argc, char *argv[])
{
    DIR *dir;             
    struct stat st1;    
    struct dirent *fisier;  
    char aux[10];        
    int length = 0;       
    int contor = 1;          
    char path1[100];
    char path2[100];

    if (argc != 3) 
        {
            printf("Usage: ./executabil <director> <optiuni>\n"); 
            return 0;
        }

    dir = opendir(argv[1]);                              
    if (dir == NULL )  
      printf("Eroare deschidere.\n");


   // fisier = readdir(dir);                                     
   // if(fisier == NULL)
     //   printf("Erore parcurgere fisier!\n");

    while((fisier = readdir(dir)) && (fisier != NULL))
     {
       if(verificareFisier(fisier))        
        {
          int pid, status;
          length = strlen(argv[2])-1;
          contor = 1;
          strcpy(aux,argv[2]);   //parcurgem sirul de optiuni
          strcpy(path1,argv[1]);
	        strcat(path1,"/");
		      strcat(path1,fisier->d_name);

          if (strchr(argv[2], 'g') != NULL)
          {
            if ( (pid = fork()) == 0)
            {
              strcpy(path2, path1);
              path2[strlen(path2) - 2] = '\0';
              execlp("gcc", "gcc", "-o", path2, path1, NULL);
              exit(0);
            }
            pid = wait(&status);
            printf("Procesul cu PID <%d> s-a terminat cu codul <%d>.\n", pid, WEXITSTATUS(status));
          }
          pid = fork();
          if (pid == 0)
          {
            length = strlen(argv[2]) - 1;
            contor = 1;

          while(length>0)
           {
             switch (aux[contor])
                {

                  case 'n': printf("Nume: %s\n",fisier->d_name);
                            break;

                  case 'u':
                             if(stat(path1,&st1) == 0)
                             {
                               printf("Utilizator: %d\n",st1.st_uid);
                             }
                            break;

                  case 'a': printf("Utilizator:\nRead - %s\n", st1.st_mode & S_IRUSR ? "DA" : "NU");
                            printf("Write - %s\n", st1.st_mode & S_IWUSR ? "DA" : "NU");
                            printf("Write - %s\n", st1.st_mode & S_IWUSR ? "DA" : "NU");
                            printf("Execute - %s\n", st1.st_mode & S_IXUSR ? "DA" : "NU");

                            printf("Grup:\nRead - %s\n", st1.st_mode & S_IRUSR ? "DA" : "NU");
                            printf("Write - %s\n", st1.st_mode & S_IWGRP ? "DA" : "NU");
                            printf("Write - %s\n", st1.st_mode & S_IWGRP ? "DA" : "NU");
                            printf("Execute - %s\n", st1.st_mode & S_IXGRP ? "DA" : "NU");

                            printf("Altii:\nRead - %s\n", st1.st_mode & S_IRUSR ? "DA" : "NU");
                            printf("Write - %s\n", st1.st_mode & S_IWOTH ? "DA" : "NU");
                            printf("Write - %s\n", st1.st_mode & S_IWOTH ? "DA" : "NU");
                            printf("Execute - %s\n", st1.st_mode & S_IXOTH ? "DA" : "NU");
                            break;

                  case 'd': if(stat(path1,&st1) == 0)
                             {
                               printf("Dimensiune in octeti: %ld\n",st1.st_size);
                             }
                             break;

                  case 'c': if(stat(path1,&st1) == 0)
                             {
                               printf("Numarul de legaturi: %lu\n",st1.st_nlink);
                             }
                            break;
                  
                }
            length--;
            contor++;
          }

          exit(0);
      }
      wait(&status);
      printf("Procesul cu PID <%d> s-a terminat cu codul <%d>.\n", pid, WEXITSTATUS(status));

      pid = fork();
      if (pid == 0)
      {
        if (st1.st_size < 1024 * 100)
        {
          strcpy(path2, path1);
          path2[strlen(path2) - 2] = '\0';
           unlink(path2);
           symlink(path1,path2);
        }
        exit(0);
      }
      wait(&status);
      printf("Procesul cu PID <%d> s-a terminat cu codul <%d>.\n", pid, WEXITSTATUS(status));
    }
    }
    return 0;
}
