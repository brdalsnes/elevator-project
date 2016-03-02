#include <pthread.h>
#include "sendrec.h"


int main(){
	
	pthread_t t1;
	pthread_create(&t1, NULL, Sender, NULL);

	pthread_t t2;
	pthread_create(&t2, NULL, Reciever, NULL);

	printf ("heiho\n");

	sleep(5);

	return 0;
}