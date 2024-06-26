#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int getinverse(int a,int m)
{
    for(int i=1;i<m;i++)
    {
        if( (i*a) % m == 1)
            return i;
    }
}

int gcd(int a,int b)
{
    while(b!=0)
    {
        int temp = a;
        a = b;
        b = temp % b;
    }
    return a;
}

int ifisPrime(int a,int b)
{
    if(gcd(a,b)==1)
        return 1;
    else 
        return 0;
}

void encrypt(int a,int b)
{
    int m = 26,i=0,len=0;
    char c[10000] = {0},ch;
    FILE *fp1,*fp2;
    fp1 = fopen("plaintext.txt","r");
    fp2 = fopen("ciphertext.txt","w");
    if(fp1==NULL)
    {
        printf("error!\n");
        exit;
    }
    while(fscanf(fp1,"%c",&ch)!=EOF)
    {
        if(islower(ch))
            c[i] = toupper(ch);
        else
            c[i] = ch;
        i++;
    }
    len = strlen(c);
    for(i=0;i<len;i++)
    {
        if(isupper(c[i]))
            c[i] = 'A' + ( (a * (c[i] - 'A') + b) % 26);
    }
    fputs(c,fp2);
    fclose(fp1);
    fclose(fp2);
    printf("加密成功\n");
}

void decrypt(int a,int b)
{
    FILE *fp1,*fp2;
    fp1 = fopen("ciphertext.txt","r");
    fp2 = fopen("devrypted_plaintext.txt","w");
    if(fp1==NULL)
    {
        printf("error!\n");
        exit;
    }
    char c[10000] = {0},ch;
    int i=0,len=0,inva = getinverse(a,26);
    while(fscanf(fp1,"%c",&ch)!=EOF)
    {
        if(isupper(ch))
            c[i] = tolower(ch);
        else 
            c[i] = ch;
        i++;
    }
    len = strlen(c);
    for(i=0;i<len;i++)
    {
        if(islower(c[i]))
        {
            if((c[i] - 'a') < b)
                c[i] = ( inva * (c[i] - 'a' - b + 26) % 26) + 'a'; 
            else
                c[i] = ( inva * (c[i] - 'a' - b)  % 26) + 'a'; 
        }
    }
    fputs(c,fp2);
    fclose(fp1);
    fclose(fp2);
    printf("解密成功\n");
}
int main()
{
    int a,b,m;
    do
	{
		printf("请输入工作模式：1.加密；2.解密；0.退出\n");
    	scanf("%d",&m);
    	if(m==0)
    		break;
    	else if(m!=0&&m!=1&&m!=2)
    		printf("输入有误，请重新输入！\n");
    	else
    	{
		    printf("请输入密钥a、b，其中a与26互素\n");
		    scanf("%d %d",&a,&b);
		    if(!(ifisPrime(a,26)))
		    {
		        while(!(ifisPrime(a,26)))
		        {
		            printf("请输入与26互素的a!\n");
		            scanf("%d",&a);
		        }
		    }
		    if(m==1)
		        encrypt(a,b);
		    else if(m==2)
		        decrypt(a,b);
		}
	}while(m!=0); 
    return 0;
}
