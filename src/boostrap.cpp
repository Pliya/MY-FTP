/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** project
*/

#include "../my.h"

int read_write(char *buff, int i, int nfds, server_t *serv)
{
    serv->client_fd = serv->fds[i].fd;
    int bytes_read = read(serv->client_fd, buff, 1024);

    if (bytes_read <= 0) {
        close(serv->client_fd);
        serv->fds[i] = serv->fds[nfds - 1];
        nfds--;
        i--;
    } else {
        buff[bytes_read] = 0;
        if (strncasecmp(buff, "QUIT\r\n", 7) == 0 || strncasecmp(buff, "QUIT\n", 6) == 0) {
            write(serv->fds[i].fd, "221 Goodbye.\r\n", strlen("221 Goodbye.\r\n"));
            close(serv->fds[i].fd);
            serv->fds[i] = serv->fds[nfds - 1];
            nfds--;
            i--;
        } else {
            int lo = 0;
            char *mppp = strdup(buff);
            char *sfm = strtok(mppp, "\r");
            if (sfm == NULL) {
                lo = write(serv->client_fd, "500 Unknown command.\r\n", strlen("500 Unknown command.\r\n"));
                return 0;
            }
            sfm[strlen(sfm)] = '\0';
            char **pm = my_str_to_word_array(sfm, ' ');
            command(pm, serv, lo);
        }
    }
    return serv->client_fd;
}

void handle_client_events(server_t *serv, int *nfds, int i)
{
    int lo = 0;
    char buff[1024];
    int new_socket = 0;

    if (serv->fds[i].revents & POLLIN) {
        if (serv->fds[i].fd == serv->server_fd) {
            new_socket = accept(serv->server_fd, (struct sockaddr *)&(serv->add), &(serv->addr));
            printf("A client is connected!\n");
            lo = write(new_socket, "220 Welcome to myFTP!\r\n", strlen("220 Welcome to myFTP!\r\n"));
            my_perror(lo);
            serv->fds[*nfds].fd = new_socket;
            serv->fds[*nfds].events = POLLIN;
            (*nfds)++;
        } else {
            new_socket = read_write(buff, i, *nfds, serv);
        }
    }
}

int configurate_socket_server(server_t *serv)
{
    int status;
    int nfds = 1;
    int timeout = 3000;

    serv->add.sin_family = AF_INET;
    serv->add.sin_addr.s_addr = INADDR_ANY;
    serv->add.sin_port = htons(serv->port);

    if (bind(serv->server_fd, (struct sockaddr*)&(serv->add), sizeof(serv->add)) < 0) {
        perror(" ");
        return 84;
    }
    serv->addr = sizeof(serv->add);
    if (listen(serv->server_fd, 10) < 0) {
        perror(" ");
        return 84;
    }

    serv->fds[0].fd = serv->server_fd;
    serv->fds[0].events = POLLIN;

    while (1) {
        status = poll(serv->fds, nfds, timeout);
        my_perror(status);
        if (status == 0)
            continue;
        for (int i = 0; i < nfds; i++)
            handle_client_events(serv, &nfds, i);
    }
    close(serv->server_fd);
    return serv->server_fd;
}

void coupure(char **av)
{
    if (verificate_the_port(av[1]) == 84 ||
    verificate_the_path(av[2]) == 84)
        exit(84);
}
