# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Target executable
TARGET = WZOU_HW02

# Source files
SRC = WZOU_HW02.c

# Default rule to build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Rule to compile .c files into .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(TARGET) $(OBJECTS)

# Convenience rule to run the program
run: $(TARGET)
	./$(TARGET)

# run this for example 
run_custom:
	./$(TARGET) -S -s [1000] /workspaces/-WZOU-CS332/

# Phony targets
.PHONY: clean run