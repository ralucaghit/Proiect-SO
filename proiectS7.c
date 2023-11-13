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
#include <dirent.h>

void afisareFisierBmp(struct stat variabila, int out, char *nume){
    
    int filedescriptor = open(nume, O_RDONLY); //deschid fisierul dat ca argument
    int width = 0;  //lungimea
    int height = 0; //inaltimea
    char ceva[300]; //variabila in care pun bytes pe care ii citesc, dar de care nu am nevoie
    read(filedescriptor,ceva,18);   //citesc primii 18 bytes si ii pun in "ceva"
    read(filedescriptor,&width,4);  //citesc urmatorii 4 bytesc, care sunt lungimea de fapt
    read(filedescriptor,&height,4); //citesc urmatorii 4 bytesc, care sunt de fapt iinaltimea
    
    char buff[100]; 
    sprintf(buff,"nume fisier: %s\n",nume);  //salvez numele fisierului dat ca argument, in buff
    write(out,buff,strlen(buff));   //scriu in "statistica.txt" ce am in buff, adica numele fisierului
    
    sprintf(buff,"inaltime: %d\n",height);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"lungime: %d\n",width);
    write(out,buff,strlen(buff));
    
    int aux = variabila.st_size;
    sprintf(buff,"dimensiune: %d\n",aux);
    write(out,buff,strlen(buff));
    
    aux = variabila.st_uid;
    sprintf(buff,"identificatorul utilizatorului: %d\n",aux);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"timpul ultimei modificari: %s",ctime(&variabila.st_mtime));
    write(out,buff,strlen(buff));
    
    aux = variabila.st_nlink;
    sprintf(buff,"contorul de legaturi: %d\n", aux);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces user: "); write(out,buff,strlen(buff));
    if(S_IRUSR & variabila.st_mode) sprintf(buff,"R"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IWUSR & variabila.st_mode) sprintf(buff,"W"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IXUSR & variabila.st_mode) sprintf(buff,"X\n"); else sprintf(buff,"-\n");
    write(out,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces grup: "); write(out,buff,strlen(buff));
    if(S_IRGRP & variabila.st_mode) sprintf(buff,"R"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IWGRP & variabila.st_mode) sprintf(buff,"W"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));

    if(S_IXGRP & variabila.st_mode) sprintf(buff,"X\n"); else sprintf(buff,"-\n");
    write(out,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces altii: "); write(out,buff,strlen(buff));
    if(S_IROTH & variabila.st_mode) sprintf(buff,"R"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IWOTH & variabila.st_mode) sprintf(buff,"W"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IXOTH & variabila.st_mode) sprintf(buff,"X\n\n"); else sprintf(buff,"-\n\n");
    write(out,buff,strlen(buff));
    
}

void afisareFisier(struct stat variabila, int out, char *nume){
    
    int filedescriptor = open(nume, O_RDONLY); //deschid fisierul dat ca argument
    char ceva[300]; //variabila in care pun bytes pe care ii citesc, dar de care nu am nevoie
    read(filedescriptor,ceva,18);   //citesc primii 18 bytes si ii pun in "ceva" //citesc urmatorii 4 bytesc, care sunt de fapt iinaltimea
    
    char buff[100]; 
    sprintf(buff,"nume fisier: %s\n",nume);  //salvez numele fisierului dat ca argument, in buff
    write(out,buff,strlen(buff));   //scriu in "statistica.txt" ce am in buff, adica numele fisierului
    
    int aux = variabila.st_size;
    sprintf(buff,"dimensiune: %d\n",aux);
    write(out,buff,strlen(buff));
    
    aux = variabila.st_uid;
    sprintf(buff,"identificatorul utilizatorului: %d\n",aux);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"timpul ultimei modificari: %s",ctime(&variabila.st_mtime));
    write(out,buff,strlen(buff));
    
    aux = variabila.st_nlink;
    sprintf(buff,"contorul de legaturi: %d\n", aux);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces user: "); write(out,buff,strlen(buff));
    if(S_IRUSR & variabila.st_mode) sprintf(buff,"R"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IWUSR & variabila.st_mode) sprintf(buff,"W"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IXUSR & variabila.st_mode) sprintf(buff,"X\n"); else sprintf(buff,"-\n");
    write(out,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces grup: "); write(out,buff,strlen(buff));
    if(S_IRGRP & variabila.st_mode) sprintf(buff,"R"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IWGRP & variabila.st_mode) sprintf(buff,"W"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));

    if(S_IXGRP & variabila.st_mode) sprintf(buff,"X\n"); else sprintf(buff,"-\n");
    write(out,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces altii: "); write(out,buff,strlen(buff));
    if(S_IROTH & variabila.st_mode) sprintf(buff,"R"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IWOTH & variabila.st_mode) sprintf(buff,"W"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IXOTH & variabila.st_mode) sprintf(buff,"X\n\n"); else sprintf(buff,"-\n\n");
    write(out,buff,strlen(buff));
    
}

