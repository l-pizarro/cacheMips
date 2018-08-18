HEADERS = functions.h

all: functions.c $(HEADERS)
	gcc -o program.out main.c functions.c -Wall -lm -g

clean:
	-rm -f program.out
run:
	./program.out -n addresses.txt -m 128 -p 2
