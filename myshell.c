#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFF_SIZE 4040

 void greetings ()
{

    printf("MYSHELL RUNNING\n");

};

 void freeAll (char * chars[])
{

    for (int i = 1; chars[i] != NULL; i++)
    {

	free(chars[i]);

    }

};

void leftTrim(char *str)
{
    int i = 0;
    int k = 0;

    while (str[i] == ' ')
    {
        i++;
    }

    while (str[i] != '\0')
    {
        str[k++] = str[i++];
    }

    str[k] = '\0';
}

 int execute (char * program, char * argv[], char** envp)
{

    pid_t pid = fork();

    if (pid == 0)
    {

        int n = execve(program, argv, envp);

        if (n == -1) return 0;

    } else
    {

	wait(NULL);

    }


    return 1;

};

 void parser (char* command, char programName[], char * argv[])
{

    int i = 0;
    int j = 1;
    int k = 0;

    leftTrim(command);

    while (command[i] != ' ' && command[i] != '\0')
    {

	programName[i] = command[i];

        i++;

    }

    programName[i] = '\0';

    argv[0] = programName;

    i++;

    while (command[i] != '\0')
    {

	if (command[i] == ' ')
        {

            if (k > 0)
	    {

    	        argv[j][k] = '\0';

		j++;

		k = 0;

	    }

	    i++;

	    continue;

	} else
        {

	    if (argv[j] == NULL)
	    {

		argv[j] = malloc(BUFF_SIZE);

	    }

	    argv[j][k] = command[i];

            k++;

    	    i++;

	}

    }

    if (k > 0)
    {

	argv[j][k] = '\0';

	j++;

    }

    argv[j] = NULL;

};

 ssize_t reader (char * buff, size_t size)
{

    ssize_t s = read(0, buff, size);

    return s;

};

 void shell (char** envp)
{

    char programName[BUFF_SIZE];
    char * argv[BUFF_SIZE];

    char buff[BUFF_SIZE];

    char cli[4] = {'~', '$', ' ', '\0'};

    greetings();

    while (1)
    {

	write(0, cli, sizeof(cli));

        ssize_t s = reader(buff, sizeof(buff));

        for (int i = 0; i < BUFF_SIZE; i++)
        {

            argv[i] = NULL;

        }

        if (s <= 0) buff[0] = '\0';
        else buff[s] = '\0';

        parser(buff, programName, argv);

        int n = execute(programName, argv, envp);

        if (n == -1) printf("Invalid program name: %s\n", programName);

        freeAll(argv);

    }

};


 int main (int argc, char* argv[], char* envp[])
{

    shell(envp);

    return 0;

};
