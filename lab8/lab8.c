#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int main()
{
    DIR *dir = opendir("./so");
    struct stat st = {0}, fileAttrib;
    FILE *fp;
    char c;
    //char *c = "abc", *dir = "/so/";

    if(stat("./so",&st) == -1)
        mkdir("./so", S_IRWXU);
    
    if(stat("./so/a",&st) == -1)
    {
        mkdir("./so/a", S_IRWXU);
        fp  = fopen ("./so/a/arqa.txt", "w");
        fputs("O guilhon eh feio", fp);
        fclose(fp);

        if (stat("./so/a/arqa.txt", &fileAttrib) < 0)
            printf("File Error Message = %s\n", strerror(errno));
        else
            printf( "Permissions: %d\n", fileAttrib.st_mode );

    }
    
    if(stat("./so/b",&st) == -1)
    {
        mkdir("./so/b", S_IRWXU);
        fp  = fopen ("./so/b/arqb.txt", "w");
        fclose(fp);
    }

    if(stat("./so/c",&st) == -1)
    {
        mkdir("./so/c", S_IRWXU);
        fp  = fopen ("./so/c/arqc.txt", "w");
        fclose(fp);
    }

    // leitura do arquivo
    fp  = fopen ("./so/a/arqa.txt", "r");
    c = fgetc(fp);

    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fp);
    }
    fclose(fp);

    // alteração do arquivo
    fp  = fopen ("./so/a/arqa.txt", "w");
    fseek( fp, 0, SEEK_SET );
    fputs("O guilhon eh bonito", fp);
    fclose(fp);

    fp  = fopen ("./so/a/arqa.txt", "r");
    c = fgetc(fp);
    printf("\n");
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fp);
    }
    //fclose(fp);

    if (chmod("./so/a/arqa.txt", S_IRUSR) != 0)
      perror("chmod() error");
    else {
      stat("./so/a/arqa.txt", &fileAttrib);
      printf("\nAfter chmod(), permissions are: %08x\n", fileAttrib.st_mode);
    }

    fclose(fp);
    return 0;
}