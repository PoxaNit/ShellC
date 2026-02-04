#include <stdio.h>
#include <unistd.h>
#define BUFF_SIZE 4040

 void greetings ()
{

    printf("MYSHELL RUNNING\n");

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

 int execute (char * program, char * argv[])
{
printf("execute executing...\n");
    int n = execve(program, argv, NULL);
printf("n: %i\n", n);
    if (n == -1) return 0;

    return 1;

};

 void parser (char* command, char programName[], char * argv[])
{
printf("parser executing...\n");

    int i = 0;
    int j = 0;
    int k = 0;

    leftTrim(command);

    while (command[i] != ' ')
    {

	programName[i] = command[i];

        i++;

    }

    i++;

    while (command[i] != '\0')
    {
printf("command[i]: %c\n", command[i]);

	if (command[i] != ' ')
	{

	    if (argv[j] == NULL)
	    {

		char buff[BUFF_SIZE];

		argv[j] = buff;

	    }

	    argv[j][k] = command[i];

            k++;

	    i++;

	    continue;

	}
printf("arg: %s\n", argv[j]);



        if (command[i - 1] != ' ') { k = 0; j++; }
	i++;

    }

printf("parser executed\n");

};

 ssize_t reader (char * buff, size_t size)
{

    ssize_t s = read(0, buff, size);
printf("reader executed\n");
    return s;

};

 void shell ()
{

    char programName[BUFF_SIZE];
    char * argv[BUFF_SIZE];

    char buff[BUFF_SIZE];

    char cli[3] = {'~', '$', '\0'};

    greetings();

//    while (1)
  //  {

	write(0, cli, sizeof(cli));

        ssize_t s = reader(buff, sizeof(buff));

        parser(buff, programName, argv);

        int n = execute(programName, argv);

        if (n == -1) printf("Invalid program name: %s\n", programName);

    //}

};


 int main ()
{

    shell();

    return 0;

};
