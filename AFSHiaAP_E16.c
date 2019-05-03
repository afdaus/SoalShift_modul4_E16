
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

void decrypt(char *text)
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

void encrypt(char *text)
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

void* ekstension(void *arg)
{
	char temp[1005];
	strcpy(temp, fpath);
	printf("%s", temp);
	decrypt(temp);
	if (strstr(temp, "/YOUTUBER") != NULL)
	{
		while(flag==0){}
		char namafilelama[1100];
		char namafilebaru[1100];
		encrypt(temp);
		sprintf(namafilelama, "%s",temp);
		encrypt(namafilelama);
		strcpy(namafilebaru,namafilelama);
		char iz[10] = ".iz1";
		encrypt(ext);
		strcpy(namafilebaru+strlen(namafilebaru), ext);
		printf("ini namafilebaru: %s\n", namafilebaru);
		printf("%s %s", namafilelama,namafilebaru);
		rename(namafilelama, namafilebaru);
		memset(fpath, '\0', sizeof(fpath));
		flag = 0;
	}
	return NULL;
}

static int xmp_mkdir(const char *path, mode_t mode)
{

	char fpath[1000];
	char temp[1000];
	
	strcpy(temp,path);

	if (strstr(temp, "/YOUTUBER") != NULL) {
		mode = 0750;
	}
	
	encrypt(temp);

	if(strcmp(temp,"/") == 0)
	{
		sprintf(fpath,"%s",dirpath);
	}
	else{
		sprintf(fpath, "%s%s",dirpath,temp);
	}
    int res;

    res = mkdir(fpath, mode);
    if(res == -1)
        return -errno;

    return 0;
}

static int xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
	
	char temp[1000];
	
	strcpy(temp,path);
	
	if (strstr(temp, "/YOUTUBER") != NULL) {
		mode = 0640;
		flag = 1;
	}

	encrypt(temp);

	if(strcmp(temp,"/") == 0)
	{
		sprintf(fpath,"%s",dirpath);
	}
	else{
		sprintf(fpath, "%s%s",dirpath,temp);
	}

	int fd;
	
	fd = creat(fpath, mode);
	if (fd == -1)
		return -errno;
	close(fd);
	char lope[1005];
	strcpy(lope,fpath);
	pthread_create(&tid, NULL, &ekstension, NULL);

	return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{

	char fpath[1005];
	char temp[1005];
	char temp2[1005];

	strcpy(temp,path);
	encrypt(temp);

	sprintf(temp2, "%s%s",dirpath,temp);
	printf("ini path nya oi : %s\n", temp2);

	struct stat atribut;
	memset(&atribut, 0, sizeof(atribut));

	stat(temp2,&atribut);

	decrypt(temp);

	int len = strlen(temp);
	if (strstr(temp, "/YOUTUBER/") != NULL && temp[len - 1] == '1' && temp[len - 2] == 'z' && temp[len - 3] == 'i' && temp[len - 4] == '.' && S_ISREG (atribut.st_mode)) {
    	printf("File ekstensi iz1 tidak boleh diubah permissionnya.\n");
    	return -1;
	}

	encrypt(temp);

	if(strcmp(temp,"/") == 0)
	{
		sprintf(fpath,"%s",dirpath);
	}
	else{
		sprintf(fpath, "%s%s",dirpath,temp);
	}

	int res;

	res = chmod(fpath, mode);
	if (res == -1) return -errno;

	return 0;
}

static int xmp_utimens(const char *path, const struct timespec ts[2])
{
	memset(resu,'\0',sizeof(resu));
	char fpath[1000];
	char temp[1000];
	
	strcpy(temp,path);
	
	//encrypt(temp,17);
	
	if(strcmp(temp,"/") == 0)
	{
		sprintf(fpath,"%s",dirpath);
	}
	else{
		sprintf(fpath, "%s%s",dirpath,temp);
	}

	int res;

	res = utimensat(0, fpath, ts, AT_SYMLINK_NOFOLLOW);
	flag = 1;
	if (res == -1)
		return -errno;

	return 0;
}

int getPositionLastChar(char *str, char chr){
	char *posChar = NULL;
	char *tempPosChar = strchr(str, chr);
 	while(tempPosChar != NULL){
		posChar = tempPosChar;
 		tempPosChar = strchr(tempPosChar+1, chr);
	}
	if(posChar==NULL)
		return 0;
 	return (int) (posChar-str);
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

static int xmp_truncate(const char *path, off_t size)
{
	char fpath[1000], temp[1000];
	strcpy(temp, path);
	encrypt(temp);

	if(strcmp(temp,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,temp);
	
	int res;

	res = truncate(fpath, size);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_write(const char *path, const char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi)
{
	char fileTujuan[1000], sementara[1000],sementara2[1000];
	
	strcpy(sementara, path);	
	encrypt(sementara);

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fileTujuan,"%s",path);
	}
	else sprintf(fileTujuan, "%s%s",dirpath,sementara);

	int fd;
	int res;

	(void) fi;
	fd = open(fileTujuan, O_WRONLY);
	if (fd == -1)
		return -errno;

	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	
	strcpy(sementara2,path);
	encrypt(sementara2);
	sprintf(sementara, "%s/%s", dirpath,sementara2);

	if(access(sementara, R_OK)<0)				//JIKA FILE TIDAK ADA
		return res;


	char locBackup[1000] = "/home/samuel/testttnomor3/XB.Jhu";
	mkdir(locBackup, 0777);

	char fnameNoExt[1000], ext[100], waktu[1000], fBackup[1000];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(waktu, "%04d-%02d-%02d_%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	int garis = getPositionLastChar(path, '/');
	int titik = getPositionLastChar(path, '.');
	
	if (titik==0) {
		titik = strlen(path);
		ext[0] = '\0';
	}
	else{
		strcpy(ext, path+titik);
	}

	strncpy(fnameNoExt, path+garis+1, titik-(garis+1));
	fnameNoExt[titik-(garis+1)] = '\0';
	sprintf(fBackup,"%s_%s%s", fnameNoExt, waktu, ext);
	encrypt(fBackup);
	sprintf(sementara, "%s%s", dirpath, sementara2);
	FILE *sumber = fopen(sementara, "r");
	sprintf(sementara, "%s/%s", locBackup, fBackup);
	FILE *target = fopen(sementara, "w");
	char ch;
	while(!feof(sumber))
	{
		ch = fgetc(sumber);
		fprintf(target, "%c", ch);
	}
	// while ((ch = fgetc(sumber)) != EOF)
	// 	fprintf(target, "%c", ch);
	fclose(target);
	fclose(sumber);
	return res;
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
	.write 		= xmp_write,
	.unlink 	= xmp_unlink,
	.rmdir 		= xmp_rmdir,
	.truncate 	= xmp_truncate,
	.mkdir		= xmp_mkdir,
	.read		= xmp_read,
	.create     = xmp_create,
	.utimens	= xmp_utimens,
	.chmod		= xmp_chmod,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
