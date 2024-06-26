/******************************************************************************/
//	工程：AES
//	功能：AES加、解密文件
//  作者：epsoft|MISTP

/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <afxwin.h>
#include <fstream.h>

#include "aes.h"

#define DECRYPT_FILE "AES加密密文.txt"
#define ENCRYPT_FILE "AES解密明文.txt"
//! 约束文件最大2M
#define MAX_FILE	1024*1024*2

/******************************************************************************/
//	名称：usage
//	功能：帮助信息
//  参数：应用程序名称
//	返回：提示信息

/******************************************************************************/
void Usage( const char *appname )
{
	printf( "\n\tusage: aes -e 明文文件 128位密钥\n" );
	printf( "\tusage: aes -d 密文文件 128位密钥\n" );
}

/******************************************************************************/
//	名称：FileOut
//	功能：加/解密结果输出到当前目录磁盘文件中
//  参数：strOut指向输出字符缓冲区，输出大小len，strFile为输出文件
//	返回：更新成功返回实际输出长度，否则返回0

/******************************************************************************/
int FileOut( const void *strOut, int len, const char *strFile )
{
	FILE *fp = NULL;
	int iWrite=0;

	if( strOut == NULL || len ==0 )
		goto out;

	//! 打开文件句柄
	if( (fp = fopen( strFile,"wb" )) == NULL ) // 二进制写
		goto out;

	iWrite = fwrite( strOut, 1, len, fp );
	fclose(fp);

out:
	return iWrite;
}

/******************************************************************************/
//	名称：CheckParse
//	功能：校验应用程序入口参数
//  参数：argc等于main主函数argc参数，argv指向main主函数argv参数
//	返回：若参数合法返回true，否则返回false
//  备注：简单的入口参数校验

/******************************************************************************/
bool CheckParse( int argc, char** argv )
{
	if( (argc != 4) || 
		(argv[1][1]!='e' && argv[1][1]!='d') ||
		(strlen( argv[3] ) >(128/8) ) )
	{
		Usage( argv[0] );
		return false;
	}

	return true;
}

//! 程序主函数(Use MFC in a Shared DLL)
int main( int argc, char **argv )
{
	//! 在此处填写代码......
	unsigned char s[100];//密钥
	unsigned int c[100];//文件内容

	int n;
    printf("AES加解密程序：\n");
	while(1)
	{
		cout<<"0.加密；1.解密；2.退出"<<endl;
		cin>>n;

		if(n == 2)
			break;
		else if(n == 0)
		{
			cout<<"请输入需要加密的文件名："<<endl;
			char textfilename[100];
			gets(textfilename);

			fstream f1(textfilename,ios::in);
			int j=0;
			unsigned char p;
			while(f1>>p)
			{
				c[j] = (unsigned int)p;
				j++;
			}

			cout<<"请输入密钥文件名："<<endl;
			char keyfilename[100];
			gets(keyfilename);

			fstream f(keyfilename,ios::in);
			int i = 0;
			while(f>>s[i])
			{
				i++;
			}

			aes_encrypt(s,c);//AES加密

			cout<<"请输入加密后的文件名"<<endl;
			char textendfilename[100];
			gets(textendfilename);

			fstream f2(textendfilename,ios::out);
			for(int k=0;k<j;k++)
			{
				f2<<c[k]<<" ";
			}
			f.close();
			f1.close();
			f2.close();

			cout<<"加密成功！"<<endl;
		}

		else if(n == 1)
		{
			cout<<"请输入需要解密的文件名"<<endl;
			char text2filename[100];
			gets(text2filename);

			fstream f3(text2filename,ios::in);
			unsigned int c2[100];
			int q=0;
			while(f3>>c2[q])
			{
				q++;
			}

			unsigned char s2[100];
			cout<<"请输入解密密钥文件名"<<endl;
			char key2[100];
			gets(key2);
			
			fstream f4(key2,ios::in);
			int pkey2=0;
			while(f4>>s2[pkey2])
			{
				pkey2++;
			}
			
			aes_decrypt(s2,c2);//AES解密

			cout<<"请输入解密后的文件名"<<endl;
			char textend2filename[100];
			gets(textend2filename);

			fstream f5(textend2filename,ios::out);
			for(int kp=0;kp<q;kp++)
			{
				f5<<(unsigned char)c2[kp];
			}
			f3.close();
			f4.close();
			f5.close();

			cout<<"解密成功！"<<endl;
			
		}
		else
			cout<<"输入有误，请重新输入！"<<endl;
	}

	return 0;
}