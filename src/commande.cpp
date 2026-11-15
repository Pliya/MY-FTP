/*
** EPITECH PROJECT, 2025
** commande
** File description:
** commande
*/

#include "../my.h"
#include "../hash.h"

extern int h;
extern int io;
extern int cmt;
extern int lolo;

int user_command(char **pm, server_t *serv, int lo)
{
    if (strncasecmp(clean_str(pm[0]), "USER", 4) == 0) {
        if (pm[1]) {
            if (strncasecmp(clean_str(pm[1]), "Anonymous", 9) == 0) {
                io = 2;
                lo = write(serv->client_fd, "331 User name okay, need password.\r\n", strlen("331 User name okay, need password.\r\n"));
            } else {
                io = 1;
                lo = write(serv->client_fd, "331 User name okay, need password.\r\n", strlen("331 User name okay, need password.\r\n"));
            }
        } else {
            io = 1;
            lo = write(serv->client_fd, "331 User name okay, need password.\r\n", strlen("331 User name okay, need password.\r\n"));
        }
    }
    my_perror(lo);
    return 0;
}

int pass_command(char **pm, server_t *serv, int lo)
{
    if (strcasecmp(pm[0], "PASS") == 0) {
        if (io == 2) {
            h = 1;
            lo = write(serv->client_fd, "230 Login successful.\r\n", strlen("230 Login successful.\r\n"));
        } else if (io == 0)
            lo = write(serv->client_fd, "503 Login with USER first.\r\n", strlen("503 Login with USER first.\r\n"));
        else
            lo = write(serv->client_fd, "530 Login incorrect.\r\n", strlen("530 Login incorrect.\r\n"));
    }
    my_perror(lo);
    return 0;
}

int directory_command(char **pm, server_t *serv, int lo)
{
    char *dir = NULL;

    if (h == 1) {
        if (strncasecmp(clean_str(pm[0]), "PWD", 3) == 0)
            lo = write(serv->client_fd, "257 \"\\\" is the current directory.\r\n", strlen("257 \"\\\" is the current directory.\r\n"));
        if (strncasecmp(clean_str(pm[0]), "CWD", 3) == 0) {
            if (pm[1]) {
                chdir(pm[1]);
                lo = write(serv->client_fd, "250 Directory successfully changed.\r\n", strlen("250 Directory successfully changed.\r\n"));
            } else
                lo = write(serv->client_fd, "550 Failed to change directory.\r\n", strlen("550 Failed to change directory.\r\n"));
        }
    } else
        lo = write(serv->client_fd, "530 Not logged in.\r\n", strlen("530 Not logged in.\r\n"));
    my_perror(lo);
    return 0;
}

int help_command(char **pm, server_t *serv, int lo)
{
    if (strcasecmp(clean_str(pm[0]), "HELP") == 0) {
        lo = write(serv->client_fd, "214-Available commands:\r\n",
            strlen("214-Available commands:\r\n"));
        lo = write(serv->client_fd, " USER PASS ACCT CWD CDUP SMNT QUIT REIN\r\n",
            strlen(" USER PASS ACCT CWD CDUP SMNT QUIT REIN\r\n"));
        lo = write(serv->client_fd, " PORT PASV TYPE STRU MODE RETR STOR STOU\r\n",
            strlen(" PORT PASV TYPE STRU MODE RETR STOR STOU\r\n"));
        lo = write(serv->client_fd, " APPE ALLO REST RNFR RNTO ABOR DELE RMD\r\n",
            strlen(" APPE ALLO REST RNFR RNTO ABOR DELE RMD\r\n"));
        lo = write(serv->client_fd, " MKD  PWD  LIST NLST SITE SYST STAT HELP\r\n",
            strlen(" MKD  PWD  LIST NLST SITE SYST STAT HELP\r\n"));
        lo = write(serv->client_fd, " NOOP\r\n", strlen(" NOOP\r\n"));
        lo = write(serv->client_fd, "214 Help OK.\r\n", strlen("214 Help OK.\r\n"));
        my_perror(lo);
    }
    return 0;
}

int noop_command(char **pm, server_t *serv, int lo)
{
    if (strcasecmp(clean_str(pm[0]), "NOOP") == 0) {
        lo = write(serv->client_fd, "200 NOOP ok.\r\n", strlen("200 NOOP ok.\r\n"));
        my_perror(lo);
    }
    return 0;
}

