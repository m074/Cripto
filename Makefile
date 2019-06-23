OUTPUT_FILE=ss
LIBRARIES= -lm
FLAGS= --std=c99 -pedantic -pedantic-errors -Wall -Wextra -Werror -Wno-unused-parameter -D_POSIX_C_SOURCE=200112L -O0 

all:
	gcc -o $(OUTPUT_FILE) src/*.c  $(LIBRARIES) $(FLAGS)

clean:
	rm -f $(OUTPUT_FILE)
