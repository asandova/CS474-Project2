#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <ctype.h>
#include <string>

#define FROM_PARENT 0
#define FROM_CHILD 1
#define TO_PARENT 1
#define TO_CHILD 0

using namespace std;

string readPipe(int fd);
void writePipe(int fd, string message);
string reverseCase(string s);

int main( int argc, char* argv[] ){
    pid_t pid;
    //int PChild[2];
    //int PParent[2];
    int Pipes[2]; 
    string swapCase;
    
    if(argc == 1){
        cout << "Enter massage: " << endl;
        cin >> swapCase;
    }else{
        swapCase = argv[1];
    }

    if( pipe(Pipes)){
        perror((char*) stderr);
        printf("Pipe failed\n");
        return -1;
    }
    /*if( pipe(PChild) ){
        perror((char*)stderr);
        cout << "Pipe failed" << endl;
        return -1;
    }
    if( pipe(PParent) ){
        perror((char*)stderr);
        cout << "Pipe failed" << endl;
        return -1;
    }*/

    pid = fork();
    if(pid == (pid_t)0){
        wait(NULL);
        cout << "in child" << endl;
        cout << "Reading from parent Pipe:" << Pipes[FROM_PARENT] << endl;
        string mess = readPipe(Pipes[FROM_PARENT]);
        close(Pipes[FROM_PARENT]);
        cout << "Recived message: " << mess << endl;
        cout << "Reversing Case" << endl;
        mess = reverseCase(mess);
        cout << "Writing to child Pipe: " << Pipes[TO_PARENT] << endl;
        cout << "Massage: " << mess << endl;
        writePipe(Pipes[TO_PARENT], mess);
        return 0;
    }
    else if( pid < (pid_t) 0){
        perror((char*)stderr);
        cout << "Fork failed" << endl;
        return -1;
    }else{
        cout << "In parent" << endl;
        cout << "Writing to Child: " << Pipes[TO_CHILD] << endl;
        writePipe(Pipes[TO_CHILD], swapCase);
        wait(NULL);
        cout << "Reading from Child: " << Pipes[FROM_CHILD] << endl;
        cout << readPipe(Pipes[FROM_CHILD]) << endl;
        close(Pipes[FROM_CHILD]);
        return 0;
    }
    return 0;
}

string reverseCase(string s){
    printf("int reverse Case\n");
    for(int i = 0; i < s.size(); i++){
        if(s[i] >= 'a' && s[i] <= 'z'){
            printf("%c to %c\n",s[i], s[i]+32);
            s[i] += 32;
        }
        if(s[i] >= 'A' && s[i] <= 'Z'){
            printf("%c to %c\n",s[i], s[i]-32);
            s[i] -= 32;
        }
    }
    return s;
}

string readPipe(int fd){
    cout << "Reading from Pipe: " << fd << endl;/*
    FILE *in;
    in = fdopen(fd,"r");
    string input;
    char c;
    if(in == NULL) {
        perror((char*)stderr);
        printf("Failed to read from file descriptor: %d\n", fd);
        exit(-1);
    }
    while( (c = fgetc(in)) != EOF ){
        printf("%c", c);
        input += c;
    }
    printf("\n");
    fclose(in);*/
    int readin;
    char buffer[100];
    string input;
    printf("before read\n");
    readin = read(fd, buffer, sizeof(buffer));
    printf("after read\n");
    if( readin == -1){
        perror( (char*) stderr); 
        exit(-1);
    }
    printf("readin: %d\n", readin);
    input = buffer;
    return input;
}

void writePipe(int fd, string message){
    cout << "Writing to Pipe:" << fd << endl;
    cout << "Message: " << message << endl;
    FILE *out;
    out = fdopen(fd, "w");
    int byteswritten = fprintf(out, "%s" ,message.c_str());
    printf("bytes written: %d\n",byteswritten);
    if(byteswritten < 0){
        perror( (char*)stderr );
        exit(-1);
    }
    fclose(out);
}
