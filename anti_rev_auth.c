#include <stdio.h>
#include "base64.h"
#include <string.h>
#include <stdlib.h>
#include <sys/ptrace.h>
char* gen_key(const char* login);
const char M=0xfb;
const char a=0xfa;
const char c=0xee;
char state;
char LCG();
char* (*indirect_call)(const char*)=NULL;//trick to erase xrefs in IDA/ghidra/...

char* gen_key(const char* login) //generating key based on user's login
{
	int l=strlen(login);
	int flen;
	char* key=(char *)malloc(sizeof(char)*l);
	for(size_t i=0; i<l; i++)
	{
		key[i]=login[i]^LCG();
	}
	char* ret=base64(key, l, &flen);
	free(key);
	return ret;

}
void detect() //detecting debuggers:)
{
	if(ptrace(PTRACE_TRACEME, 0, NULL, NULL)==-1)
	{
		printf("Debuggers are not allowed bro\n");
		exit(0);
	}
	else
		return;
}
void reg() //asks for the username and generates the key
{
	state=0xaa;
	printf("Enter username to register:\n");
	char login[32];
	fgets(login, 32, stdin);
	char* key=(*indirect_call)(login);
	printf("Successfully registered\n");
	printf("Your key: %s\n", key);
	free(key);
}

void login() //asks for the username and the key, generates the key and comparing with userinput
{
	state=0xaa;
	char user_key[64];
	printf("Enter your username to login:\n");
	char login[32];
	fgets(login, 32, stdin);
	char* key=(*indirect_call)(login);
	//printf("[DEBUG] key=%s\n", key);
	printf("\nEnter your key:\n");
	fgets(user_key, 64, stdin);
	user_key[strcspn(user_key, "\n")]=0;
	if(strcmp(user_key, key)==0)
		printf("Successful authentication.....\nHere is your secret information: HSE{Im_bad_in_anti_reversing_techniques:(}\n");
	else
		printf("Wrong key");
	free(key);
	
}
void menu() //displaying menu
{
	printf("Welcome to the great authentication system:)");
	printf("\n1 - Register\n2 - Login\n3 - Exit\n");
	int choice;
	scanf("%d\n", &choice);
	if(choice==1)
		reg();
	else if(choice==2)
		login();
	else if(choice==3)
		exit(0);
	else
	{
		printf("Wrong choice\n");
		return;
	}
}
char LCG() //Simple LCG generator with constant initial state:(
{
	state=(a*state+c)%M;
	return state;
}

/*void __attribute__((constructor)) before_main() //detect debuggers before main
{
	detect();
}*/

int main()
{
	detect();
	indirect_call=gen_key;
	menu();
}
