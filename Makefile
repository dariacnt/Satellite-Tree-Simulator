build:
	gcc main.c functii.c -o tema2

run:
	./tema2 -c1 file.in file.out

valgrind:
	valgrind --leak-check=full --track-origins=yes ./tema2 -c1 file.in file.out

clean:
	rm -f tema2
