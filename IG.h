#pragma once
#include <unordered_map>

#include "com.h"
#include "FBTime.h"

//初始化

int NEH2_en_B(vector<vector<int>>& Sol)
{
	Sol.clear();
	Sol.resize(gFactory);  //设置容量

	vector<int> FullPermutation;
	FullPermutation.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
	{
		FullPermutation[j] = j;
	}
	NEHInit(FullPermutation);

	int FinalMakespan = 0;
	for (int i = 0; i < FullPermutation.size(); i++)
	{
		int Job = FullPermutation[i];
		int SelFac = 0;
		int BestPos = 0;
		FinalMakespan = Job_To_BestFactory_Bestposition_B(Job, Sol, SelFac, BestPos);
		if (Sol[SelFac].size() > 1)
		{
			if (BestPos == 0)
			{
				int RetryJob = Sol[SelFac][BestPos + 1];
				Sol[SelFac].erase(Sol[SelFac].begin() + BestPos + 1);
				Job_To_SomeFactory_Bestposition_B(RetryJob, Sol[SelFac]);
			}
			else if (BestPos == (Sol[SelFac].size() - 1))
			{
				int RetryJob = Sol[SelFac][BestPos - 1];
				Sol[SelFac].erase(Sol[SelFac].begin() + BestPos - 1);
				Job_To_SomeFactory_Bestposition_B(RetryJob, Sol[SelFac]);
			}
			else
			{
				int RandNum = wyt_rand(2);// rand() % 2;
				if (RandNum == 0)
				{
					int RetryJob = Sol[SelFac][BestPos + 1];
					Sol[SelFac].erase(Sol[SelFac].begin() + BestPos + 1);
					Job_To_SomeFactory_Bestposition_B(RetryJob, Sol[SelFac]);
				}
				else
				{
					int RetryJob = Sol[SelFac][BestPos - 1];
					Sol[SelFac].erase(Sol[SelFac].begin() + BestPos - 1);
					Job_To_SomeFactory_Bestposition_B(RetryJob, Sol[SelFac]);
				}
			}
		}
	}
	FinalMakespan = GetFspan_Block(Sol);
	//for (int i = 0; i < Sol.size(); i++)
	//{
	//	FactorySpan[i] = GetFspan_BLOCK(Sol[i]);
	//}
	//return *max_element(begin(FactorySpan), end(FactorySpan));
	return FinalMakespan;
}

int NEH2_en_B_ZCY(vector<vector<int>>& Sol, vector<int>& FactorySpan)
{
	Sol.clear();
	Sol.resize(gFactory);  //设置容量

	vector<int> FullPermutation;
	FullPermutation.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
	{
		FullPermutation[j] = j;
	}
	NEHInit(FullPermutation);

	int FinalMakespan = 0;
	for (int i = 0; i < FullPermutation.size(); i++)
	{
		int Job = FullPermutation[i];
		int SelFac = 0;
		int BestPos = 0;
		FinalMakespan = Job_To_BestFactory_Bestposition_B_ZCY(Job, Sol, SelFac, BestPos, FactorySpan);
		if (Sol[SelFac].size() > 1)
		{
			if (BestPos == 0)
			{
				int RetryJob = Sol[SelFac][BestPos + 1];
				Sol[SelFac].erase(Sol[SelFac].begin() + BestPos + 1);
				Job_To_SomeFactory_Bestposition_B(RetryJob, Sol[SelFac]);
			}
			else if (BestPos == (Sol[SelFac].size() - 1))
			{
				int RetryJob = Sol[SelFac][BestPos - 1];
				Sol[SelFac].erase(Sol[SelFac].begin() + BestPos - 1);
				Job_To_SomeFactory_Bestposition_B(RetryJob, Sol[SelFac]);
			}
			else
			{
				int RandNum = wyt_rand(2);// rand() % 2;
				if (RandNum == 0)
				{
					int RetryJob = Sol[SelFac][BestPos + 1];
					Sol[SelFac].erase(Sol[SelFac].begin() + BestPos + 1);
					Job_To_SomeFactory_Bestposition_B(RetryJob, Sol[SelFac]);
				}
				else
				{
					int RetryJob = Sol[SelFac][BestPos - 1];
					Sol[SelFac].erase(Sol[SelFac].begin() + BestPos - 1);
					Job_To_SomeFactory_Bestposition_B(RetryJob, Sol[SelFac]);
				}
			}
		}
	}
	//FinalMakespan = GetFspan_Block(Sol);
	for (int i = 0; i < Sol.size(); i++)
	{
		FactorySpan[i] = GetFspan_BLOCK(Sol[i]);
	}
	return *max_element(begin(FactorySpan), end(FactorySpan));
	//return FinalMakespan;
}

