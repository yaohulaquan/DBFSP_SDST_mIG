#pragma once
#include "FBTime.h"
#include "Rand.h"

typedef struct
{
	int dim;
	int value;
} Pair;

class PairGreater
{
public:
	bool operator ()(Pair a, Pair b)
	{
		return a.value > b.value;
	}
};

class PairLess
{
public:
	bool operator ()(Pair a, Pair b)
	{
		return a.value < b.value;
	}
};

//-------------end ----------------

int gJobs, gMachine, gFactory;
vector<vector<int>> pTime;
vector<vector<vector<int>>> pSetupTime;

//FBTime gFBTime(0, 0);
//FBTime gTempFBTime(0, 0);

//获取时间函数
long GetElapsedProcessTime()
{
	FILETIME createTime;
	FILETIME exitTime;
	FILETIME kernelTime;
	FILETIME userTime;

	if (GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime, &kernelTime, &userTime) != 0)
	{
		//  Returns total user time.
		SYSTEMTIME userSystemTime;
		if (FileTimeToSystemTime(&userTime, &userSystemTime) != -1)
			return (userSystemTime.wDay - 1) * 24 * 3600 * 1000
				+ userSystemTime.wHour * 3600 * 1000 +
				userSystemTime.wMinute * 60 * 1000 +
				userSystemTime.wSecond * 1000 +
				userSystemTime.wMilliseconds;
		else
			return 0;
	}
	else
		return 0;
}

vector<int> IdleTimeE;
vector<vector<int>> pTimeE;
vector<vector<vector<int>>> SetupTimeE;
vector<int> MinPTime;

void Read_E(int NO)
{
	string RunFileName = string("RunInstance\\") + string("D_PRO_SETUP_") + to_string(NO) + ".txt";

	ifstream ifile;
	ifile.open(RunFileName);
	ifile >> gJobs >> gMachine >> gFactory;
	//	cout << gJobs << gMachine << gFactory << endl;

	pTime.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
		pTime[j].resize(gMachine);

	pSetupTime.resize(gMachine);
	for (int m = 0; m < gMachine; m++)
	{
		pSetupTime[m].resize(gJobs);
		for (int j = 0; j < gJobs; j++)
			pSetupTime[m][j].resize(gJobs);
	}

	for (int j = 0; j < gJobs; j++)
	{
		for (int i = 0; i < gMachine; i++)
		{
			int value;
			ifile >> value;
			pTime[j][i] = value;
			//	cout << pTime[j][i] << "\t";
		}
		//	cout << endl;
	}
	//	cout << endl;
	for (int m = 0; m < gMachine; m++)
	{
		for (int j = 0; j < gJobs; j++)
		{
			for (int i = 0; i < gJobs; i++)
			{
				int value;
				ifile >> value;
				pSetupTime[m][j][i] = value;
				//cout << pSetupTime[m][j][i] << "\t";
			}
			//	cout << endl;
		}
		//	cout << endl;
	}
	ifile.close();

	//随机产生单位能耗值

	IdleTimeE.resize(gMachine, 0);


	pTimeE.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
		pTimeE[j].resize(gMachine);


	SetupTimeE.resize(gMachine);
	for (int i = 0; i < gMachine; i++)
	{
		SetupTimeE[i].resize(gJobs);
		for (int j = 0; j < gJobs; j++)
			SetupTimeE[i][j].resize(gJobs, 0);
	}

	// srand ((unsigned)time(NULL));
	//srand((int)time(0));

	for (int i = 0; i < gMachine; i++)
	{		
		IdleTimeE[i] = wyt_rand(1, 2);
	}

	for (int i = 0; i < gMachine; i++)
	{
		for (int j = 0; j < gJobs; j++)
		{
			for (int x = 0; x < gJobs; x++)
			{
				SetupTimeE[i][j][x] = wyt_rand(1, 3); //rand() % 3 + 1;
			}
		}
	}

	for (int i = 0; i < gJobs; i++)
	{
		for (int j = 0; j < gMachine; j++)
		{
			pTimeE[i][j] = wyt_rand(4, 6); //rand() % 3 + 4;
		}
	}
}

void Read(int NO)
{
	string RunFileName = string("RunInstance\\") + string("D_PRO_SETUP_") + to_string(NO) + ".txt";

	ifstream ifile;
	ifile.open(RunFileName);
	ifile >> gJobs >> gMachine >> gFactory;
	//	cout << gJobs << gMachine << gFactory << endl;

	//gFBTime = FBTime(gJobs, gMachine);
	//gTempFBTime = FBTime(gJobs, gMachine);

	pTime.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
		pTime[j].resize(gMachine);

	pSetupTime.resize(gMachine);
	for (int m = 0; m < gMachine; m++)
	{
		pSetupTime[m].resize(gJobs);
		for (int j = 0; j < gJobs; j++)
			pSetupTime[m][j].resize(gJobs);
	}

	for (int j = 0; j < gJobs; j++)
	{
		for (int i = 0; i < gMachine; i++)
		{
			int value;
			ifile >> value;
			pTime[j][i] = value;
		}
	}
	for (int m = 0; m < gMachine; m++)
	{
		for (int j = 0; j < gJobs; j++)
		{
			for (int i = 0; i < gJobs; i++)
			{
				int value;
				ifile >> value;
				pSetupTime[m][j][i] = value;
			}
		}
	}

	MinPTime.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
	{
		int TempminPTime = INT_MAX;
		for (int m = 0; m < gMachine; m++)
		{
			if (pTime[j][m] < TempminPTime)
			{
				TempminPTime = pTime[j][m];
			}
		}
		MinPTime[j] = TempminPTime;
	}

	ifile.close();
}

double GetTemperature(double Tem)
{
	double Temperature = 0;
	for (int j = 0; j < gJobs; j++)
	{
		for (int m = 0; m < gMachine; m++)
			Temperature += pTime[j][m];
	}
	Temperature /= gJobs * gMachine * 10;
	Temperature *= Tem;
	return Temperature;
}

//阻塞
int GetFEnergy_BLOCK(vector<int> Seq)
{
	vector<vector<int>> StartTime(Seq.size());
	for (int i = 0; i < Seq.size(); i++)
		StartTime[i].resize(gMachine, 0);
	vector<vector<int>> FinishTime(Seq.size());
	for (int i = 0; i < Seq.size(); i++)
		FinishTime[i].resize(gMachine, 0);

	int Span = 0, TotalEnergy = 0;
	int preJob;
	int TpTimeE = 0, TSetupTimeE = 0, TIdleTimeE = 0;
	//判断序列里是否有工件
	if (Seq.size() == 0)
		Span = 0;
	else
	{
		int Job = Seq[0]; //第一个工件
		StartTime[0][0] = pSetupTime[0][Job][Job]; //第一个工件在第一台机器上的开始时间
		FinishTime[0][0] = StartTime[0][0] + pTime[Job][0]; //第一个工件在第一台机器上的结束时间


		//StartTime[1][0] = StartTime[0][0] + pTime[0][Job] + pSetupTime[0][Job][NJob];
		//StartTime[0][1] = max(pSetupTime[1][Job][Job], FinishTime[0][0]);


		for (int j = 1; j < gMachine; j++)
		{
			//第1个工件在第2、3、4...台机器上的开始时间，比较 机器准备时间 和 第1个工件在上一台机器的完成时间
			StartTime[0][j] = max(pSetupTime[j][Job][Job], FinishTime[0][j - 1]);
			FinishTime[0][j] = StartTime[0][j] + pTime[Job][j]; //第1个工件在其余机器上的完工时间
		}
		int m;
		//非第1个工件
		for (int ii = 1; ii < Seq.size(); ii++)
		{
			Job = Seq[ii];
			int ProJob = Seq[ii - 1]; //前一个工件

			//StartTime[i][0] = max(FinishTime[ProJob][0], StartTime[ProJob][1]) + pSetupTime[0][ProJob][Job];

			//非第1个工件在第1台机器上的开始时间
			StartTime[ii][0] = StartTime[ii - 1][1] + pSetupTime[0][ProJob][Job];
			FinishTime[ii][0] = StartTime[ii][0] + pTime[Job][0];
			int c = 0;
			//非第1个工件在非第1台机器上的开始、结束时间
			for (m = 1; m < gMachine - 1; m++)
			{
				//开始时间=比较这个工件 在上一台机器的完成时间 和 上1个工件在下1台机器上的开始时间+当前工件的机器准备时间（上1个工件在下1台机器的开始时间=上1个工件在当前机器的完成时间finishtime[ii-1][m]+阻塞时间+当前机器准备时间
				StartTime[ii][m] = max(FinishTime[ii][m - 1], StartTime[ii - 1][m + 1] + pSetupTime[m][ProJob][Job]);
				FinishTime[ii][m] = StartTime[ii][m] + pTime[Job][m]; //结束时间=开始时间+加工时间
			}
			//最后1台机器上 不用考虑阻塞时间 工件在最后一台机器上加工完就离开
			StartTime[ii][m] = max(FinishTime[ii - 1][m] + pSetupTime[m][ProJob][Job], FinishTime[ii][m - 1]);
			FinishTime[ii][m] = StartTime[ii][m] + pTime[Job][m];
		}
		Span = FinishTime[Seq.size() - 1][gMachine - 1];

		//计算能耗


		for (int m = 1; m < gMachine - 1; m++)
		{
			Job = Seq[0];
			int n = pTime[Job][m];
			int d = 0;
			int b = pTimeE[Job][m];
			TpTimeE = n * b;

			//TpTimeE += pTime[Job][m] * pTimeE[Job][m];
			TSetupTimeE += pSetupTime[m][Job][Job] * SetupTimeE[m][Job][Job];
			int Tptime = 0, Tsetuptime = 0;
			Tptime += pTime[Job][m];
			Tsetuptime += pSetupTime[m][Job][Job];

			for (int i = 1; i < Seq.size(); i++)
			{
				Job = Seq[i];
				preJob = Seq[i - 1];
				TpTimeE += pTime[Job][m] * pTimeE[Job][m];
				TSetupTimeE += pSetupTime[m][preJob][Job] * SetupTimeE[m][preJob][Job];
				Tptime += pTime[Job][m];
				Tsetuptime += pSetupTime[m][preJob][Job];
			}
			TIdleTimeE += (FinishTime[Seq.size() - 1][m] - Tptime - Tsetuptime) * IdleTimeE[m];
			int a = 1;
		}
		TotalEnergy = TpTimeE + TSetupTimeE + TIdleTimeE;
	}


	return TotalEnergy;
}

