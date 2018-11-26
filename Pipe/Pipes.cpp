#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <ctype.h>
#include <string>
#include <string.h>

#define PARENT_IN 0
#define PARENT_OUT 1
#define CHILD_IN 0
#define CHILD_OUT 1

using namespace std;

string readPipe(int fd);
void writePipe(int fd, string message);
string reverseCase(string s);

int main( int argc, char* argv[] ){
    pid_t pid;
    int Pipes[2]; 
    string swapCase;
    
    if(argc == 1){
        cout << "Enter massage: " << endl;
        cin >> swapCase;
    }else{
        swapCase = argv[1];
    }
    if( pipe(Pipes) ){
        perror((char*)stderr);
        cout << "Pipe failed" << endl;
        return -1;
    }

    pid = fork();
    if(pid == (pid_t)0){
        wait(NULL);
        //cout << "in child" << endl;
        //cout << "Reading from parent Pipe: " << Pipes[CHILD_IN] << endl;
        string mess = readPipe(Pipes[CHILD_IN]);
        //cout << "Recived message: " << mess << endl;
        //cout << "Reversing Case" << endl;
        mess = reverseCase(mess);
        //cout << "Writing to child Pipe: " << Pipes[CHILD_OUT] << endl;
        //cout << "Massage: " << mess << endl;
        writePipe(Pipes[CHILD_OUT], mess);
        return 0;
    }
    else if( pid < (pid_t) 0){
        perror((char*)stderr);
        cout << "Fork failed" << endl;
        return -1;
    }else{
        //cout << "In parent" << endl;
        //cout << "Writing to Child: " << Pipes[PARENT_OUT] << endl;
        printf("Parent sent: %s\n", swapCase.c_str());
        writePipe(Pipes[PARENT_OUT], swapCase);
        wait(NULL);
        //cout << "Reading from Child: " << Pipes[PARENT_IN] << endl;
        cout << "Childed returned: " << readPipe(Pipes[PARENT_IN]) << endl;
        close(Pipes[0]);
        close(Pipes[1]);
        return 0;
    }
    return 0;
}

string reverseCase(string s){
    //printf("in reverse Case\n");
    for(int i = 0; i < s.size(); i++){
        if(s[i] >= 'a' && s[i] <= 'z'){
            //printf("%c to %c\n",s[i], s[i]-32);
            s[i] -= 32;
        }
        else if(s[i] >= 'A' && s[i] <= 'Z'){
            //printf("%c to %c\n",s[i], s[i]+32);
            s[i] += 32;
        }
    }
    return s;
}

string readPipe(int fd){
    //cout << "Reading from Pipe: " << fd << endl;
    int readin;
    //char buffer[100];
    char* buffer = (char*) malloc(sizeof(char) * 101);
    memset(buffer, 0, 100);
    string input;
    readin = read(fd, buffer, sizeof(char) * 100);
    if( readin == -1){
        perror( (char*) stderr); 
        exit(-1);
    }
    //printf("readin: %d\n", readin);
    input = string(buffer);
    free(buffer);
    return input;
}

void writePipe(int fd, string message){
    //cout << "Writing to Pipe: " << fd << endl;
    //cout << "Message: " << message << endl;
    write(fd, message.c_str(), sizeof(char) * message.size());
    //printf("Message written\n");
}
