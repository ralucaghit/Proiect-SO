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
#include <sys/wait.h>
#include <ctype.h>

void afisareFisierBmp(char *dir, char *dir2, char *nume){
    char buff[100];
    char path[100];
    
    snprintf(path, sizeof(path), "%s/%s", dir, nume);
    struct stat variabila;
    lstat(path, &variabila);
    
    int filedescriptor = open(path, O_RDONLY);
    int width = 0;
    int height = 0;
    char ceva[300];
    read(filedescriptor,ceva,18);
    read(filedescriptor,&width,4);
    read(filedescriptor,&height,4);
    
    char path2[100];
    snprintf(path2, sizeof(path2), "%s/%s_statistica.txt", dir2, nume);
    int out = open(path2, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    
    sprintf(buff,"nume fisier: %s\n",nume);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"inaltime: %d\n",height);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"lungime: %d\n",width);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"dimensiune: %ld\n", variabila.st_size);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"identificatorul utilizatorului: %d\n", variabila.st_uid);
    write(out,buff,strlen(buff));
    
    sprintf(buff,"timpul ultimei modificari: %s",ctime(&variabila.st_mtime));
    write(out,buff,strlen(buff));
    
    sprintf(buff,"contorul de legaturi: %ld\n", variabila.st_nlink);
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
    
    close(filedescriptor);
}

