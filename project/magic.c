#include<stdio.h>
	void crypt(char *c){
		char*ptr=c;
		while(*ptr!='\0'){
		*ptr=*ptr-1;
		 ptr++;
	}
}
int main(){
	char c[]="Tivcibn!jt!jo!mpwf";
	crypt(c);
	printf("%s",c);
	return 0;
}