//得到单工厂序列最大完工时间
int GetFspan(vector<int> Seq) //传一个参数
{
	int Span = 0;
	if (Seq.size() == 0)
		Span = 0;
	else
	{
		vector<int> mIdleTime(gMachine, 0);
		vector<vector<int>> jCTime(Seq.size());
		for (int j = 0; j < jCTime.size(); j++)
			//二维数组，行是第几个工件，列是第几台机器
			jCTime[j].resize(gMachine, 0);
		//序列第一个工件
		int Job = Seq[0];
		jCTime[0][0] = mIdleTime[0] + pSetupTime[0][Job][Job] + pTime[Job][0];
		for (int i = 1; i < gMachine; i++)
			//比较空闲时间+准备时间和第一个工件在上一台机器上的完成时间
			jCTime[0][i] = max(mIdleTime[i] + pSetupTime[i][Job][Job], jCTime[0][i - 1]) + pTime[Job][i];
		//机器开始空闲的时间
		mIdleTime = jCTime[0];
		//其余工件
		for (int j = 1; j < Seq.size(); j++)
		{
			//定义前一个工件
			int PreJob = Seq[j - 1];
			//定义当前工件
			int Job = Seq[j];
			jCTime[j][0] = mIdleTime[0] + pSetupTime[0][PreJob][Job] + pTime[Job][0];
			for (int i = 1; i < gMachine; i++)
				jCTime[j][i] = max(mIdleTime[i] + pSetupTime[i][PreJob][Job], jCTime[j][i - 1]) + pTime[Job][i];
			mIdleTime = jCTime[j];
		}
		//得到最后一个工件在最后一台机器上的完工时间
		Span = jCTime[Seq.size() - 1][gMachine - 1];
	}
	return Span;
}

int GetFspan(vector<int> Seq, vector<vector<int>>& jCTime) //传两个参数
{
	vector<int> mIdleTime(gMachine, 0);
	jCTime.clear();
	jCTime.resize(Seq.size());
	for (int j = 0; j < jCTime.size(); j++)
		jCTime[j].resize(gMachine, 0);

	int Job = Seq[0];
	jCTime[0][0] = mIdleTime[0] + pSetupTime[0][Job][Job] + pTime[Job][0];
	for (int i = 1; i < gMachine; i++)
		jCTime[0][i] = max(mIdleTime[i] + pSetupTime[i][Job][Job], jCTime[0][i - 1]) + pTime[Job][i];
	//jCTime[0]所有工件加工完的完工时间
	mIdleTime = jCTime[0];

	for (int j = 1; j < Seq.size(); j++)
	{
		int PreJob = Seq[j - 1];
		int Job = Seq[j];
		//工件j在第一台机器上的完工时间
		jCTime[j][0] = mIdleTime[0] + pSetupTime[0][PreJob][Job] + pTime[Job][0];
		for (int i = 1; i < gMachine; i++)
			//工件j在其余机器上（除第一台）上的完工时间
			jCTime[j][i] = max(mIdleTime[i] + pSetupTime[i][PreJob][Job], jCTime[j][i - 1]) + pTime[Job][i];
		mIdleTime = jCTime[j];
	}
	//得到最后一个工件在最后一台机器上的完工时间
	return jCTime[Seq.size() - 1][gMachine - 1];
}

//得到多工厂（关键工厂）最后的最大完工时间
int GetFspan(vector<vector<int>> Sol)
{
	int Span = 0;
	for (int f = 0; f < Sol.size(); f++)
	{
		//存储每个工厂的完工时间
		int TSpan = GetFspan(Sol[f]);
		//比较每个工厂的完工时间，得到最终所有工厂的最大完工时间
		if (TSpan > Span)
			Span = TSpan;
	}
	return Span;
}

//阻塞
int GetFspan_BLOCK(vector<int> Seq)
{
	vector<vector<int>> StartTime(Seq.size());
	for (int i = 0; i < Seq.size(); i++)
		StartTime[i].resize(gMachine, 0);
	vector<vector<int>> FinishTime(Seq.size());
	for (int i = 0; i < Seq.size(); i++)
		FinishTime[i].resize(gMachine, 0);

	int Span = 0, TotalEnergy = 0;
	int preJob;
	int TpTimeE = 0, TSetupTimeE = 0, TIdleTimeE = 0;
	//判断序列里是否有工件
	if (Seq.size() == 0)
		Span = 0;
	else
	{
		int Job = Seq[0]; //第一个工件
		StartTime[0][0] = pSetupTime[0][Job][Job]; //第一个工件在第一台机器上的开始时间
		FinishTime[0][0] = StartTime[0][0] + pTime[Job][0]; //第一个工件在第一台机器上的结束时间


		//StartTime[1][0] = StartTime[0][0] + pTime[0][Job] + pSetupTime[0][Job][NJob];
		//StartTime[0][1] = max(pSetupTime[1][Job][Job], FinishTime[0][0]);


		for (int j = 1; j < gMachine; j++)
		{
			//第1个工件在第2、3、4...台机器上的开始时间，比较 机器准备时间 和 第1个工件在上一台机器的完成时间
			StartTime[0][j] = max(pSetupTime[j][Job][Job], FinishTime[0][j - 1]);
			FinishTime[0][j] = StartTime[0][j] + pTime[Job][j]; //第1个工件在其余机器上的完工时间
		}
		int m;
		//非第1个工件
		for (int ii = 1; ii < Seq.size(); ii++)
		{
			Job = Seq[ii];
			int ProJob = Seq[ii - 1]; //前一个工件

			//StartTime[i][0] = max(FinishTime[ProJob][0], StartTime[ProJob][1]) + pSetupTime[0][ProJob][Job];

			//非第1个工件在第1台机器上的开始时间
			StartTime[ii][0] = StartTime[ii - 1][1] + pSetupTime[0][ProJob][Job];
			FinishTime[ii][0] = StartTime[ii][0] + pTime[Job][0];
			int c = 0;
			//非第1个工件在非第1台机器上的开始、结束时间
			for (m = 1; m < gMachine - 1; m++)
			{
				//开始时间=比较这个工件 在上一台机器的完成时间 和 上1个工件在下1台机器上的开始时间+当前工件的机器准备时间（上1个工件在下1台机器的开始时间=上1个工件在当前机器的完成时间finishtime[ii-1][m]+阻塞时间+当前机器准备时间
				StartTime[ii][m] = max(FinishTime[ii][m - 1], StartTime[ii - 1][m + 1] + pSetupTime[m][ProJob][Job]);
				FinishTime[ii][m] = StartTime[ii][m] + pTime[Job][m]; //结束时间=开始时间+加工时间
			}
			//最后1台机器上 不用考虑阻塞时间 工件在最后一台机器上加工完就离开
			StartTime[ii][m] = max(FinishTime[ii - 1][m] + pSetupTime[m][ProJob][Job], FinishTime[ii][m - 1]);
			FinishTime[ii][m] = StartTime[ii][m] + pTime[Job][m];
		}
		Span = FinishTime[Seq.size() - 1][gMachine - 1];
	}
	return Span;
}

