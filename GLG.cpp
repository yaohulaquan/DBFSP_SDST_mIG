#include <tchar.h>
#include <cstdio>
#include <tchar.h>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iomanip>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <random>
#include <ctime>
#include <string>
//#pragma comment(lib,"ws2_32.lib")
//#pragma warning(disable:4996)


using namespace std;
# include "com.h"
# include "Local.h"
# include "Global.h"
# include "IG.h"
# include"IGZCY.h"



#define _CRT_SECURE_NO_WARNINGS

int old_main()
{



	/*
	int job = 4;
	vector<vector<int>>Seq(2);
	for (int i = 0; i < 2; i++)
		Seq[i].resize(2);


	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			Seq[i][j] = j+i;
	}

	Seq[0][0] = 0;
	Seq[0][1] = 1;
	Seq[1][0] = 2;
	Seq[1][1] = 3;





	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			printf("%d", Seq[i][j]);
		printf("\n");
	}





	vector<int>block(3);
	for (int i = 0; i < 3; i++)
		block[i] = i;

	vector<vector<int>>seq(2);
	for (int i = 0; i < 2; i++)
		seq[i].resize(2);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			seq[i][j] = j;
	}
	//Block_To_Best_Factory_Bestposition_B(block, seq, 3);
	for (int i = 0; i < 3; i++)
		printf("%d ", block[i]);
	printf("\n");

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			printf("%d", seq[i][j]);
		printf("\n");
	}



	*/





	int CPU = 5;
	cout << "IGVND_" << CPU << endl;
	vector<vector<int>>SpanFactory_IGVND;
	SpanFactory_IGVND.resize(270);
	for (int ins = 0; ins < SpanFactory_IGVND.size(); ins++)
		SpanFactory_IGVND[ins].resize(5, 0);

	string FileDirectory = "Result\\";
	ostringstream str;
	str << "IGVND1_" << CPU << ".txt";               //��ͬ���㷨
	ofstream ofile;
	ofile.open(str.str());


	//for (int aa = 39; aa <= 40; aa++)
	//{
	for (int Ins = 0; Ins < 270; Ins++)
	{
		Read(Ins);
		long TimeLimit = CPU * gJobs * gMachine;
		//cout << TimeLimit * 1.0 / 1000 << endl;

		//Job_To_BestFactory_Bestposition_B(job, Seq);

		cout << Ins + 1 << ":  " << gJobs << "*" << gFactory << "*" << gMachine << ":";

		//cout << " IGVND1:  ";
		printf("\n");

		//cout << "a= " << aa << "   ";
		for (int i = 0; i < 5; i++)      
		{
			//srand(i + 100 + Ins);
			long  StartTime = GetTickCount();
			//SpanFactory_IGVND[Ins][i] = ES(TimeLimit, 3, 5);
			//SpanFactory_IGVND[Ins][i] = IG_NH_B(TimeLimit, 4, 0.0, 1);
			//SpanFactory_IGVND[Ins][i] = IG_VND2(TimeLimit, 3, 0.0);


			//SpanFactory_IGVND[Ins][i] = DABC_NEW(TimeLimit, 7, 5);
			//SpanFactory_IGVND[Ins][i] = DABC_Compared_B(TimeLimit, 18, 3);
			//SpanFactory_IGVND[Ins][i] = IGM_B(TimeLimit, 3, 10, 3);
			//SpanFactory_IGVND[Ins][i] = IG_Compared(TimeLimit, 5, 0.2);
			//SpanFactory_IGVND[Ins][i] = IG_ZCY(TimeLimit, 4, 0.0, 40);
			SpanFactory_IGVND[Ins][i] = IG_ZCY_WYT(TimeLimit, 4, 0.0, 40);

			long EndTime = GetTickCount();
			double Time = (EndTime - StartTime) * 1.0 / 1000;

			//SpanFactory[Ins][i] = IG_Compared(TimeLimit, Psize, Mcoefficien);
		 //SpanFactory[Ins][i] = HDDE(TimeLimit, Psize, Mcoefficien, Crossovercoefficient, Selectcoefficient, Iter);   //��ͬ���㷨
			ofile << SpanFactory_IGVND[Ins][i] << "\t";
			cout << SpanFactory_IGVND[Ins][i] << "\t";
			cout << Time << "s  ";
		}
		printf("\n");

		ofile << endl;
		cout << endl;

	}
	//printf("____________________________________________");
//}

	ofile.close();

	//vector<vector<int>> Energy_consumption(270);
	//for (int ins = 0; ins < 270; ins++)
	//	Energy_consumption[ins].resize(5, 0);

	//vector<vector<int>> Energy_consumption_1(270);
	//for (int ins = 0; ins < 270; ins++)
	//	Energy_consumption_1[ins].resize(5, 0);

	//vector<vector<int>> Energy_consumption_2(270);
	//for (int ins = 0; ins < 270; ins++)
	//	Energy_consumption_2[ins].resize(5, 0);

	//vector<vector<int>> Energy_consumption_3(270);
	//for (int ins = 0; ins < 270; ins++)
	//	Energy_consumption_3[ins].resize(5, 0);

	//vector<vector<int>> Energy_consumption_5(270);
	//for (int ins = 0; ins < 270; ins++)
	//	Energy_consumption_5[ins].resize(5, 0);

	//vector<vector<int>> Energy_consumption_6(270);
	//for (int ins = 0; ins < 270; ins++)
	//	Energy_consumption_6[ins].resize(5, 0);

	//char fileName1[30];
	//FILE* f1;
	//sprintf(fileName1, "GLG6_10.txt");
	//f1 = fopen(fileName1, "a+");


	//cout << "GLG6_" << CPU << endl;

	//for (int ins = 70; ins < 270; ins++)
	//{
	//	int min_GLG = INT_MAX;
	//	int min_GLG_1 = INT_MAX;
	//	int min_GLG_2 = INT_MAX;
	//	int min_NIG = INT_MAX;
	//	int min_DABC = INT_MAX;
	//	int min_IG = INT_MAX;
	//	int Min = INT_MAX;
	//	int Min_1 = INT_MAX;
	//	int t = 0;
	//	int tt = 0;

		//Read_E(ins);

	//	long TimeLimit = CPU * gJobs * gMachine;
	//	cout << gJobs << "*" << gMachine << "*" << gFactory << "\t";
	//	fprintf(f1, "%d*%d*%d", gJobs, gMachine, gFactory);
	//	fprintf(f1, ": ");
	//	//GLG
	//	fprintf(f1, "DABC_NEW:");
	//	for (int i = 0; i < 5; i++)
	//	{
	//		Energy_consumption[ins][i] = IG_VND1(TimeLimit, 3, 0.0);
	//		//Energy_consumption[ins][i] = DABC_NEW(TimeLimit, 7, 5);
	//		//Energy_consumption[ins][i] = GLG_6_R_2(TimeLimit, 1, 2, 3);
	//		//cout << Energy_consumption[ins][i]<<", ";
	//		//fprintf(f1, ",", Energy_consumption[ins][i]);
	//		if (Energy_consumption[ins][i] < min_GLG)
	//			min_GLG = Energy_consumption[ins][i];
	//	}
	//	if (min_GLG < Min)
	//	{
	//		Min = min_GLG;
	//		t = 1;
	//	}
	//	fprintf(f1, "%d,", min_GLG);
	//	cout << "DABC_NEW: " << min_GLG << ",";
	//	//cout << "GLG_R_2: " << min_GLG << ",";

	//	
	//	for (int i = 0; i < 5; i++)
	//	{
	//		Energy_consumption_1[ins][i] = GLG_6_R(TimeLimit, 1, 5);
	//		//cout << Energy_consumption[ins][i]<<", ";
	//		//fprintf(f1, ",", Energy_consumption[ins][i]);
	//		if (Energy_consumption_1[ins][i] < min_GLG_1)
	//			min_GLG_1 = Energy_consumption_1[ins][i];
	//	}
	//	if (min_GLG_1 < Min)
	//	{
	//		Min = min_GLG_1;
	//		t = 2;
	//	}
	//	if (min_GLG_1 < Min_1)
	//	{
	//		Min_1 = min_GLG_1;
	//		tt = 11;
	//	}
	//	fprintf(f1, "GLG_6_R:");
	//	fprintf(f1, "%d,", min_GLG_1);
	//	cout << "GLG_6_R:" << min_GLG_1 << ",";

	//	for (int i = 0; i < 5; i++)
	//	{
	//		Energy_consumption_2[ins][i] = IGM_BE(TimeLimit, 3, 10, 3);
	//		//Energy_consumption_2[ins][i] = GLG_6_R_2(TimeLimit, 1, 2, 3);
	//		//cout << Energy_consumption[ins][i]<<", ";
	//		//fprintf(f1, ",", Energy_consumption[ins][i]);
	//		if (Energy_consumption_2[ins][i] < min_GLG_2)
	//			min_GLG_2 = Energy_consumption_2[ins][i];
	//	}
	//	if (min_GLG_2 < Min)
	//	{
	//		Min = min_GLG_2;
	//		t = 3;
	//	}
	//	if (min_GLG_2 < Min_1)
	//	{
	//		Min_1 = min_GLG_2;
	//		tt = 22;
	//	}
	//	fprintf(f1, "IGR:");
	//	fprintf(f1, "%d,", min_GLG_2);
	//	cout << "IGR:" << min_GLG_2 << ",";

	//	for (int i = 0; i < 5; i++)
	//	{
	//		Energy_consumption_5[ins][i] = DABC_Compared_BE(TimeLimit, 18, 3);
	//		//Energy_consumption_5[ins][i] = GLG_6(TimeLimit, 1, 2, 3);
	//		//cout << Energy_consumption[ins][i]<<", ";
	//		//fprintf(f1, ",", Energy_consumption[ins][i]);
	//		if (Energy_consumption_5[ins][i] < min_DABC)
	//			min_DABC = Energy_consumption_5[ins][i];
	//	}
	//	if (min_DABC < Min)
	//	{
	//		Min = min_DABC;
	//		t = 4;
	//	}
	//	if (min_DABC < Min_1)
	//	{
	//		Min_1 = min_DABC;
	//		tt = 33;
	//	}
	//	fprintf(f1, "DABC:");
	//	fprintf(f1, "%d,", min_DABC);
	//	cout << "DABC:" << min_DABC << ",";
	//	//cout << "GLG_6:" << min_DABC << ",";

	//	for (int i = 0; i < 5; i++)
	//	{
	//		Energy_consumption_3[ins][i] = CRO_BE(TimeLimit, 150, 0.7, 10, 50);
	//		//cout << Energy_consumption[ins][i]<<", ";
	//		//fprintf(f1, ",", Energy_consumption[ins][i]);
	//		if (Energy_consumption_3[ins][i] < min_NIG)
	//			min_NIG = Energy_consumption_3[ins][i];
	//	}
	//	if (min_NIG < Min)
	//	{
	//		Min = min_NIG;
	//		t = 5;
	//	}
	//	if (min_NIG < Min_1)
	//	{
	//		Min_1 = min_NIG;
	//		tt = 44;
	//	}
	//	fprintf(f1, "CRO:");
	//	fprintf(f1, "%d,", min_NIG);
	//	fprintf(f1, "t = %d\n", t);
	//	cout << "CRO:" << min_NIG << ",";

	//	for (int i = 0; i < 5; i++)
	//	{
	//		Energy_consumption_6[ins][i] = IG_Compared(TimeLimit, 5, 0.2);
	//		//cout << Energy_consumption[ins][i]<<", ";
	//		//fprintf(f1, ",", Energy_consumption[ins][i]);
	//		if (Energy_consumption_6[ins][i] < min_IG)
	//			min_IG = Energy_consumption_6[ins][i];
	//	}
	//	if (min_IG < Min)
	//	{
	//		Min = min_IG;
	//		t = 6;
	//	}
	//	if (min_IG < Min_1)
	//	{
	//		Min_1 = min_IG;
	//		tt = 55;
	//	}
	//	
	//	fprintf(f1, "IG:");
	//	fprintf(f1, "%d,", min_IG);
	//	fprintf(f1, "t = %d\n", t);
	//	cout << "IG:" << min_IG << ",";

	//	cout << " , t = " << t << ", tt=" << tt << endl;




	//	//cout << endl;
	//}



	//fclose(f1);
	return 0;
}


