#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define BUFFER_LEN 1024

#define read_stream 0
#define write_stream 1

char command[BUFFER_LEN];

size_t read_command(char *cmd) {
    if(!fgets(cmd, BUFFER_LEN, stdin)) /*get command and put it in line*/
    return 0;    /*if user hits CTRL+D break*/
    size_t length = strlen(cmd); /* get command length*/
    strncpy(command,cmd,length+1);
    if (cmd[length - 1] == '\n') cmd[length - 1] = '\0'; /* clear new line*/
    return strlen(cmd); /* return length of the command read*/
}

int build_args(char * cmd, char ** argv, char* delimiter) {
    char *token; /*split command into separate strings*/
    token = strtok(cmd,delimiter);
    int i=0;
    while(token!=NULL){/* loop for all tokens*/
		argv[i]=token; /* store token*/
		token = strtok(NULL,delimiter); /* get next token*/
		i++; /* increment number of tokens*/
    }
    argv[i]=NULL; /*set last value to NULL for execvp*/
    return i; /* return number of tokens*/
}

void set_program_path (char * path, char * bin, char * prog) {
	memset (path,0,1024); /* intialize buffer*/
	strcpy(path, bin);	/*copy /bin/ to file path*/
	strcat(path, prog);	/*add program to path*/
	int i;
	for(i=0; i<strlen(path); i++) /*delete newline*/
	if(path[i]=='\n') path[i]='\0';
}

int exec_cd(char* dir_to_go_to){
	return chdir(dir_to_go_to);
}

void exec_multi_pipes(char** argv,int pipes_argc);

void exec_redirection(char* command,int in_out){
	
	char* argv[100];
	int pipes_argc;
	if(in_out==1)pipes_argc=build_args(command,argv,">");
	else if(in_out==0)pipes_argc=build_args(command,argv,"<");

	int pid = fork();
	if (pid < 0){
			printf("\nError in fork");
			exit(0);
	}
    
	else if (pid == 0)
	{
	    /* Be childish */
	    if (in_out==0)
	    {
	    	char es[BUFFER_LEN];
			strcpy(es,argv[1]);
			es[strlen(argv[1])-1]='\0';
			
	        int fd0 = open(es, O_RDONLY);
	        dup2(fd0, 0);/*STDIN_FILENO);*/
	        close(fd0);
	    }

	    else if (in_out==1)
	    {
	        int fd1 = creat(argv[1], 0644) ;
	        dup2(fd1, STDOUT_FILENO);
	        close(fd1);
	    }
	    

		if(strchr(command,'|')!=NULL){
			char* pipes_argv[100];
			command[strlen(command)-1]='\0';
			int pipes_argc=build_args(command,pipes_argv,"|");
			exec_multi_pipes(pipes_argv,pipes_argc);
		}

				if(strchr(argv[0],'<')!=NULL){
					exec_redirection(argv[0],0);
				}
				
				char* argv_curr[100];
				int argc;
				argc = build_args (argv[0],argv_curr," "); /* build program argument*/
				
				char* bin= "/bin/"; /*set path at bin*/
	    		char path[1024];   	/*full file path*/
	    		set_program_path (path,bin,argv_curr[0]); /* set program full path*/
				execve(path,argv_curr,0);
				printf("failed to execute\n");
				exit(0);
		
	}
	/*cat</etc/hosts | grep 127 > dump.txt*/

	else
	{	
			waitpid(pid, NULL, 0);		
			exit(0);
	}

}

void exec_multi_pipes(char** argv,int pipes_argc)
{
	int fd[100][2];
	int status;
	int pid[100] = {-1};
	int count = 0;
	int i;
		
	while (1)
	{
		status = pipe(fd[count]);
		if (status < 0)
		{
			printf("\npipe error");
			exit(0);
		}
		
		
		pid[count] = fork();
		
		if (pid[count] < 0)
		{
			printf("\nError in fork");
			exit(0);
		}
		else if (pid[count]) /* parent*/
		{
			if (count<pipes_argc-1)
			{
				count++;
				continue;
			}
			
			/*close all opened pipes*/
			for (i = 0; i <= count; i++)
			{
				close(fd[i][read_stream]);				
				close(fd[i][write_stream]);
			}


			
				for (i = 0; i <= count; i++)
					waitpid(pid[i], NULL, 0);
			
			exit(0);
		}
		else	/* child*/
		{
			if (count == 0)
				close(fd[count][read_stream]);
			else
				dup2(fd[count-1][read_stream], 0);
			



			if (count==pipes_argc-1)
				close(fd[count][write_stream]);
			else
				dup2(fd[count][write_stream],1);
							

			/*close all other opened pipes*/
			for (i = 0; i <= count; i++)
			{
				close(fd[i][read_stream]);
				close(fd[i][write_stream]);
			}
			
			
			if(strchr(argv[0],'>')!=NULL){
					char* argv[100];
					int pipes_argc;
					pipes_argc=build_args(command,argv,">");
					
			        int fd1 = creat(argv[1], 0644) ;
			        dup2(fd1, STDOUT_FILENO);
	    		    close(fd1);

	    		}
    		else if(strchr(argv[0],'<')!=NULL){
				char* argv[100];
				int pipes_argc;
				pipes_argc=build_args(command,argv,"<");
	        	char es[BUFFER_LEN];
				strcpy(es,argv[1]);
				es[strlen(argv[1])-1]='\0';
			
	        	int fd0 = open(es, O_RDONLY);
	        	dup2(fd0, 0);/*STDIN_FILENO);*/
	        	close(fd0);
	        }
	        
			char* argv_curr[100];
			int argc = build_args (argv[count],argv_curr," "); /* build program argument*/
			char* bin= "/bin/"; /*set path at bin*/
    		char path[1024];   	/*full file path*/
    		set_program_path (path,bin,argv_curr[0]); /* set program full path*/
    		execve(path,argv_curr,0);

			printf("failed to execute\n");
			exit(0);
			
		}
		
					
	}	
				
}


