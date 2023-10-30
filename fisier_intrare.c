#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){
    struct stat variabila;
    lstat(argv[1], &variabila);
    
    if(argc==1){
        printf("Usage ./program <fisier_intrare>\n");
        exit (-1);
    }
    
    if(!S_ISREG(variabila.st_mode)) //verific daca e fisier obisnuit si nu un director spre exemplu
    {
        printf("Usage ./program <fisier_intrare>\n");
        exit(-1);
    }
    
    open("/home/student/Proiect-SO", O_RDONLY);
    
    return 0;
}
