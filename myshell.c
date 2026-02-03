#include <stdio.h>
#include <unistd.h>
#define BUFF_SIZE 4040

 void greetings ()
{

    printf("MYSHELL RUNNING\n\n");

};

 int execute (char * program, char * argv[])
{

    int n = execve(program, argv, NULL);

    if (n == -1) return 0;

    return 1;

};

 void parser (char* command, char programName[], char * argv[])
{

    int programNameDone = 0;
    int i;
    int charFound = 0;
printf("parser executing...\n");
    for (i = 0; command[i] != '\n'; i++)
    {

        if (!programNameDone)
        {
            if (command[i] != ' ')
            {

                charFound = 1;

                programName[i] = command[i];

            } else {

                if (charFound) programNameDone = 1;

            }

        } else
        {

            int j = 0;

            while (command[i] != '\n')
            {

                int k = 0;

                while (command[i] != ' ')
                {

                    argv[j][k] = command[i];

		    k++;

                    i++;

                }

                if (command[i - 1] != ' ') j++;

		i++;


            }

        }

    }
printf("parser executed\n");

};

 ssize_t reader (char * buff)
{

    ssize_t s = read(0, buff, sizeof(buff));
printf("reader executed\n");
    return s;

};

 void shell ()
{

    char programName[BUFF_SIZE];
    char * argv[BUFF_SIZE];

    char buff[BUFF_SIZE];

    greetings();

    while (1)
    {

        printf("~$");

        reader(buff);

        parser(buff, programName, argv);

        int n = execute(programName, argv);

        if (n == -1) printf("Invalid program name: %s\n", programName);

    }

};


 int main ()
{

    shell();

    return 0;

};
