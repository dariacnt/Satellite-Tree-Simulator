build:
	gcc main.c functii.c -o sim

run:
	./tema2 -c1 file.in file.out

valgrind:
	valgrind --leak-check=full --track-origins=yes ./sim -c1 file.in file.out

clean:
	rm -f sim
