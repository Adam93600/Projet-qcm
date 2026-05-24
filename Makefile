CC = gcc
CFLAGS = -Wall -Wextra
EXEC = qcm_cytech
SRC = main.c storage.c prof.c eleve.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

fclean: clean
	rm -f $(EXEC)

re: fclean all