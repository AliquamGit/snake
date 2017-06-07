snake:*.c
	gcc -o snake *.c -lpthread -lcurses

clean:
	rm snake