void afisareDirector(struct stat variabila, int out, char *nume){
    char buff[100];
    sprintf(buff,"nume director: %s\n",nume);
    write(out,buff,strlen(buff));
    
    int aux = variabila.st_uid;
    sprintf(buff,"identificatorul utilizatorului: %d\n",aux);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces user: "); write(out,buff,strlen(buff));
    if(S_IRUSR & variabila.st_mode) sprintf(buff,"R"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IWUSR & variabila.st_mode) sprintf(buff,"W"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IXUSR & variabila.st_mode) sprintf(buff,"X\n"); else sprintf(buff,"-\n");
    write(out,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces grup: "); write(out,buff,strlen(buff));
    if(S_IRGRP & variabila.st_mode) sprintf(buff,"R"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IWGRP & variabila.st_mode) sprintf(buff,"W"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));

    if(S_IXGRP & variabila.st_mode) sprintf(buff,"X\n"); else sprintf(buff,"-\n");
    write(out,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces altii: "); write(out,buff,strlen(buff));
    if(S_IROTH & variabila.st_mode) sprintf(buff,"R"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IWOTH & variabila.st_mode) sprintf(buff,"W"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IXOTH & variabila.st_mode) sprintf(buff,"X\n\n"); else sprintf(buff,"-\n\n");
    write(out,buff,strlen(buff));
}

void afisareLegaturaSimbolica(struct stat variabila, int out, char *nume){
    char buff[100];
    sprintf(buff,"nume legatura: %s\n",nume);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"dimensiune legatura: %ld\n",variabila.st_size);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces user: "); write(out,buff,strlen(buff));
    if(S_IRUSR & variabila.st_mode) sprintf(buff,"R"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IWUSR & variabila.st_mode) sprintf(buff,"W"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IXUSR & variabila.st_mode) sprintf(buff,"X\n"); else sprintf(buff,"-\n");
    write(out,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces grup: "); write(out,buff,strlen(buff));
    if(S_IRGRP & variabila.st_mode) sprintf(buff,"R"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IWGRP & variabila.st_mode) sprintf(buff,"W"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));

    if(S_IXGRP & variabila.st_mode) sprintf(buff,"X\n"); else sprintf(buff,"-\n");
    write(out,buff,strlen(buff));
    
    sprintf(buff,"drepturi de acces altii: "); write(out,buff,strlen(buff));
    if(S_IROTH & variabila.st_mode) sprintf(buff,"R"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IWOTH & variabila.st_mode) sprintf(buff,"W"); else sprintf(buff,"-");
    write(out,buff,strlen(buff));
    
    if(S_IXOTH & variabila.st_mode) sprintf(buff,"X\n\n"); else sprintf(buff,"-\n\n");
    write(out,buff,strlen(buff));
}

void parcurgeFisiere(char *dir, int out){
    struct stat variabila;
    
    DIR *director =  opendir(dir);
    if(director==NULL){
        printf("Nick nu stie nimic\n");
        exit(-1);
    }
    
    struct dirent *intrare;
    
    while((intrare=readdir(director))!=NULL){
        lstat(intrare->d_name, &variabila);
        
        if(strcmp(intrare->d_name,".")==0 || strcmp(intrare->d_name,"..")==0)
            continue;
        if(intrare->d_type == DT_DIR)
            afisareDirector(variabila,out,intrare->d_name);
        else if(intrare->d_type == DT_LNK)
            afisareLegaturaSimbolica(variabila,out,intrare->d_name);
        else if(intrare->d_type == DT_REG && strstr(intrare->d_name,".bmp")!=NULL)
            afisareFisierBmp(variabila,out,intrare->d_name);
        else 
            afisareFisier(variabila,out,intrare->d_name);
    }
}

int main(int argc, char **argv){
    struct stat variabila;
    lstat(argv[1], &variabila);
    
    if(argc!=2){            //verific daca am dat un singur argument
        printf("Usage ./program <fisier_intrare>\n");
        exit (-1);
    }
    
    if(!S_ISDIR(variabila.st_mode)) //verific daca un director si nu un fisier obisnuit spre exemplu
    {
        printf("Usage ./program <fisier_intrare>\n");
        exit(-1);
    }
    
    int filedescriptor2 = open("statistica1.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR); //deschid sau in cazul in care nu exista, creez fisierul "statistica.txt"
    
    parcurgeFisiere(argv[1],filedescriptor2);
       
    
    close(filedescriptor2);
    
    
    return 0;
}
