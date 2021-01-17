//此文件单独编译，用于查看键盘的key值
#include <stdio.h>
#include <conio.h>

int main(){
	int kv; 				//键值
	while(1){
		kv = getch();
		printf("%d\n", kv);
		if (kv == 3 || kv == 27) break;
	}
	return 0;
}