int GetFSpan_BLOCK_BTW_FBTime_WYT(const vector<int>& Seq, FBTime& fbTime)
{
	if (Seq.empty())
	{
		return 0;
	}

	int preJob = -1;
	for (auto job : Seq)
	{
		if (preJob == -1)//第一个工件
		{
			fbTime.forwardStartTime[job][0] = pSetupTime[0][job][job];
			fbTime.forwardFinishTime[job][0] = fbTime.forwardStartTime[job][0] + pTime[job][0];
			fbTime.forwardDepartureTime[job][0] = fbTime.forwardFinishTime[job][0];
			for (int m = 1; m < gMachine; m++)
			{
				fbTime.forwardStartTime[job][m] = max(pSetupTime[m][job][job],
				                                      fbTime.forwardDepartureTime[job][m - 1]);
				fbTime.forwardFinishTime[job][m] = fbTime.forwardStartTime[job][m] + pTime[job][m];
				fbTime.forwardDepartureTime[job][m] = fbTime.forwardFinishTime[job][m];
				fbTime.forwardDepartureTime[job][m - 1] = fbTime.forwardStartTime[job][m];
			}
		}
		else//非第一个工件
		{
			fbTime.forwardStartTime[job][0] = pSetupTime[0][preJob][job] + fbTime.forwardDepartureTime[preJob][0];
			fbTime.forwardFinishTime[job][0] = fbTime.forwardStartTime[job][0] + pTime[job][0];
			fbTime.forwardDepartureTime[job][0] = fbTime.forwardFinishTime[job][0];

			for (int m = 1; m < gMachine; m++)
			{
				fbTime.forwardStartTime[job][m] = max(
					pSetupTime[m][preJob][job] + fbTime.forwardDepartureTime[preJob][m],
					fbTime.forwardDepartureTime[job][m - 1]);
				fbTime.forwardFinishTime[job][m] = fbTime.forwardStartTime[job][m] + pTime[job][m];
				fbTime.forwardDepartureTime[job][m] = fbTime.forwardFinishTime[job][m];
				fbTime.forwardDepartureTime[job][m - 1] = fbTime.forwardStartTime[job][m];
			}
		}
		preJob = job;
	}

	int nextJob = -1;
	for (auto jobIt = Seq.rbegin(); jobIt != Seq.rend(); ++jobIt)
	{
		int job = *jobIt;
		if (nextJob == -1)
		{
			fbTime.backwardStartTime[job][gMachine - 1] = 0;
			fbTime.backwardFinishTime[job][gMachine - 1] = fbTime.backwardStartTime[job][gMachine -	1] + pTime[job][gMachine - 1];
			fbTime.backwardDepartureTime[job][gMachine - 1] = fbTime.backwardFinishTime[job][
				gMachine - 1];

			for (int m = gMachine - 2; m >= 0; m--)
			{
				fbTime.backwardStartTime[job][m] = fbTime.backwardDepartureTime[job][m + 1];
				fbTime.backwardFinishTime[job][m] = fbTime.backwardStartTime[job][m] + pTime[job][m];
				fbTime.backwardDepartureTime[job][m] = fbTime.backwardFinishTime[job][m];
			}
		}
		else
		{
			fbTime.backwardStartTime[job][gMachine - 1] = pSetupTime[gMachine - 1][job][nextJob] + fbTime.backwardDepartureTime[nextJob][gMachine - 1];
			fbTime.backwardFinishTime[job][gMachine - 1] = fbTime.backwardStartTime[job][gMachine - 1] + pTime[
				job][gMachine - 1];
			fbTime.backwardDepartureTime[job][gMachine - 1] = fbTime.backwardFinishTime[job][gMachine - 1];
			for (int m = gMachine - 2; m >= 0; m--)
			{
				fbTime.backwardStartTime[job][m] = max(
					pSetupTime[m][job][nextJob] + fbTime.backwardDepartureTime[nextJob][m],
					fbTime.backwardDepartureTime[job][m + 1]);
				fbTime.backwardFinishTime[job][m] = fbTime.backwardStartTime[job][m] + pTime[job][m];
				fbTime.backwardDepartureTime[job][m] = fbTime.backwardFinishTime[job][m];
				fbTime.backwardDepartureTime[job][m + 1] = fbTime.backwardStartTime[job][m];
			}
		}
		nextJob = job;
	}

	int Span = fbTime.forwardFinishTime[Seq[Seq.size() - 1]][gMachine - 1];
	return Span;
}

int RefreshFBTime_InFactory_WYT(const vector<int>& SeqInFac, FBTime& fbTime, int ForwardPos, int BackwardPos)
{
	if (SeqInFac.empty())
	{
		return 0;
	}
	if (ForwardPos <= SeqInFac.size() - 1)
	{
		int preJob = -1;
		if (ForwardPos == 0)
		{
			preJob = -1;
		}
		else
		{
			preJob = SeqInFac[ForwardPos - 1];
		}
		for (int jobPosition = ForwardPos; jobPosition < SeqInFac.size(); jobPosition++)
		{
			int job = SeqInFac[jobPosition];
			if (preJob == -1) //第一个工件
			{
				fbTime.forwardStartTime[job][0] = pSetupTime[0][job][job];
				fbTime.forwardFinishTime[job][0] = fbTime.forwardStartTime[job][0] + pTime[job][0];
				fbTime.forwardDepartureTime[job][0] = fbTime.forwardFinishTime[job][0];
				for (int m = 1; m < gMachine; m++)
				{
					fbTime.forwardStartTime[job][m] = max(pSetupTime[m][job][job],
					                                      fbTime.forwardDepartureTime[job][m - 1]);
					fbTime.forwardFinishTime[job][m] = fbTime.forwardStartTime[job][m] + pTime[job][m];
					fbTime.forwardDepartureTime[job][m] = fbTime.forwardFinishTime[job][m];
					fbTime.forwardDepartureTime[job][m - 1] = fbTime.forwardStartTime[job][m];
				}
			}
			else //非第一个工件
			{
				fbTime.forwardStartTime[job][0] = pSetupTime[0][preJob][job] + fbTime.
					forwardDepartureTime[preJob][
						0];
				fbTime.forwardFinishTime[job][0] = fbTime.forwardStartTime[job][0] + pTime[job][0];
				fbTime.forwardDepartureTime[job][0] = fbTime.forwardFinishTime[job][0];

				for (int m = 1; m < gMachine; m++)
				{
					fbTime.forwardStartTime[job][m] = max(
						pSetupTime[m][preJob][job] + fbTime.forwardDepartureTime[preJob][m],
						fbTime.forwardDepartureTime[job][m - 1]);
					fbTime.forwardFinishTime[job][m] = fbTime.forwardStartTime[job][m] + pTime[job][m];
					fbTime.forwardDepartureTime[job][m] = fbTime.forwardFinishTime[job][m];
					fbTime.forwardDepartureTime[job][m - 1] = fbTime.forwardStartTime[job][m];
				}
			}
			preJob = job;
		}
	}

	if (BackwardPos >= 0)
	{
		int nextJob;
		if (BackwardPos == SeqInFac.size() - 1) 
		{
			nextJob = -1;
		}
		else
		{
			nextJob = SeqInFac[BackwardPos + 1];
		}
		for (int jobPosition = BackwardPos; jobPosition >= 0; jobPosition--)
		{
			int job = SeqInFac[jobPosition];
			if (nextJob == -1)
			{
				fbTime.backwardStartTime[job][gMachine - 1] = 0;
				fbTime.backwardFinishTime[job][gMachine - 1] = fbTime.backwardStartTime[job][gMachine - 1] + pTime[job][gMachine - 1];
					fbTime.backwardDepartureTime[job][gMachine - 1] = fbTime.backwardFinishTime[job][
						gMachine - 1];

					for (int m = gMachine - 2; m >= 0; m--)
					{
						fbTime.backwardStartTime[job][m] = fbTime.backwardDepartureTime[job][m + 1];
						fbTime.backwardFinishTime[job][m] = fbTime.backwardStartTime[job][m] + pTime[job][
							m];
						fbTime.backwardDepartureTime[job][m] = fbTime.backwardFinishTime[job][m];
					}
			}
			else
			{
				fbTime.backwardStartTime[job][gMachine - 1] = pSetupTime[gMachine - 1][job][nextJob] +
					fbTime.
					backwardDepartureTime[nextJob][gMachine - 1];
				fbTime.backwardFinishTime[job][gMachine - 1] = fbTime.backwardStartTime[job][gMachine -
					1] + pTime[
						job][gMachine - 1];
						fbTime.backwardDepartureTime[job][gMachine - 1] = fbTime.backwardFinishTime[job][
							gMachine - 1];
						for (int m = gMachine - 2; m >= 0; m--)
						{
							fbTime.backwardStartTime[job][m] = max(
								pSetupTime[m][job][nextJob] + fbTime.backwardDepartureTime[nextJob][m],
								fbTime.backwardDepartureTime[job][m + 1]);
							fbTime.backwardFinishTime[job][m] = fbTime.backwardStartTime[job][m] + pTime[job][
								m];
							fbTime.backwardDepartureTime[job][m] = fbTime.backwardFinishTime[job][m];
							fbTime.backwardDepartureTime[job][m + 1] = fbTime.backwardStartTime[job][m];
						}
			}
			nextJob = job;
		}
	}
	/*
	int lastJob1 = *SeqInFac.rbegin();
	int span1 = fbTime.forwardFinishTime[lastJob1][gMachine - 1];


	int firstJob = *SeqInFac.begin();
	
	int span2 = INT_MIN;
	for (int m =0; m < gMachine; ++m)
	{
		span2 = max(span2, fbTime.backwardDepartureTime[firstJob][m] + pSetupTime[m][firstJob][firstJob]);
	}
	
	int span3 = GetFspan_BLOCK(SeqInFac);

	FBTime fb_time(gJobs, gMachine);
	int span4 = GetFSpan_BLOCK_BTW_FBTime_WYT(SeqInFac, fb_time);

	int span5 = INT_MIN;
	for (int m = 0; m < gMachine; ++m)
	{
		span5 = max(span5, fb_time.backwardDepartureTime[firstJob][m] + pSetupTime[m][firstJob][firstJob]);
	}

	assert(span1 == span3);
	assert(span1 == span2);
	*/
	int lastJob = *SeqInFac.rbegin();
	return fbTime.forwardFinishTime[lastJob][gMachine - 1];
}

