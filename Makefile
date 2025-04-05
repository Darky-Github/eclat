CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = utouch
SRC = utouch.c

all: $(TARGET)

$(TARGET): $(SRC)
    $(CC) $(CFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
    sudo cp $(TARGET) /usr/local/bin/

uninstall:
    sudo rm -f /usr/local/bin/$(TARGET)

clean:
    rm -f $(TARGET)

check: $(TARGET)
    ./$(TARGET)  # Replace this line with actual test cases if applicable
