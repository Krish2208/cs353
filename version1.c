#include <stdio.h>
#include <stdlib.h>

int main()
{
    char input;
    while (1)
    {
        printf("Enter the name of the binary to run (Firefox-1, gedit-2, code-3, Exit-e): ");
        scanf("%c", &input);

        if(input=='1'){
            char *args[] = {"/usr/bin/firefox", "www.google.com", NULL};
            execl(args[0], args);
        }
        else if(input=='2'){
            char *args[] = {"/usr/bin/gedit", "./test.txt", NULL};
            execl(args[0], args);
        }
        else if(input=='3'){
            char *args[] = {"/mnt/c/Users/HP/AppData/Local/Programs/Microsoft VS Code/bin/code", "test.txt", NULL};
            execl(args[0], args);
        }
        else if(input=='e') return 0;
        else printf("Invalid input\n");
    }
    return 0;
}