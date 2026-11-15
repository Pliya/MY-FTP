/*
** EPITECH PROJECT, 2025
** my
** File description:
** h
*/


#include <stdio.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/syscall.h>
#include <poll.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/poll.h>

#ifndef _MY_H_
    #define _MY_H_

void help_func(void);
void my_perror(int lo);
void coupure(char **av);
int printt(char **str);
int create_socket(void);
char *clean_str(char *str);
int verificate_the_port(const char *c);
int verificate_the_path(const char *str);
int contlin(char const *c, char p);

typedef struct server {
    struct sockaddr_in add;
    socklen_t addr;
    int server_fd;
    int client_fd;
    int port;
    struct pollfd fds[1024];
} server_t;

char *generate_pasv_response(server_t *serv);

int command(char **pm, server_t *serv, int lo);
int user_command(char **pm, server_t *serv, int lo);
int port_commande(char **pm, server_t *serv, int lo);
int pass_command(char **pm, server_t *serv, int lo);
int noop_command(char **pm, server_t *serv, int lo);
int help_command(char **pm, server_t *serv, int lo);
char **my_str_to_word_array(char const *str, char c);
int configurate_socket_server(server_t *serv);
int directory_command(char **pm, server_t *serv, int lo);
int directory_cmm(char **pm, server_t *serv, int lo);
int retr_command(char **pm, server_t *serv, int lo);
int stor_command(char **pm, server_t *serv, int lo);
char *min_clean(char *prend, int j);
int lentab(char **tab);
int count_virgule(char *str);
#endif
