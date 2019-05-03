#include <stdio.h> 

#include <string.h> 

#include <stdlib.h> 

#include <unistd.h> 

#include <sys/types.h> 

#include <sys/wait.h> 

#include <readline/readline.h> 

#include <readline/history.h> 

#include <errno.h>

#include <signal.h>

#include <sys/stat.h> 
  
#define max_word 10 
 
#define max_char 50  

#define clear() printf("\033[H\033[J") 
  
//###################################################################################################
void init_shell();

int read_parse_line(char *args[],char line[]);

void read_line(char line[]);

void remove_endofline(char line[]);

int process_line(char *args[],char line[]);

void execargs(char *parsed[4]);

int owncmdhandler(char *parsed[]);

int pipe_redirection_checking(char *temp[]);

void printdir();

void openHelp();

//####################################################################################

int input_redirection_flag=0;

int output_redirection_flag=0;

int piping_flag=0;

char *inputfile;

char *outputfile;

char *username;

//#########################################################################

int main(){

char *args[max_word];

int status;

char line[max_char];

init_shell();

while(1){

read_parse_line(args,line);
}
return 1;
}

int read_parse_line(char *args[],char line[]){

int pos;

int i=0;

printf("%s@%s>>>:",username,username);

char *temp[max_word];

read_line(line);

process_line(temp,line);

return 1;

}

void read_line(char line[]){

char *x=fgets(line,max_char,stdin);

remove_endofline(line);

if(strcmp(line,"exit")==0||x==NULL){

printf("\n GOOD TO EXIT SHELL\n");

exit(0);
}

}

void remove_endofline(char line[]){

int i=0;

while(line[i]!='\n'){

i++;

}

line[i]='\0';

}


int process_line(char *temp[],char line[]){

int i=0;

temp[i]=strtok(line," ");

if(temp[i]==NULL){

return 1;

}

while(temp[i]!=NULL){

i++;

temp[i]=strtok(NULL," ");

}

execargs(temp);

owncmdhandler(temp);

return 1;

}

void execargs(char *parsed[4]){

pid_t pid=fork();

if(pid==-1){

printf("\n failed forking\n ");

return;

}

else if(pid==0){

execvp(parsed[0],parsed);

}

else{

wait(NULL);

return;

}

}

void init_shell() 
{ 
    clear(); 

    printf("\n\n\n\n******************"
        "************************"); 
    printf("\n\n\n\t****MY SHELL****"); 
    printf("\n\n\t-USE AT YOUR OWN RISK-"); 
    printf("\n\n\n\n*******************"
        "***********************"); 
    username = getenv("USER");
 
    printf("\n\n\nUSER is: @%s", username); 

    printf("\n"); 

    sleep(3); 

    clear(); 

} 

int owncmdhandler(char *parsed[4]){

  int NoOfOwnCmds = 3, i, switchOwnArg = 0; 

    char* ListOfOwnCmds[NoOfOwnCmds];
 
    char* username; 
  
    ListOfOwnCmds[0] = "cd"; 

    ListOfOwnCmds[1] = "help"; 
    
  
    for (i = 0; i < NoOfOwnCmds; i++) { 

        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) { 

            switchOwnArg = i + 1; 

            break; 
        } 
    } 
  
    switch (switchOwnArg) { 

    case 1: 

        chdir(parsed[1]); 

        break;
        
    case 2: 

        openHelp(); 

       break; 
   
      
    default: 

        break; 
    } 
  
    return 0; 
} 
  


void openHelp() 
{ 
    puts("\n***WELCOME TO MY SHELL HELP***"
        "\nCopyright @ Suprotik Dey"
        "\n-Use the shell at your own risk..."
        "\nList of Commands supported:"
        "\n>cd"
        "\n>ls"
        "\n>exit"
        "\n>all other general commands available in UNIX shell"
        "\n>pipe handling"
        "\n>improper space handling"); 
  
    return; 
} 

int pipe_redirection_checking(char *temp[]){

int i=0;

while(temp[i]!=NULL){

if(strcmp(temp[i],">")==0){

 int output_redirection_flag=1;

outputfile=temp[i+1];

return i;
}
if(strcmp(temp[i],"<")==0){

 int input_redirection_flag=1;

inputfile=temp[i+1];

return i;

}

if(strcmp(temp[i],"|")==0){

 int piping_flag=1;

return i;
}

}
return i;
 } 

