#include <iostream>
#include <unistd.h>
#include <vector>
#include <signal.h>
#include <sys/wait.h>
int procA(void)
{
    while (!std::cin.eof()) 
{
        std::string line;
        std::getline(std::cin, line);
        std::cout << line << std::endl;
}
    return 0;
}
int main (int argc, char **argv) 
{
    int RgentoA1[2];
    int A1toA2[2];
    pipe(RgentoA1);
    pipe(A1toA2);
    pid_t child_id;
    child_id = fork();
    if(child_id == 0)
    {

        dup2(RgentoA1[1], STDOUT_FILENO);
        close(RgentoA1[0]);
        close(RgentoA1[1]);

        execv("./rgen",argv);
    }
    else if(child_id<0)
    {
      std::cerr<<"Error: could not fork\n";
      return 1;
    }
    else
    {
    pid_t child2_id = fork();
    if(child2_id == 0)
    {
        dup2(RgentoA1[0], STDIN_FILENO);
        close(RgentoA1[0]);
        close(RgentoA1[1]);

        dup2(A1toA2[1], STDOUT_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);

        char *argv1[3];

        argv1[0] = (char *)"python";
        argv1[1] = (char *)"ece650-a1.py";
        argv1[2] = nullptr;

        execvp("python", argv1);
    }
    else if(child2_id<0)
    {
     std::cerr << "Error: could not fork\n";
     return 1;
    }
    else{
    pid_t child3_id = fork();
    if(child3_id == 0)
    {
        dup2(A1toA2[0], STDIN_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);
        execv("ece650-a2", argv);
    }
    else if(child3_id<0)
    {
     std::cerr << "Error: could not fork\n";
     return 1;
    }
    dup2(A1toA2[1], STDOUT_FILENO);
    close(A1toA2[0]);
    close(A1toA2[1]);
    int end_of_file = procA();

     int status;
     kill(child_id, SIGTERM);
     waitpid(child_id, &status, 0);
     kill(child2_id, SIGTERM);
     waitpid(child2_id, &status, 0);
     kill(child3_id, SIGTERM);
     waitpid(child3_id, &status, 0);

     return end_of_file;
}
}
}
