#include "stdio.h"

unsigned char *point;
float num;

int main()
{
	printf("Ctrl + C�˳���Enter��ʼ��");
	while (getchar() != EOF) {
		printf("���븡����:");
		scanf("%f", &num);
		printf("\n������:      %f\n", num);
		point = (unsigned char*)&num;
		printf("ʮ������:    %X", point[3]);
		printf("-%X", point[2]);
		printf("-%X", point[1]);
		printf("-%X\n\n\n", point[0]);	
	}
}

