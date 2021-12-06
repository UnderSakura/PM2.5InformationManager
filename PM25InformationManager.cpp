#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MaxInfoList 100
#define MaxAdminInfo 10
#define MaxCharNum 20

typedef struct
{
	int CityNum;//4
	char CityName[MaxCharNum];//8
	int AQIValue;
	char AirCondi[MaxCharNum];
	int PM2Value;
	int PM10Value;
	int COValue;
}CityInfo;

typedef struct
{
	char AdminName[MaxAdminInfo];
	char AdminPassword[MaxAdminInfo];
}AdminInfo;

typedef struct
{
	CityInfo Info[MaxInfoList];
	int Length;
}SortList;

int AdminAuthen()//管理员认证
{
	AdminInfo adminInfo;
	char InputAdminName[]="Admin",InputAdminPassword[]="12345";
	int currentChance=5;
	while(currentChance>0)
	{
		printf("请输入管理员用户名: ");
		scanf("%s",&adminInfo.AdminName);
		if(strcmp(adminInfo.AdminName,InputAdminName))
		{
			printf("管理员用户名输入错误!\n");
		}
		else
		{
			printf("请输入管理员密码: ");
			scanf("%s",&adminInfo.AdminPassword);
			if(strcmp(adminInfo.AdminPassword,InputAdminPassword))
			{
				printf("管理员密码输入错误!(您还有%d次输入)\n",currentChance-1);
				currentChance--;
			}
			else
				return 1;
		}
	}
	printf("输入次数已达上限!\n");
	return 0;
}

bool SequenListInsert(SortList *&sortList,int i,CityInfo cityInfo)//顺序表
{
	int j;
	if(i<1 || i>sortList->Length+1 || sortList->Length==MaxInfoList)
	{	
		printf("数据表已满或插入不合法或值错误\n");
		return false;
	}
	i--;
	for(j=sortList->Length;j>i;j--)
	{
		sortList->Info[j]=sortList->Info[j-1];
	}
	sortList->Info[i]=cityInfo;
	sortList->Length++;
	//printf("Debug");
	return true;
}

int CreateSortList(SortList *&sortList)
{
	int i,num,currentCityNum=1;
	CityInfo cityInfo;
	sortList=(SortList *)malloc(sizeof(SortList));
	sortList->Length=0;
	printf("请输入录入城市总数: \n");
	scanf("%d",&num);
	for(i=1;i<=num;i++)
	{	
		cityInfo.CityNum=currentCityNum;
		printf("请输入城市名称: \n");
		scanf("%s",&cityInfo.CityName);
		printf("请输入城市AQI值: \n");
		scanf("%d",&cityInfo.AQIValue);
		printf("请输入城市空气状况: \n");
		scanf("%s",&cityInfo.AirCondi);
		printf("请输入城市PM2.5值: \n");
		scanf("%d",&cityInfo.PM2Value);
		printf("请输入城市PM10值: \n");
		scanf("%d",&cityInfo.PM10Value);
		printf("请输入城市CO值: \n");
		scanf("%d",&cityInfo.COValue);
		SequenListInsert(sortList,i,cityInfo);
		currentCityNum++;
	}
	printf("\n////创建成功///\n");
	return 1;
}

bool CityDataAlter(SortList *&sortList)
{
	char currentCityName[MaxCharNum];
	printf("请输入要修改的城市名称：\n");
	scanf("%s",&currentCityName);
	for(int i=0;i<sortList->Length;i++)
	{
		if(!strcmp(currentCityName,sortList->Info[i].CityName))
		{
			printf("请输入城市AQI值: \n");
			scanf("%d",&sortList->Info[i].AQIValue);
			printf("请输入城市空气状况: \n");
			scanf("%s",&sortList->Info[i].AirCondi);
			printf("请输入城市PM2.5值: \n");
			scanf("%d",&sortList->Info[i].PM2Value);
			printf("请输入城市PM10值: \n");
			scanf("%d",&sortList->Info[i].PM10Value);
			printf("请输入城市CO值: \n");
			scanf("%d",&sortList->Info[i].COValue);
		}
	}
	return true;
}

bool LocateCityData(SortList *sortList)
{
	char currentCityName[MaxCharNum];
	printf("请输入要查找的城市名称：\n");
	scanf("%s",&currentCityName);
	for(int i=0;i<sortList->Length;i++)
	{
		if(!strcmp(currentCityName,sortList->Info[i].CityName))
		{
			printf("城市AQI值: ");
			printf("%d\n",sortList->Info[i].AQIValue);
			printf("城市空气状况: ");
			printf("%s\n",sortList->Info[i].AirCondi);
			printf("城市PM2.5值: ");
			printf("%d\n",sortList->Info[i].PM2Value);
			printf("城市PM10值: ");
			printf("%d\n",sortList->Info[i].PM10Value);
			printf("城市CO值: ");
			printf("%d\n",sortList->Info[i].COValue);
		}
	}
	return true;
}

void DispSortList(SortList *sortList)
{
	for(int i=0;i<sortList->Length;i++)
	{
		printf("城市编号\t  城市名字\t  \tAQI值   空气状况   PM2.5值   PM10值   CO值\n");
		printf("%d\t",sortList->Info[i].CityNum);
		printf("\t%s\t\t",sortList->Info[i].CityName);
		printf("\t%d\t",sortList->Info[i].AQIValue);
		printf("  %s\t",sortList->Info[i].AirCondi);
		printf("\t%d\t",sortList->Info[i].PM2Value);
		printf("%d\t",sortList->Info[i].PM10Value);
		printf("%d\n",sortList->Info[i].COValue);
	}
}