int GetFSpan_BLOCK_After_Switch_One_Job_WYT(const vector<int>& SeqInFac, int Pos, int Job,
	const FBTime& fbTime)
{
	std::vector<int> srartTimeOfInsertJob(gMachine, 0);
	std::vector<int> finishTimeOfInsertJob(gMachine, 0);
	std::vector<int> departureTimeOfInsertJob(gMachine, 0);

	auto calculateTimeOfJob = [&](int pos)
	{
		if (pos == 0)
		{
			srartTimeOfInsertJob[0] = pSetupTime[0][Job][Job];
			finishTimeOfInsertJob[0] = srartTimeOfInsertJob[0] + pTime[Job][0];
			departureTimeOfInsertJob[0] = finishTimeOfInsertJob[0];
			for (int m = 1; m < gMachine; m++)
			{
				srartTimeOfInsertJob[m] = max(pSetupTime[m][Job][Job], departureTimeOfInsertJob[m - 1]);
				finishTimeOfInsertJob[m] = srartTimeOfInsertJob[m] + pTime[Job][m];
				departureTimeOfInsertJob[m] = finishTimeOfInsertJob[m];
				departureTimeOfInsertJob[m - 1] = srartTimeOfInsertJob[m];
			}
		}
		else
		{
			int PreJob = SeqInFac[pos - 1];
			srartTimeOfInsertJob[0] = fbTime.forwardDepartureTime[PreJob][0] + pSetupTime[0][PreJob][Job];
			finishTimeOfInsertJob[0] = srartTimeOfInsertJob[0] + pTime[Job][0];
			departureTimeOfInsertJob[0] = finishTimeOfInsertJob[0];

			for (int m = 1; m < gMachine; m++)
			{
				srartTimeOfInsertJob[m] =
					max(departureTimeOfInsertJob[m - 1],
						fbTime.forwardDepartureTime[PreJob][m] + pSetupTime[m][PreJob][Job]);
				finishTimeOfInsertJob[m] = srartTimeOfInsertJob[m] + pTime[Job][m];
				departureTimeOfInsertJob[m] = finishTimeOfInsertJob[m];
				departureTimeOfInsertJob[m - 1] = srartTimeOfInsertJob[m];
			}
		}
	};
	calculateTimeOfJob(Pos);

	int span = 0;
	if (Pos == SeqInFac.size() - 1)
	{
		span = departureTimeOfInsertJob[gMachine - 1];
	}
	else
	{
		int NextJob = SeqInFac[Pos + 1];
		span = 0;
		for (int m = 0; m < gMachine; m++)
		{
			span = max(span,
				departureTimeOfInsertJob[m] + pSetupTime[m][Job][NextJob]
				+ fbTime.backwardDepartureTime[NextJob][m]);
		}
	}	
	return span;
}


int GetFSpan_BLOCK_After_Swap_Two_Job_WYT(const vector<int>& SeqInFac, int ForwardPos, int BackwardPos,	const FBTime& fbTime)
{
	
	int index = 0;

	std::vector<vector<int>> srartTime(BackwardPos - ForwardPos +1, vector<int>(gMachine, 0));
	std::vector<vector<int>> finishTime(BackwardPos - ForwardPos + 1, vector<int>(gMachine, 0));
	std::vector<vector<int>> departureTime(BackwardPos - ForwardPos + 1, vector<int>(gMachine, 0));

	int preJob = -1;
	if (ForwardPos == 0)
	{
		preJob = -1;
	}
	else
	{
		preJob = SeqInFac[ForwardPos - 1];
	}

	int curJob = SeqInFac[BackwardPos];
	if (preJob == -1)
	{
		srartTime[index][0] = pSetupTime[0][curJob][curJob];
		finishTime[index][0] = srartTime[index][0] + pTime[curJob][0];
		departureTime[index][0] = finishTime[index][0];
		for (int m = 1; m < gMachine; m++)
		{
			srartTime[index][m] = max(pSetupTime[m][curJob][curJob],departureTime[index][m - 1]);
			finishTime[index][m] = srartTime[index][m] + pTime[curJob][m];
			departureTime[index][m] = finishTime[index][m];
			departureTime[index][m - 1] = srartTime[index][m];
		}
	}
	else
	{
		srartTime[index][0] = pSetupTime[0][preJob][curJob] + fbTime.forwardDepartureTime[preJob][0];
		finishTime[index][0] = srartTime[index][0] + pTime[curJob][0];
		departureTime[index][0] = finishTime[index][0];

		for (int m = 1; m < gMachine; m++)
		{
			srartTime[index][m] = max(pSetupTime[m][preJob][curJob] + fbTime.forwardDepartureTime[preJob][m], departureTime[index][m - 1]);
			finishTime[index][m] = srartTime[index][m] + pTime[curJob][m];
			departureTime[index][m] = finishTime[index][m];
			departureTime[index][m - 1] = srartTime[index][m];
		}
	}

	++index;
	preJob = curJob;
	for (int jobPosition = ForwardPos+1; jobPosition <= BackwardPos; jobPosition++)
	{
		if(jobPosition == BackwardPos)
		{
			curJob = SeqInFac[ForwardPos];
		}
		else
		{
			curJob = SeqInFac[jobPosition];
		}	
		
		srartTime[index][0] = pSetupTime[0][preJob][curJob] + departureTime[index-1][0];
		finishTime[index][0] = srartTime[index][0] + pTime[curJob][0];
		departureTime[index][0] = finishTime[index][0];

		for (int m = 1; m < gMachine; m++)
		{
			srartTime[index][m] = max(pSetupTime[m][preJob][curJob] + departureTime[index - 1][m], departureTime[index][m - 1]);
			finishTime[index][m] = srartTime[index][m] + pTime[curJob][m];
			departureTime[index][m] = finishTime[index][m];
			departureTime[index][m - 1] = srartTime[index][m];
		}

		preJob = curJob;
		++index;
	}

	
	int span = 0;
	if (BackwardPos == SeqInFac.size() - 1)
	{
		span = departureTime[BackwardPos-ForwardPos][gMachine - 1];
	}
	else
	{
		curJob = SeqInFac[ForwardPos];
		int NextJob = SeqInFac[BackwardPos + 1];
		for (int m = 0; m < gMachine; m++)
		{
			span = max(span,
				departureTime[BackwardPos - ForwardPos][m] + pSetupTime[m][curJob][NextJob]
				+ fbTime.backwardDepartureTime[NextJob][m]);
		}
	}
	return span;
}

