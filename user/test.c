
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

// int main(int argc, char **argv)
// {
//     int cpid = fork();
//     if (cpid != 0)
//     {
//         set_priority(4);
//         //sleep(10);
//         for (int i = 1; i < 999; i++)
//         {
//             printf("I am a process with priority 4: %d\n", i);
//             //            sleep(10);
//         }
//     }
//     else
//     {
//         set_priority(1);
//         //sleep(10);
//         for (int j = 1; j < 999; j++)
//         {
//             printf("I am a process with priority 1: %d\n", j);
//             //            sleep(10);
//         }
//     }
//     exit(0);
// }

//////////////////////////////////////////////////////////////////////////////////////

// CFSD test
//     int i;
//     for (i = 1; i < 101; i++){
//         if (i % 10 == 0){
//             set_priority(1);
//         }
//         if (fork() != 0) {
//             set_priority(5);
//         }
//         else {
//             if (i %10 == 0){
// 				fprintf(1,"entered process #%d: high priority job\n", i);
//                 int j;
//                 for (j = 0; j < 100000; j++){
//                     int k;
//                     for (k = 0; k < 100000; k++) {}
//                 }
// 				fprintf(1,"exited process #%d: high priority job\n", i);
//             }
//             else {
// 				fprintf(1,"entered process #%d: low priority job\n", i);
//                 int j;
//                 for (j = 0; j < 100000; j++){
//                     int k;
//                     for (k = 0; k< 100000; k++) {}
//                 }
//                 fprintf(1,"exited process #%d: low priority job\n", i);
//             }
//             exit(0);
//         }
//     }
//     for (i=1; i < 101; i++){
//         wait(0);
//     }
// 	exit(0);
// }

//////////////////////////////////////////////////////////////////////////////////////

// FCFS test
int main(int argc, char **argv){
    int i;
    for (i = 0; i < 60; i++){
        if (fork() == 0){
            fprintf(1, "entered process %d\n", i);
            if (i >= 20 && i <= 30) {
                fprintf(1, "process %d went to sleep\n", i);
                sleep(10);
                fprintf(1, "process %d woke up\n", i);
            }
            int j;
            for (j = 0; j < 10000; j++){
                int k;
                for (k = 0; k < 10000; k++) {}
            }
            fprintf(1, "exited process %d\n", i);
            exit(0);
        }
    }
    for(i = 0; i < 60; i++){
        wait(0);
    }
    exit(0);
}