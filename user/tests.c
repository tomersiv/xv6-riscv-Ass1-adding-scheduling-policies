#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

//funcs
void test_for_bursttime_when_son_just_dies();
void testing_trace();
void extra_complicated_long_test();
void test_for_bursttime_when_son_does_long_stuff();
void test_for_bursttime_when_proces_with_lots_short_running_time(int num);
void test_with_lots_of_processes_for_order_checks();
void test_for_FCFS();
void test_for_FCFS_2childs_different_creation_time();
void test_for_SRT_preemptive();

struct perf {
    int ctime;
    int ttime;
    int stime;
    int retime;
    int rutime;
    int average_bursttime; //average of bursstimes in 100ths (so average*100)

};


int main(int argc, char** argv){
    fprintf(2, "Hello world!\n");
    // testing_trace();//task2
    // extra_complicated_long_test();//mainly for task3
    // test_for_bursttime_when_son_just_dies();// tasks 3 + 4.3. expecte bursttime 500?
    //test_for_bursttime_when_son_does_long_stuff();
    test_for_bursttime_when_proces_with_lots_short_running_time(100);//with num 100 expects burrst time 0.  
                                                                      //with num 2 expects burrst time ? Explenation: 
                                                                      // - born with 500
                                                                      // after firsr run in while - 250
                                                                      // after second run in whike - 125
                                                                      // afetr exit - 62
    //test_with_lots_of_processes_for_order_checks();                                                                  
    //test_for_FCFS();
    //test_for_FCFS_2childs_different_creation_time();
    test_for_SRT_preemptive();
    exit(0);

}

void test_for_SRT_preemptive(){
    int i= 0;
    while(i<300000000){
        i++;
    }
    exit(0);
}

void test_for_FCFS_2childs_different_creation_time(){
    int cpid=fork();
    fprintf(1, "cpid is: %d\n", cpid);
    if(cpid==0){//son like sunshine
        fprintf(1, "son going to sleep...\n");
        sleep(2);
        fprintf(1, "son waking up & exiting...\n");
        exit(0);
    }
    else{//father
        int i = 0;
        fprintf(1, "father start wasting time...\n");
        while(i<1000000000){
            i++;
            //if(i==100000000){sleep(1);}
        }
        int cpid2=fork();
        fprintf(1, "cpid2 is: %d\n", cpid2);
        if(cpid2==0){//son like sunshine
            fprintf(1, "son going to sleep...\n");
            sleep(2);
            fprintf(1, "son waking up & exiting...\n");
            exit(0);
        }
        else{
            fprintf(1, "father going to sleep...\n");
            sleep(2);
            fprintf(1, "father waking up & waiting...\n");
            wait(0);
            wait(0);
        }
    }
}

void test_for_FCFS(){
    int cpid=fork();
    fprintf(1, "cpid is: %d\n", cpid);
    if(cpid==0){//son like sunshine
    int i = 0;
            while(i<1000000000){
            i++;
        }
        fprintf(1, "son going to sleep...\n");
        sleep(2);
        fprintf(1, "son waking up & exiting...\n");
        exit(0);
    }
    else{//father
        //int i = 0;
        fprintf(1, "father start wasting time...\n");
        /*
        while(i<1000000000){
            i++;
            if(i==100000000){sleep(1);}
        }
        */
        fprintf(1, "father going to sleep...\n");
        sleep(2);
        fprintf(1, "father waking up & waiting...\n");
        wait(0);
    }
}


void test_with_lots_of_processes_for_order_checks(){
    int i=0;
    struct perf* performance = malloc(sizeof(struct perf));
    int cpid=fork();
    if(cpid==0){//son like sunshine
        while(i<5){
            int cpid2=fork();
            if(cpid2==0){//grandchild
                if(i%2==0){
                    int k=0;
                    while(k<10000000000000){
                        k++;
                    }
                }
                else{
                    sleep(1);
                    sbrk(2);
                    int k=0;
                    while(k<10000000000000){
                        k++;
                    }
                }
                exit(0); //so grandchild won't make kids
            }
            else{//father (child1)
                wait(0);
            }
            i++;
        }
    }
    else{//father
    int t_pid = wait_stat(0, performance);
    fprintf(1, "terminated pid: %d, ctime: %d, ttime: %d, stime: %d, retime: %d, rutime: %d average_bursttime: %d \n",
                t_pid, performance->ctime, performance->ttime, performance->stime, performance->retime, performance->rutime,
                 performance->average_bursttime);
    }
}

