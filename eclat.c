#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

// Function to check if a file or directory exists
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

// Function to create a directory with enhanced features
void create_directory(const char *path, int create_parents, int use_timestamp, mode_t permissions) {
    char dir_path[1024];
    strcpy(dir_path, path);

    // Optionally add timestamp to directory name
    if (use_timestamp) {
        char timestamp[20];
        struct timeval tv;
        gettimeofday(&tv, NULL);
        snprintf(timestamp, sizeof(timestamp), "_%ld", tv.tv_sec);
        strcat(dir_path, timestamp);
    }

    // Create parent directories if needed
    if (create_parents) {
        if (mkdir(dir_path, permissions) == -1) {
            perror("Error creating directory");
        } else {
            printf("Directory '%s' created successfully with parents.\n", dir_path);
        }
    } else {
        if (mkdir(dir_path, permissions) == -1) {
            perror("Error creating directory");
        } else {
            printf("Directory '%s' created successfully.\n", dir_path);
        }
    }
}

// Function to display help
void show_help() {
    printf("Usage:\n");
    printf("  eclat <filename>    - Create file if not exists, else read it\n");
    printf("  eclat -r <filename> - Delete a file\n");
    printf("  eclat -e <filename> - Edit a file (write/delete lines)\n");
    printf("  eclat -t <filename> - Update timestamp (like 'touch')\n");
    printf("  eclat -d <dirname>  - Create directory\n");
    printf("  eclat -d <dirname> --parents - Create directory and parents if needed\n");
    printf("  eclat -h            - Show this help message\n");
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
    } else if (strcmp(argv[1], "-d") == 0) {
        if (argc < 3) {
            printf("Error: Missing directory name.\n");
            return 1;
        }

        int create_parents = 0;
        int use_timestamp = 0;
        mode_t permissions = 0755;  // Default permissions

        // Check for additional flags
        for (int i = 3; i < argc; i++) {
            if (strcmp(argv[i], "--parents") == 0) {
                create_parents = 1;
            } else if (strcmp(argv[i], "--timestamp") == 0) {
                use_timestamp = 1;
            }
        }

        create_directory(argv[2], create_parents, use_timestamp, permissions);
    } else {
        if (!file_exists(argv[1])) {
            create_file(argv[1]);
        } else {
            read_file(argv[1]);
        }
    }

    return 0;
}
