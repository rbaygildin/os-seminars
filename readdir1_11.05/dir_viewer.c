#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

int main(int argc, char * argv[])
{
 	DIR *dir;
    struct dirent *entry;

	if(argc < 2)
	{
		perror("You didn\'t input a path to directory!");
		exit(-1);
	}

	struct stat statBuf;
	char* path = argv[1];
	stat(path, &statBuf);
	if(!S_ISDIR(statBuf.st_mode))
	{
		printf("%s is not path\n", path);
		exit(-1);
	}

	dir = opendir(argv[1]);

	if (!dir) 
	{
        perror("Can not to open a directory!");
        exit(-1);
   	}

	while ( (entry = readdir(dir)) != NULL) 
	{
		char filePath[255];
		sprintf(filePath, "%s/%s", path, entry->d_name);
		stat(filePath, &statBuf);

		switch(entry->d_type)
		{	
			case DT_DIR:
				printf("#D: ");
				break;

			case DT_REG:
				printf("#R: ");
				break;

			default:
				printf("#O: ");
				break;
		}
        printf("%s [owned by user = %d group = %d, size = %lld bytes, last access time = %s]\n", entry->d_name, statBuf.st_uid, statBuf.st_gid, statBuf.st_size, ctime(&statBuf.st_atime));
	};

	closedir(dir);

	return 0;
}
