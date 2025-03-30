#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

// Function to check if a file exists
int file_exists(const char *filename) {
    return access(filename, F_OK) == 0;
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

    char buffer[1024];
    printf("Contents of '%s':\n", filename);
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    printf("\n");

    fclose(file);
}

// Function to update file timestamps (like touch)
void update_timestamp(const char *filename) {
    struct timeval times[2];
    gettimeofday(&times[0], NULL); // Set access time (atime) to now
    gettimeofday(&times[1], NULL); // Set modification time (mtime) to now

    if (utimes(filename, times) != 0) {
        perror("Error updating timestamp");
    } else {
        printf("Timestamp updated for '%s'.\n", filename);
    }
}

// Function to display help
void show_help() {
    printf("Usage:\n");
    printf("  utouch <filename>    - Create file if not exists, else read it\n");
    printf("  utouch -r <filename> - Delete a file\n");
    printf("  utouch -e <filename> - Edit a file (write/delete lines)\n");
    printf("  utouch -t <filename> - Update timestamp (like 'touch')\n");
    printf("  utouch -h            - Show this help message\n");
}

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
    } else if (strcmp(argv[1], "-t") == 0) {
        if (argc < 3) {
            printf("Error: Missing filename for timestamp update.\n");
            return 1;
        }
        if (!file_exists(argv[2])) {
            create_file(argv[2]); // If file doesn't exist, create it
        }
        update_timestamp(argv[2]);
    } else {
        if (!file_exists(argv[1])) {
            create_file(argv[1]);
        } else {
            read_file(argv[1]);
        }
    }

    return 0;
}