int NEH2_en_B_WYT(vector<vector<int>>& Sol, vector<int>& FactorySpan, FBTime& fbTime)
{
	Sol.clear();
	Sol.resize(gFactory);  //设置容量

	vector<int> FullPermutation(gJobs);
	std::iota(begin(FullPermutation), end(FullPermutation), 0);

	vector<int> totalPTimeOfJob(gJobs, 0);
	for (int j = 0; j < gJobs; j++)
	{
		for (int m = 0; m < gMachine; m++)
		{
			totalPTimeOfJob[j] += pTime[j][m];
		}
	}

	sort(begin(FullPermutation), end(FullPermutation), [&](int a, int b) {return totalPTimeOfJob[a] > totalPTimeOfJob[b]; });
	
	for (int Job : FullPermutation)
	{
		tuple<int, int, int> re = Job_To_BestFactory_BestPosition_B_WYT(Job, Sol, FactorySpan, fbTime);

		int FinalMakespan = get<0>(re);
		int SelectedFac = get<1>(re);
		int BestPos = get<2>(re);


		if (Sol[SelectedFac].size() > 1)
		{
			int RetryJobPosition;
			if (BestPos == 0)
			{
				RetryJobPosition = BestPos + 1;
			}
			else if (BestPos == (Sol[SelectedFac].size() - 1))
			{
				RetryJobPosition = BestPos - 1;
			}
			else
			{				
				if (wyt_rand() == true)
				{
					RetryJobPosition = BestPos + 1;
				}
				else
				{
					RetryJobPosition = BestPos - 1;
				}
			}
			int RetryJob = Sol[SelectedFac][RetryJobPosition];
			Sol[SelectedFac].erase(Sol[SelectedFac].begin() + RetryJobPosition);
			FactorySpan[SelectedFac] = RefreshFBTime_InFactory_WYT(Sol[SelectedFac], fbTime, RetryJobPosition, RetryJobPosition - 1);
			FactorySpan[SelectedFac] = Job_To_SomeFactory_BestPosition_B_WYT(RetryJob, Sol[SelectedFac], fbTime);
		}		
	}
	//int FinalMakespan = GetFspan_Block(Sol);
	return *max_element(begin(FactorySpan), end(FactorySpan));
}

//破坏
void Destruction_B(vector<vector<int>>& Seq, vector<int>& DesJobSeq, int PLen)
{
	DesJobSeq.clear();

	vector<int>FactorySpan(Seq.size(), 0);
	for (int f = 0; f < Seq.size(); f++)
		FactorySpan[f] = GetFspan_BLOCK(Seq[f]);

	int CriticalFacPt = -1;
	int TempFacSpan = INT_MIN;
	for (int i = 0; i < FactorySpan.size(); i++)
	{
		if (FactorySpan[i] > TempFacSpan)
		{
			TempFacSpan = FactorySpan[i];
			CriticalFacPt = i;
		}
	}

	for (int i = 0; i < PLen / 2; i++)
	{
		int Pt =  wyt_rand(Seq[CriticalFacPt].size());
		DesJobSeq.push_back(Seq[CriticalFacPt][Pt]);
		Seq[CriticalFacPt].erase(Seq[CriticalFacPt].begin() + Pt);
	}

	while (DesJobSeq.size() < PLen)
	{
		int Fpt =  wyt_rand(Seq.size());
		if ((Seq[Fpt].size() > 1) && (Fpt != CriticalFacPt))
		{
			int pt =  wyt_rand(Seq[Fpt].size());
			DesJobSeq.push_back(Seq[Fpt][pt]);
			Seq[Fpt].erase(Seq[Fpt].begin() + pt);
		}
	}
}

