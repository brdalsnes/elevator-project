#include <pthread.h>
#include <stdio.h>

int i = 0;


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* ThreadFunction1(){
	pthread_mutex_lock(&lock);
    for(int j = 0; j < 1000000; j++){
    	i++;
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* ThreadFunction2(){
	pthread_mutex_lock(&lock);
    for(int j = 0; j < 1000000; j++){
    	i--;
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(){

    pthread_t t1;
    pthread_create(&t1, NULL, ThreadFunction1, NULL);

    pthread_t t2;
    pthread_create(&t2, NULL, ThreadFunction2, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("%i\n",i);

    return 0; 
}
