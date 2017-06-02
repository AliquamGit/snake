snake:*.c
	gcc -o snake *.c -lpthread

clean:
	rm snake
