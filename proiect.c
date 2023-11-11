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
    
    if(argc!=2){            //verific daca am dat un singur argument
        printf("Usage ./program <fisier_intrare>\n");
        exit (-1);
    }
    
    if(!S_ISREG(variabila.st_mode)) //verific daca e fisier obisnuit si nu un director spre exemplu
    {
        printf("Usage ./program <fisier_intrare>\n");
        exit(-1);
    }
    
    int filedescriptor = open(argv[1], O_RDONLY); //deschid fisierul dat ca argument
    int width = 0;  //lungimea
    int height = 0; //inaltimea
    char ceva[300]; //variabila in care pun bytes pe care ii citesc, dar de care nu am nevoie
    read(filedescriptor,ceva,18);   //citesc primii 18 bytes si ii pun in "ceva"
    read(filedescriptor,&width,4);  //citesc urmatorii 4 bytesc, care sunt lungimea de fapt
    read(filedescriptor,&height,4); //citesc urmatorii 4 bytesc, care sunt de fapt iinaltimea
    
    int filedescriptor2 = open("statistica.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR); //deschid sau in cazul in care nu exista, creez fisierul "statistica.txt"
    
    char buff[100]; 
    sprintf(buff,"nume fisier: %s\n",argv[1]);  //salvez numele fisierului dat ca argument, in buff
    write(filedescriptor2,buff,strlen(buff));   //scriu in "statistica.txt" ce am in buff, adica numele fisierului
    
    sprintf(buff,"inaltime: %d\n",height);
    write(filedescriptor2,buff,strlen(buff));
    
    sprintf(buff,"lungime: %d\n",width);
    write(filedescriptor2,buff,strlen(buff));
    
    int aux;
    if(stat(argv[1],&variabila))    //verific daca am erori si le tratez
        exit(-1);
    aux = variabila.st_size;
    sprintf(buff,"dimensiune: %d\n",aux);
    write(filedescriptor2,buff,strlen(buff));
    
    aux = variabila.st_uid;
    sprintf(buff,"identificatorul utilizatorului: %d\n",aux);
    write(filedescriptor2,buff,strlen(buff));
    
    sprintf(buff,"timpul ultimei modificari: %s",ctime(&variabila.st_mtime));
    write(filedescriptor2,buff,strlen(buff));
    
    aux = variabila.st_nlink;
    sprintf(buff,"contorul de legaturi: %d\n", aux);
    write(filedescriptor2,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces user: ");
    write(filedescriptor2,buff,strlen(buff));
    if(S_IRUSR & variabila.st_mode)     //verific daca am drept de read pt user
        sprintf(buff,"R");
    else
        sprintf(buff,"-");
    write(filedescriptor2,buff,strlen(buff));
    
    if(S_IWUSR & variabila.st_mode)     //verific daca am drept de write pt user
        sprintf(buff,"W");
    else
        sprintf(buff,"-");
    write(filedescriptor2,buff,strlen(buff));
    
    if(S_IXUSR & variabila.st_mode)     //verific daca am drept de executie pt user
        sprintf(buff,"X\n");
    else
        sprintf(buff,"-\n");
    write(filedescriptor2,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces grup: ");   //verific mai jos drepturile de acces pt grup
    write(filedescriptor2,buff,strlen(buff));
    if(S_IRGRP & variabila.st_mode)
        sprintf(buff,"R");
    else
        sprintf(buff,"-");
    write(filedescriptor2,buff,strlen(buff));
    
    if(S_IWGRP & variabila.st_mode)
        sprintf(buff,"W");
    else
        sprintf(buff,"-");
    write(filedescriptor2,buff,strlen(buff));

    
    if(S_IXGRP & variabila.st_mode)
        sprintf(buff,"X\n");
    else
        sprintf(buff,"-\n");
    write(filedescriptor2,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces altii: ");
    write(filedescriptor2,buff,strlen(buff));
    if(S_IROTH & variabila.st_mode)
        sprintf(buff,"R");
    else
        sprintf(buff,"-");
    write(filedescriptor2,buff,strlen(buff));
    
    if(S_IWOTH & variabila.st_mode)
        sprintf(buff,"W");
    else
        sprintf(buff,"-");
    write(filedescriptor2,buff,strlen(buff));
    
    if(S_IXOTH & variabila.st_mode)
        sprintf(buff,"X");
    else
        sprintf(buff,"-");
    write(filedescriptor2,buff,strlen(buff));
    
    close(filedescriptor2);
    close(filedescriptor);
    
    return 0;
}
