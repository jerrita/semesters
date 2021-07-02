#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

//#define C_PORT 40000
//#define S_PORT 40001

#define BUF_SIZE 1024

void client()
{
    int sock_fd;
    char buffer[BUF_SIZE];
    int size;
    int len;
    int ret;
    int server_port;

    struct sockaddr_in server_addr;
    printf("input server port to connect: ");
    scanf("%d", &server_port);

    if (-1 == (sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)))
    {
        printf("Failed to create a socket!\n");
        return;
    }

    //server infomation
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(buffer, BUF_SIZE);
    len = sizeof(server_addr);

    //read from stdin and send to server
    while (1)
    {
        //printf("Please enter the content to be sent:\n");
        size = read(0, buffer, BUF_SIZE);
        if (size)
        {
            sendto(sock_fd, buffer, size, 0, (struct sockaddr *)&server_addr, len);
            bzero(buffer, BUF_SIZE);
        }
    }

    close(sock_fd);
}

void server()
{
    int sock_fd;
    int len;
    char buffer[BUF_SIZE];
    struct sockaddr_in server_addr, client_addr;
    int server_port;
    if (-1 == (sock_fd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        printf("Failed to create a socket!\n");
        return;
    }

    printf("input port to bind the server to: ");
    scanf("%d", &server_port);

    //server information
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (-1 == bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        printf("Failed to bind the socket!\n");
        return;
    }
    len = sizeof(client_addr);

    //rec and print
    while (1)
    {
        bzero(buffer, BUF_SIZE);
        if (-1 != (recvfrom(sock_fd, buffer, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &len)))
        {
            printf("The message received is: %s", buffer);
        }
    }

    return;
}

int main()
{
    pthread_t s = 1, c = 2;
    pthread_create(&s, NULL, server, NULL);
    pthread_create(&c, NULL, client, NULL);
    pthread_join(s, NULL);
    pthread_join(c, NULL);

    //client();

    return 0;
}
