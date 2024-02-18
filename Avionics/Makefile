# Target microcontroller
MCU = atmega328pb

# Compiler and flags
CC = avr-gcc
CFLAGS = -0s -mmcu=$(MCU)

# Object files from individual source files
OBJ = main.o sensors.o telemetry.o # These are hypothetical, subject to change

# Output file
TARGET = rocket_controller.elf

# Default: Build the target
all: $(TARGET)

# Create the output file
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Convert to HEX format
%.hex: %.elf
	avr-objcopy -O ihex $< $@

# Target cleanup
clean:
	rm -f $(OBJ) $(TARGET) *.hex