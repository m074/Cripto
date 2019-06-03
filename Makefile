OUTPUT_FILE=Cripto
LIBRARIES= -lm 
FLAGS= --std=c99 -pedantic -pedantic-errors -Wall -Wextra -Werror -Wno-unused-parameter -D_POSIX_C_SOURCE=200112L -O1 #-fsanitize=address

all:
	gcc -o $(OUTPUT_FILE) *.c  $(LIBRARIES) $(FLAGS)

clean:
	rm -f $(OUTPUT_FILE) *.o
