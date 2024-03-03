#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd;
    const char *texteconfig = "bind = ALT , Tab , exec, $configs/Move_Fluently.out";
    ssize_t bytewritten;
    fd = open("Keybinds.conf", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        printf("Error while opening the file 🤔.\n");
        return 1;
    }
    bytewritten = write(fd, texteconfig, strlen(texteconfig));
    if (bytewritten == -1) {
        printf("Error while writting in the file 🤔.\n");
        return 1;
    }
    return 0;

}