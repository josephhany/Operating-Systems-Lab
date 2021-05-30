//#include <pfork.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "pfork.h"

int main ( int argc, char ** argv ) {
    pid_t cpid = pfork();
    if (cpid !=0 )
        for (;wait(NULL) > 0 ;);
    else
        {
            char who[10];
            memset (who,10,0);
            if ( pfork_who() == 1 )
                strcpy (who,"STANDBY");
            else strcpy (who,"ACTIVE");
            for ( int  i = 0 ; i  < 5 ; i ++ )
                {
                    long int status = get_pfork_status();
                    if ( status == i )
                        {
                            printf ("%s: Current Status is %d \n",who,status);
                            sleep ((i+1)*10);
                            set_pfork_status(i+1);

                            printf ("%s: Set Status is %d \n",who,status+1);
                        }
                }
        }
        return 0;
}
