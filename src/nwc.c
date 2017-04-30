#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096

void * header(void)
{
    fprintf(stderr, "NetWatchConfig Tool\n--------------\n\n");
    return 0;
}

void * print(char* message)
{
    fprintf(stdout, "%s\n", message);
    return NULL;
}

void * rld(char *buffer) {
    /* This function is used to realloc buffer contents to avoid memory mis-use */
    if (realloc(buffer, BUFFER_SIZE) == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    return NULL;
}

int write_to_config(char *ip_address)
{
    /* Writes IP addresses line by line into configuration file */
    char *tmp = malloc(sizeof(char) * BUFFER_SIZE);
    FILE *fp;
    fp = fopen("nwc.conf", "a");
    if(fp == NULL) return 1;
    sprintf(tmp, "%s\n", ip_address);
    fwrite(tmp, strlen(tmp), sizeof(char), fp);
    free(tmp);
    return 0;
}


int main(int argc, char* argv[])
{
    header();
    if (argc < 3) {
        fprintf(stderr, "Usage: %s -r <IP_ADDRESS>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    int opt;
    while( (opt = getopt(argc, argv, "r:c:")) != -1 )
    {
        switch(opt) {
            case 'r':
                rld(buffer);
                sprintf(buffer, "IP address set to: %s", optarg);
                print(buffer);
                if (write_to_config(optarg) != 0) {
                    perror("write_to_config");
                    exit(EXIT_FAILURE);
                } else {
                    rld(buffer);
                    sprintf(buffer, "IP address %s added to monitoring list.", optarg);
                    print(buffer);
                }
                break;

            case '?':
                print("Invalid option");
                exit(EXIT_FAILURE);
        }
    }
    free(buffer);
    return 0;
}
