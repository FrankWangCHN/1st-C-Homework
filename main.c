#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
typedef struct student
{
	char number[10];  //ѧ��
	char name[10];    //����
	float dailyScore; //ƽʱ�ɼ�
	float experimentalScore;//ʵ��ɼ�
	float finalScore;   //��ĩ�ɼ�
	float generalScore; //�����ɼ�

}SS;

    SS *readDataFromFile(int *N)
    {

	printf("\n\n------��һ��: ���ļ���ȡѧ���ĳɼ���Ϣ--------\n\n");

	SS *stu;// �����¿ռ�,��ȡ�ļ��е�ÿ��ѧ����Ϣ

	FILE *fp = NULL;
	int count = 0;
	int index = 0;

	fp = fopen("data.txt", "r");

	//1.��ȡѧ����Ŀ
	if (fp != NULL)
	{
		fscanf(fp, "%d", &count);
		*N = count;
	}
	else
	{
		printf("failed to open the info file\n");
		getchar();
	}

	printf("ѧ����ĿΪ:%d\n", count);


	//2.������ѧ������洢�ռ�
	stu = (SS*)malloc(count * sizeof(SS));


	//3.��ȡÿ��ѧ������Ϣ
	while ((!feof(fp)))
	{

		//�����ļ����ݵ��ڴ�
		fscanf(fp, "%s%s%f%f%f\n", (stu[index].number), (stu[index].name), &stu[index].dailyScore, &stu[index].experimentalScore, &stu[index].finalScore);

		//���������ѧ����Ϣ
		printf("* ѧ�ţ�%s	����:%s		ƽʱ�ɼ���%4.2f��		ʵ��ɼ���%4.2f��		��ĩ�ɼ�:%4.2f��\n", (stu[index].number), (stu[index].name), stu[index].dailyScore, &stu[index].experimentalScore,stu[index].finalScore);

		index++;
	}

	getchar();

	fclose(fp);

	return stu;
}

void writeData(SS stu[], int N)
{

	printf("\n");

    FILE *fp;
    int i=0,n=0;
    char sign='y';
    system("cls");                              //����ϵͳ����
    SS *stu;
    while(sign!='n'&&sign!='N')                    //��ʵֻ�е�����N��nʱ������ѭ��
      {
        printf("             ----ѧ����¼���----\n");
        printf("ѧ�ţ�\n");
        scanf("\t%s",&stu[i].number);
        printf("����:\n");
        scanf("\t%s",&stu[i].name);
        printf("ƽʱ�ɼ���\n");
        scanf("\t%f",&stu[i].dailyScore);
        printf("ʵ��ɼ���\n");
        scanf("\t%f",&stu[i].experimentalScore);
        printf("��ĩ�ɼ���\n");
        scanf("\t%f",&stu[i].finalScore);
        printf("�Ƿ�������?(y/n)");
        scanf("\t%c",&sign);
        i++;
        n=n+1;
        system( "cls ");
   }system("pause");                                     //ϵͳ�ȴ�����

   if((fp=fopen("data.txt","a"))==NULL)                    //��2������ʽ�����ļ�β׷��//
      {
         printf("cannot open the files\n");
         system("pause");
         return;                                         //����ļ����ִ��� �ͷ���
       }
        for(i=0;i<n;i++)
        {
            fprintf(fp,"%s %s %f %f %f %f %f\n",stu[i].number, (stu[i].name), &stu[i].dailyScore, &stu[i].experimentalScore, &stu[i].finalScore);    //��2������ʽд���ļ���//һ��д��һ������//

        }
        //printf("file write error\n");
        fclose(fp);                                       //�ر��ļ�
        system("pause");

	printf("------�ɼ�¼�����!--------\n");

}

void calcuScore(SS stu[], int N)
{


	printf("\n\n------�ڶ���: ����ÿ��ѧ���������ɼ�--------\n\n");

	for (int i = 0; i < N; i++)
	{

		stu[i].generalScore = 0.2*stu[i].dailyScore + 0.6*stu[i].experimentalScore + 0.6*stu[i].finalScore;
		printf("* ѧ�ţ�%s	����:%s		�ܳɼ�:%4.2f��\n", (stu[i].number), (stu[i].name), stu[i].generalScore);

	}

	getchar();
}

int cmpBigtoSmall(const void *a, const void *b)
{

	SS *aa = (SS *)(a);
	SS *bb = (SS *)(b);



	if ((*aa).generalScore < (*bb).generalScore)  return 1;

	else if ((*aa).generalScore > (*bb).generalScore)  return -1;

	else
		return 0;

}

void sortScore(SS stu[], int N)
{

	qsort(&(stu[0]), N, sizeof(stu[0]), cmpBigtoSmall);

}


void printOut(SS stu[], int N)
{

	printf("\n------������: �����ܳɼ����ѧ��������Ϣ!------\n\n");

	for (int i = 0; i < N; i++)
	{

		printf("��%d����Ϣ ѧ�ţ�%s	����:%s		�ܳɼ�:%4.2f��\n", i + 1, &(stu[i].number[0]), &(stu[i].name[0]), stu[i].generalScore);
	}

	getchar();

}

int main()
{
    char ds;
    	/*-1.������ʼ��-*/
	int N = 0;            //ѧ������
	SS  *pstu = NULL;    //ѧ������-�ṹ������ָ��ʵ��

	//2.��ȡѧ����Ϣ
	pstu = readDataFromFile(&N);

	//3.���ѧ����Ϣ
	printf("�Ƿ�Ҫ���ѧ����Ϣ��(y/n)\n");
	ds=getchar();
	if(ds=='y')
	writedata(pstu,N);
	else;

	/*-3.����ѧ���ܳɼ����ܳɼ� = 0.3*ƽʱ�ɼ� + 0.8*��ĩ�ɼ�)--*/
	calcuScore(pstu, N);

	/*-4.����ѧ���ɼ�����-*/
	sortScore(pstu, N);

	/*-5.�����������ѧ����Ϣ-*/
	printOut(pstu, N);

	/*-6.�ͷŶ�̬�ڴ�ռ�-*/
	free(pstu);


	system("pause");
	return 0;
}

