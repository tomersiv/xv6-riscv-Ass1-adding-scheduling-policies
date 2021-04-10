#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

struct perf
{
    int ctime;
    int ttime;
    int stime;
    int retime;
    int rutime;
    int average_bursttime; //average of bursstimes in 100ths (so average*100)
};
void print_perf(int *status, struct perf *performance);

int main(int argc, char **argv)
{
    int pid1, status1; 
    struct perf perf2;
    pid1 = fork();
    if (pid1 > 0)
    {
        wait_stat(&status1, &perf2);
        print_perf(&status1, &perf2);
    }
    else
    {
        for (int a = 0; a < 10; ++a)
        {
            uint64 i = 0;
            while (i < 9999){
                i++;
                uint64 j = 0;
                while (j < 9999) {
                    j++;
                }
            }
            sleep(1);
        }

        exit(1);
    }
    exit(0);
}

void print_perf(int *status, struct perf *performance)
{
    fprintf(1, "exit status: %d\n", *status);
    fprintf(1, "pref:\n");
    fprintf(1, "\tctime: %d\n", performance->ctime);
    fprintf(1, "\tttime: %d\n", performance->ttime);
    fprintf(1, "\tstime: %d\n", performance->stime);
    fprintf(1, "\tretime: %d\n", performance->retime);
    fprintf(1, "\trutime: %d\n", performance->rutime);
    fprintf(1, "\n\tTurnaround time: %d\n", (performance->ttime - performance->ctime));
}