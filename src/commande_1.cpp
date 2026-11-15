/*
** EPITECH PROJECT, 2025
** commande
** File description:
** commande
*/

#include "../my.h"

int lentab(char **tab)
{
    int c = 0;
    for (int i = 0; tab[i] != NULL; i++)
        c++;
    return c;
}

int count_virgule(char *str)
{
    int m = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',')
            m++;
    }
    return m;
}

char *generate_pasv_response(server_t *serv)
{
    static char response[100];
    int p1 = serv->port / 256;
    int p2 = serv->port % 256;
    snprintf(response, sizeof(response),
    "227 Entering Passive Mode (127,0,0,1,%d,%d).\r\n", p1, p2);
    return response;

}