int main(){
    char line[BUFFER_LEN]; /*get command line*/
    char* argv[100];    /*user command*/
    char* bin= "/bin/"; /*set path at bin*/
    char path[1024];   	/*full file path*/
    int argc;    /*arg count*/


    while(1){
	    printf("My shell>> ");	    /*print shell prompt*/
	    if (read_command(line) == 0 ){
		   	printf("\n"); 
		   	break;
	   	} /* CRTL+D pressed*/


	   	if(strchr(command,'=') && strchr(command,'\`')){
	   			char* pipes_argv[100];
				int pipes_argc=build_args(command,pipes_argv,"=");
				char *token; /*split command into separate strings*/
    			token = strtok(pipes_argv[1],"\`");
				char es[BUFFER_LEN];
				strcpy(es,"=");
				strcat(es,token);
				setenv(pipes_argv[0],es,1);
				continue;
			}
		else if(strchr(command,'=') && strchr(command,'$')){
	   			char* pipes_argv[100];
				int pipes_argc=build_args(command,pipes_argv,"=");

				char* ar[100];
	    		int rc=build_args(pipes_argv[1],ar,"$");

	    		char c[BUFFER_LEN];
	    		memset (c,0,1024); /* intialize buffer*/
	    		strcpy(c,ar[0]);
	    		c[strlen(ar[0])-1]='\0';
				setenv(pipes_argv[0],getenv(c),1);	
				
				continue;
			}
    	else if(strchr(command,'=')){
				char* pipes_argv[100];
				int pipes_argc=build_args(command,pipes_argv,"=");
				setenv(pipes_argv[0],pipes_argv[1],1);
				continue;
			}
			else if(strchr(command,'echo') && strchr(command,'$')){
				char* pipes_argv[100];
	    		int pipes_argc=build_args(command,pipes_argv,"$");
	    		char c[BUFFER_LEN];
	    		memset (c,0,1024); /* intialize buffer*/
	    		strcpy(c,pipes_argv[1]);
	    		c[strlen(pipes_argv[1])-1]='\0';
	    		if(strchr(getenv(c),'=')){
	    			char *token; /*split command into separate strings*/
    				token = strtok(getenv(c),"=");
	    			strcpy(line,token);
	    		}
	    		else{
	    			printf("%s",getenv(c));
	    			continue;
	    		}
			}
	
	

	    if (strcmp(line, "exit") == 0) exit(0); /*exit*/

	    argc = build_args (line,argv," "); /* build program argument*/

	    
	    if(strcmp(argv[0],"cd")==0){

	    	if(argc==1){
	    		if(exec_cd(getenv("HOME"))<0)perror(getenv("HOME"));
	    	}
	    	else{
	    		if(exec_cd(argv[1])<0)perror(argv[1]);
	    	}

	    	continue; /* we do not need to execute the fork any more*/
	    }

	    set_program_path (path,bin,argv[0]); /* set program full path*/
	    int pid= fork();	    /*fork child*/
	    if(pid==0){	        /*Child*/
			
			if(strchr(command,'>')){
	    			exec_redirection(command,1);
	    		}
	    	else if(strchr(command,'|')!=NULL){
	    			char* pipes_argv[100];
	    			command[strlen(command)-1]='\0';
	    			int pipes_argc=build_args(command,pipes_argv,"|");
	    			exec_multi_pipes(pipes_argv,pipes_argc);
	        }
	        else if(strchr(command,'<')!=NULL){
	        	exec_redirection(command,0);
	        }
	        else{
	        	execve(path,argv,0); /* if failed process is not replaced*/
	        	printf("failed\n");
	    	}
	        /* then print error message*/
	        fprintf(stderr, "Child process could not do execve\n");
	    }else wait(NULL);/*Parent*/
    }
    return 0;
}