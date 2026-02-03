#include <stdio.h>
#include <unistd.h>
#define BUFF_SIZE 1000

 int execute (char * program, char * const argv[])
{

    int n = execve(program, argv);

    (n == -1) ? return 0 : return 1;

};

 void parser (char* command, char programName[], char * const argv[])
{

    int programNameDone = 0;
    int i;
    int charFound = 0;

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

};

 int main ()
{

    char programName[BUFF_SIZE];
    char * argv[BUFF_SIZE][BUFF_SIZE];

    

    return 0;

};
