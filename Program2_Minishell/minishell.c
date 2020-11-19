#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

// method that prints the prompt before the user types their input
void prompt(){
  // creating a string where the current working directory is going to be stored
  char cwd[256];
  if(getcwd(cwd, sizeof(cwd)) != NULL){
    // prints the current working directory if it exists
    printf("%s> ", cwd);
  } else {
    // prints an error is there is not current working directory
    perror("getcwd() error");
  }
}

// method that parses the string into its individual tokens to allow processing of the input
// be alot easier
void parseArgs(char* str, char** args, int* nargs){
  // delimeter used to parse the string
  const char delim[4]  = "  \t\n";
  // breaking up the string passed into smaller tokens using the delimeter created in the line above
  // ptr will become the first token of the code
  char* ptr = strtok(str, delim);
  
  // variable that keeps track of the args index when in the while loop
  int i = 0;
  
  // loop that runs through until the variable 'ptr' is NULL
  while(ptr != NULL){
    // sets args at index i to the token
    args[i] = ptr;
    // incrementing i by 1 to fill args with the next token of the array
    i++;
    // changing the 'ptr' to the next token
    ptr = strtok(NULL, delim);
  }
  // sets the final arguement as null
  args[i] = NULL;
  // sets the nargs to i to keep track of the number of arguements that were passed
  *nargs = i;
  
}
// method that return 1 if the command is a shell command i.e exit or cd
int checkShellCommand(char** args){
  if (strcmp(args[0], "cd") == 0 || strcmp(args[0], "exit") == 0){
    // only returns true if the command is a cd or exit otherwise it returns 0
    return 1;
  } else{
    return 0;
  }
}

// method that excecutes all of the shell commands i.e exit and cd
void shellCommands(char** args){
  // carrying out the cd command
  if (strcmp(args[0], "cd") == 0){
    // changes the directory to args[1] which is the directory that was passed in with the command
    int ch = chdir(args[1]);
    // checking to see if the call above returned a value less than 0 in which case the program should print an error message
    if(ch < 0){
      printf("%s: No such file or directory\n", args[1]);
    }
  }
  // carrying out the exit command
  else if(strcmp(args[0], "exit") == 0){
    // stops the programm if the command is exit
    exit(0);
  }
}

// method to handle the SIGCHLD signal that is passed
void handleSig(int sig){
  waitpid(0, &sig, WNOHANG);
}
void redirectOutput(char** args, FILE** out, int* nargs){
  // variable to check if ">" has been found
  int found = 0;
  // variable to be the index of the filename at the end of the loop if the character ">" is found
  int i = 0;

  while((found == 0) && (i < *nargs)){
    // looking for ">" within the args array at index i
    if(strcmp(">",args[i]) == 0){
      // sets the found variable to true
      found = 1;
    }
    // increments the index to set it to check the next index during the iteration to come
    i++;
  }
  if ((args[i] != NULL) && (found == 1)){
    // if the character ">" is found then the output(stdout) is writen to the file out
    *out = freopen(args[i], "w", stdout);
    // looping through to remove the ">" and also the filename from the args
    for(int j = i + 1; j <= *nargs; j++){
      args[j-2] = args[j];
    }
    // reduces the number of arguements by 2 because the filename and "<" arguemetn have been removed
    *nargs = *nargs - 2;
  }

}

void redirectInput(char** args, FILE** in, int* nargs){
  // the first half of this code is the same as it was for the method redirectOut
  // variable to check if "<" has been found
  int found = 0;
  // variable to be the index of the filename at the end of the loop if the character "<" is found
  int i = 0;

  while((found == 0) && (i < *nargs)){
    // looking for "<" within the args array at index i
    if (strcmp("<",args[i]) == 0){
      // sets the found the variable to true
      found = 1;
    }
    // increments the index to set it to check the next index during the iteration to come
    i++;  
  }

  if((args[i] != NULL) && (found == 1)){
    *in = freopen(args[i], "r", stdin);
    // looping through to remove the "<" and also the filename from the args
    for(int j = i + 1; j <= *nargs; j++){
      args[j-2] = args[j];
    }
    // reduces the number of arguements by 2 because the filename and "<" arguemetn have been removed
    *nargs = *nargs - 2;
  }
  
}

//method that runs the whole programs including the other commands such as ls
void excecuteProgram(char** args, int* nargs){
  // used to help with the reaping zombie process
  signal(SIGCHLD, handleSig);
  int status;

  // variable to keep track of the background processes running
  int background = 0;

  // looking for an "&" sign a the end of the args array to look for any background processes
  if(strcmp(args[*nargs-1], "&") == 0){
    // sets background to true
    background = 1;
    // removes the & from the array
    args[*nargs-1] = NULL;
    // reduces the size of nargs by 1
    (*nargs)--;
  }
  // forks of a child process and stores the process id in the variable "pid"
  int pid = fork();

  // if the process id returns a -1 the fork process failed and so the program needs to exit
  if(pid == -1){
    printf("Failed forking child process.. \n");
    exit(1);
  }
  // if the forking is sucessfull
  else if(pid == 0){
    // creating file variables that can be used for an input or output redirection
    FILE* fpIn;
    FILE* fpOut;
    // it calls on the methods redirectInput and redirectOutput to check if a "<" or ">" has been included with a file name
    redirectInput(args, &fpIn, nargs);
    redirectOutput(args, &fpOut, nargs);

    // this will now exceute the program with the commands that were passed in through the shell
    // if it return a number less than 0 there was an error and the error message will print out and exit the program
    // else it will excecute the command
    if(execvp(*args, args) < 0){
      printf("%s: Invalid Command\n", *args);
      exit(1);
    }

    // closing the file instances that were opened
    fclose(fpIn);
    fclose(fpOut);

    // if there are no background processes blocking will be used to wait for the child processes
    if(background == 0){
      waitpid(pid, &status, 0);
    }
    // otherwise it will return immediately whilewaiting for the child process
    else {
      printf("background\n");
      waitpid(pid, &status, WNOHANG);
      
    }
  }
}
// this will process the command entering the loop
int processCommand(char** args){
  if (checkShellCommand(args)){
    shellCommands(args);
    return 0;
  } else {
    return 1;
  }

}

int main(){
  //printing the input prompt
  prompt();
  while(1){
    //string used to enter the command
    char str[1000];
    // token array of the command entered
    char* args[100];
    // number of arguements
    int nargs = 0;
    // reading in a command from the user
    
    if(fgets(str,60, stdin) != NULL){
      if(strcmp(str,"\n") > 0){     
	// parses the input into a token array
	//printf("%s\n", str);
	//printf("here\n");
	parseArgs(str, args, &nargs);
	int excecute = processCommand(args);
	if(excecute == 1){
	  excecuteProgram(args, &nargs);
	  //printf("excecuted\n");
	  sleep(1);  
	}
	
      }
    }
    //printing the input prompt
    
    prompt();
  }

}
