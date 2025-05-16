# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude

# Source files
SRCS = main.c maze.c player.c solver.c BFS_queue.c helper_functions.c
OBJS = $(SRCS:.c=.o)

# Output name
TARGET = maze_game

# SDL2 library paths (update if needed)
LDFLAGS = -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows

# Build and run
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	del /Q $(OBJS) $(TARGET).exe 2>nul || true
