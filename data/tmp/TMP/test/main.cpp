#include <stdio.h>

using namespace std;

int main(int argc, char *argv[]) {
	int Sl=0,Sr=0,Dl=0,Dr=0,N=0;
	scanf("%d %d %d %d %d",&Sl, &Sr, &Dl, &Dr, &N);	
	int brak=0, norm=0;
	char ** out = new char *[N];
	int i=0;
	while(N != i) {
		int Si, Di;
		scanf("%d %d",&Si, &Di);
		if(Si >= Sl && Si <= Sr && Di >= Dl && Di <= Dr) {
			out[i] = new char[2];		
			out[i]="0";
			norm++;
		} else {
			out[i] = new char[2];
			out[i]="1";
			brak++;
		}
		i++;
	}
	
	
	i=0;
	while(N != i) {
		printf("%s\n",out[i]);
		i++;
	}
	printf("%d %d\n",norm, brak);
    	return 0;
}
