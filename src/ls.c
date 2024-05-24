#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define WHITE "\x1b[37m"

void print_permissions(mode_t mode) {
    char permissions[11];
    strcpy(permissions, "----------");

    if (S_ISDIR(mode)) permissions[0] = 'd';
    if (mode & S_IRUSR) permissions[1] = 'r';
    if (mode & S_IWUSR) permissions[2] = 'w';
    if (mode & S_IXUSR) permissions[3] = 'x';
    if (mode & S_IRGRP) permissions[4] = 'r';
    if (mode & S_IWGRP) permissions[5] = 'w';
    if (mode & S_IXGRP) permissions[6] = 'x';
    if (mode & S_IROTH) permissions[7] = 'r';
    if (mode & S_IWOTH) permissions[8] = 'w';
    if (mode & S_IXOTH) permissions[9] = 'x';

    printf("%s ", permissions);
}

void print_detailed_info(const char *path, const struct dirent *ep) {
    char fullpath[512];
    struct stat st;
    struct passwd *pw;
    struct group *gr;
    struct tm *tm;
    char datestring[256];

    sprintf(fullpath, "%s/%s", path, ep->d_name);
    stat(fullpath, &st);

    print_permissions(st.st_mode);
    printf("%ld ", st.st_nlink);

    pw = getpwuid(st.st_uid);
    printf("%s ", pw->pw_name);

    gr = getgrgid(st.st_gid);
    printf("%s ", gr->gr_name);

    printf("%5ld ", st.st_size);

    tm = localtime(&st.st_mtime);
    strftime(datestring, sizeof(datestring), "%b %d %H:%M", tm);
    printf("%s ", datestring);

    printf("%s\n", ep->d_name);
}

void RecDir(char *path, int recursive, int include_hidden, int detailed) {
    DIR *dp = opendir(path);
    if (!dp) {
        perror(path);
        return;
    }
    struct dirent *ep;
    char newdir[512];
    printf(BLUE "\n%s :\n\n" WHITE, path);
    while ((ep = readdir(dp))) {
        if (!include_hidden && strncmp(ep->d_name, ".", 1) == 0) {
            continue;
        }
        if (detailed) {
            print_detailed_info(path, ep);
        } else {
            printf("%s   ", ep->d_name);
        }
    }
    closedir(dp);
    dp = opendir(path);
    while ((ep = readdir(dp))) {
        if (!include_hidden && strncmp(ep->d_name, ".", 1) == 0) {
            continue;
        }
        if (recursive && ep->d_type == DT_DIR && strncmp(ep->d_name, ".", 1) != 0) {
            sprintf(newdir, "%s/%s", path, ep->d_name);
            RecDir(newdir, recursive, include_hidden, detailed);
        }
    }
    closedir(dp);
}

int main(int argc, char **argv) {
    int recursive = 0, include_hidden = 0, detailed = 0;
    char *path = ".";
    int buffer = 10, count = 0;
    char *command[buffer];
    if(argc > 1){
        char *token = strtok(argv[1], " ");
        while (token != NULL) {
            command[count] = strdup(token); // Alocar memória para cada token e copiá-lo
            count++;
            token = strtok(NULL, " ");
        }
    }

    for (int i = 1; i < count; i++) {
        if (strcmp(command[i], "-R") == 0) {
            recursive = 1;
        } else if (strcmp(command[i], "-a") == 0) {
            include_hidden = 1;
        } else if (strcmp(command[i], "-l") == 0) {
            detailed = 1;
        } else {
            path = command[i];
        }
    }

    RecDir(path, recursive, include_hidden, detailed);
    printf("\n\n");
    return 0;
}
