
#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>

static const char *dirpath = "/home/bastian/shift4";
int remove_directory(const char *path);

void decrypt(char text[100])
{
	
	char acuan[100]="qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
	for(int i=0;i<100;++i)
	{
		
		if(text[i]=='/')
		{
			
			text[i]='/';
			continue;
			
		}
		for(int j=0;j<94;++j)
		{
			
			if(text[i]==acuan[j])
			{	
				
				if(j>17)
				{
					
					text[i]=acuan[j-17];	
					j=94;
					
				}
				else 
				{
					
					int a=94-(17-j);
					text[i]=acuan[a];
					j=94;
					
				}
				
			}
			
		}		
		
	}	

}

void encrypt(char text[100])
{
	char acuan[100]="qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
	for(int i=0;i<100;++i)
	{
		
		if(text[i]=='/')
		{
			
			text[i]='/';
			continue;
			
		}
		for(int j=0;j<94;++j)
		{
			
			if(text[i]==acuan[j])
			{	
				
				if((94-j)>17)
				{
					
					text[i]=acuan[j+17];	
					j=94;
					
				}
				else 
				{
					
					int a=17-(94-j);
					text[i]=acuan[a];
					j=94;
					
				}
				
			}
			
		}		
		
	}	

}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
  int res;
	char fpath[1000];
	char dekrip[1000];
	sprintf(dekrip,"%s",path);
	encrypt(dekrip);
	sprintf(fpath,"%s%s",dirpath,dekrip);
	res = lstat(fpath, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

int remove_directory(const char *path){
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;

   if (d){
      struct dirent *p;
      r = 0;

      while (!r && (p=readdir(d))){
          int r2 = -1;
          char *buf;
          size_t len;

          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")){
             continue;
          }

          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);

          if (buf){
             struct stat statbuf;
             snprintf(buf, len, "%s/%s", path, p->d_name);
             if (!stat(buf, &statbuf)){
                if (S_ISDIR(statbuf.st_mode)){
                   r2 = remove_directory(buf);
                }else{
                   r2 = unlink(buf);
                }
             }
             free(buf);
          }
          r = r2;
      }
      closedir(d);
   }

   if (!r){
      r = rmdir(path);
   }

   return r;
}

void xmp_destroy(void *private_data){
    remove_directory("/home/bastian/shift4/g[xO#Y");
}

void xmp_init(struct fuse_conn_info *conn, struct fuse_config *cfg){
DIR* dir = opendir("/home/bastian/shift4/g[xO#Y");
    int r = -1;
    if (dir){
        closedir(dir);
    }else{
        mkdir("/home/bastian/shift4/g[xO#Y", 0777);
    }
}

static int xmp_mkdir(const char *path, mode_t mode)
{
	int res;

	res = mkdir(path, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_chown(const char *path, uid_t uid, gid_t gid)
{
	int res;

	res = lchown(path, uid, gid);
	if (res == -1)
		return -errno;

	return 0;
}

char* formatdate(char* str, time_t val){
        strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
        return str;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi){
  	char fileTujuan[1000];
  	char sementara[1000];	
	strcpy(sementara,path);
	encrypt(sementara);
	char target1[20]="chipset";
	char targetgrup[20]="rusak";
	char target2[20]="ic_controller";
	DIR *dp;
	struct dirent *de;

	if(strcmp(sementara,"/") == 0)
	{
		sprintf(fileTujuan,"%s",dirpath);
	}
	else{
		sprintf(fileTujuan, "%s%s",dirpath,sementara);
	} 
	int res = 0;


	(void) offset;
	(void) fi;

	dp = opendir(fileTujuan);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) 
	{
		//memset(result,'\0',sizeof(result));
		memset(sementara,'\0',sizeof(sementara));
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		strcpy(sementara,de->d_name);
		char pathnya[1000];
		gid_t gid;
		uid_t uid;
		strcpy(pathnya,fileTujuan);
		strcpy(pathnya+strlen(pathnya),"/");
		strcpy(pathnya+strlen(pathnya),sementara);

		//printf("ini path skrg: %s\n", pathnya);
		stat(pathnya,&st);

		gid = st.st_gid;
		uid = st.st_uid;
		struct group *grp;
		grp = getgrgid(gid);

		char namegrup[20];
		strcpy(namagrup, grp->gr_name);

		struct passwd *usr;
		usr = getpwuid(uid);

		char namauser[20];
		strcpy(namauser, usr->pw_name);
		//printf("ini grpname: %s dan usrname %s\n\n %s" ,namagrup, namauser, target1);
		if(strcmp(namauser,target1) == 0) 
		{
			//printf("masuk sini broo\n");
			FILE *cek;
			cek = fopen(pathnya,"r");
			if(cek!=NULL){
				FILE *target;
				//printf("ga bisa dibuka broo\n");
				char tujuan[1005];
				char textTujuan[1005];
				strcpy(tujuan,"/filemiris.txt");
				encrypt(tujuan);
				printf("dirpath : %s\n", dirpath);
				sprintf(textTujuan, "%s%s", dirpath,tujuan);
				printf("ini path miris: %s\n" , textTujuan);
				target = fopen(textTujuan,"w");
				if(target==NULL)
				{
					int fd;
					mode_t perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

					fd = creat(textTujuan, perm);
					if (fd == -1)
						return -errno;
				}
				struct tm mod = *localtime(&(st.st_atime));
				char isiFIlenya[1100];
				memset(isiFIlenya,'\0',sizeof(isiFIlenya));
				sprintf(isiFilenya,"%s %s %s %s\n", temp, pw->pw_name, gr->gr_name, formatdate(waktu, su.st_atime));
				fputs(isiFIlenya,target);
				fclose(target);
				remove(pathnya);
			}
			else fclose(cek);
		}
		if (strcmp(sementara, ".") != 0 && strcmp(sementara, "..") != 0) {
			decrypt(sementara);
			res = (filler(buf, sementara, &st, 0));
			if(res!=0) break;
		}
	}
	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;
  int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read	= xmp_read,
	.init		= xmp_init,
	.destroy	= xmp_destroy,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
