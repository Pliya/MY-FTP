/*
** EPITECH PROJECT, 2025
** c++
** File description:
** c++
*/

#include "../my.h"

void my_perror(int lo)
{
    if (lo < 0) {
        perror("");
        exit(84);
    }
}

void help_func(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("        port is the port number");
    printf(" on which the server socket listens\n");
    printf("        path is the path to the home");
    printf(" directory for the Anonymous user\n");
}

int contlin(char const *c, char p)
{
    int i = 0;
    int j = 1;

    while (c[i] != '\0') {
        if (c[i] == p) {
            j++;
        }
        i++;
    }
    return j;
}

char **my_str_to_word_array(char const *str, char c)
{
    int j = 0;
    int k = 0;
    int num_words = contlin(str, c);
    char **pc = (char **)malloc(sizeof(char *) * (num_words + 1));

    for (int i = 0; i < (num_words + 1); i++)
        pc[i] = (char *)malloc(sizeof(char) * (strlen(str) + 1));
    for (int l = 0; str[l] != '\0'; l++) {
        if (str[l] != c) {
            pc[j][k] = str[l];
            k++;
        } else {
            pc[j][k] = '\0';
            k = 0;
            j++;
        }
    }
    pc[j][k] = '\0';
    pc[num_words] = NULL;
    return pc;
}

int printt(char **str)
{
    for (int i = 0; str[i] != NULL; i++)
        printf("%s\n", str[i]);
    return 0;
}


char *min_clean(char *prend, int j)
{
    if (prend[j - 1] == ' ') {
        prend[j - 1] = '\0';
    } else {
        prend[j] = '\0';
    }
    return prend;
}

char *clean_str(char *str)
{
    int k = 0;
    int j = 0;
    int i = 0;
    int m = strlen(str);
    char *prend = (char *)malloc(sizeof(char) * (m + 1));

    for (i = 0; i < m; i++) {
        if (str[i] != ' ' && str[i] != '\t') {
            prend[j] = str[i];
            k = 1;
            j++;
        }
        if (k == 1 && (str[i] == '\t' || str[i] == ' ')) {
            prend[j] = ' ';
            k = 0;
            j++;
        }
    }
    return min_clean(prend, j);
}

int verificate_the_port(const char *c)
{
    for (int i = 0; c[i] != '\0'; i++) {
        if (c[i] >= '0' && c[i] <= '9') {
            return 0;
        }
    }
    return 84;
}

int verificate_the_path(const char *str)
{
    struct stat st;
    int i;

    stat(str, &st);
    if (!S_ISDIR(st.st_mode))
        return 84;
    if (access(str, X_OK) != 0)
        return 84;
    return 0;
}