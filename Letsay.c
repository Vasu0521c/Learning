#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
//--------------------------------------------//

char* extension(char* name){

    char* ext = NULL;
    ext = strrchr(name, '.');

    if (ext == NULL || ext == name)
        return "others";

    ext++;
    return ext;

}

//--------------------------------------------//

void move_files(char* path, char* name){

    char* ext = NULL;
    char oldpath[1024];
    snprintf(oldpath, sizeof(oldpath),"%s/%s",path, name);

    ext = extension(name);

    char newpath[1024];
    snprintf(newpath, sizeof(newpath),"%s/%s",path,ext);


    if(mkdir(newpath, 0755)!=0 && errno != EEXIST){
        perror("MkDir Failed");
    }

    snprintf(newpath, sizeof(newpath),"%s/%s/%s",path,ext,name);

    if(rename(oldpath, newpath)!=0){
        perror("Rename failed");
    }

}

//-------------------------------------------//

int grouping(char *path){

    DIR *dp;
    struct dirent *entry;

    dp = opendir(path);

    if(dp != NULL){

        while ((entry = readdir(dp)) != NULL){

            if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
                continue;

            char fullpath[1024];
            snprintf(fullpath, sizeof(fullpath), "%s/%s",path,entry->d_name);
            struct stat direc;

            if (stat(fullpath, &direc)==0){

                if(!S_ISDIR(direc.st_mode)){                        // Directoty Check

                    move_files(path, entry->d_name);
                }

                else
                    continue;
            }
            else{

                perror("Stat Failed");
            }


        }
    }
    else{

        perror("Opendir Failed");
        return -1;
    }

    closedir(dp);
    return 0;
}
//--------------------------------------------//

int alt_main(){

    printf("Enter the path of the folder or directory you wish to organize : ");
    char des_dir[500];
    fgets(des_dir, sizeof(des_dir), stdin);
    des_dir[strcspn(des_dir,"\n")] = '\0';

    list_dir(des_dir);

    printf("\n \n File are Being Organized \n");

    grouping(des_dir);

    printf("\n Files organization Completed \n \n The organized file system follows : ");

    list_dir(des_dir);

    printf("\n");
    return 0;
}
