/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Creat
#include <cygwin/in.h>
#include <cygwin/socket.h>
#include <cygwin/socket.h>ed on 2012年3月20日, 下午8:03
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char**argv) {
    printf("*********Client***********\n");

    int r; // template save some results

    int s = socket(PF_INET, SOCK_STREAM, 0);
    printf("Tcp Socket has created...\n");

    // convert host byte order to network byte order
    struct sockaddr_in sa;
    sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1984);

    r = connect(s, (struct sockaddr *) &sa, sizeof (sa));
    if (r == -1) {
        perror("--->Be failed to connect...\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Finish connection...\n");
    }

    char buf[100];

    strcpy(buf, "Hello!");

    r = send(s, buf, sizeof (buf), 0);
    if (r == -1) {
        perror("--->Be failed to send...\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Finish sending...\n");
    }

    strcpy(buf, "");

    r = recv(s, buf, sizeof (buf), 0);
    if (r == -1) {
        perror("--->Be failed to receive...\n");
        exit(EXIT_FAILURE);
    } else {
        printf("the server said: \"%s\"\n", buf);
    }

    // Don't forget close the socket
    // Aslo can call the close() function
    shutdown(s, 0);
    printf("Disconnect with the server...\n");
    return EXIT_SUCCESS;
}
