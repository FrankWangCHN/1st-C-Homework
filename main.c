#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
typedef struct student
{
	char number[10];  //学号
	char name[10];    //姓名
	float dailyScore; //平时成绩
	float experimentalScore;//实验成绩
	float finalScore;   //期末成绩
	float generalScore; //总评成绩

}SS;

    SS *readDataFromFile(int *N)
    {

	printf("\n\n------第一步: 从文件读取学生的成绩信息--------\n\n");

	SS *stu;// 开辟新空间,存取文件中的每个学生信息

	FILE *fp = NULL;
	int count = 0;
	int index = 0;

	fp = fopen("data.txt", "r");

	//1.获取学生数目
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

	printf("学生数目为:%d\n", count);


	//2.给所有学生分配存储空间
	stu = (SS*)malloc(count * sizeof(SS));


	//3.读取每条学生的信息
	while ((!feof(fp)))
	{

		//读入文件数据到内存
		fscanf(fp, "%s%s%f%f%f\n", (stu[index].number), (stu[index].name), &stu[index].dailyScore, &stu[index].experimentalScore, &stu[index].finalScore);

		//输出排序后的学生信息
		printf("* 学号：%s	姓名:%s		平时成绩：%4.2f分		实验成绩：%4.2f分		期末成绩:%4.2f分\n", (stu[index].number), (stu[index].name), stu[index].dailyScore, &stu[index].experimentalScore,stu[index].finalScore);

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
    system("cls");                              //清屏系统函数
    SS *stu;
    while(sign!='n'&&sign!='N')                    //其实只有当输入N或n时才跳出循环
      {
        printf("             ----学生纪录添加----\n");
        printf("学号：\n");
        scanf("\t%s",&stu[i].number);
        printf("姓名:\n");
        scanf("\t%s",&stu[i].name);
        printf("平时成绩：\n");
        scanf("\t%f",&stu[i].dailyScore);
        printf("实验成绩：\n");
        scanf("\t%f",&stu[i].experimentalScore);
        printf("期末成绩：\n");
        scanf("\t%f",&stu[i].finalScore);
        printf("是否继续添加?(y/n)");
        scanf("\t%c",&sign);
        i++;
        n=n+1;
        system( "cls ");
   }system("pause");                                     //系统等待命令

   if((fp=fopen("data.txt","a"))==NULL)                    //以2进制形式进行文件尾追加//
      {
         printf("cannot open the files\n");
         system("pause");
         return;                                         //如果文件出现错误 就返回
       }
        for(i=0;i<n;i++)
        {
            fprintf(fp,"%s %s %f %f %f %f %f\n",stu[i].number, (stu[i].name), &stu[i].dailyScore, &stu[i].experimentalScore, &stu[i].finalScore);    //以2进制形式写入文件中//一次写入一个数组//

        }
        //printf("file write error\n");
        fclose(fp);                                       //关闭文件
        system("pause");

	printf("------成绩录入完毕!--------\n");

}

void calcuScore(SS stu[], int N)
{


	printf("\n\n------第二步: 计算每个学生的总评成绩--------\n\n");

	for (int i = 0; i < N; i++)
	{

		stu[i].generalScore = 0.2*stu[i].dailyScore + 0.6*stu[i].experimentalScore + 0.6*stu[i].finalScore;
		printf("* 学号：%s	姓名:%s		总成绩:%4.2f分\n", (stu[i].number), (stu[i].name), stu[i].generalScore);

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

	printf("\n------第三步: 根据总成绩输出学生排名信息!------\n\n");

	for (int i = 0; i < N; i++)
	{

		printf("第%d名信息 学号：%s	姓名:%s		总成绩:%4.2f分\n", i + 1, &(stu[i].number[0]), &(stu[i].name[0]), stu[i].generalScore);
	}

	getchar();

}

int main()
{
    char ds;
    	/*-1.变量初始化-*/
	int N = 0;            //学生总数
	SS  *pstu = NULL;    //学生数组-结构体数组指针实现

	//2.读取学生信息
	pstu = readDataFromFile(&N);

	//3.添加学生信息
	printf("是否要添加学生信息？(y/n)\n");
	ds=getchar();
	if(ds=='y')
	writedata(pstu,N);
	else;

	/*-3.计算学生总成绩（总成绩 = 0.3*平时成绩 + 0.8*期末成绩)--*/
	calcuScore(pstu, N);

	/*-4.根据学生成绩排名-*/
	sortScore(pstu, N);

	/*-5.按照排名输出学生信息-*/
	printOut(pstu, N);

	/*-6.释放动态内存空间-*/
	free(pstu);


	system("pause");
	return 0;
}

