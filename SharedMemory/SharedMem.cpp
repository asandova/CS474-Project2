#include <iostream>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <string>

using namespace std;

void ViewSharedMem(int segID, shmid_ds* shmBuffer);

int main(int argc, char* argv[]){
    int segID;
    bool test = false;
    if(argc > 1){
        int i = 1;
        while(i < argc){
            if(strcmp("-test",argv[i]) == 0 && test == false){
                //Used for testing
                //setting Key to 0, size of segment to 50, and permitions to Owner:RW, Group:R, World:R
                test = true;
                segID = shmget((key_t)0, 50, 0400 | 0200 | 0040 | 0004);
                if(segID == -1){
                    printf("errno: %d\n", errno);
                    perror( "shmget failed" );
                    exit(-1);
                }
            }
            if(strcmp("-MemoryID",argv[i]) == 0){
                segID = atoi(argv[i+1]);
                i++;
            }
            i++;
        }
    }else{
        cout << "Enter Shared Memory ID: ";
        cin >> segID;
    }
    shmid_ds* shmBuffer = (shmid_ds*) malloc(sizeof(shmid_ds));
    ViewSharedMem(segID, shmBuffer);
    free(shmBuffer);

    return 0;
}

void ViewSharedMem(int segID, shmid_ds* shmBuffer){

        if( shmctl(segID, IPC_STAT, shmBuffer ) == -1){
            printf("errno: %d\n", errno);
            perror( "shmctl failed" );
            exit(-1);
        }else{
            cout << "Segment ID: " << segID << endl;
            cout << "Key: " << shmBuffer->shm_perm.__key << endl;
            cout << "Mode: " << shmBuffer->shm_perm.mode << endl;
            cout << "Owner UID: " << shmBuffer->shm_perm.uid << endl;
            cout << "Size(bytes): " << shmBuffer->shm_segsz << endl;
            cout << "Number of attaches: " << shmBuffer->shm_nattch << endl;
        }
}