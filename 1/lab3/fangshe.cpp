//仿射密码

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//计算a在模m下的乘法逆元。
//通过遍历1到m-1的整数，找到满足(i * a) % m = 1的数i，并返回i。
//如果不存在则返回0。 
int getinverse(int a,int m){
	int i; 
    for(i=1;i<m;i++){
        if( (i*a) % m == 1)
            return i;
    }
}
//求a和b的最大公约数。
//使用辗转相除法（欧几里德算法）计算a和b的最大公约数，直到b为0，返回a的值。
int gcd(int a,int b){
    while(b!=0){
        int temp = a;
        a = b;
        b = temp % b;
    }
    return a;
}
//判断a和b是否互质
//原理即调用gcd函数计算a和b的最大公约数
//如果最大公约数为1，则返回1，否则返回0。
int ifisPrime(int a,int b){
    if(gcd(a,b)==1)
        return 1;
    else 
        return 0;
}

//对明文进行加密
void encrypt(int a,int b){
    int m = 26,i=0,len=0;
    char c[10000] = {0},ch;
    FILE *fp1,*fp2;
    fp1 = fopen("origion.txt","r");
    fp2 = fopen("encrypt.txt","w");
    if(fp1==NULL){
        printf("open file error!\n");
        exit;
    }
    while(fscanf(fp1,"%c",&ch)!=EOF){
        c[i] = ch;
        i++;
    }
    len = strlen(c);
    for(i=0;i<len;i++){
    	if(islower(c[i]))
            c[i] = 'a' + ( (a * (c[i] - 'a') + b) % 26);
        if(isupper(c[i]))
            c[i] = 'A' + ( (a * (c[i] - 'A') + b) % 26);
    }
    fputs(c,fp2);
    
    fclose(fp1);
    fclose(fp2);
    printf("加密密文为：%s\n",c);
	printf("加密方成功进行加密！\n");
}

//对密文进行解密。
void decrypt(int a,int b){
    FILE *fp1,*fp2;
    fp1 = fopen("encrypt.txt","r");
    fp2 = fopen("decrypt.txt","w");
    if(fp1==NULL){
        printf("open file error!\n");
        exit;
    }
    char c[10000] = {0},ch;
    int i=0,len=0,inva = getinverse(a,26);
    while(fscanf(fp1,"%c",&ch)!=EOF){
        c[i] = ch;
        i++;
    }
    len = strlen(c);
    for(i=0;i<len;i++){
        if(islower(c[i])){
            if((c[i] - 'a') < b)
                c[i] = ( inva * (c[i] - 'a' - b + 26) % 26) + 'a'; 
            else
                c[i] = ( inva * (c[i] - 'a' - b)  % 26) + 'a'; 
        }
        if(isupper(c[i])){
            if((c[i] - 'A') < b)
                c[i] = ( inva * (c[i] - 'A' - b + 26) % 26) + 'A'; 
            else
                c[i] = ( inva * (c[i] - 'A' - b)  % 26) + 'A'; 
        }
    }
    fputs(c,fp2);
    fclose(fp1);
    fclose(fp2); 
    printf("解密所得明文为：%s\n",c);
	printf("解密方成功进行解密！\n");
}
int main(){
    int a,b,m;
    do{
		printf("加密请输入1\n解密请输入2\n退出请输入0\n");
    	scanf("%d",&m);
    	if(m==0)
    		break;
    	else if(m!=0&&m!=1&&m!=2)
    		printf("输入有误，请重新输入！\n");
    	else{
		    printf("请输入密钥a、b，其中a与26互素\n");
		    scanf("%d %d",&a,&b);
		    if(!(ifisPrime(a,26))){
		        while(!(ifisPrime(a,26))){
		            printf("经检测，输入a值与26不满足互素条件，请输入与26互素的a!\n");
		            scanf("%d",&a);
		        }
		    }
		    if(m==1)
		        encrypt(a,b);
		    else if(m==2)
		        decrypt(a,b);
		}
	}while(m!=3); 
    return 0;
}

