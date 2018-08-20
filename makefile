HEADERS = functions.h queue.h

all: functions.c $(HEADERS)
	gcc -o program.out main.c functions.c queue.c -Wall -lm -g

clean:
	-rm -f program.out
run:
	./program.out -n addresses.txt -m 32 -p 2
