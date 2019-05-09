#include<stdio.h>
#include<pthread.h>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include "MyQueue.h"
using namespace std;
pthread_mutex_t Mutex1 = PTHREAD_MUTEX_INITIALIZER; // used to lock the queue
pthread_mutex_t Mutex2 = PTHREAD_MUTEX_INITIALIZER; // Mutex2 is used to lock currentSeq

struct thread_data{ // thread argument passing
    int interval;
    int maxtoken;
};

// init
int tokenFetch=0, tokenDrop=0, currentSeq=0, tokenAdd=0;
sem_t empty;
MyQueue* que;

void* generate(void* arg);
void* fetch(void* arg);
void* add(void* arg);
int getDigit(int num){  // get integer's digit to unify output format
    if(num==0)return 1;

    int res =0;
    while(num>=1){
        res++;
        num /= 10;
    }
    return res;
    
}

int main(int argc, char* argv[]){

    int maxToken, flowInterval;

    // check input
    if(argc<=2){    // handle no input
        printf("Please input maxToken and flowInterval!\n");
        exit(EXIT_FAILURE);
    }

    maxToken = atoi(argv[1]);
    flowInterval = atoi(argv[2]); 

    if(maxToken<=0 && flowInterval<1){  // handle no maxtoken or flowinterval
        printf("maxToken and flowInterval are invalid!\n");
        exit(EXIT_FAILURE);
    }
    else if(maxToken <= 0){ 
        printf("maxToken should be a positive integer!\n");
        exit(EXIT_FAILURE);
    }
    else if(flowInterval< 1){   
        printf("FlowInterval should be an integer >= 1!\n");
        exit(EXIT_FAILURE);
    }
    que = new MyQueue(maxToken);

    // output information
    printf("The Max Token is %d and the interval time for flow is %d\n",maxToken,flowInterval);
    printf("Flow%*sQueue%*sServer\n",36,"",11,"");
    printf("Token added%*sLast sequence number%*sCurrent Length%*sToken fetched%*sTotal Token fetched\n",5,"",4,"",2,"",3,"");

    int flow, pflow, server;
    pthread_t threads[3];
    sem_init(&empty,0,0);

    // create flow thread
    thread_data flow_thread_data = {flowInterval,maxToken};
    flow = pthread_create(&threads[0],NULL,generate,(void *)&flow_thread_data);
    if(flow){   // judge if flow create pthread successful
        printf("Error when creating flow thread!\n");
        exit(EXIT_FAILURE);
    }

    // create server
    thread_data server_thread_data = {2,maxToken};
    server = pthread_create(&threads[1],NULL,fetch,(void *)&server_thread_data);
    if(server){ // judge if flow create thread successful
        printf("Error when creating server thread!\n");
        exit(-1);
    }

    // create pflow
    thread_data pflow_thread_data = {1,maxToken};
    pflow = pthread_create(&threads[2],NULL,add,(void *)&server_thread_data);
    if(pflow){ // judge if flow create thread successful
        printf("Error when creating pflow thread!\n");
        exit(-1);
    }

    // join flow and server threads
    void *retval;
    flow = pthread_join(threads[0],&retval);
    if(flow){   // judge if join flow thread successful
        printf("Error when joining flow thread!\n");
        exit(-1);
    }

    server = pthread_join(threads[1],&retval);
    if(server){ // judge if join flow thread successful
        printf("Error when joining server thread!\n");
        exit(-1);
    }

    pflow = pthread_join(threads[2],&retval);
    if(pflow){   // judge if join flow thread successful
        printf("Error when joining flow thread!\n");
        exit(-1);
    }

    // output result
    printf("The total number of tokens that have been fetched by the server is %d\n",tokenFetch);
    printf("The total number of tokens that have been generated by the flow is %d\n",currentSeq-tokenAdd);
    printf("The total number of tokens that have been generated by the pflow is %d\n",tokenAdd);
    printf("The total number of tokens that have been dropped by the queue is %d\n",tokenDrop);

    sem_destroy(&empty);
    pthread_exit(NULL); //exit main thread
}

