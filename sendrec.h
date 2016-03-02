#pragma once

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>

#define BUFLEN 512  //Max length of buffer
#define PORT 20022   //The port on which to listen for incoming data
#define OURADDRESS "129.241.187.32"
#define SADDRESS "129.241.187.23"

void die(char *);

void* Sender();
void* Reciever();
