// ***************************************************************************//**
//   @file         MyShell.c
//   @author       Zachary Anderson

// *******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>  //String manipulation possible
#include <sys/wait.h>
#define MAXSTR 255
#define ARGCNT 5

/**
DONOT change the existing function definitions. You can add functions, if necessary.
*/

//Global variables
char shell[MAXSTR];

/**
  @brief Fork a child to execute the command using execvp. The parent should wait for the child to terminate
  @param args Null terminated list of arguments (including program).
  @return returns 1, to continue execution and 0 to terminate the MyShell prompt.
 */
int execute(char **args)
{
    // Displays args array
    // for (int i = 0; i < ARGCNT; i++)
    // {
    //     // printf("args[%d]=%s\n", i, args[i]);
    //     printf("i=%d args[i]=%s\n", i, *(args + i));
    // }

    int rc = fork();
    //After child is created it runs the process and terminates the child once the
    //process is finished, while the parent remains running until MyShell is exited
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        execvp(args[0], args); // runs OS command

        //Result is used to compare string at args[0] with "exit"
        int result = strcmp(args[0], "exit");

        //If the result is anything but false, then display the error
        if (result != 0) 
        {
            printf("Error executing command: No such file or directory\n");
        }
        exit(1);
    } else {
        // parent goes down this path (original process)
        wait(NULL);
    }
    return 0;
}


/**
  @brief gets the input from the prompt and splits it into tokens. Prepares the arguments for execvp
  @return returns char** args to be used by execvp
 */
char** parse(void)
{
    int i = 0;
    char ** args = malloc(sizeof(char *) * ARGCNT);

    //The space is used as the delimiter for the string to be split
    char delimiter[] = " ";

    //Empty string to store the token
    char* token;

    //Store first token
    token = strtok(shell, delimiter);
        

    //Store remaining tokens with NULL as delimiter
    while (token != NULL)
    {
        // printf("Token: %s\n", token);
        *(args + i) = token;
        token = strtok(NULL, delimiter);
        i++;
    }

    // Displays args array
    // for (int i = 0; i < ARGCNT; i++)
    // {
    //     // printf("args[%d]=%s\n", i, args[i]);
    //     printf("i=%d args[i]=%s\n", i, *(args + i));
    // }
    return args;
}


/**
   @brief Main function should run infinitely until terminated manually using CTRL+C or typing in the exit command
   It should call the parse() and execute() functions
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv)
{
    int bool = 1;
    
    //Will continue to display MyShell> until "exit" is entered
    while (bool == 1)
    {
        if (strlen(shell) == 0)
        {
          printf("MyShell>");  //Prints MyShell> if an empty string is entered
        } else {
          printf("MyShell>");  //Prints MyShell> if a string is entered
        }
        // fscanf(stdin, "%s", shell); // stdin reads from consol, %s indicates a string input, shell is the array its entered in


        fgets(shell, sizeof(shell), stdin);
        //Removes trailing newline for fgets
        shell[strcspn(shell, "\n")] = 0;

        execute(parse());

        //Once "exit" is entered, bool is changed to zero to end while loop
        if (strcmp(shell, "exit") == 0)
        {
            bool = 0;
        }
    }

  return EXIT_SUCCESS;
}
//RESOURCES
//For use of fgets, used AI response on google
//https://www.google.com/search?q=fscanf+input+from+user+when+empty+string+is+entered+in+c&sca_esv=28f8fab5923385a6&ei=tsgOZ8iuJ5m40PEPx7uJyA4&ved=0ahUKEwjI4ZOxlZGJAxUZHDQIHcddAukQ4dUDCA8&uact=5&oq=fscanf+input+from+user+when+empty+string+is+entered+in+c&gs_lp=Egxnd3Mtd2l6LXNlcnAiOGZzY2FuZiBpbnB1dCBmcm9tIHVzZXIgd2hlbiBlbXB0eSBzdHJpbmcgaXMgZW50ZXJlZCBpbiBjMggQABiABBiiBDIIEAAYgAQYogQyCBAAGIAEGKIEMggQABiABBiiBDIIEAAYgAQYogRIm0JQlwZY5z9wAXgBkAEAmAGoAaAB6wyqAQQzLjEyuAEDyAEA-AEBmAIMoAKdCcICChAAGLADGNYEGEfCAgoQIRigARjDBBgKmAMAiAYBkAYIkgcEMi4xMKAHpEQ&sclient=gws-wiz-serp
//For string tokenizing example
//https://www.geeksforgeeks.org/string-tokenization-in-c/