#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#pragma pack (push, 4)

struct header   // записываемая структура данных
{
	unsigned short head; // заголовок пакета2
	unsigned short vkl_num;// номер вкюлючения прибора4
	unsigned int source_addr;// IP источника пакета8
	unsigned short source_port;// порт источника пакета10
	unsigned int packet_num; // порядковый номер пакета14
	unsigned int sec;// время приема пакета, сек18
	unsigned int usec;// время приема пакета, мксек22
	unsigned short packet_size; // размер пакета (полезные данные)24
	unsigned int ks;// контрольная сумма заголовка28
};

#pragma pack (pop)

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

void seekStart(FILE* f,long start)
{
	unsigned char data[2048];
	int cnt2048=0;
	if (start)
		fseek(f,start,SEEK_CUR);
	while (!feof(f))
	{
		fread(data,2048,1,f);
		for (int i=0;i<2047;i++)
			if (data[i]==0x55 && data[i+1]==0xAA)
			{
				fseek(f,-2048+i,SEEK_CUR);
				printf("seekStart OK +%d\n",i+2048*cnt2048);
				return;
			}
		cnt2048++;
	}
}

unsigned char res[4096][2048];
unsigned char pelFlags[4096]={0,};

int main(int argc,char* argv[])
{
	FILE*  f=fopen("./prim.doc","rb");
	char resname[256];
	struct header hdr={0,};
	unsigned char data[2048];
	struct prim_header *phdr=(struct prim_header*)data;
	int peleng=0;
	int port=2104;
	int size=0;
	int seek=0;
	if (!f)
	{
		puts("Error open primary file: ./prim.doc");
		return 1;
	}
	if(argc>1)
		port=atoi(argv[1]);
	if(argc>2)
		seek=atoi(argv[2]);
	printf("seekStart...\n");
	for(int i=0;i<seek;i++)
	    fseek(f,1024*1024,SEEK_CUR);
	seekStart(f,0);
	printf("seekStart END\n");


	while (!feof(f))
	{
		fread(&hdr,sizeof(struct header),1,f);
		if (hdr.packet_size<2048)
		{
			fread(data,hdr.packet_size,1,f);
			if (hdr.source_port==port)
			{
				if(!size) size=hdr.packet_size;
				peleng=htons(phdr->peleng);
				printf("peleng %d\n",peleng);
				memcpy(res[peleng],data,2048);
				pelFlags[peleng]=1;
				int allP=1;
				for(int i=0;i<4096;i++)
					if(!pelFlags[i])
					{
						allP=0;
						break;
					}
				if(allP)
					break;
			}
			else continue;
		}
		else
		{
			puts("Too big!");
			return 1;
		}
	}
	fclose(f);

	sprintf(resname,"./primres%d.doc",port);
	f=fopen(resname,"wb");
	if(f)
	{
		fwrite(&size,sizeof(size),1,f);
		fwrite(res,4096*2048,1,f);
		fclose(f);
	}
	else printf("Error open %s\n",resname);
	return 0;
}
