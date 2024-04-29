NAME=scrollmagica
CC=gcc

$(NAME): obj/main.o obj/Player.o
	$(CC) -o $@ $^ -Wall -Wextra

obj/main.o: main.c
	$(CC) -c -o $@ $^ -Wall -Wextra
obj/Player.o: Player.c
	$(CC) -c -o $@ $^ -Wall -Wextra

debug: obj/main.o obj/Player.o
	$(CC) -o $(NAME) $^ -Wall -Wextra -g
