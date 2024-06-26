#include <stdio.h>
#include <math.h>
//判断 p q是否为素数
int Prime(int m){    
	int i, k;
	if (m<2) return 0;
	k = sqrt(m);
	for (i = 2; i <= k; i++)
		if (m%i == 0)
			break;
	 //素数返回1,否则返回0
	if (i>k)   
		return 1;                  
	else
		return 0;                    
}
//幂的取余
int encrypt(int a, int b, int c){
	int r = 1;
	b = b + 1;
	while (b != 1){
		r = r*a;
		r = r%c;
		b--;
	}
	return r;
}
//判断两数是否互素
int husu(int x, int y){   
	int t;
	while (y){
		t = x;
		x = y;
		y = t%y;
	}
	//x与y互素时返回0，x与y不互素时返回1  
	if (x == 1) 
		return 0;           
	else  
		return 1;   
}

int main() {
	//p,q为素数，e为公钥，d为私钥，m为明文，n为模数 ,c为密文 
	int p, q, e, d, m, n, t, c, r, k;
	printf("请输入两个素数p,q:");
	while (1){
		scanf("%d%d", &p, &q);
		//判断两个数是否为素数，不是的话重新输入
		if ((Prime(p) == 1) && (Prime(q) == 1)){  
			n = p*q;
			break;
		}
		else printf("ERROR!\n请重新输入两个素数p,q\n");
	}
	//求欧拉函数t
	t = (p - 1)*(q - 1);      
	printf("请输入你想设置的公钥e，注意：1<e<φ(n)，且e与(p - 1)*(q - 1)互质。e:");
	scanf("%d", &e);

	while (e<1 || e>t || husu(e, t)){
		printf("ERROR!e不符合要求！请重新输入e:\n");
		scanf("%d", &e);
	}

	d = 1;
	//由公钥e求出私钥d
	while (((e*d) % t) != 1)   
		d++;     
	printf("计算出的私钥d:%d\n",d);
	printf("请输入想要加密的明文:");
	scanf("%d", &m);
	c = encrypt(m, e, n);
	printf("密文为: %d\n", c);
	printf("请输入密文:");
	scanf("%d", &c);
	m = encrypt(c, d, n);
	printf("明文为: %d", m);
}



