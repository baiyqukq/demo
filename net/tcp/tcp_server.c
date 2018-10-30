/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2012年3月20日, 下午8:03
 */

#include <cstdlib>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    printf("*********Server***********\n");
    
    int r;  // template save some results
    
    int s = socket(PF_INET, SOCK_STREAM, 0);
    printf("Tcp Socket has created...\n");
    
    // convert host byte order to network byte order
    sockaddr_in sa;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1984);
    
    r = bind(s, (struct sockaddr *)&sa, sizeof(sa));
    if (r == -1) {
        perror("--->Be failed to bind...\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Finish binding...\n");
    }
    
    r = listen(s, 10);
    if (r == -1) {
        perror("--->Be failed to listen...\n");
    } else {
        printf("Finish listening...\n");
    }
    
    sockaddr_in sa_c;
    socklen_t sl_c;
    int s_c;
    char buf[100];
    
    while (1) {
        s_c = accept(s, (struct sockaddr *)&sa_c, &sl_c);
        if (s_c == -1) {
            perror("--->Be failed to accept...\n");
            exit(EXIT_FAILURE);
        } else {
            printf("Has accepted a client...\n");
        }
        
        r = recv(s_c, buf, sizeof(buf), 0);
        if (r == -1) {
            perror("--->Be failed to receive...\n");
            exit(EXIT_FAILURE);
        } else {
            printf("the client[%s:%d] said: \"%s\"\n", 
                    inet_ntoa(sa_c.sin_addr),
                    ntohs(sa_c.sin_port),
                    buf);
        }
        
        strcpy(buf, "You are welcome");
        
        r = send(s_c, buf, sizeof(buf), 0);
        if (r == -1) {
            perror("--->Be failed to send...\n");
            exit(EXIT_FAILURE);
        } else {
            printf("Has replied...\n");
        }
        
        // Don't forget close the socket
        // Aslo can call the close() function
        shutdown(s_c, 0);  // only on a connection
        printf("Disconnect with the client...\n");
    }

}