int directory_cmm(char **pm, server_t *serv, int lo)
{
    if (h == 1) {
        if (strncasecmp(clean_str(pm[0]), "CDUP", 4) == 0 && lentab(pm) > 1)
            lo = write(serv->client_fd, "550 Failed to change directory.\r\n", strlen("550 Failed to change directory.\r\n"));
        if (strncasecmp(clean_str(pm[0]), "CDUP", 4) == 0 && lentab(pm) == 1)
            lo = write(serv->client_fd, "220 Command okay.\r\n", strlen("220 Command okay.\r\n"));
	    if (strncasecmp(clean_str(pm[0]), "PASV", 4) == 0) {
            char *pasv_msg = generate_pasv_response(serv);
            lo = write(serv->client_fd, pasv_msg, strlen(pasv_msg));
            lolo = 1;
        }
        if (strncasecmp(clean_str(pm[0]), "DELE", 4) == 0) {
            if (pm[1]) {
                if (remove(pm[1]) == 0)
                    lo = write(serv->client_fd, "250 Delete operation successful.\r\n", strlen("250 Delete operation successful.\r\n"));
                else
                    lo = write(serv->client_fd, "550 File unavailable.\r\n", strlen("550 File unavailable.\r\n"));
            } else
                lo = write(serv->client_fd, "501 Invalid arguments.\r\n", strlen("501 Invalid arguments.\r\n"));
        }
    } else
        lo = write(serv->client_fd, "530 Not logged in.\r\n", strlen("530 Not logged in.r\n"));
    my_perror(lo);
    return 0;
}

int port_commande(char **pm, server_t *serv, int lo)
{
    if (h == 1) {
        if (strncasecmp(clean_str(pm[0]), "PORT", 4) == 0) {
            if (count_virgule(pm[1]) != 5)
                lo = write(serv->client_fd, "501 Invalid arguments.\r\n", strlen("501 Invalid arguments.\r\n"));
            else {
                lo = write(serv->client_fd, "200 PORT command successful.\r\n", strlen("200 PORT command successful.\r\n"));
                cmt = 1;
            }
        }
        if (strncasecmp(pm[0], "LIST", 4) == 0) {
            if (cmt == 0 && lolo == 0)
                lo = write(serv->client_fd, "425 Use PORT or PASV first.\r\n", strlen("425 Use PORT or PASV first.\r\n"));
            else
                lo = write(serv->client_fd, "150 Here comes the directory listing.\r\n", strlen("150 Here comes the directory listing.\r\n"));
        }

    } else
        lo = write(serv->client_fd, "530 Not logged in.\r\n", strlen("530 Not logged in.\r\n"));
    my_perror(lo);
    return 0;
}

int retr_command(char **pm,server_t *serv, int lo)
{
    if (strncasecmp(clean_str(pm[0]), "RETR", 4) == 0) {
        if (cmt == 0 && lolo == 0)
            lo = write(serv->client_fd, "425 Use PORT or PASV first.\r\n", strlen("425 Use PORT or PASV first.\r\n"));
        else {
            if (pm[1]) {
                FILE *fp = fopen(pm[1], "rb");
                if (!fp)
                    lo = write(serv->client_fd, "550 File unavailable.\r\n", strlen("550 File unavailable.\r\n"));
                else {
                    cmt = 0;
                    lolo = 0;
                    char msg[256];
                    snprintf(msg, sizeof(msg), "150 Opening data connection for %s.\r\n", pm[1]);
                    lo = write(serv->client_fd, msg, strlen(msg));
                    sleep(1);
                    write(serv->client_fd, "226 Transfer complete.\r\n", strlen("226 Transfer complete.\r\n"));
                }
            } else
                lo = write(serv->client_fd, "501 Invalid arguments.\r\n", strlen("501 Invalid arguments.\r\n"));
        }
    }
    my_perror(lo);
    return 0;
}

int stor_command(char **pm,server_t *serv, int lo)
{
    if (strncasecmp(clean_str(pm[0]), "STOR", 4) == 0) {
        if (cmt == 0 && lolo == 0)
            lo = write(serv->client_fd, "425 Use PORT or PASV first.\r\n", strlen("425 Use PORT or PASV first.\r\n"));
        else {
            if (pm[1]) {
                FILE *fp = fopen(pm[1], "wb");
                if (fp == NULL)
                    lo = write(serv->client_fd, "550 File unavailable.\r\n", strlen("550 File unavailable.\r\n"));
                else {
                    cmt = 0;
                    lolo = 0;
                    char msg[256];
                    snprintf(msg, sizeof(msg), "150 Ready to receive %s.\r\n", pm[1]);
                    lo = write(serv->client_fd, msg, strlen(msg));
                    sleep(1);
                    write(serv->client_fd, "226 Transfer complete.\r\n", strlen("226 Transfer complete.\r\n"));
                }
            } else
                lo = write(serv->client_fd, "501 Invalid arguments.\r\n", strlen("501 Invalid arguments.\r\n"));
        }
    }
    my_perror(lo);
    return 0;
}

int command(char **pm, server_t *serv, int lo)
{
    for (int i = 0; command_table[i].command != NULL; i++) {
        if (strcasecmp(clean_str(pm[0]), command_table[i].command) == 0) {
            return command_table[i].handler(pm, serv, lo);
        }
    }
    lo = write(serv->client_fd, "500 Unknown command.\r\n", strlen("500 Unknown command.\r\n"));
    return lo;
}