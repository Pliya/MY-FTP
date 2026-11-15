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

#ifndef _HASH_H_
    #define _HASH_H_

typedef int (*command_handler_t)(char **, server_t *, int);

struct command_map {
    const char *command;
    command_handler_t handler;
};

static const struct command_map command_table[] = {
    {"CDUP", directory_cmm},
    {"DELE", directory_cmm},
    {"PASV", directory_cmm},
    {"PORT", port_commande},
    {"LIST", port_commande},
    {"USER", user_command},
    {"PWD", directory_command},
    {"CWD", directory_command},
    {"HELP", help_command},
    {"NOOP", noop_command},
    {"PASS", pass_command},
    {"RETR", retr_command},
    {"STOR", stor_command},
    {NULL, NULL}
};

#endif
//Le port est un nombre entier sur 16 bits (de 0 à 65535).
//Pour l’envoyer dans la réponse PASV, il faut le diviser en deux octets :
//p1 * 256 + p2	Recomposition du port côté client