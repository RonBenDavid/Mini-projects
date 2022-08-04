//Autor:Ron ben david 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <math.h>
#include <arpa/inet.h>

#define PORT "9034" // the port client will be connecting to

#define MAXDATASIZE 150 // max number of bytes we can get at once

float check_GPS_latitude();
float check_GPS_longitude();
char check_ans(char* tmp);

// get sockaddr, IPv4 or IPv6:
void* get_in_addr(struct sockaddr* sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char* argv[])
{
    int sockfd, numbytes, num_of_hurt = 0;
    char ans, tmp[10], buf[MAXDATASIZE];
    struct addrinfo hints, * servinfo, * p;
    int rv;
    char s[INET6_ADDRSTRLEN];


    if (argc != 2) {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
            p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr*)p->ai_addr),
        s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    //recivce first message
    if ((numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0)) == -1) {
        perror("recv");
        exit(1);
    }
    buf[numbytes] = '\0';
    printf("%s", buf);

    //send massage with temp
    float GPS_latitude = check_GPS_latitude();
    float GPS_longitude = check_GPS_longitude();
    char GPS_converted[30];
    sprintf(GPS_converted, "%lf %lf\n", GPS_latitude, GPS_longitude);
    write(sockfd, GPS_converted, strlen(GPS_converted));

    //server's response
    numbytes = read(sockfd, buf, MAXDATASIZE - 1);
    buf[numbytes] = '\0';
    printf("%s\n", buf);

    //get and send ID
    gets(buf);
    while ((strlen(buf) == 0) || (strlen(buf) > 9))
    {
        printf("Enter new ID: ");
        gets(buf);
        printf("\n");
    }
    write(sockfd, buf, strlen(buf));
    
    numbytes = read(sockfd, buf, MAXDATASIZE - 1);
    buf[numbytes] = '\0';
    printf("%s\n", buf);
    scanf("%s", &tmp);
    while ((strcmp(tmp, "1")) && (strcmp(tmp, "2")) && (strcmp(tmp, "3")) && (strcmp(tmp, "4")))
    {
        printf("invalid value\n");
        scanf("%s", tmp);
    }
    write(sockfd, &tmp, 2);
    numbytes = read(sockfd, buf, MAXDATASIZE - 1);
    buf[numbytes] = '\0';
    printf("%s\n", buf);
    scanf("%s", &tmp);
    write(sockfd, &tmp, sizeof(tmp));

    printf("\nPolice and\\or Medical help is on the way!\n\n");



}

float check_GPS_latitude()
{
    int temp1;
    float temp2, ret;
    time_t  t;

    srand((unsigned)time(&t));

    temp1 = rand();
    temp2 = temp1 % 100;
    ret = 31.0000023+((temp2 / 100) * 4 + pow(8.6 ,2))/100;
    printf("My GPS latitude is: %.5lf degrees \n", ret);
    return ret;
}
float check_GPS_longitude()
{
    int temp1;
    float temp2, ret;
    time_t  t;

    srand((unsigned)time(&t));

    temp1 = rand();
    temp2 = temp1 % 100;
    ret = 35.0000023+((temp2 / 100) * 4 + pow(3.46 ,2))/100;
    printf("My GPS longitude is: %.5lf degrees \n", ret);
    return ret;
}