int GetFspan_Block(vector<vector<int>>& Sol)
{
	int Span = 0;
	for (int f = 0; f < Sol.size(); f++)
	{
		//存储每个工厂的完工时间
		int TSpan = GetFspan_BLOCK(Sol[f]);
		//比较每个工厂的完工时间，得到最终所有工厂的最大完工时间
		if (TSpan > Span)
			Span = TSpan;
	}
	return Span;
}

int GetFspan_BE(vector<vector<int>> Sol)
{
	int Span = 0;
	for (int f = 0; f < Sol.size(); f++)
	{
		int TSpan = GetFEnergy_BLOCK(Sol[f]);
		if (TSpan > Span)
			Span = TSpan;
	}
	return Span;
}


//在一个工厂中找到最好位置
int FindBestInsertionPositon_B(int& BestPos, int Job, vector<int>& Seq)
{
	int minTSpan = INT_MAX;
	/*
	vector<vector<int>>Fij;
	Fij.resize(Seq.size() + 1);
	for (int i = 0; i < Seq.size() + 1; i++)
		Fij[i].resize(gMachine, 0);
	 */
	vector<int> NewSeq(Seq.size() + 1, 0);

	for (int Pos = 0; Pos <= Seq.size(); Pos++) //5个工件6个位置
	{
		int TSpan = 0;
		if (Pos == Seq.size())
		{
			/*
			int PreJob = Seq[Pos - 1];
			Fij[Pos][0] = Eij[Pos - 1][0] + pSetupTime[0][PreJob][Job] + pTime[Job][0];
			for (int m = 1; m < gMachine; m++)
				Fij[Pos][m] = max(Eij[Pos - 1][m] + pSetupTime[m][PreJob][Job], Fij[Pos][m - 1]) + pTime[Job][m];
			*/
			for (int i = 0; i < Seq.size(); i++)
				NewSeq[i] = Seq[i];

			NewSeq[Seq.size()] = Job;

			TSpan = GetFspan_BLOCK(NewSeq);
		}
		else if (Pos == 0)
		{
			NewSeq[0] = Job;

			for (int i = 1; i < Seq.size() + 1; i++)
				NewSeq[i] = Seq[i - 1];

			TSpan = GetFspan_BLOCK(NewSeq);
		}
		else
		{
			for (int i = 0; i < Pos; i++)
				NewSeq[i] = Seq[i];

			NewSeq[Pos] = Job;

			for (int j = Pos + 1; j < Seq.size() + 1; j++)
				NewSeq[j] = Seq[j - 1];

			TSpan = GetFspan_BLOCK(NewSeq);
		}

		if (TSpan < minTSpan)
		{
			minTSpan = TSpan;
			BestPos = Pos;
		}
	}
	return minTSpan;
}

int FindBestInsertionPositon_B_WYT(int& bestPos, int job, const vector<int>& seq,
                                   const FBTime& fbTime)
{
	std::vector<int> srartTimeOfInsertJob(gMachine, 0);
	std::vector<int> finishTimeOfInsertJob(gMachine, 0);
	std::vector<int> departureTimeOfInsertJob(gMachine, 0);

	auto calculateTimeOfJob = [&](int pos)
	{
		if (pos == 0)
		{
			srartTimeOfInsertJob[0] = pSetupTime[0][job][job];
			finishTimeOfInsertJob[0] = srartTimeOfInsertJob[0] + pTime[job][0];
			departureTimeOfInsertJob[0] = finishTimeOfInsertJob[0];
			for (int m = 1; m < gMachine; m++)
			{
				srartTimeOfInsertJob[m] = max(pSetupTime[m][job][job], departureTimeOfInsertJob[m - 1]);
				finishTimeOfInsertJob[m] = srartTimeOfInsertJob[m] + pTime[job][m];
				departureTimeOfInsertJob[m] = finishTimeOfInsertJob[m];
				departureTimeOfInsertJob[m - 1] = srartTimeOfInsertJob[m];
			}
		}
		else
		{
			int PreJob = seq[pos - 1];
			srartTimeOfInsertJob[0] = fbTime.forwardDepartureTime[PreJob][0] + pSetupTime[0][PreJob][job];
			finishTimeOfInsertJob[0] = srartTimeOfInsertJob[0] + pTime[job][0];
			departureTimeOfInsertJob[0] = finishTimeOfInsertJob[0];

			for (int m = 1; m < gMachine; m++)
			{
				srartTimeOfInsertJob[m] =
					max(departureTimeOfInsertJob[m - 1],
					    fbTime.forwardDepartureTime[PreJob][m] + pSetupTime[m][PreJob][job]);
				finishTimeOfInsertJob[m] = srartTimeOfInsertJob[m] + pTime[job][m];
				departureTimeOfInsertJob[m] = finishTimeOfInsertJob[m];
				departureTimeOfInsertJob[m - 1] = srartTimeOfInsertJob[m];
			}
		}
	};
	int bestSpan = INT32_MAX;
	if (seq.empty())
	{
		calculateTimeOfJob(0);
		bestSpan = departureTimeOfInsertJob[gMachine - 1];
		bestPos = 0;
	}
	else
	{
		for (int pos = 0; pos <= seq.size(); ++pos)
		{
			int spanAfterInsert = 0;
			calculateTimeOfJob(pos);
			if (pos == seq.size())
			{
				spanAfterInsert = departureTimeOfInsertJob[gMachine - 1];
			}
			else
			{
				int NextJob = seq[pos];
				for (int m = 0; m < gMachine; m++)
				{
					spanAfterInsert = max(spanAfterInsert,
					                      departureTimeOfInsertJob[m] + pSetupTime[m][job][NextJob]
					                      + fbTime.backwardDepartureTime[NextJob][m]);
				}
			}

			if (bestSpan > spanAfterInsert)
			{
				bestSpan = spanAfterInsert;
				bestPos = pos;
			}
		}
	}
	return bestSpan;
}

//在所有工厂中找到最好位置插入工件
int Job_To_BestFactory_Bestposition_B(int Job, vector<vector<int>>& Sol)
{
	//先将每个工厂的makespan都初始化为0
	vector<int> FactorySpan;
	FactorySpan.resize(Sol.size(), 0); //

	for (int f = 0; f < Sol.size(); f++) //
		FactorySpan[f] = GetFspan_BLOCK(Sol[f]); ////用GetFEnergy得到每个工厂的完工时间赋给FactorySpan


	vector<int> minPTime;
	minPTime.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
	{
		int TempminPTime = INT_MAX;
		for (int m = 0; m < gMachine; m++)
		{
			if (pTime[j][m] < TempminPTime)
				TempminPTime = pTime[j][m];
		}
		minPTime[j] = TempminPTime;
	}

	//Test the job at all the factories, and select the best position
	int SelFac = 0, minTSpan = INT_MAX, BestPos = -1;
	for (int fac = 0; fac < gFactory; fac++)
	{
		if (Sol[fac].size() == 0) //工厂无工件
		{
			for (int m = 0; m < gMachine; m++)
				minTSpan = pSetupTime[m][Job][Job] + pTime[Job][m];
			BestPos = 0;
			SelFac = fac;
			break;
		}
		if (!(FactorySpan[fac] + minPTime[Job] < minTSpan)) //minPTime[Job]为工件Job的最小处理时间
			continue;

		int TempSpan = 0, TempPos = -1; //////

		TempSpan = FindBestInsertionPositon_B(TempPos, Job, Sol[fac]);
		if (TempSpan < minTSpan)
		{
			minTSpan = TempSpan;
			BestPos = TempPos;
			SelFac = fac;
		}
	}

	//将工件插入最好的位置
	Sol[SelFac].insert(Sol[SelFac].begin() + BestPos, Job);
	FactorySpan[SelFac] = minTSpan;

	return *max_element(FactorySpan.begin(), FactorySpan.end());
}

