#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// Function to check if a file exists
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// Function to create a file
void create_file(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("Error creating file");
        return;
    }
    fclose(file);
}

// Function to delete a file
void delete_file(const char *filename) {
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}

// Function to read a file
void read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error reading file");
        return;
    }

    char buffer[BUFFER_SIZE];
    printf("Contents of '%s':\n", filename);
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        printf("%s", buffer);
    }
    printf("\n");

    fclose(file);
}

// Function to get a character without Enter (for Ctrl+Q and Ctrl+W detection)
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// Function to edit a file
void edit_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    char lines[100][BUFFER_SIZE];  // Store up to 100 lines
    int line_count = 0;

    // Read existing content
    if (file) {
        while (fgets(lines[line_count], BUFFER_SIZE, file) && line_count < 100) {
            line_count++;
        }
        fclose(file);
    } else {
        printf("New file created: %s\n", filename);
    }

    printf("Editing '%s'. Press Ctrl+Q to quit without saving, Ctrl+W to save and quit.\n", filename);

    // Editing loop
    while (1) {
        printf("Enter line %d (or press ENTER to finish): ", line_count + 1);
        if (!fgets(lines[line_count], BUFFER_SIZE, stdin)) {
            continue;
        }

        // Check for Ctrl+Q (Quit without saving)
        if (lines[line_count][0] == 17) { // ASCII for Ctrl+Q
            printf("Exiting without saving.\n");
            return;
        }

        // Check for Ctrl+W (Save and Quit)
        if (lines[line_count][0] == 23) { // ASCII for Ctrl+W
            break;
        }

        // Remove newline character
        lines[line_count][strcspn(lines[line_count], "\n")] = 0;

        // Delete line if user enters "-d"
        if (strcmp(lines[line_count], "-d") == 0 && line_count > 0) {
            line_count--;
            printf("Last line deleted.\n");
        } else {
            line_count++;
        }
    }

    // Save to file
    file = fopen(filename, "w");
    if (!file) {
        perror("Error saving file");
        return;
    }
    for (int i = 0; i < line_count; i++) {
        fprintf(file, "%s\n", lines[i]);
    }
    fclose(file);
    printf("File '%s' saved successfully.\n", filename);
}

// Function to display help
void show_help() {
    printf("Usage:\n");
    printf("  utouch <filename>    - Create file if not exists, else read it\n");
    printf("  utouch -r <filename> - Delete a file\n");
    printf("  utouch -e <filename> - Edit a file (write/delete lines)\n");
    printf("  utouch -h            - Show this help message\n\n");
    printf("Editing mode:\n");
    printf("  - Type text to add lines.\n");
    printf("  - Type '-d' to delete the last line.\n");
    printf("  - Press Ctrl+Q to quit without saving.\n");
    printf("  - Press Ctrl+W to save and quit.\n");
}

// Main function to handle command-line arguments
int main(int argc, char *argv[]) {
    if (argc < 2) {
        show_help();
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0) {
        show_help();
    } else if (strcmp(argv[1], "-r") == 0) {
        if (argc < 3) {
            printf("Error: Missing filename for deletion.\n");
            return 1;
        }
        delete_file(argv[2]);
    } else if (strcmp(argv[1], "-e") == 0) {
        if (argc < 3) {
            printf("Error: Missing filename for editing.\n");
            return 1;
        }
        edit_file(argv[2]);
    } else {
        if (!file_exists(argv[1])) {
            create_file(argv[1]);
        } else {
            read_file(argv[1]);
        }
    }

    return 0;
}