void test_for_bursttime_when_proces_with_lots_short_running_time(int num){
    int i=0;
    struct perf* performance = malloc(sizeof(struct perf));
    int cpid=fork();
    if(cpid==0){//son like sunshine
        while(i<num){
            i++;
            sleep(1);
        }
    }
    else{//father
    int t_pid = wait_stat(0, performance);
    fprintf(1, "terminated pid: %d, ctime: %d, ttime: %d, stime: %d, retime: %d, rutime: %d average_bursttime: %d \n",
                t_pid, performance->ctime, performance->ttime, performance->stime, performance->retime, performance->rutime,
                 performance->average_bursttime);
    }
}


void test_for_bursttime_when_son_does_long_stuff(){
    int i=0;
    struct perf* performance = malloc(sizeof(struct perf));
    int cpid=fork();
    if(cpid==0){//son like sunshine
        while(i<1000000000){
            i++;
        }
    }
    else{//father
    int t_pid = wait_stat(0, performance);
    fprintf(1, "terminated pid: %d, ctime: %d, ttime: %d, stime: %d, retime: %d, rutime: %d average_bursttime: %d \n",
                t_pid, performance->ctime, performance->ttime, performance->stime, performance->retime, performance->rutime,
                 performance->average_bursttime);
    }
}


void test_for_bursttime_when_son_just_dies(){
    struct perf* performance = malloc(sizeof(struct perf));
    int cpid=fork();
    if(cpid==0){//son like sunshine
        exit(0);
    }
    else{//father
    int t_pid = wait_stat(0, performance);
    fprintf(1, "terminated pid: %d, ctime: %d, ttime: %d, stime: %d, retime: %d, rutime: %d average_bursttime: %d \n",
                t_pid, performance->ctime, performance->ttime, performance->stime, performance->retime, performance->rutime,
                 performance->average_bursttime);
    }
}

void testing_trace(){
    //mask=(1<< SYS_fork)|( 1<< SYS_kill)| ( 1<< SYS_sbrk) | ( 1<< SYS_write);
    int mask=(1<< 1);
    sleep(1); //doesn't print this sleep
    trace(mask, getpid());
    int cpid=fork();//prints fork once
    if (cpid==0){
        fork();// prints fork for the second time - the first son forks
        //mask= (1<< 13); //to turn on only the sleep bit
        mask= (1<< 1)|(1<< 13); //you can uncomment this inorder to check you print for both fork and sleep syscalls
        trace(mask, getpid()); //the first son and the grandchilde changes mask to print sleep
        sleep(1);
        fork();//should print nothing
        exit(0);//shold print nothing
    }
    else {
        sleep(10);// the father doesnt pring it - has original mask
    }
    mask= (1<< 12)|( 1<< 2) | (1<<6); //sbrk & exit & kill
    trace(mask, getpid());
    cpid= fork();
    kill(cpid);
    sbrk(4096);
}

void extra_complicated_long_test(){

    struct perf* performance = malloc(sizeof(struct perf));
    int mask=(1<< 1) | (1<< 23) | (1<< 3);
    trace(mask, getpid());
    int cpid = fork();
    if (cpid != 0){
        int t_pid = wait_stat(0, performance);
        fprintf(1, "terminated pid: %d, ctime: %d, ttime: %d, stime: %d, retime: %d, rutime: %d average_bursttime: %d \n", t_pid, performance->ctime, performance->ttime, performance->stime, performance->retime, performance->rutime, performance->average_bursttime);
    }
    else{
        sleep(10);
        for(int i=1; i < 15; i++){
            int c_pid = fork();
            if(c_pid == 0){
                sleep(i);
                exit(0);
            }
            else{
                int i = 0;
                while(i<100000000){
                    i++;
                }
            }
        }
        sleep(10);
        for(int i=1; i < 15; i++){
            int c_pid = fork();
            if(c_pid == 0){
                int i = 0;
                while(i<10000000){
                    i++;
                }
                exit(0);
            }
            else{
                int t_pid = wait_stat(0, performance);
                fprintf(1, "terminated pid: %d, ctime: %d, ttime: %d, stime: %d, retime: %d, rutime: %d average_bursttime: %d \n", t_pid, performance->ctime, performance->ttime, performance->stime, performance->retime, performance->rutime, performance->average_bursttime);
                int i = 0;
                while(i<10000){
                    i++;
                }
            }
        }
    }
}