void Destruction_B_ZCY(vector<vector<int>>& Seq, vector<int>& DesJobSeq, int PLen, vector<int>& FactorySpan)
{
	DesJobSeq.clear();

	int CriticalFacPt = -1;
	int TempFacSpan = INT_MIN;
	for (int i = 0; i < FactorySpan.size(); i++)
	{
		if (FactorySpan[i] > TempFacSpan)
		{
			TempFacSpan = FactorySpan[i];
			CriticalFacPt = i;
		}
	}

	for (int i = 0; i < PLen / 2; i++)
	{
		int Pt = wyt_rand(Seq[CriticalFacPt].size());
		DesJobSeq.push_back(Seq[CriticalFacPt][Pt]);
		Seq[CriticalFacPt].erase(Seq[CriticalFacPt].begin() + Pt);
	}

	while (DesJobSeq.size() < PLen)
	{
		int Fpt = wyt_rand(Seq.size());
		if ((Seq[Fpt].size() > 1) && (Fpt != CriticalFacPt))
		{
			int pt = wyt_rand(Seq[Fpt].size());
			DesJobSeq.push_back(Seq[Fpt][pt]);
			Seq[Fpt].erase(Seq[Fpt].begin() + pt);
		}
	}
}

void Destruction_B_WYT(vector<vector<int>>& Seq, vector<int>& DesJobSeq, int PLen, vector<int>& FactorySpan, FBTime& fbTime)
{
	DesJobSeq.clear();

	int CriticalFacPt = -1;
	int TempFacSpan = INT_MIN;
	for (int i = 0; i < FactorySpan.size(); i++)
	{
		if (FactorySpan[i] > TempFacSpan)
		{
			TempFacSpan = FactorySpan[i];
			CriticalFacPt = i;
		}
	}

	unordered_map<int, pair<int, int>> JobErasedFromFac;

	for (int i = 0; i < PLen / 2; i++)
	{
		int pos =  wyt_rand(Seq[CriticalFacPt].size());
		DesJobSeq.push_back(Seq[CriticalFacPt][pos]);
		Seq[CriticalFacPt].erase(Seq[CriticalFacPt].begin() + pos);

		if(JobErasedFromFac.find(CriticalFacPt) == end(JobErasedFromFac))
		{
			JobErasedFromFac[CriticalFacPt] = { pos, pos - 1 };
		}
		else
		{
			if (pos < JobErasedFromFac[CriticalFacPt].first)
			{
				JobErasedFromFac[CriticalFacPt].first = pos;
			}
			if (pos >= JobErasedFromFac[CriticalFacPt].second)
			{
				JobErasedFromFac[CriticalFacPt].second = pos - 1;
			}
			else
			{
				JobErasedFromFac[CriticalFacPt].second = JobErasedFromFac[CriticalFacPt].second - 1;
			}
		}
	}

	while (DesJobSeq.size() < PLen)
	{
		int Fpt =  wyt_rand(Seq.size());
		if (Seq[Fpt].size() > 1 && Fpt != CriticalFacPt)
		{
			int pos =  wyt_rand(Seq[Fpt].size());
			DesJobSeq.push_back(Seq[Fpt][pos]);
			Seq[Fpt].erase(Seq[Fpt].begin() + pos);
			if (JobErasedFromFac.find(Fpt) == end(JobErasedFromFac))
			{
				JobErasedFromFac[Fpt] = { pos, pos - 1 };
			}
			else
			{
				if (pos < JobErasedFromFac[Fpt].first)
				{
					JobErasedFromFac[Fpt].first = pos;
				}
				if (pos >= JobErasedFromFac[Fpt].second)
				{
					JobErasedFromFac[Fpt].second = pos - 1;
				}
				else
				{
					JobErasedFromFac[Fpt].second = JobErasedFromFac[Fpt].second - 1;
				}
			}
		}
	}

	for (auto v : JobErasedFromFac)
	{
		FactorySpan[v.first] = RefreshFBTime_InFactory_WYT(Seq[v.first], fbTime, v.second.first, v.second.second);
	}
}

