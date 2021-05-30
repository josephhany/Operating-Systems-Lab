//#include <pfork.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <unistd.h>

int main ( int argc, char ** argv ) {
    pid_t cpid = syscall(440);
    if (cpid !=0 )
        for (;wait(NULL) > 0 ;);
    else
        {
            char who[10];
            memset (who,10,0);
            if ( syscall(444)== 1 )
                strcpy (who,"STANDBY");
            else strcpy (who,"ACTIVE");
            for ( int  i = 0 ; i  < 5 ; i ++ )
                {
                    long int status = syscall(441);;
                    if ( status == i )
                        {
                            printf ("%s: Current Status is %d \n",who,status);
                            sleep ((i+1)*10);
                            syscall(443, i+1);

                            printf ("%s: Set Status is %d \n",who,status+1);
                        }
                }
        }
        return 0;
}