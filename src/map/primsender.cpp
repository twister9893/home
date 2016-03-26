#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>

#pragma pack (push, 1)

struct prim_header
{
	unsigned short pack:8;
	unsigned short kvant:4;
	unsigned short proreg:4;

	unsigned short discrets;

	unsigned short um;

	unsigned short peleng;

	unsigned short sost;
};

#pragma pack (pop)

int createSocket()
{
  int val = 1;
  int fd;
  fd=socket (AF_INET, SOCK_DGRAM, 0);
  if (fd < 0)
  {
    perror ("create socket: ");
	return 0;
  }
  if (setsockopt (fd, SOL_SOCKET, SO_BROADCAST, &val, sizeof (val)) < 0)
  {
    perror ("setsockopt SO_BROADCAST: ");
	return 0;
  }
  return fd;
};


unsigned char res[4096][2048];
unsigned char res2[4096][2048];

int main(int argc,char* argv[])
{
	int curpel=0;
	int fd=0;
	int size;
	int port=2104;
	struct sockaddr_in out_addr;
	char resname[256];
	struct timeval tv1,tv2;

	if(argc>1)
		port=atoi(argv[1]);

	sprintf(resname,"./primres%d.doc.1",port);
	FILE*  f=fopen(resname,"rb");
	FILE* f2=0;

	if (!f)
	{
		printf("Error open primary file: %s\n",resname);
		return 1;
	}
	if(port==2101)
	{
		sprintf(resname,"./primres%d.doc.2",port);
		f2=fopen(resname,"rb");

		if (!f2)
		{
			printf("Error open primary file: %s\n",resname);
			return 1;
		}
	}
	fd=createSocket();
	if(!fd)
		return 1;

	out_addr.sin_family = AF_INET;
	out_addr.sin_addr.s_addr = inet_addr ("127.0.0.1");
	out_addr.sin_port = htons (port);

	fread(&size,sizeof(size),1,f);
	fread(res,4096*2048,1,f);
	fclose(f);
	printf("size %d\n",size);
	if(port==2101)
	{
		fread(&size,sizeof(size),1,f2);
		fread(res2,4096*2048,1,f2);
		fclose(f2);
	}
	gettimeofday(&tv1,0);
	while(1)
	{
		gettimeofday(&tv2,0);
		if(port==2101 && (tv2.tv_sec-tv1.tv_sec>60))
			sendto(fd,res2[curpel++],size,0,(struct sockaddr *) &out_addr, sizeof (out_addr));
		else
			sendto(fd,res[curpel++],size,0,(struct sockaddr *) &out_addr, sizeof (out_addr));
		if(curpel>=4096) curpel=0;
		usleep((port==2104)?1000:2000);
	}
	return 0;
}