// the rountine that the flow thread execute to generate token
void* generate(void* arg){

    srand((unsigned)time(NULL));    // prepare generate random number

    // save arguments to local
    thread_data *gen_data;
    gen_data = (thread_data *) arg;

    int flow_Interval = gen_data->interval;
    int max_Token = gen_data->maxtoken;

    while((tokenFetch+tokenDrop)<max_Token){  // generate token until reach maxtoken
        
        sleep(flow_Interval);    // wait few second

        int nb_generate = rand()%10+1; // generate random number to fetch

        if(pthread_mutex_lock(&Mutex1) != 0){   // lock the queue and check if it success
            printf("Fail to lock the queue!\n");
            exit(-1);
        }
        if(pthread_mutex_lock(&Mutex2) != 0){   // lock currentSeq and check if it success
            printf("Fail to lock currentSeq!\n");
            exit(-1);
        }   

        currentSeq += nb_generate;
        if(que->isFull()){  // if queue is full, drop token
            tokenDrop += nb_generate;
        }
        else    // if queue not full, add tokens into queue
        {
            for(int i=0;i<nb_generate;i++)
                que->enqueue(1);
        }

        printf("%d(flow)%*s%d%*s%d\n",nb_generate,10-getDigit(nb_generate),"",currentSeq-1,24-getDigit(currentSeq),"",que->getSize());

        if(pthread_mutex_unlock(&Mutex2) != 0){   // unlock currentSeq and check if it success
            printf("Fail to unlock currentSeq!\n");
            exit(-1);
        }
        if(pthread_mutex_unlock(&Mutex1) != 0){     // unlock queue and check
            printf("Fail to unlock the queue!\n");
            exit(-1);
        } 
    }

    pthread_exit(NULL); // thread exit
}

// the rountine that the server thread execute to fetch token
void* fetch(void* arg){

    srand((unsigned)time(NULL));

    thread_data *fet_data;
    fet_data = (thread_data *)arg;

    int fetch_Interval = fet_data->interval;
    int max_Token = fet_data->maxtoken;

    while((tokenFetch+tokenDrop)<max_Token){  // fetch token until reach maxtoken
        sleep(fetch_Interval);

        int nb_fetch = rand()%20+1;   // generate random number to fetch
        if(pthread_mutex_lock(&Mutex1) != 0){   // lock the queue and check if it success
            printf("Fail to lock the queue!\n");
            exit(-1);
        }
        int server_fetch_num=0;

        if(que->getSize() > nb_fetch){   // if enough tokens in queue to fetch
            for(int i=0;i<nb_fetch;i++){
                tokenFetch++;
                que->dequeue();
                server_fetch_num++;
                if (tokenFetch == max_Token) { // judge if reach maxtoken after every fetch
                    sem_post(&empty);	
		    break;    
                }     
            }
        }
        else    // if tokens in queue isn't enough to fetch
        {
            int len = que->getSize();
            for(int i=0;i<len;i++){
                tokenFetch++;
                que->dequeue();
                server_fetch_num++;
                if (tokenFetch == max_Token) { // judge if reach maxtoken after every fetch
                    sem_post(&empty);
		    break;    
                }     
            }
	    sem_post(&empty);
        }
        printf("%*s%d%*s%d%*s%d\n",40,"",que->getSize(),16-getDigit(que->getSize()),"",server_fetch_num,16-getDigit(server_fetch_num),"",tokenFetch);
        
        if(pthread_mutex_unlock(&Mutex1) != 0){     // unlock queue and check
            printf("Fail to unlock the queue!\n");
            exit(-1);
        }
    }

    pthread_exit(NULL); // server thread exit
}

void* add(void* arg){
    srand((unsigned)time(NULL));    // prepare generate random number

    // save arguments to local
    thread_data *gen_data;
    gen_data = (thread_data *) arg;

    int pflow_Interval = gen_data->interval;
    int max_Token = gen_data->maxtoken;

    while(tokenFetch+tokenDrop < max_Token){  // generate token until reach maxtoken
	sem_wait(&empty);
	if((tokenFetch + tokenDrop) >= max_Token) break;

        int nb_add = rand()%5+1; // generate random number to fetch
        
       if(pthread_mutex_lock(&Mutex1) != 0){   // lock the queue and check if it success
            printf("Fail to lock the queue!\n");
            exit(-1);
        }
        if(pthread_mutex_lock(&Mutex2) != 0){   // lock currentSeq and check if it success
            printf("Fail to lock currentSeq!\n");
            exit(-1);
        }
        currentSeq += nb_add;
        tokenAdd += nb_add;
        for(int i=0;i<nb_add;i++)
            que->enqueue(1);

        printf("%d(pflow)%*s%d%*s%d\n",nb_add,9-getDigit(nb_add),"",currentSeq-1,24-getDigit(currentSeq),"",que->getSize());

        if(pthread_mutex_unlock(&Mutex2) != 0){   // unlock currentSeq and check if it success
            printf("Fail to unlock currentSeq!\n");
            exit(-1);
        }
        if(pthread_mutex_unlock(&Mutex1) != 0){     // unlock queue and check
            printf("Fail to unlock the queue!\n");
            exit(-1);
        }
    }

    pthread_exit(NULL); // thread exit
}