int Job_To_BestFactory_Bestposition_B(int Job, vector<vector<int>>& Sol, int& SelFac, int& BestPos)
{
	//先将每个工厂的makespan都初始化为0
	vector<int> FactorySpan;
	FactorySpan.resize(Sol.size(), 0); //

	for (int f = 0; f < Sol.size(); f++) //
		FactorySpan[f] = GetFspan_BLOCK(Sol[f]); //

	vector<int> minPTime;
	minPTime.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
	{
		int TempminPTime = INT_MAX;
		for (int m = 0; m < gMachine; m++)
		{
			if (pTime[j][m] < TempminPTime)
				TempminPTime = pTime[j][m];
		}
		minPTime[j] = TempminPTime;
	}

	//Test the job at all the factories, and select the best position
	int minTSpan = INT_MAX;
	for (int fac = 0; fac < gFactory; fac++)
	{
		if (Sol[fac].size() == 0)
		{
			for (int m = 0; m < gMachine; m++)
				minTSpan = pSetupTime[m][Job][Job] + pTime[Job][m];
			BestPos = 0;
			SelFac = fac;
			break;
		}
		if (!(FactorySpan[fac] + minPTime[Job] < minTSpan)) //minPTime[Job]为工件Job的最小处理时间
			continue;


		int TempSpan = 0, TempPos = -1; //////
		TempSpan = FindBestInsertionPositon_B(TempPos, Job, Sol[fac]);
		if (TempSpan < minTSpan)
		{
			minTSpan = TempSpan;
			BestPos = TempPos;
			SelFac = fac;
		}
	}

	//将工件插入最好的位置
	Sol[SelFac].insert(Sol[SelFac].begin() + BestPos, Job);
	FactorySpan[SelFac] = minTSpan;
	return *max_element(FactorySpan.begin(), FactorySpan.end());
}


int Job_To_BestFactory_Bestposition_B_ZCY(int Job, vector<vector<int>>& Sol, int& SelFac, int& BestPos, vector<int>& FactorySpan)
{
	
	vector<int> minPTime;
	minPTime.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
	{
		int TempminPTime = INT_MAX;
		for (int m = 0; m < gMachine; m++)
		{
			if (pTime[j][m] < TempminPTime)
				TempminPTime = pTime[j][m];
		}
		minPTime[j] = TempminPTime;
	}

	//Test the job at all the factories, and select the best position
	int minTSpan = INT_MAX;
	for (int fac = 0; fac < gFactory; fac++)
	{
		if (Sol[fac].size() == 0)
		{
			for (int m = 0; m < gMachine; m++)
				minTSpan = pSetupTime[m][Job][Job] + pTime[Job][m];
			BestPos = 0;
			SelFac = fac;
			break;
		}
		if (!(FactorySpan[fac] + minPTime[Job] < minTSpan)) //minPTime[Job]为工件Job的最小处理时间
			continue;


		int TempSpan = 0, TempPos = -1; //////
		TempSpan = FindBestInsertionPositon_B(TempPos, Job, Sol[fac]);
		if (TempSpan < minTSpan)
		{
			minTSpan = TempSpan;
			BestPos = TempPos;
			SelFac = fac;
		}
	}

	//将工件插入最好的位置
	Sol[SelFac].insert(Sol[SelFac].begin() + BestPos, Job);
	FactorySpan[SelFac] = minTSpan;
	return *max_element(FactorySpan.begin(), FactorySpan.end());
}


std::tuple<int, int, int> Job_To_BestFactory_BestPosition_B_WYT(int job, vector<vector<int>>& sol,
                                                                vector<int>& factorySpan, FBTime& fbTime)
{
	int bestFac;
	int bestPos;
	//Test the job at all the factories, and select the best position
	
	auto it = find_if(begin(sol), end(sol), [&](const auto& seq)
	{
		return seq.empty();
	});
	if (it != end(sol))
	{
		bestPos = 0;
		bestFac = static_cast<int>(it - begin(sol));
		//将工件插入最好的位置
		sol[bestFac].insert(sol[bestFac].begin() + bestPos, job);
		//factorySpan[bestFac] = GetFspan_BLOCK(sol[bestFac]);
		factorySpan[bestFac] = RefreshFBTime_InFactory_WYT(sol[bestFac], fbTime, bestPos, bestPos);
	}
	else
	{
		int minTSpan = INT_MAX;
		for (int fac = 0; fac < gFactory; fac++)
		{
			if (factorySpan[fac] + MinPTime[job] >= minTSpan) //minPTime[job]为工件Job的最小处理时间
			{
				continue;
			}

			int TempPos = -1;
			int TempSpan = FindBestInsertionPositon_B_WYT(TempPos, job, sol[fac], fbTime);

			if (TempSpan < minTSpan)
			{
				minTSpan = TempSpan;
				bestPos = TempPos;
				bestFac = fac;
			}
		}
		//将工件插入最好的位置
		sol[bestFac].insert(sol[bestFac].begin() + bestPos, job);
		factorySpan[bestFac] = minTSpan;
		factorySpan[bestFac] = RefreshFBTime_InFactory_WYT(sol[bestFac], fbTime, bestPos, bestPos);
	}
	int span = *max_element(factorySpan.begin(), factorySpan.end());
	return make_tuple(span, bestFac, bestPos);
}

//2022改进重构 by Ahmed Missaoui a, Rubén Ruiz
int FindBestInsertionPositon_Improved_B(int& BestPos, int Job, vector<int>& Seq)
{
	int minTSpan = INT_MAX;
	vector<int> NewSeq(Seq.size() + 1, 0);
	int K = 1;

	for (int Pos = 0; Pos <= Seq.size(); Pos = Pos + K) //5个工件6个位置
	{
		int TSpan = 0;

		if (Pos == Seq.size()) //位置在最后
		{
			for (int i = 0; i < Seq.size(); i++)
				NewSeq[i] = Seq[i];

			NewSeq[Seq.size()] = Job;

			TSpan = GetFspan_BLOCK(NewSeq);
		}
		else if (Pos == 0) //位置在第一
		{
			NewSeq[0] = Job;

			for (int i = 1; i < Seq.size() + 1; i++)
				NewSeq[i] = Seq[i - 1];

			TSpan = GetFspan_BLOCK(NewSeq);
		}
		else //其余位置
		{
			for (int i = 0; i < Pos; i++)
				NewSeq[i] = Seq[i];

			NewSeq[Pos] = Job;

			for (int j = Pos + 1; j < Seq.size() + 1; j++)
				NewSeq[j] = Seq[j - 1];

			TSpan = GetFspan_BLOCK(NewSeq);
		}

		if (TSpan < minTSpan) //结果比以前好，更新数据，k不变
		{
			minTSpan = TSpan;
			BestPos = Pos;
			K = 1;
		}
		else //结果比以前差，不更新，k=k+1
		{
			K = K + 1;
		}
	}
	return minTSpan;
}