void afisareFisier(char *dir, char *dir2, char *nume, char c){
    char buff[100];
    char path[100];
    
    snprintf(path, sizeof(path), "%s/%s", dir, nume);
    struct stat variabila;
    lstat(path, &variabila);
    
    int filedescriptor = open(path, O_RDONLY);
    
    char path2[100];
    snprintf(path2, sizeof(path2), "%s/%s_statistica.txt", dir2, nume);
    int out = open(path2, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    
    sprintf(buff,"nume fisier: %s\n",nume);
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
    
    close(filedescriptor);
    
    int filedescriptor2 = open(path, O_RDONLY);
    int fd[2];
    
    if(pipe(fd)<0){
        perror("Eroare la crearea pipe-ului\n");
        exit(1);
    }
    
    pid_t pidFis = fork();
                
    if(pidFis < 0){
        perror("Eroare");
        exit(1);
    }
                
    if(pidFis == 0){
        dup2(fd[1],1);
        close(fd[0]);
        close(fd[1]);
        execlp("cat", "cat", path, NULL);
        printf("eroare la execlp1");
        exit(1);
    }
    else{
        pidFis = fork();
        
        if(pidFis == 0){
            dup2(fd[0],0);
            close(fd[0]);
            close(fd[1]);
        
            char ch[2] = {c, '\0'};
            execlp("bash", "bash", "script.sh", ch, NULL);
            printf("eroare la execlp2");
            exit(1);
        }
        else{
            int status;
            close(fd[0]);
            close(fd[1]);
            waitpid(pidFis, &status, 0);
        }
    }
    
    close(filedescriptor2);
}

void afisareDirector(char *dir, char *dir2, char *nume){
    char buff[100];
    char path[100];
    
    snprintf(path, sizeof(path), "%s/%s", dir, nume);
    struct stat variabila;
    lstat(path, &variabila);
    
    char path2[100];
    snprintf(path2, sizeof(path2), "%s/%s_statistica.txt", dir2, nume);
    int out = open(path2, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    
    sprintf(buff, "nume director: %s\n", nume);
    write(out, buff, strlen(buff));
    
    sprintf(buff, "identificatorul utilizatorului: %d\n", variabila.st_uid);
    write(out, buff, strlen(buff));
    
    sprintf(buff, "drepturi de acces user: "); write(out, buff, strlen(buff));
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

void afisareLegaturaSimbolica(char *dir, char *dir2, char *nume){
    char buff[100];
    char path[100];
    
    snprintf(path, sizeof(path), "%s/%s", dir, nume);
    struct stat variabila;
    lstat(path, &variabila);
    
    char path2[100];
    snprintf(path2, sizeof(path2), "%s/%s_statistica.txt", dir2, nume);
    int out = open(path2, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    
    sprintf(buff, "nume legatura: %s\n", nume);
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

void covertesteImagine(char *dir, char *dir2, char *nume){
    char path[100];
    
    snprintf(path, sizeof(path), "%s/%s", dir, nume);
    struct stat variabila;
    lstat(path, &variabila);
    
    int filedescriptor = open(path, O_RDWR);
    
    int width = 0;
    int height = 0;
    char ceva[300];
    read(filedescriptor,ceva,18);
    read(filedescriptor,&width,4);
    read(filedescriptor,&height,4);
    read(filedescriptor,ceva,26);
    
    int numarPixeli = width * height;
    unsigned char pixeli[3];
    
    for(int i=0; i < numarPixeli; i++){
        read(filedescriptor,pixeli,sizeof(pixeli));
        int p_gri = 0.299 * pixeli[0] + 0.587 * pixeli[1] + 0.114 * pixeli[2];
        pixeli[0] = p_gri;
        pixeli[1] = p_gri;
        pixeli[2] = p_gri;
        lseek(filedescriptor, -3, SEEK_CUR);
        write(filedescriptor, pixeli, sizeof(pixeli));
    }
    close(filedescriptor);
}

void parcurgeFisiere(char *dir, char *dir2, char c){
    struct stat variabila;
    
    DIR *director = opendir(dir);
    if(director == NULL){
        printf("Eroare la deschidere director\n");
        exit(-1);
    }
    
    struct dirent *intrare;
    
    int numarLinii=0;
    
    pid_t pid;
    
    while((intrare = readdir(director)) !=NULL){
        
        lstat(intrare->d_name, &variabila);
        
        if(strcmp(intrare->d_name,".") == 0 || strcmp(intrare->d_name,"..") == 0)
                continue;
        
        pid = fork(); //creez un proces
        
        if(pid < 0){
            perror("Eroare");
            exit(1);
        }
        
        if(pid == 0){       //fiul
            if(intrare->d_type == DT_DIR){
                afisareDirector(dir,dir2,intrare->d_name);
                numarLinii = 5;
            }
            else if(intrare->d_type == DT_LNK){
                afisareLegaturaSimbolica(dir,dir2,intrare->d_name);
                numarLinii = 6;
            }
            else if(intrare->d_type == DT_REG && strstr(intrare->d_name,".bmp")!=NULL){
                pid_t pidBmp = fork();
                
                if(pidBmp < 0){
                    perror("Eroare");
                    exit(1);
                }
                
                if(pidBmp == 0){
                    covertesteImagine(dir,dir2,intrare->d_name);
                    exit(252);
                }
                
                int status;
                pid_t pid3;
                while((pid3 = waitpid(-1, &status, 0)) > 0){
                    if(WIFEXITED(status)){
                        numarLinii = WEXITSTATUS(status);
                        printf("S-a încheiat procesul cu pid-ul %d și codul %d\n", pid3, numarLinii);
                    }
                }
                
                afisareFisierBmp(dir,dir2,intrare->d_name);
                numarLinii = 10;
            }
            else{
                afisareFisier(dir,dir2,intrare->d_name,c);
                numarLinii = 8;
            }
            exit(numarLinii);
        }
    }
    
    int status;
    pid_t pid2;
    while((pid2 = waitpid(-1, &status, 0)) > 0){
        if(WIFEXITED(status)){
            numarLinii = WEXITSTATUS(status);
            printf("S-a încheiat procesul cu pid-ul %d și codul %d\n", pid2, numarLinii);
        }
    }
}

int main(int argc, char **argv){
    struct stat variabila;
    struct stat variabila2;
    lstat(argv[1], &variabila);
    lstat(argv[2], &variabila2);
    
    if(argc!=4){            
        printf("Nu ati introdus suficiente argumente\n");
        exit (-1);
    }
    
    if(!S_ISDIR(variabila.st_mode))
    {
        printf("Usage ./program <fisier_intrare>\n");
        exit(-1);
    }
    
    if(!S_ISDIR(variabila2.st_mode))
    {
        printf("Usage ./program <fisier_intrare2>\n");
        exit(-1);
    }
    
    int c = argv[3][0];
    
    if(!isalnum(c)){
        printf("Al treilea argument nu e un caracter alfanumeric\n");
        exit(-1);
    }
    
    parcurgeFisiere(argv[1], argv[2], c);
    
    return 0;
}
