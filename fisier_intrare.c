#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdint.h>
#include <sys/sysmacros.h>

int main(int argc, char **argv){
    struct stat variabila;
    lstat(argv[1], &variabila);
    
    if(argc!=2){
        printf("Usage ./program <fisier_intrare>\n");
        exit (-1);
    }
    
    if(!S_ISREG(variabila.st_mode)) //verific daca e fisier obisnuit si nu un director spre exemplu
    {
        printf("Usage ./program <fisier_intrare>\n");
        exit(-1);
    }
    
    int filedescriptor = open(argv[1], O_RDONLY);
    char ceva[300];
    read(filedescriptor,ceva,18);
    int width;
    read(filedescriptor,&width,4);
    int height;
    read(filedescriptor,&height,4);
    
    int filedescriptor2 = open("statistica.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    
    char buff[100];
    sprintf(buff,"nume fisier: %s\n", argv[1]);
    write(filedescriptor2,buff,strlen(buff));
    
    sprintf(buff,"inaltime: %d\n", height);
    write(filedescriptor2,buff,strlen(buff));
    
    sprintf(buff,"lungime: %d\n", width);
    write(filedescriptor2,buff,strlen(buff));
    
    if(stat(argv[1],&variabila)==-1)
        exit(-1);
    int aux = variabila.st_size;
    sprintf(buff,"dimensiune: %d\n", aux);
    write(filedescriptor2,buff,strlen(buff));
    
    aux = variabila.st_uid;
    sprintf(buff,"identificatorul utilizatorului: %d\n", aux);
    write(filedescriptor2,buff,strlen(buff));
    
    sprintf(buff,"timpul ultimei modificari: %s",ctime(&variabila.st_mtime));
    write(filedescriptor2,buff,strlen(buff));
    
    aux = variabila.st_nlink;
    sprintf(buff,"contorul de legaturi: %d\n", aux);
    write(filedescriptor2,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces user: ");
    write(filedescriptor2,buff,strlen(buff));
    if(S_IRUSR&&variabila.st_mode){
        sprintf(buff,"R");
        write(filedescriptor2,buff,strlen(buff));
    }
    else{
        sprintf(buff,"-");
        write(filedescriptor2,buff,strlen(buff));
    }
    
    if(S_IWUSR&&variabila.st_mode){
        sprintf(buff,"W");
        write(filedescriptor2,buff,strlen(buff));
    }
    else{
        sprintf(buff,"-");
        write(filedescriptor2,buff,strlen(buff));
    }
    
    if(S_IXUSR&&variabila.st_mode==0){
        sprintf(buff,"X");
        write(filedescriptor2,buff,strlen(buff));
    }
    else{
        sprintf(buff,"-");
        write(filedescriptor2,buff,strlen(buff));
    }
    
    
    close(filedescriptor);
    close(filedescriptor2);
    
    return 0;
}
