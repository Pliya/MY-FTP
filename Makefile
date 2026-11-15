##
## EPITECH PROJECT, 2024
## make
## File description:
## fiel
##

SRC		=	src/*.cpp

NAME	=	myftp

all:
	g++ $(SRC) -o $(NAME) -g3

clean:
	rm -f *~
	rm -f *#

fclean:
	rm -f $(NAME)
	rm -f *unit_tests
	rm -f *~
	rm -f *#
	rm -f *.gcno
	rm -f *.gcda

re:	fclean all

unit_tests: fclean
	g++ -o unit_tests src/commande_1.cpp tests/test.cpp -lcriterion --coverage

tests_run:	unit_tests
		./unit_tests