int main()
{

	int CPU = 5;
	cout << "IGVND_" << CPU << endl;
	vector<vector<int>> SpanFactory_IGVND;
	SpanFactory_IGVND.resize(270);
	for (int ins = 0; ins < SpanFactory_IGVND.size(); ins++)
	{
		SpanFactory_IGVND[ins].resize(5, 0);
	}

	string FileDirectory = "Result\\";

	ofstream ofile_IG_ZCY;
	ofile_IG_ZCY.open(FileDirectory + "IG_ZCY_MODEL" + to_string(CPU) + ".txt"); //不同的算法
	
	//ofstream ofile_IG_ZCY_WYT;
	//ofile_IG_ZCY_WYT.open(FileDirectory + "IG_ZCY_WYT_" + to_string(CPU) + ".txt"); //不同的算法

		
	for (int Ins = 0; Ins < 270; Ins++)
	{
		Read(Ins);
		long TimeLimit = CPU * gJobs * gMachine;
		
		cout << Ins + 1 << ":  " << gJobs << "*" << gFactory << "*" << gMachine << ":";
		cout << endl;

		long StartTime;
		long EndTime;
		double Time;

		//int d = 2 + rand() % (6 - 2 + 1);//破坏阶段的d=最小值+随机（）
		//SpanFactory_IGVND[Ins][0] = IGZCY_WYT_Curve(TimeLimit, d, 0.0, 42, 1);
		//SpanFactory_IGVND[Ins][0] = IGM_B_Curve(TimeLimit, 3, 10, 3, 1);
		//SpanFactory_IGVND[Ins][0] = DABC_Curve(TimeLimit, 7, 5, 1);
	    //SpanFactory_IGVND[Ins][0] = ES_Curve(TimeLimit, 7, 5, 1);
		//SpanFactory_IGVND[Ins][0] = EA_Curve(TimeLimit, 2, 1);
		//SpanFactory_IGVND[Ins][0] = DDE_Curve(TimeLimit, 20, 0.0, 0.1, 0.0, 4000, 1);

		
		cout << " ";
		for (int i = 0; i < 5; i++) //每个测试用例执行5遍
		{
			//int d = 4 + rand() % (6 - 2 + 1) ;//破坏阶段的d=最小值+随机（）
			int d = 2 + rand() % (6 - 2 + 1);//破坏阶段的d=最小值+随机（）

			StartTime = GetTickCount();
			
			//SpanFactory_IGVND[Ins][i] = IG_ZCY_WYT(TimeLimit, d, 0.9, 42);
			SpanFactory_IGVND[Ins][i] = IG_ZCY(TimeLimit, d, 0.9, 42);
			//SpanFactory_IGVND[Ins][i] = ES(TimeLimit, 7, 5);
			//SpanFactory_IGVND[Ins][i] = NIG_Block(TimeLimit, 1, 5);
			//SpanFactory_IGVND[Ins][i] = EA(TimeLimit, 2);
			//SpanFactory_IGVND[Ins][i] = DDE(TimeLimit, 20, 0.0, 0.1 ,0.0, 4000);
			//SpanFactory_IGVND[Ins][i] = IGM_B(TimeLimit, 3, 10, 3);
			//SpanFactory_IGVND[Ins][i] = DABC_NEW(TimeLimit, 7, 5);
			EndTime = GetTickCount();
			Time = (EndTime - StartTime) * 1.0 / 1000;
			ofile_IG_ZCY << SpanFactory_IGVND[Ins][i] << "\t";
			cout << SpanFactory_IGVND[Ins][i] << " ";
			cout << fixed << setprecision(2) << Time << "s\t";
			
		}
		cout << endl;
		ofile_IG_ZCY << endl;
		
		//cout << " ";
		//for (int i = 0; i < 5; i++) //每个测试用例执行5遍
		//{			
		//	StartTime = GetTickCount();
		//	SpanFactory_IGVND[Ins][i] = IG_ZCY_WYT(TimeLimit, 4, 0.0, 40);
		//	EndTime = GetTickCount();
		//	Time = (EndTime - StartTime) * 1.0 / 1000;
		//	ofile_IG_ZCY_WYT << SpanFactory_IGVND[Ins][i] << "\t";
		//	cout << SpanFactory_IGVND[Ins][i] << " ";
		//	cout << fixed << setprecision(2) << Time << "s\t";
		//}
		//
		//ofile_IG_ZCY_WYT << endl;
		//cout << endl;
	}

	ofile_IG_ZCY.close();
	//ofile_IG_ZCY_WYT.close();
	
	return 0;
}