//重构
int Construction_B(vector<vector<int>>& Seq, vector<int>DesJobSeq)
{
	for (int i = 0; i < DesJobSeq.size(); i++)
	{
		int Job = DesJobSeq[i];
		int SelFac = 0;
		int BestPos = 0;
		Job_To_BestFactory_Bestposition_B(Job, Seq, SelFac, BestPos);

		if (Seq[SelFac].size() > 1)
		{
			if (BestPos == 0)
			{
				int RetryJob = Seq[SelFac][BestPos + 1];
				Seq[SelFac].erase(Seq[SelFac].begin() + BestPos + 1);
				Job_To_SomeFactory_Bestposition_B(RetryJob, Seq[SelFac]);
			}
			else if (BestPos == (Seq[SelFac].size() - 1))
			{
				int RetryJob = Seq[SelFac][BestPos - 1];
				Seq[SelFac].erase(Seq[SelFac].begin() + BestPos - 1);
				Job_To_SomeFactory_Bestposition_B(RetryJob, Seq[SelFac]);
			}
			else
			{
				int RandNum = wyt_rand(2); //rand() % 2;
				if (RandNum == 0)
				{
					int RetryJob = Seq[SelFac][BestPos + 1];
					Seq[SelFac].erase(Seq[SelFac].begin() + BestPos + 1);
					Job_To_SomeFactory_Bestposition_B(RetryJob, Seq[SelFac]);
				}
				else
				{
					int RetryJob = Seq[SelFac][BestPos - 1];
					Seq[SelFac].erase(Seq[SelFac].begin() + BestPos - 1);
					Job_To_SomeFactory_Bestposition_B(RetryJob, Seq[SelFac]);
				}
			}
		}
	}
	int FinalMakespan = GetFspan_Block(Seq);
	return FinalMakespan;
}


int LS_3_B(vector<vector<int>>& Seq)
{
	vector<int>FactorySpan(Seq.size(), 0);
	for (int f = 0; f < Seq.size(); f++)
		FactorySpan[f] = GetFspan_BLOCK(Seq[f]);

	int CriticalFacPt = -1;
	int TempFacSpan = INT_MIN;//关键工厂
	for (int i = 0; i < FactorySpan.size(); i++)
	{
		if (FactorySpan[i] > TempFacSpan)
		{
			TempFacSpan = FactorySpan[i];
			CriticalFacPt = i;
		}
	}

	int Counter = 0;
	vector<int>TempCriticalFacSeq = Seq[CriticalFacPt];
	while (Counter < Seq[CriticalFacPt].size())
	{
		int MakeSpan = *max_element(FactorySpan.begin(), FactorySpan.end());//最大完工时间
		int RandNum =  wyt_rand(TempCriticalFacSeq.size());
		int Job = TempCriticalFacSeq[RandNum];//选择一个工件
		TempCriticalFacSeq.erase(TempCriticalFacSeq.begin() + RandNum);// erase（）删除此处的一个字符
		vector<vector<int>>TempSeq = Seq;


		int SelFac = 0;
		int BestPos = 0;
		int Pos = -1;

		for (int i = 0; i < Seq[CriticalFacPt].size(); i++)
		{
			if (Seq[CriticalFacPt][i] == Job)
			{
				Pos = i;
				Seq[CriticalFacPt].erase(Seq[CriticalFacPt].begin() + i);//执行删除操作
				break;
			}
		}
		int TempMakeSpan = Job_To_BestFactory_Bestposition_B(Job, Seq, SelFac, BestPos);
		if (TempMakeSpan >= MakeSpan)
		{
			Seq = TempSeq;
			Counter++;
		}
		else//有改进时
		{
			FactorySpan[CriticalFacPt] = GetFspan_BLOCK(Seq[CriticalFacPt]);
			FactorySpan[SelFac] = GetFspan_BLOCK(Seq[SelFac]);
			TempFacSpan = INT_MIN;
			for (int i = 0; i < FactorySpan.size(); i++)
			{
				if (FactorySpan[i] > TempFacSpan)
				{
					TempFacSpan = FactorySpan[i];
					CriticalFacPt = i;
				}
			}
			TempCriticalFacSeq = Seq[CriticalFacPt];
			Counter = 0;
		}
	}
	int FinalMakespan = GetFspan_Block(Seq);
	return FinalMakespan;
}

int IG_Compared(long TimeLimit, int PLen, double Tem)
{
	long InitTime = GetElapsedProcessTime();
	vector<vector<int>>Seq;
	int Span = NEH2_en_B(Seq);//return Makespan;return Makespan;
	Span = LS_3_B(Seq);//return FinalMakespan；

	vector<vector<int>>BestSeqSofar = Seq;
	int BestValueSofar = Span;
	double Temperature = GetTemperature(Tem);

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		vector<vector<int>>TempSeq = Seq;
		int TempSpan = Span;

		vector<int>DesJobSeq;//tr
		Destruction_B(TempSeq, DesJobSeq, PLen);
		Construction_B(TempSeq, DesJobSeq);//return FinalMakespan;
		TempSpan = LS_3_B(TempSeq);//return FinalMakespan;

		if (TempSpan < Span)
		{
			Span = TempSpan;
			Seq = TempSeq;

			if (Span < BestValueSofar)
			{
				BestValueSofar = Span;
				BestSeqSofar = Seq;
			}
		}
		else
		{
			double  t = exp((Span - TempSpan) / Temperature);            //改过的模拟退火
			if (wyt_rand(0, RAND_MAX) < int(RAND_MAX * t))//if (rand() < int(RAND_MAX * t))
			{
				Span = TempSpan;
				Seq = TempSeq;
			}
		}
	}
	CheckChrom1(BestSeqSofar, BestValueSofar);
	return BestValueSofar;
}





