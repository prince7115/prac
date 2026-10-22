#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
int buf[5];
pthread_t pid,cid;
pthread_mutex_t m;
sem_t empty,full;
void *producer(void *arg)
{
  int n,i=0;
  while(1){
    sem_wait(&empty);
    pthread_mutex_lock(&m);
    n=random()%10;
    buf[i++]=n;
    printf("\nNumber %d is added at %d",n,i);
    if(i==5)i=0;
    pthread_mutex_unlock(&m);
    sem_post(&full);
    sleep(1);
  }
}
void *consumer(void *arg){
  int key,i=0;
  while(1){
    sem_wait(&full);
    pthread_mutex_lock(&m);
    key=buf[i++];
    printf("\nNumber %d is consumed %d",key,i);
    if(i==5)i=0;
    pthread_mutex_unlock(&m);
    sem_post(&full);
    sleep(2);
  }
}
int main(){
  pthread_mutex_init(&m,NULL);
  sem_init(&empty,0,5);
  sem_init(&full,0,0);
  pthread_create(&pid,NULL,producer,NULL);
  pthread_create(&cid,NULL,consumer,NULL);
  pthread_join(pid,NULL);
  pthread_join(cid,NULL);
  return 0;
}

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t wrt;
sem_t mutex;
int readcount=0;
int shared_data=0;

void *reader(void *arg){
  int reader_id = *(int *)arg;
  while(1){
    sem_wait(&mutex);
    readcount++;
    if(readcount==1){
      sem_wait(&wrt);
    }
    sem_post(&mutex);
    printf("Reader %d is reading : %d\n",reader_id,shared_data);
    sleep(1);
    sem_wait(&mutex);
    readcount--;
    if(readcount==0){
      sem_post(&wrt);
    }
    sem_post(&mutex);
    sleep(2);
  }
}
void *writer(void *arg){
  int writer_id = *(int *)arg;
  while(1){
    sem_wait(&wrt);
    shared_data++;
    printf("Writer %d is writing : %d\n",writer_id,shared_data);
    sleep(2);
    sem_post(&wrt);
    sleep(3);
  }
}
int main(){
  pthread_t reader_threads[5];
  pthread_t writer_threads[5];
  int reader_ids[5];
  int writer_ids[5];
  sem_init(&wrt,0,1);
  sem_init(&mutex,0,1);
  for(int i=0;i<5;i++){
    reader_ids[i]=i+1;
    pthread_create(&reader_threads[i],NULL,reader,&reader_ids[i]);
  }
  for(int i=0;i<2;i++){
    writer_ids[i]=i+1;
    pthread_create(&writer_threads[i],NULL,writer,&writer_ids[i]);
  }
  for(int i=0;i<5;i++){
    pthread_join(reader_threads[i],NULL);
  }
  for(int i=0;i<2;i++){
    pthread_join(writer_threads[i],NULL);
  }
  sem_destroy(&wrt);
  sem_destroy(&mutex);
  return 0;
}
  
  

