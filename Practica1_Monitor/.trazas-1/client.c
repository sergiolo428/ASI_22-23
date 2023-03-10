/*Sergio Lopez Alejandro - Practica1_Monitor */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

void handler(int);
void *funcionHilo(void *arg);

int threadTimer = 0;

int main(int argc, char** argv) {
    int val;
    int idm=atoi(argv[1]);    
    int pid1,pid2,status,i;
    
    pthread_t mythread;
    
    while(1){
        printf("Introduce el ejercicio a realizar: ");
        scanf("%d",&val);
        switch(val){
            case 1:
                printf("Ejercicio 1: \n");
                kill(idm,SIGUSR1);
                printf("Señal enviada a %d\n",idm);
                sleep(5);
                exit(0);
                break;
            case 2:
                kill(idm,SIGUSR1);
                signal(SIGUSR2,handler);
                printf("Ejercicio 2: %d \n",getpid());
                pause();
                kill(idm,SIGUSR2);
                exit(0);
                break;
            case 3:
                
                printf("Ejercicio 3: \n");
                kill(idm,SIGUSR1);
                sleep(1);
                
                pid1=fork();
                if(pid1==0){
                    /*Hijo 1*/
                    sleep(3);
                    _exit(0);
                }else{
                    pid2=fork();
                    if(pid2==0){
                        /*Hijo 2*/
                        kill(idm,SIGUSR1);
                        sleep(1);
                        _exit(0);
                    }else{
                        /*Padre*/
                        wait(&status);
                        sleep(1);
                        _exit(0);
                    }
                }
                    
                
                break;
            case 4:
               /* 
                //Try1
                printf("Ejercicio 4: \n");
                pid1=fork();
                if(pid1==0){
                    //Hijo1
                    i=0;
                    signal(SIGUSR2,handler);
                    
                    while(1){
                        pause();
                        i++;
                        printf("%d Señal\n",i);
                        //Creamos hilo
                        pthread_create(&mythread,NULL,funcionHilo,&i);
                    }
                    _exit(0);
                }else{
                    //Padre
                    sleep(25);
                    kill(pid1,SIGKILL);
                    _exit(0);
                }
                break;
                */
                        
                //Try2
                printf("Ejercicio 4: \n");
                pid1=fork();
                if(pid1==0){
                    //Hijo 1
                    signal(SIGUSR2,handler);
                    do{
                        pause();
                        if(threadTimer==0){
                            pthread_create(&mythread,NULL,funcionHilo,&i);
                        }
                    }while(threadTimer==0);
                }else{
                    //Padre
                    wait(&status);
                    printf("Padre saliendo.\n");
                    exit(0);
                }
                break;
            case 5:
                printf("Ejercicio 5: \n");
                
                kill(idm,SIGUSR1);
                
                pid1=fork();
                if(pid1==0){
                    /*Hijo1*/
                    signal(SIGUSR2,handler);
                    pause();
                    printf("a");
                    _exit(0);
                }else{
                    pid2=fork();
                    if(pid2==0){
                        /*Hijo2*/
                        printf("Soy el Hijo 2: %d.\n",getpid());
                        signal(SIGUSR1,handler);
                        pause();
                        printf("Comienzo.\n");
                        i=0;
                        while(1){
                            signal(SIGUSR2,handler);
                            pause();
                            kill(idm,SIGUSR2);
                            i++;
                            printf("Señal %d.\n",i);
                        }
                    }else{
                        /*Padre*/
                        sleep(60);
                        kill(pid1,SIGKILL);
                        kill(pid2,SIGKILL);
                        _exit(0);
                    }
                }
                
                break;
            case 6:
                printf("Ejercicio 6: \n");
                kill(idm,SIGUSR1);
                sleep(1);
                
                _exit(0);
                break;
            default:
                printf("Programa finalizado.\n");
                _exit(0);
        }
    }
    return (EXIT_SUCCESS);
}

void handler(int n){
    printf("Señal %d obtenida.\n",n);
}

void handlerexit(int n){
    printf("Señal %d obtenida y saliendo.\n",n);
    _exit(0);
}

void* funcionHilo(void *arg){
    int val=*(int *)arg;
    int a=0;
    while(a<=3){
        printf("Soy el hilo %d.\n",val);
        sleep(5);
        a++;
    }
    threadTimer=1;
    kill(getpid(),SIGUSR2);
    pthread_exit(NULL);
}