
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char **argv){
    int i;
    for (i = 0; i < 2; i++){
        if (i == 1){
            set_priority(1);
        }

        if (fork() == 0) {
            if (i == 0){
				printf("entered low priority job\n");
                int j;
                for (j = 0; j < 999999999; j++){}
				printf("finished low priority job\n");
            }
            else {
				printf("entered high priority job\n");
                printf("finished high priority job\n");
            }
            exit(0);
        }
    }
	exit(0);
}

//     int cpid = fork();
//     if (cpid != 0)
//     {
//         set_priority(3);
//         //sleep(10);
//         for (int i = 1; i < 2; i++)
//         {
//             printf("I am a process with priority 3: %d\n", cpid);
//             //            sleep(10);
//         }
//     }
//     else
//     {
//         set_priority(4);
//         sleep(10);
//         for (int j = 1; j < 2; j++)
//         {
//             printf("I am a process with priority 4: %d\n", cpid);
//             //            sleep(10);
//         }
//     }
//     exit(0);
// }