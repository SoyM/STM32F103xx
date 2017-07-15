#include "stdio.h"

unsigned char *point;
float num;

int main()
{
	printf("Ctrl + C退出，Enter开始。");
	while (getchar() != EOF) {
		printf("输入浮点数:");
		scanf("%f", &num);
		printf("\n浮点数:      %f\n", num);
		point = (unsigned char*)&num;
		printf("十六进制:    %X", point[3]);
		printf("-%X", point[2]);
		printf("-%X", point[1]);
		printf("-%X\n\n\n", point[0]);	
	}
}

