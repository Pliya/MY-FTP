/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-tekspice-romaric.dega
** File description:
** test.cpp
*/

#include <criterion/criterion.h>
#include "../my.h"

Test(lentab, count_basic)
{
    char *tab[] = {"hello", "world", NULL};
    cr_assert_eq(lentab(tab), 2);
}

Test(lentab, count_empty_array)
{
    char *tab[] = {NULL};
    cr_assert_eq(lentab(tab), 0);
}

Test(lentab, count_multiple_entries)
{
    char *tab[] = {"a", "b", "c", "d", "e", NULL};
    cr_assert_eq(lentab(tab), 5);
}

Test(count_virgule, count_commas_basic)
{
    char *str = "127,0,0,1,128,128";
    cr_assert_eq(count_virgule(str), 5);
}

Test(count_virgule, no_commas)
{
    char *str = "no commas here";
    cr_assert_eq(count_virgule(str), 0);
}

Test(count_virgule, all_commas)
{
    char *str = ",,,,,";
    cr_assert_eq(count_virgule(str), 5);
}

Test(count_virgule, mixed_content)
{
    char *str = "hello,world,this,is,a,test";
    cr_assert_eq(count_virgule(str), 5);
}

Test(generate_pasv_response, default_port_2121)
{
    server_t serv;
    serv.port = 2121;
    char *resp = generate_pasv_response(&serv);

    cr_assert_str_eq(resp, "227 Entering Passive Mode (127,0,0,1,8,73).\r\n");
}

Test(generate_pasv_response, port_21)
{
    server_t serv;
    serv.port = 21;
    char *resp = generate_pasv_response(&serv);

    cr_assert_str_eq(resp, "227 Entering Passive Mode (127,0,0,1,0,21).\r\n");
}

Test(generate_pasv_response, port_boundary_65535)
{
    server_t serv;
    serv.port = 65535;
    char *resp = generate_pasv_response(&serv);

    cr_assert_str_eq(resp, "227 Entering Passive Mode (127,0,0,1,255,255).\r\n");
}
