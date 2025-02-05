#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

// Function to recursively list directories
void list_directories(const char *base_path) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    // Open the directory
    if ((dir = opendir(base_path)) == NULL) {
        perror("opendir");
        return;
    }

    // Traverse the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." to avoid infinite loops
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);

        // Get file/directory status
        if (stat(path, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        // Check if it's a directory
        if (S_ISDIR(statbuf.st_mode)) {
            printf("Directory: %s\n", path);

            // Recursively list subdirectories
            list_directories(path);
        }
    }

    // Close the directory
    closedir(dir);
}

int main() {
    // Start from the current directory
    printf("Listing all directories recursively:\n");
    list_directories(".");
    return 0;
}