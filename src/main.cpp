/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/

#include "../my.h"

int h = 0;
int io = 0;
int cmt = 0;
int lolo = 0;

int create_socket(void)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        perror(" ");
        return 84;
    }
    return server_fd;
}

int main(int ac, char **av)
{
    server_t serv = {0};
    char cwd[1024];

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        help_func();
    else if (ac == 3) {
        coupure(av);
        serv.server_fd = create_socket();
        serv.port = atoi(av[1]);
        getcwd(cwd, sizeof(cwd));
        printf("Starting myFTP on port %d.\nServing %s to the Anonymous user.\n", serv.port, cwd);
        configurate_socket_server(& serv);
    } else
        return 84;
    return 0;
}