bool SortListAQICompareUp(SortList *&sortList,int currentCityNum)
{
	CityInfo cityInfo;
	bool isAQIMoveInSort=false;
	for(int i=0;i<sortList->Length-1;i++)
	{
		if(sortList->Info[currentCityNum].AQIValue<sortList->Info[i].AQIValue)
		{
			cityInfo=sortList->Info[currentCityNum];
			sortList->Info[currentCityNum]=sortList->Info[i];
			sortList->Info[i]=cityInfo;
			isAQIMoveInSort=true;
		}
	}
	if(!isAQIMoveInSort)
		return false;
	if(isAQIMoveInSort==true)
		return true;
}

void AQIRankUp(SortList *&sortList)//升序
{
	int currentCityNum=0;
	bool isMove=true;
	for(currentCityNum;currentCityNum<sortList->Length;currentCityNum++)
	{
		isMove=true;
		while (isMove)
		{
			isMove=SortListAQICompareUp(sortList,currentCityNum);
		}
	}
}

bool SortListAQICompareDown(SortList *&sortList,int currentCityNum)
{
	CityInfo cityInfo;
	bool isAQIMoveInSort=false;
	for(int i=0;i<sortList->Length-1;i++)
	{
		if(sortList->Info[currentCityNum].AQIValue>sortList->Info[i].AQIValue)
		{
			cityInfo=sortList->Info[currentCityNum];
			sortList->Info[currentCityNum]=sortList->Info[i];
			sortList->Info[i]=cityInfo;
			isAQIMoveInSort=true;
		}
	}
	if(!isAQIMoveInSort)
		return false;
	if(isAQIMoveInSort==true)
		return true;
}

void AQIRankDown(SortList *&sortList)//降序
{
	int currentCityNum=0;
	bool isMove=true;
	for(currentCityNum;currentCityNum<sortList->Length;currentCityNum++)
	{
		isMove=true;
		while (isMove)
		{
			isMove=SortListAQICompareDown(sortList,currentCityNum);
		}
	}
}
bool ListDelete(SortList *&L,int i)
{
	int j;
	if(i<1||i>L->Length)
		return false;
	i--;
	for(j=i;j<L->Length-1;j++)
	{
		L->Info[j]=L->Info[j+1];
	}
	L->Length--;
	return true;
}

bool FuzzySearch(SortList *sortList)
{
	return true;
}

int MainUser(SortList *sortList)
{
	int isChoose,isExit=1;
	do
	{
		printf("-----------PM2.5管理员系统---------------\n");
		printf("//        1.城市空气指数表               //\n");
		printf("//        2.选择城市显示空气指数         //\n");
		printf("//        3.城市AQI降序                 //\n");
		printf("//        4.城市AQI升序                 //\n");
		printf("//        0.退出管理系统                //\n");
		printf("----------------------------------------\n");
		printf("请输入您的选择：");
		scanf("%d",&isChoose);
		switch(isChoose)
		{
			case 1:
				DispSortList(sortList);
				break;
			case 2:
				LocateCityData(sortList);
				break;
			case 3:
				AQIRankDown(sortList);
				break;
			case 4:
				AQIRankUp(sortList);
				break;
			case 0:
				isExit=0;
				break;
			default:
				printf("输入有误，请重新输入(0~2)\n");
				break;
		}
	}while(isExit);
	return 1;
}

int MainAdminManager(SortList *&sortList)
{
	int isChoose,isExit=1;
	do
	{
		printf("-----------PM2.5管理员系统---------------\n");
		printf("//         1.城市空气指数表              //\n");
		printf("//         2.城市空气指数修改            //\n");
		printf("//         0.退出管理系统                //\n");
		printf("-----------------------------------------\n");
		printf("请输入您的选择：");
		scanf("%d",&isChoose);
		switch(isChoose)
		{
			case 1:
				CreateSortList(sortList);
				break;
			case 2:
				CityDataAlter(sortList);
				break;
			case 3:
				DispSortList(sortList);
				break;
			case 0:
				isExit=0;
				break;
			default:
				printf("输入有误，请重新输入(0~2)\n");
				break;
		}
	}while(isExit);
	return 1;
}


int main()//主函数
{	
	int isChoose;
	SortList *sortList;
	do
	{
		printf("-----------PM2.5实时信息管理系统---------\n");
		printf("\\         1.普通用户入口             \\\n");
		printf("\\         2.管理员入口               \\\n");
		printf("\\         0.退出系统                 \\\n");
		printf("-----------------------------------------\n");
		printf("请输入您的选择：");
		scanf("%d",&isChoose);
		switch(isChoose)
		{
			case 1:
				printf("欢迎!");
				MainUser(sortList);
				break;
			case 2:
				printf("已进入管理员入口!\n");
				AdminAuthen();
				MainAdminManager(sortList);
				break;
			case 0:
				exit(0);
			default:
				printf("输入有误，请重新输入(0~2)\n");
				break;
		}
	}while(1);
	return 0;
}
