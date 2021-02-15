all: clean
	gcc -std=c89 -g main.c -o main -ldl -lprocstat -lkvm -Wall -Wextra -Wpedantic

clean:
	if [ -f main ]; then rm main; fi