//块破坏
void block_Destruction_B(vector<vector<int>>& Seq, vector<int>& DesJobSeq, int d)
{
	DesJobSeq.clear();

	vector<int>FactorySpan(Seq.size(), 0);
	for (int f = 0; f < Seq.size(); f++)
		FactorySpan[f] = GetFspan_BLOCK(Seq[f]);

	//vector<int> block_1(d, 0);

	int CriticalFacPt = -1;
	int TempFacSpan = INT_MIN;
	for (int i = 0; i < FactorySpan.size(); i++)
	{
		if (FactorySpan[i] > TempFacSpan)
		{
			TempFacSpan = FactorySpan[i];
			CriticalFacPt = i;
		}
	}
	int Span = FactorySpan[CriticalFacPt];

	vector<vector<int>>TempSeq = Seq;
	vector<int>Block;
	Block.clear();

	int num_CriticalF = Seq[CriticalFacPt].size();
	int Pt = wyt_rand(num_CriticalF);// rand() % num_CriticalF;

	if ((Seq[CriticalFacPt].size() - Pt) >= d)
	{
		for (int j = 0; j < d; j++)
			Block.push_back(Seq[CriticalFacPt][Pt + j]);
	}
	else
	{
		for (int j = 0; j < d; j++)
			Block.push_back(Seq[CriticalFacPt][Seq[CriticalFacPt].size() - d + j]);
	}

	for (int j = 0; j < Block.size(); j++)
	{
		for (int n = 0; n < Seq[CriticalFacPt].size(); n++)
		{
			if (Block[j] == Seq[CriticalFacPt][n])
			{
				Seq[CriticalFacPt].erase(Seq[CriticalFacPt].begin() + n);
				break;
			}
		}
	}
	DesJobSeq = Block;
}

//块重构
int block_Construction_B(vector<vector<int>>& Sol, vector<int>Block, int d)
{
	int FinalMakespan = Block_To_Best_Factory_Bestposition_B(Block, Sol, d);
	return FinalMakespan;
}

//2022改进重构 by Ahmed Missaoui a, Rubén Ruiz 
int Construction_Improved_B(vector<vector<int>>& Seq, vector<int>DesJobSeq)
{
	int FinalMakespan;
	for (int i = 0; i < DesJobSeq.size(); i++)
	{
		int Job = DesJobSeq[i];
		int SelFac = 0;
		int BestPos = 0;
		FinalMakespan = Job_To_BestFactory_Bestposition_Improved_B(Job, Seq, SelFac, BestPos);
	}
	
	return FinalMakespan;
}

int Construction_Improved_B_ZCY(vector<vector<int>>& Seq, vector<int>DesJobSeq, vector<int>& FactorySpan)
{
	int FinalMakespan;
	for (int i = 0; i < DesJobSeq.size(); i++)
	{
		int Job = DesJobSeq[i];
		int SelFac = 0;
		int BestPos = 0;
		FinalMakespan = Job_To_BestFactory_Bestposition_Improved_B_ZCY(Job, Seq, SelFac, BestPos, FactorySpan);
	}

	return FinalMakespan;
}

int Construction_Improved_B_WYT(vector<vector<int>>& Seq, const vector<int>& DesJobSeq, vector<int>& FactorySpan, FBTime& fbTime)
{
	int FinalMakespan;
	for (int i = 0; i < DesJobSeq.size(); i++)
	{
		int Job = DesJobSeq[i];
		FinalMakespan = Job_To_BestFactory_Bestposition_Improved_B_WYT(Job, Seq, FactorySpan, fbTime);		
	}
	//int FinalMakespan = GetFspan_Block(Seq);
	return FinalMakespan;
}

