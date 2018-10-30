/* 
 * Author: cr
 * Purpose : Demonstrate how to develop a UDP server program
 * Created on March 26, 2012, 11:17 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
//  ARPA stands for Address and Routing Parameter Area
#include <arpa/inet.h> // func: inet_ntoa

int main(int argc, char** argv) {
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    if (fd >= 0) {
        printf("UDP Socket has been created...\n");
    } else {
        perror("Be failed to create socket...\n");
    }
    
    // the socket address/name of this server
    struct sockaddr_in sockAddr;
    sockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //Byte Order Conversion
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(1984); //Byte Order Conversion
    
    // bind the UDP socket with the socket address
    int r_b = bind(fd, (struct sockaddr *)&sockAddr, sizeof(sockAddr));
    if (r_b >= 0) {
        printf("UDP Socket and socket Address/name have been bound...\n");
    } else {
        perror("Be failed to bind...\n");
    }
    
    // UDP server shouldn't call the listen function
    
    struct sockaddr_in sockAddr_client;
    int socket_len;
    char buf[100];
    int nbytes;
    
    while (1) {
        nbytes = recvfrom(fd, buf, sizeof(buf), 0, 
                (struct sockaddr *)&sockAddr_client, &socket_len);
        if (nbytes <= 0) {
            perror("Be failed to receive\n");
        }
        
        printf("the client[%s:%u] say:\" %s \"\n", 
                inet_ntoa(sockAddr_client.sin_addr), 
                ntohs(sockAddr_client.sin_port),
                buf);
        
        strcpy(buf, "You are welcome");
        sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *)&sockAddr_client, 
                sizeof(sockAddr_client));
        printf("I told the client :\"%s\"\n", buf);
    }
    
    return EXIT_SUCCESS;
}

