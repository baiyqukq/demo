/* 
 * File:   main.c
 * Author: cr
 *
 * Created on March 26, 2012, 11:17 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
/*
 * 
 */
int main(int argc, char** argv) {
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    if (fd >= 0) {
        printf("UDP Socket has been created...\n");
    } else {
        perror("Be failed to create socket...\n");
    }
    
    // the socket address/name of the server
    struct sockaddr_in name;
    name.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //Byte Order Conversion
    name.sin_family = AF_INET;
    name.sin_port = htons(1984); //Byte Order Conversion
   
    
    char buf[100];
    strcpy(buf, "Hello");
    
    sendto(fd, buf, sizeof(buf), 0, 
            (struct sockaddr *)&name, sizeof(name));
    printf("I told the server :\"%s\"\n", buf);
    
    int sock_len;
    recvfrom(fd, buf, sizeof(buf), 0, 
            (struct sockaddr *)&name, &sock_len);
    printf("the server reply:\"%s\"", buf);
        
    return (EXIT_SUCCESS);
}

