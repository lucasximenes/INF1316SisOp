#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

//Alunos: Lucas Ximenes Guilhon e Miguel Fagundes Vuori

int main()
{
    DIR *dir = opendir("./so");
    struct stat st = {0}, fileAttrib;
    FILE *fp;
    char c;

    if (stat("./so", &st) == -1)
    {
        printf("\nCriando subdiretório SO\n");
        mkdir("./so", S_IRWXU);
    }
    if (stat("./so/a", &st) == -1)
    {
        printf("\nCriando subdiretório A\n");
        mkdir("./so/a", S_IRWXU);
        printf("\nEscrevendo no arquivo arqa.txt\n");
        fp = fopen("./so/a/arqa.txt", "w");
        fputs("Conteúdo arquivo a", fp);
        fclose(fp);

        if (stat("./so/a/arqa.txt", &fileAttrib) < 0)
            printf("File Error Message = %s\n", strerror(errno));
        else
        {
            printf("Permissões do arquivo: \t");
            printf((S_ISDIR(fileAttrib.st_mode)) ? "d" : "-");
            printf((fileAttrib.st_mode & S_IRUSR) ? "r" : "-");
            printf((fileAttrib.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileAttrib.st_mode & S_IXUSR) ? "x" : "-");
            printf((fileAttrib.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileAttrib.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileAttrib.st_mode & S_IXGRP) ? "x" : "-");
            printf((fileAttrib.st_mode & S_IROTH) ? "r" : "-");
            printf((fileAttrib.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileAttrib.st_mode & S_IXOTH) ? "x" : "-");
            printf("\n\n");
        }
    }

    if (stat("./so/b", &st) == -1)
    {
        printf("\nCriando subdiretório B\n");
        mkdir("./so/b", S_IRWXU);
        printf("\nEscrevendo no arquivo arqb.txt\n");
        fp = fopen("./so/b/arqb.txt", "w");
        fputs("Conteúdo arquivo b", fp);
        fclose(fp);

        if (stat("./so/b/arqb.txt", &fileAttrib) < 0)
            printf("File Error Message = %s\n", strerror(errno));
        else
        {
            printf("Permissões do arquivo: \t");
            printf((S_ISDIR(fileAttrib.st_mode)) ? "d" : "-");
            printf((fileAttrib.st_mode & S_IRUSR) ? "r" : "-");
            printf((fileAttrib.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileAttrib.st_mode & S_IXUSR) ? "x" : "-");
            printf((fileAttrib.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileAttrib.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileAttrib.st_mode & S_IXGRP) ? "x" : "-");
            printf((fileAttrib.st_mode & S_IROTH) ? "r" : "-");
            printf((fileAttrib.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileAttrib.st_mode & S_IXOTH) ? "x" : "-");
            printf("\n\n");
        }
    }

    if (stat("./so/c", &st) == -1)
    {
        printf("\nCriando subdiretório C\n");
        mkdir("./so/c", S_IRWXU);
        printf("\nEscrevendo no arquivo arqc.txt\n");
        fp = fopen("./so/c/arqc.txt", "w");
        fputs("Conteúdo arquivo c", fp);
        fclose(fp);
        if (stat("./so/c/arqc.txt", &fileAttrib) < 0)
            printf("File Error Message = %s\n", strerror(errno));
        else
        {
            printf("Permissões do arquivo: \t");
            printf((S_ISDIR(fileAttrib.st_mode)) ? "d" : "-");
            printf((fileAttrib.st_mode & S_IRUSR) ? "r" : "-");
            printf((fileAttrib.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileAttrib.st_mode & S_IXUSR) ? "x" : "-");
            printf((fileAttrib.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileAttrib.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileAttrib.st_mode & S_IXGRP) ? "x" : "-");
            printf((fileAttrib.st_mode & S_IROTH) ? "r" : "-");
            printf((fileAttrib.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileAttrib.st_mode & S_IXOTH) ? "x" : "-");
            printf("\n\n");
        }
    }

    // leitura do arquivo
    printf("\nLendo conteúdo do arquivo A == ");
    fp = fopen("./so/a/arqa.txt", "r");
    c = fgetc(fp);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(fp);
    }
    fclose(fp);
    printf("\n");

    // alteração do arquivo
    printf("\nAlterando conteúdo do arquivo A\n");
    fp = fopen("./so/a/arqa.txt", "w+");
    fseek(fp, 7, SEEK_SET);
    fputs(" ALTERADO!", fp);
    fclose(fp);

    printf("\nLendo conteúdo do arquivo A == ");
    fp = fopen("./so/a/arqa.txt", "r");
    c = fgetc(fp);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(fp);
    }
    fclose(fp);
    printf("\n");

    printf("\nMudando permissões do arquivo A\n");
    if (chmod("./so/a/arqa.txt", S_IRUSR) != 0)
        perror("erro chmod()");
    else
    {
        stat("./so/a/arqa.txt", &fileAttrib);
        printf("Permissões do arquivo: \t");
        printf((S_ISDIR(fileAttrib.st_mode)) ? "d" : "-");
        printf((fileAttrib.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileAttrib.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileAttrib.st_mode & S_IXUSR) ? "x" : "-");
        printf((fileAttrib.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileAttrib.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileAttrib.st_mode & S_IXGRP) ? "x" : "-");
        printf((fileAttrib.st_mode & S_IROTH) ? "r" : "-");
        printf((fileAttrib.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileAttrib.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n\n");
    }

    return 0;
}