int FindBestInsertionPositon_Improved_B_WYT(int& BestPos, int Job, vector<int>& Seq, const FBTime& fbTime)
{
	
	std::vector<int> srartTimeOfInsertJob(gMachine, 0);
	std::vector<int> finishTimeOfInsertJob(gMachine, 0);
	std::vector<int> departureTimeOfInsertJob(gMachine, 0);

	auto calculateTimeOfJob = [&](int pos)
	{
		if (pos == 0)
		{
			srartTimeOfInsertJob[0] = pSetupTime[0][Job][Job];
			finishTimeOfInsertJob[0] = srartTimeOfInsertJob[0] + pTime[Job][0];
			departureTimeOfInsertJob[0] = finishTimeOfInsertJob[0];
			for (int m = 1; m < gMachine; m++)
			{
				srartTimeOfInsertJob[m] = max(pSetupTime[m][Job][Job], departureTimeOfInsertJob[m - 1]);
				finishTimeOfInsertJob[m] = srartTimeOfInsertJob[m] + pTime[Job][m];
				departureTimeOfInsertJob[m] = finishTimeOfInsertJob[m];
				departureTimeOfInsertJob[m - 1] = srartTimeOfInsertJob[m];
			}
		}
		else
		{
			int PreJob = Seq[pos - 1];
			srartTimeOfInsertJob[0] = fbTime.forwardDepartureTime[PreJob][0] + pSetupTime[0][PreJob][Job];
			finishTimeOfInsertJob[0] = srartTimeOfInsertJob[0] + pTime[Job][0];
			departureTimeOfInsertJob[0] = finishTimeOfInsertJob[0];

			for (int m = 1; m < gMachine; m++)
			{
				srartTimeOfInsertJob[m] =
					max(departureTimeOfInsertJob[m - 1],
						fbTime.forwardDepartureTime[PreJob][m] + pSetupTime[m][PreJob][Job]);
				finishTimeOfInsertJob[m] = srartTimeOfInsertJob[m] + pTime[Job][m];
				departureTimeOfInsertJob[m] = finishTimeOfInsertJob[m];
				departureTimeOfInsertJob[m - 1] = srartTimeOfInsertJob[m];
			}
		}
	};
	int bestSpan = INT32_MAX;
	if (Seq.empty())
	{
		calculateTimeOfJob(0);
		bestSpan = departureTimeOfInsertJob[gMachine - 1];
		BestPos = 0;
	}
	else
	{
		int k = 1;
		for (int pos = 0; pos <= Seq.size(); pos+=k)
		{
			int spanAfterInsert = 0;
			calculateTimeOfJob(pos);
			if (pos == Seq.size())
			{
				spanAfterInsert = departureTimeOfInsertJob[gMachine - 1];
			}
			else
			{
				int NextJob = Seq[pos];
				for (int m = 0; m < gMachine; m++)
				{
					spanAfterInsert = max(spanAfterInsert,
						departureTimeOfInsertJob[m] + pSetupTime[m][Job][NextJob]
						+ fbTime.backwardDepartureTime[NextJob][m]);
				}
			}

			if (bestSpan > spanAfterInsert)
			{
				bestSpan = spanAfterInsert;
				BestPos = pos;
				k = 1;
			}
			else
			{
				++k;
			}
		}
	}
	return bestSpan;

}

int Job_To_BestFactory_Bestposition_Improved_B(int Job, vector<vector<int>>& Sol, int& SelFac, int& BestPos)
{
	//先将每个工厂的makespan都初始化为0
	vector<int> FactorySpan;
	FactorySpan.resize(Sol.size(), 0); //

	for (int f = 0; f < Sol.size(); f++) //
		FactorySpan[f] = GetFspan_BLOCK(Sol[f]); //

	vector<int> minPTime;
	minPTime.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
	{
		int TempminPTime = INT_MAX;
		for (int m = 0; m < gMachine; m++)
		{
			if (pTime[j][m] < TempminPTime)
				TempminPTime = pTime[j][m];
		}
		minPTime[j] = TempminPTime;
	}

	//Test the job at all the factories, and select the best position
	int minTSpan = INT_MAX;
	for (int fac = 0; fac < gFactory; fac++)
	{
		if (Sol[fac].size() == 0)
		{
			for (int m = 0; m < gMachine; m++)
				minTSpan = pSetupTime[m][Job][Job] + pTime[Job][m];
			BestPos = 0;
			SelFac = fac;
			break;
		}
		if (!(FactorySpan[fac] + minPTime[Job] < minTSpan)) //minPTime[Job]为工件Job的最小处理时间
			continue;


		int TempSpan = 0, TempPos = -1; //////
		TempSpan = FindBestInsertionPositon_Improved_B(TempPos, Job, Sol[fac]);
		if (TempSpan < minTSpan)
		{
			minTSpan = TempSpan;
			BestPos = TempPos;
			SelFac = fac;
		}
	}

	//将工件插入最好的位置
	Sol[SelFac].insert(Sol[SelFac].begin() + BestPos, Job);
	FactorySpan[SelFac] = minTSpan;
	return *max_element(FactorySpan.begin(), FactorySpan.end());
}

int Job_To_BestFactory_Bestposition_Improved_B_ZCY(int Job, vector<vector<int>>& Sol, int& SelFac, int& BestPos, vector<int>& FactorySpan)
{
	

	vector<int> minPTime;
	minPTime.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
	{
		int TempminPTime = INT_MAX;
		for (int m = 0; m < gMachine; m++)
		{
			if (pTime[j][m] < TempminPTime)
				TempminPTime = pTime[j][m];
		}
		minPTime[j] = TempminPTime;
	}

	//Test the job at all the factories, and select the best position
	int minTSpan = INT_MAX;
	for (int fac = 0; fac < gFactory; fac++)
	{
		if (Sol[fac].size() == 0)
		{
			for (int m = 0; m < gMachine; m++)
				minTSpan = pSetupTime[m][Job][Job] + pTime[Job][m];
			BestPos = 0;
			SelFac = fac;
			break;
		}
		if (!(FactorySpan[fac] + minPTime[Job] < minTSpan)) //minPTime[Job]为工件Job的最小处理时间
			continue;


		int TempSpan = 0, TempPos = -1; //////
		TempSpan = FindBestInsertionPositon_Improved_B(TempPos, Job, Sol[fac]);
		if (TempSpan < minTSpan)
		{
			minTSpan = TempSpan;
			BestPos = TempPos;
			SelFac = fac;
		}
	}

	//将工件插入最好的位置
	Sol[SelFac].insert(Sol[SelFac].begin() + BestPos, Job);
	FactorySpan[SelFac] = minTSpan;
	return *max_element(FactorySpan.begin(), FactorySpan.end());
}

int Job_To_BestFactory_Bestposition_Improved_B_WYT(int Job, vector<vector<int>>& Sol, vector<int>& FactorySpan, FBTime& fbTime)
{
	int SelFac;
	int BestPos;
	
	//Test the job at all the factories, and select the best position
	auto it = find_if(begin(Sol), end(Sol), [&](const auto& seq)
		{
			return seq.empty();
		});
	if (it != end(Sol))
	{
		BestPos = 0;
		SelFac = static_cast<int>(it - begin(Sol));
		//将工件插入最好的位置
		Sol[SelFac].insert(Sol[SelFac].begin() + BestPos, Job);
		//factorySpan[bestFac] = GetFspan_BLOCK(sol[bestFac]);
		FactorySpan[BestPos] = RefreshFBTime_InFactory_WYT(Sol[SelFac], fbTime, BestPos, BestPos);
	}
	else
	{
		int minTSpan = INT_MAX;
		for (int fac = 0; fac < gFactory; fac++)
		{
			if (!(FactorySpan[fac] + MinPTime[Job] < minTSpan)) //minPTime[Job]为工件Job的最小处理时间
			{
				continue;
			}
			
			int TempPos = -1; 
			int TempSpan = FindBestInsertionPositon_Improved_B_WYT(TempPos, Job, Sol[fac], fbTime);
			if (TempSpan < minTSpan)
			{
				minTSpan = TempSpan;
				BestPos = TempPos;
				SelFac = fac;
			}
		}
	
		//将工件插入最好的位置
		Sol[SelFac].insert(Sol[SelFac].begin() + BestPos, Job);
		FactorySpan[SelFac] = minTSpan;
		FactorySpan[SelFac] = RefreshFBTime_InFactory_WYT(Sol[SelFac], fbTime, BestPos, BestPos);
	}		
	return *max_element(FactorySpan.begin(), FactorySpan.end());
}

//在makespan最小工厂中找到最好位置插入
int Job_To_MinFactory_Bestposition_B(int Job, vector<int>& Sol)
{
	
	int minTSpan = INT_MAX, BestPos = -1;
	if (Sol.size() == 0) //工厂无工件
	{
		for (int m = 0; m < gMachine; m++)
			minTSpan = pSetupTime[m][Job][Job] + pTime[Job][m];
		BestPos = 0;
	}
	int TempSpan = 0, TempPos = -1;

	TempSpan = FindBestInsertionPositon_B(TempPos, Job, Sol);

	if (TempSpan < minTSpan)
	{
		minTSpan = TempSpan;
		BestPos = TempPos;
	}

	//将工件插入最好的位置
	Sol.insert(Sol.begin() + BestPos, Job);


	return minTSpan;
}

//在关键工厂中找到最好的位置插入
int Job_To_KeyFactory_Bestposition_B(int Job, vector<int>& Seq)
{
	//找到关键工厂
	/*vector<int> FactorySpan(Sol.size(), 0);
	for (int f = 0; f < Sol.size(); f++)
		FactorySpan[f] = GetFspan_BLOCK(Sol[f]);

	int CriticalFacPt = -1;
	int TempFacSpan = INT_MIN;
	for (int i = 0; i < FactorySpan.size(); i++)
	{
		if (FactorySpan[i] > TempFacSpan)
		{
			TempFacSpan = FactorySpan[i];
			CriticalFacPt = i;
		}
	}*/

	int minTSpan = INT_MAX, BestPos = -1;
	if (Seq.size() == 0) //工厂无工件
	{
		for (int m = 0; m < gMachine; m++)
			minTSpan = pSetupTime[m][Job][Job] + pTime[Job][m];
		BestPos = 0;
	}
	int TempSpan = 0, TempPos = -1;

	TempSpan = FindBestInsertionPositon_B(TempPos, Job, Seq);

	if (TempSpan < minTSpan)
	{
		minTSpan = TempSpan;
		BestPos = TempPos;
	}

	//将工件插入最好的位置
	Seq.insert(Seq.begin() + BestPos, Job);


	return minTSpan;
}


