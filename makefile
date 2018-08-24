HEADERS = functions.h queue.h stack.h

all: functions.c $(HEADERS)
	gcc -o program.out main.c functions.c queue.c stack.c -Wall -lm -g

clean:
	-rm -f program.out
run:
	./program.out -n addresses.txt -m 64 -p 2
