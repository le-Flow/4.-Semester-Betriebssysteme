#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char *space = " ";
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <file_name> <string_to_write>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *text = argv[2];
    text = strcat(argv[2], "\n");

    int fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    if (write(fd, text, strlen(text) + 1) < 0) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
	
    close(fd);
    return 0;
}
