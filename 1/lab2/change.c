//单表置换

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void encrypt(char *k){
    FILE *fp1 = fopen("origion.txt","r");
    FILE *fp2 = fopen("encrypt.txt","w");
    if(fp1==NULL)
    {
        printf("error!\n");
        exit;
    }
    int i=0,len=0;
    char a[10000],ch;
    while(fscanf(fp1,"%c",&ch)!=EOF){
        if(ch>='a'&&ch<='z')
            a[i] = toupper(ch);
        else
            a[i] = ch;
        i++;
        len++;
    }
    for(i=0;i<len;i++)
    {
        if(a[i]>='A'&&a[i]<='Z')
            a[i] = k[a[i] -'A'];
    }
    printf("%s\n",a);
    fputs(a,fp2);
    fclose(fp1);
    fclose(fp2);
}
void decrypt(char *k)
{
    FILE *fp1 = fopen("encrypt.txt","r");
    FILE *fp2 = fopen("decrypt.txt","w");
    if(fp1==NULL)
    {
        printf("error!\n");
        exit;
    }
    char b[10000]={0},ch;
    int i = 0,len = 0, j = 0;
    while(fscanf(fp1,"%c",&ch)!=EOF)
    {
        b[i] = ch;
        i++;
        len++;
    }
    for(i=0;i<len;i++)
    {
        if(b[i]>='A'&&b[i]<='Z')
        {
            for(j=0;j<26;j++)
            {
                if(k[j]==b[i])
                    b[i] = 'a' + j;
            }
        }
    }
    for(i=0;i<len;i++)
    {
        b[i] = b[i] - 32;
    }
    printf("%s\n",b);
    fputs(b,fp2);
    fclose(fp1);
    fclose(fp2);
}
int main(){
    FILE *fp1,*fp2;
    int m;
    do{
	    printf("加密请输入1\n解密请输入2\n退出请输入0\n");
	    scanf("%d",&m);
	    if(m==0)
			break;
		else if(m!=0&&m!=1&&m!=2)
			printf("输出格式有误，请重新输入！\n");
		else
		{
			char k[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'},
	    	*c,*s;
	    	c = (char*)malloc(sizeof(char));
	    	s = (char*)malloc(sizeof(char));
			getchar();
		    printf("请输入密钥：\n");    
		    scanf("%[^\n]",c);
		    int len = strlen(c);
		    int i,j;
		    for(i=0,j=0;i<len;i++,j++){
		        if(isupper(c[i]))
		            s[j] = c[i];
		        else if(islower(c[i]))
		            s[j] = toupper(c[i]);
		        else
		            j--;
		    }
		    len = strlen(s);
		    int flag = 0;
		    int min = 26;
		    for(i=0;i<len;i++){
		        int temp = 1;
		        for(j=0;j<flag;j++){
		            if(s[i]==k[j]){
		                temp = 0;
		                break;
		            }
		        }
		        if(temp){
		            if(s[i]!=k[flag]){ 
		                int n = (s[i]-'A'>min)?s[i]-'A':flag+s[i]-'A';
		                for(n;n>flag;n--){
		                    k[n] = k[n-1];
		                }
		                k[flag] = s[i];       
		            }
		            flag++;
		            if(s[i]-'A'<min)
		                min = s[i]-'A';
		        }
		    }
		
		    if(m==1)
		    {
		        encrypt(k);
		        printf("加密方成功进行加密！\n"); 
		    }
		    else if(m==2)
		    {
		        decrypt(k);
		        printf("解密方成功进行解密！\n");
		    }
		}
	    
	}while(m!=0);
   
    return 0;
}

