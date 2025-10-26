CC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Wextra -Iinclude -Iinclude/core -Iinclude/modules -I../PDCursesMod
LDFLAGS = -L../PDCursesMod/wincon -lpdcurses

SRCS = $(wildcard src/core/*.c) $(wildcard src/modules/*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

TARGET_HORTIFRUTI = hortifruti.exe
TARGET_BALANCA = balanca.exe

all: $(TARGET_HORTIFRUTI) $(TARGET_BALANCA)

$(TARGET_HORTIFRUTI): $(OBJS)
$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(TARGET_BALANCA): src/modules/balanca.c
$(CC) $(CFLAGS) src/modules/balanca.c -o $@ $(LDFLAGS)

clean:
rm -f $(TARGET_HORTIFRUTI) $(TARGET_BALANCA) $(OBJS)

.PHONY: all clean
