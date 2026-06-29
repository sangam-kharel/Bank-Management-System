CC = gcc

CFLAGS = -Wall -Wextra -std=c11

SRC = src/main.c \
      src/utility.c \
      src/account.c \
      src/admin.c \
      src/transaction.c

TARGET = bank

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