//在一个工厂中找到最好的位置插入block
int Block_FindBestInsertionPosition_B(int& BestPos, vector<int> Block, vector<int>& Seq, int d)
{
	int minTSpan = INT_MAX;
	/*
	vector<vector<int>>Fij;
	Fij.resize(Seq.size() + 1);
	for (int i = 0; i < Seq.size() + 1; i++)
		Fij[i].resize(gMachine, 0);
	 */
	vector<int> NewSeq(Seq.size() + d, 0);

	for (int Pos = 0; Pos <= Seq.size(); Pos++) //5个工件6个位置
	{
		int TSpan = 0;
		if (Pos == Seq.size())
		{
			/*
			int PreJob = Seq[Pos - 1];
			Fij[Pos][0] = Eij[Pos - 1][0] + pSetupTime[0][PreJob][Job] + pTime[Job][0];
			for (int m = 1; m < gMachine; m++)
				Fij[Pos][m] = max(Eij[Pos - 1][m] + pSetupTime[m][PreJob][Job], Fij[Pos][m - 1]) + pTime[Job][m];
			*/
			for (int i = 0; i < Seq.size(); i++)
				NewSeq[i] = Seq[i];

			for (int i = 0; i < Block.size(); i++)
				NewSeq[Seq.size() + i] = Block[i];

			TSpan = GetFspan_BLOCK(NewSeq);
		}
		else if (Pos == 0)
		{
			for (int i = 0; i < d; i++)
				NewSeq[i] = Block[i];

			for (int i = d; i < Seq.size() + d; i++)
				NewSeq[i] = Seq[i - d];

			TSpan = GetFspan_BLOCK(NewSeq);
		}
		else
		{
			for (int i = 0; i < Pos; i++)
				NewSeq[i] = Seq[i];

			for (int i = Pos; i < Pos + d; i++)
				NewSeq[i] = Block[i - Pos];


			for (int j = Pos + d; j < Seq.size() + d; j++)
				NewSeq[j] = Seq[j - d];

			TSpan = GetFspan_BLOCK(NewSeq);
		}

		if (TSpan < minTSpan)
		{
			minTSpan = TSpan;
			BestPos = Pos;
		}
	}
	return minTSpan;
}

//一个Block在所有的工厂里找到最好的工厂最好的位置
int Block_To_Best_Factory_Bestposition_B(vector<int> Block, vector<vector<int>>& Sol, int d)
{
	//先将每个工厂的makespan都初始化为0
	vector<int> FactorySpan;
	FactorySpan.resize(Sol.size(), 0); //

	for (int f = 0; f < Sol.size(); f++) //
		FactorySpan[f] = GetFspan_BLOCK(Sol[f]); ////用GetFEnergy得到每个工厂的完工时间赋给FactorySpan


	//Test the block at all the factories, and select the best position
	int SelFac = 0, minTSpan = INT_MAX, BestPos = -1;
	for (int fac = 0; fac < gFactory; fac++)
	{
		if (Sol[fac].size() == 0) //工厂无工件
		{
			minTSpan = GetFspan_BLOCK(Block);

			BestPos = 0;
			SelFac = fac;
			break;
		}


		int TempSpan = 0, TempPos = -1; //////

		TempSpan = Block_FindBestInsertionPosition_B(TempPos, Block, Sol[fac], d);
		if (TempSpan < minTSpan)
		{
			minTSpan = TempSpan;
			BestPos = TempPos;
			SelFac = fac;
		}
	}

	//将块插入最好的位置
	for (int i = 0; i < d; i++)
	{
		int Job = Block[i];
		Sol[SelFac].insert(Sol[SelFac].begin() + BestPos + i, Job);
	}

	FactorySpan[SelFac] = minTSpan;

	return *max_element(FactorySpan.begin(), FactorySpan.end());
}


void NEHInit(vector<int>& JobSeq)
{
	JobSeq.clear();
	JobSeq.resize(gJobs);
	Pair* ch = new Pair[gJobs];
	for (int j = 0; j < gJobs; j++)
	{
		ch[j].dim = j;
		ch[j].value = 0;
		for (int m = 0; m < gMachine; m++)
			ch[j].value += pTime[j][m];
	}

	sort(ch, ch + gJobs, PairGreater());
	for (int j = 0; j < gJobs; j++)
		JobSeq[j] = ch[j].dim;
	delete[]ch;
}


// 一个工件在某个工厂找到最好得位置
int Job_To_SomeFactory_Bestposition_B(int Job, vector<int>& Seq) /////
{

	int minTSpan = INT_MAX, BestPos = -1;
	if (Seq.size() == 0)
	{
		for (int m = 0; m < gMachine; m++)
			minTSpan = pSetupTime[m][Job][Job] + pTime[Job][m];
		BestPos = 0;
	}
	else
	{
		minTSpan = FindBestInsertionPositon_B(BestPos, Job, Seq);
	}

	//将工件插入最好的位置
	Seq.insert(Seq.begin() + BestPos, Job);
	int Makespan = minTSpan;

	return Makespan;
}

int Job_To_SomeFactory_BestPosition_B_WYT(int job, vector<int>& seq, FBTime& fbTime)
{
	int BestPos = -1;
	int span;
	if (seq.empty())
	{
		BestPos = 0;
		//将工件插入最好的位置
		seq.insert(seq.begin() + BestPos, job);
		//span = GetFspan_BLOCK(seq);
		//span = RefreshFBTime_InFactory_WYT(seq, gFBTime, BestPos, BestPos);
	}
	else
	{
		//GetFSpan_BLOCK_BTW_FBTime_WYT(seq, gFBTime); //
		span = FindBestInsertionPositon_B_WYT(BestPos, job, seq, fbTime);
		//将工件插入最好的位置
		seq.insert(seq.begin() + BestPos, job);
	}
	span = RefreshFBTime_InFactory_WYT(seq, fbTime, BestPos, BestPos);
	return span;
}


//工件在所有工厂中找到最佳位置


//检查解序列
void CheckChrom1(vector<vector<int>> Sol, int Span)
{
	vector<bool> bExist(gJobs, false);

	for (int f = 0; f < Sol.size(); f++)
	{
		for (int j = 0; j < Sol[f].size(); j++)
			bExist[Sol[f][j]] = true;
	}

	for (int i = 0; i < bExist.size(); i++)
	{
		if (!bExist[i]) printf("/nchrom is error! Job %d is lost", i);
	}

	if (Span > 0)
	{
		int TempSpan = GetFspan_Block(Sol);
		//		printf("%d\n", TempSpan);
		//	printf("%d\n", Span);
		if (TempSpan != Span)
			printf("\n Span is Error! %d,%d", TempSpan, Span);
	}
}

//Create an initial solution by placing jobs to the factory with minimized makespan one by one
int Initialization_Rand_B(vector<vector<int>>& Seq)
{
	Seq.clear();
	Seq.resize(gFactory);

	vector<int> JobSeq;
	JobSeq.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
		JobSeq[j] = j;
	random_shuffle(JobSeq.begin(), JobSeq.end());

	//得到一个初始解
	vector<int> SeqSpan; //record the makespan of each factory
	SeqSpan.resize(gFactory, 0);

	for (int f = 0; f < gFactory; f++)
		Seq[f].push_back(JobSeq[f]);

	for (int j = gFactory; j < JobSeq.size(); j++)
	{
		int TempSpan = INT_MAX;
		int Fpt = -1;
		for (int f = 0; f < gFactory; f++)
		{
			SeqSpan[f] = GetFspan_BLOCK(Seq[f]);
			if (SeqSpan[f] < TempSpan)
			{
				TempSpan = SeqSpan[f];
				Fpt = f;
			}
		}
		Seq[Fpt].push_back(JobSeq[j]);
	}
	int FinalSpan = GetFspan_Block(Seq);
	return FinalSpan;
}
