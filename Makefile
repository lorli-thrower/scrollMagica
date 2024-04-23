scrollmagica: obj/main.o obj/Player.o
	gcc -o $@ $^ -Wall -Wextra

obj/main.o: main.c
	gcc -c -o $@ $^ -Wall -Wextra
obj/Player.o: Player.c
	gcc -c -o $@ $^ -Wall -Wextra
