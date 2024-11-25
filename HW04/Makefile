# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall - g -lpthread

# Target executable
TARGET = HW04

# Source files
SRC = HW04.c

# Default rule to build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Rule to compile .c files into .o files (if needed for modular projects)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(TARGET) *.o

# Convenience rule to run the program
run: $(TARGET)
	./$(TARGET)

# Run with custom arguments
run_custom: $(TARGET)
	./$(TARGET) -S -s 1000 /workspaces/-WZOU-CS332/

# Phony targets
.PHONY: clean run run_custom
