#include "sendrec.h"

void die(char *s)
{
    perror(s);
    exit(1);
}
 
void* Sender()
{
    struct sockaddr_in si_me, si_other;
     
    int s, recv_len, slen = sizeof(si_other);
   // socklen_t restrict slen = sizeof(si_other);
    char buf[BUFLEN];
    char moskus[BUFLEN];
    sprintf(buf, "Hello World");
    sprintf(moskus, "Hello Moskus");
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
    si_other.sin_family = AF_INET;
    inet_pton(AF_INET, SADDRESS, &si_other.sin_addr);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    inet_pton(AF_INET, OURADDRESS, &si_me.sin_addr);
    //si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
     
    //keep listening for data
    while(1)
    {
    	

        printf("Waiting for data...fine");
        fflush(stdout);
          if (sendto(s, moskus, BUFLEN, 0, &si_other, slen) == -1)
        {
            die("sendto()");
        }
        memset(&buf[0], 0, sizeof(buf)); 
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %s\n" , buf);    
        //now reply the client with the same data
        sleep(5);
    }
 
    close(s);
    return 0;
}