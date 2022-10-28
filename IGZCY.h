#pragma once
#include "com.h"
#include "IG.h"
#include "FBTime.h"
//�ؼ�������������������
//strategy1:�ƻ��ع�
int strategy1(vector<vector<int>>& Seq, vector<int> DesJobSeq, int d, vector<int>& FactorySpan)
{
	//d = 2 + rand() % (6 - 2 + 1);//�ƻ��׶ε�d=��Сֵ+�������
	//d = 2;
	Destruction_B_ZCY(Seq, DesJobSeq, d, FactorySpan);
	return Construction_Improved_B_ZCY(Seq, DesJobSeq, FactorySpan);
	//block_Destruction_B(Seq, DesJobSeq, d);
	//return block_Construction_B(Seq, DesJobSeq, d);
}

int strategy1_WYT(vector<vector<int>>& Seq, vector<int>& DesJobSeq, int d, vector<int>& FactorySpan, FBTime& fbTime)
{
	//d = 2 + rand() % (6 - 2 + 1);//�ƻ��׶ε�d=��Сֵ+�������
	Destruction_B_WYT(Seq, DesJobSeq, d, FactorySpan, fbTime);
	return Construction_Improved_B_WYT(Seq, DesJobSeq, FactorySpan, fbTime);
}

//todo
//strategy2:ִ��һ�ν����������ؼ�������makespan��С����֮�����ѡһ����������
int strategy2(vector<vector<int>>& Seq, vector<int>& FactorySpan)
{
	int CriticalFacPt = -1;
	int MinFacPt = -1;

	int Counter = 0;
	while (true)
	{
		if (Counter == 0)
		{
			int CriticalFacSpan = INT_MIN;

			for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�������makespan��С�Ĺ���
			{
				if (FactorySpan[i] > CriticalFacSpan)
				{
					CriticalFacSpan = FactorySpan[i];
					CriticalFacPt = i;
				}
			}

			int MinFacSpan = INT_MAX;
			for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�������makespan��С�Ĺ���
			{
				if (i == CriticalFacPt)
				{
					continue;
				}
				if (FactorySpan[i] < MinFacSpan)
				{
					MinFacSpan = FactorySpan[i];
					MinFacPt = i;
				}
			}
		}

		int RandPos1 = wyt_rand(Seq[CriticalFacPt].size());
		int Job1 = Seq[CriticalFacPt][RandPos1];

		int RandPos2 = wyt_rand(Seq[MinFacPt].size());
		int Job2 = Seq[MinFacPt][RandPos2];

		vector<vector<int>> TempSeq = Seq;

		Seq[CriticalFacPt][RandPos1] = Job2;
		Seq[MinFacPt][RandPos2] = Job1;

		int span1 = GetFspan_BLOCK(Seq[CriticalFacPt]);
		int span2 = GetFspan_BLOCK(Seq[MinFacPt]);

		if (max(span1, span2) >= FactorySpan[CriticalFacPt]) //��������Ч
		{
			Seq = TempSeq;
			Counter++;
		}
		else
		{

			//����FactorySpan
			FactorySpan[CriticalFacPt] = span1;
			FactorySpan[MinFacPt] = span2;

			Counter = 0;
		}

		if (Counter >= Seq[CriticalFacPt].size())
		{
			break;
		}
	}
	return *max_element(begin(FactorySpan), end(FactorySpan));;
}

int strategy2_WYT(vector<vector<int>>& Seq, vector<int>& FactorySpan, FBTime& fbTime)
{
	
	int CriticalFacPt = -1;
	int MinFacPt = -1;	

	int Counter = 0;
	while (true)
	{
		if (Counter == 0)
		{
			int CriticalFacSpan = INT_MIN;
			
			for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�������makespan��С�Ĺ���
			{
				if (FactorySpan[i] > CriticalFacSpan)
				{
					CriticalFacSpan = FactorySpan[i];
					CriticalFacPt = i;
				}
			}

			int MinFacSpan = INT_MAX;
			for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�������makespan��С�Ĺ���
			{
				if (i == CriticalFacPt)
				{
					continue;
				}
				if (FactorySpan[i] < MinFacSpan)
				{
					MinFacSpan = FactorySpan[i];
					MinFacPt = i;
				}
			}			
		}

		int RandPos1 =  wyt_rand(Seq[CriticalFacPt].size());
		int Job1 = Seq[CriticalFacPt][RandPos1];

		int RandPos2 =  wyt_rand(Seq[MinFacPt].size());
		int Job2 = Seq[MinFacPt][RandPos2];

		int span1 = GetFSpan_BLOCK_After_Switch_One_Job_WYT(Seq[CriticalFacPt], RandPos1, Job2, fbTime);
		int span2 = GetFSpan_BLOCK_After_Switch_One_Job_WYT(Seq[MinFacPt], RandPos2, Job1, fbTime);
		
		if (max(span1, span2) >= FactorySpan[CriticalFacPt]) //��������Ч
		{
			Counter++;
		}
		else
		{
			Seq[CriticalFacPt][RandPos1] = Job2;
			Seq[MinFacPt][RandPos2] = Job1;

			FactorySpan[CriticalFacPt] = RefreshFBTime_InFactory_WYT(Seq[CriticalFacPt], fbTime, RandPos1, RandPos1);
			FactorySpan[MinFacPt] = RefreshFBTime_InFactory_WYT(Seq[MinFacPt], fbTime, RandPos2, RandPos2);

			Counter = 0;
		}		

		if (Counter >= Seq[CriticalFacPt].size())
		{
			break;
		}
	}
	
	//int FinalMakespan = GetFspan_Block(Seq);
	return *max_element(begin(FactorySpan), end(FactorySpan));;
}


////��û�ã�strategy3:�ؼ����������ѡ��һ�����뵽��С������
//int strategy3(vector<vector<int>>& Seq, vector<int>& FactorySpan)
//{
//	int CriticalFacPt = -1;
//	int TempFacSpan = INT_MIN;
//	for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�����
//	{
//		if (FactorySpan[i] > TempFacSpan)
//		{
//			TempFacSpan = FactorySpan[i];
//			CriticalFacPt = i;
//		}
//	}
//
//	int Counter = 0;
//	vector<int> TempCriticalFacSeq = Seq[CriticalFacPt];
//	while (Counter < Seq[CriticalFacPt].size())
//	{
//		//���ѡ��һ������
//		int MakeSpan = *max_element(FactorySpan.begin(), FactorySpan.end());
//		/*std::random_device rdm;
//		std::uniform_int_distribution<int> distributionm(1, TempCriticalFacSeq.size());
//		int number = distributionm(rdm);*/
//		int RandNum_1 =  wyt_rand(TempCriticalFacSeq.size());
//
//		int Job_1 = TempCriticalFacSeq[RandNum_1];
//
//		vector<vector<int>> TempSeq = Seq;
//
//		int TempMakespan = 0;
//		TempMakespan = Job_To_MinFactory_Bestposition_B(Job_1, Seq[]);
//
//		if (TempMakespan >= MakeSpan) //��������Ч,��ȡ������
//		{
//			Seq = TempSeq;
//			Counter++;
//		}
//		else //����Ч
//		{
//			//����FactorySpan
//			FactorySpan[CriticalFacPt] = GetFspan_BLOCK(Seq[CriticalFacPt]);
//			TempFacSpan = INT_MIN;
//			//Ѱ���µĹؼ�����
//			for (int i = 0; i < FactorySpan.size(); i++)
//			{
//				if (FactorySpan[i] > TempFacSpan)
//				{
//					TempFacSpan = FactorySpan[i];
//					CriticalFacPt = i;
//				}
//			}
//
//			TempCriticalFacSeq = Seq[CriticalFacPt];
//			Counter = 0;
//		}
//	}
//	return *max_element(begin(FactorySpan), end(FactorySpan));;
//}
// strategy3:�ؼ����������ѡ��һ�����뵽��С������
int strategy3_ZCY(vector<vector<int>>& Seq, vector<int>& FactorySpan)
{
	int CriticalFacPt = -1;
	int MinFacPt = -1;

	int Counter = 0;
	while (true)
	{
		if (Counter == 0)
		{
			int CriticalFacSpan = INT_MIN;

			for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�������makespan��С�Ĺ���
			{
				if (FactorySpan[i] > CriticalFacSpan)
				{
					CriticalFacSpan = FactorySpan[i];
					CriticalFacPt = i;
				}
			}

			int MinFacSpan = INT_MAX;
			for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�������makespan��С�Ĺ���
			{
				if (i == CriticalFacPt)
				{
					continue;
				}
				if (FactorySpan[i] < MinFacSpan)
				{
					MinFacSpan = FactorySpan[i];
					MinFacPt = i;
				}
			}
		}
		vector<vector<int>> TempSeq = Seq;
		int MakeSpan = *max_element(FactorySpan.begin(), FactorySpan.end());
		int RandPos1 = wyt_rand(Seq[CriticalFacPt].size());
		int Job1 = Seq[CriticalFacPt][RandPos1];
		Seq[CriticalFacPt].erase(Seq[CriticalFacPt].begin() + RandPos1);

		int TempMakespan = Job_To_MinFactory_Bestposition_B(Job1, Seq[MinFacPt]);

		if (TempMakespan >= MakeSpan) //��������Ч,��ȡ������
		{
			Seq = TempSeq;
			Counter++;
		}
		else //����Ч
		{
			//����FactorySpan
			FactorySpan[CriticalFacPt] = GetFspan_BLOCK(Seq[CriticalFacPt]);
			FactorySpan[MinFacPt] = TempMakespan;		
			Counter = 0;
		}
		if (Counter >= Seq[CriticalFacPt].size())
		{
			break;
		}
	}
	return *max_element(begin(FactorySpan), end(FactorySpan));;
}

//��û�ã�strategy4:�ؼ����������ѡһ���������뵽���й����е����λ��
int strategy4(vector<vector<int>>& Seq)
{
	vector<int> FactorySpan(Seq.size(), 0);
	for (int f = 0; f < Seq.size(); f++)
		FactorySpan[f] = GetFspan_BLOCK(Seq[f]);

	int CriticalFacPt = -1;
	int TempFacSpan = INT_MIN;
	for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�����
	{
		if (FactorySpan[i] > TempFacSpan)
		{
			TempFacSpan = FactorySpan[i];
			CriticalFacPt = i;
		}
	}

	int Counter = 0;
	vector<int> TempCriticalFacSeq = Seq[CriticalFacPt];
	while (Counter < Seq[CriticalFacPt].size())
	{
		//���ѡ��һ������
		int MakeSpan = *max_element(FactorySpan.begin(), FactorySpan.end());
		int RandNum_1 =  wyt_rand(TempCriticalFacSeq.size());
		int Job_1 = TempCriticalFacSeq[RandNum_1];

		vector<vector<int>> TempSeq = Seq;

		int TempMakespan = 0;
		TempMakespan = Job_To_BestFactory_Bestposition_B(Job_1, Seq);

		if (TempMakespan >= MakeSpan) //��������Ч,��ȡ���ϴεĽ���
		{
			Seq = TempSeq;
			Counter++;
		}
		else //����Ч
		{
			//����FactorySpan
			FactorySpan[CriticalFacPt] = GetFspan_BLOCK(Seq[CriticalFacPt]);
			TempFacSpan = INT_MIN;
			//Ѱ���µĹؼ�����
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
//strategy6��һ�ν����������ؼ�������ιؼ�����
int strategy6(vector<vector<int>>& Seq, vector<int>& FactorySpan)//ֻ�Թؼ��������оֲ�����
{
	int CriticalFacPt = -1;
	int Minor_CriticalFacPt = -1;

	int Counter = 0;
	while (true)
	{
		if (Counter == 0)
		{
			int CriticalFacSpan = INT_MIN;

			for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�����
			{
				if (FactorySpan[i] > CriticalFacSpan)
				{
					CriticalFacSpan = FactorySpan[i];
					CriticalFacPt = i;
				}
			}
			
			//�ҵ���Ҫ�Ĺ���
			int Minor_TempFacSpan = INT_MIN;
			for (int i = 0; i < CriticalFacPt; i++)
			{
				if (i == CriticalFacPt)
				{
					continue;
				}
				if (FactorySpan[i] > Minor_TempFacSpan)
				{
					Minor_TempFacSpan = FactorySpan[i];
					Minor_CriticalFacPt = i;
				}
			}

			for (int i = CriticalFacPt + 1; i < FactorySpan.size(); i++)
			{
				if (i == CriticalFacPt)
				{
					continue;
				}
				if (FactorySpan[i] > Minor_TempFacSpan)
				{
					Minor_TempFacSpan = FactorySpan[i];
					Minor_CriticalFacPt = i;
				}
			}
		}

		int RandPos1 = wyt_rand(Seq[CriticalFacPt].size());
		int Job1 = Seq[CriticalFacPt][RandPos1];

		int RandPos2 = wyt_rand(Seq[Minor_CriticalFacPt].size());
		int Job2 = Seq[Minor_CriticalFacPt][RandPos2];

		vector<vector<int>> TempSeq = Seq;

		Seq[CriticalFacPt][RandPos1] = Job2;
		Seq[Minor_CriticalFacPt][RandPos2] = Job1;

		int span1 = GetFspan_BLOCK(Seq[CriticalFacPt]);
		int span2 = GetFspan_BLOCK(Seq[Minor_CriticalFacPt]);

		if (max(span1, span2) >= FactorySpan[CriticalFacPt]) //��������Ч
		{
			Seq = TempSeq;
			Counter++;
		}
		else
		{

			//����FactorySpan
			FactorySpan[CriticalFacPt] = span1;
			FactorySpan[Minor_CriticalFacPt] = span2;

			Counter = 0;
		}

		if (Counter >= Seq[CriticalFacPt].size())
		{
			break;
		}
	}
	return *max_element(begin(FactorySpan), end(FactorySpan));;
}

//strategy6��һ�ν����������ؼ�������ιؼ�����
int strategy6_WYT(vector<vector<int>>& Seq, vector<int>& FactorySpan, FBTime& fbTime)
{
	int CriticalFacPt = -1;
	int Minor_CriticalFacPt = -1;

	int Counter = 0;

	while (true)
	{
		if (Counter == 0)
		{
			int CriticalFacSpan = INT_MIN;
			for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�����
			{
				if (FactorySpan[i] > CriticalFacSpan)
				{
					CriticalFacSpan = FactorySpan[i];
					CriticalFacPt = i;
				}
			}

			int Minor_CriticalFacSpan = INT_MIN;
			for (int i = 0; i < FactorySpan.size(); ++i) //�ҵ���Ҫ�Ĺ���
			{
				if (i == CriticalFacPt)
				{
					continue;
				}
				if (FactorySpan[i] > Minor_CriticalFacSpan)
				{
					Minor_CriticalFacSpan = FactorySpan[i];
					Minor_CriticalFacPt = i;
				}
			}
		}
		
		int RandPos1 =  wyt_rand(Seq[CriticalFacPt].size());
		int Job1 = Seq[CriticalFacPt][RandPos1];

		int RandPos2 = wyt_rand(Seq[Minor_CriticalFacPt].size());
		int Job2 = Seq[Minor_CriticalFacPt][RandPos2];

		int span1 = GetFSpan_BLOCK_After_Switch_One_Job_WYT(Seq[CriticalFacPt],	RandPos1, Job2, fbTime);
		int span2 = GetFSpan_BLOCK_After_Switch_One_Job_WYT(Seq[Minor_CriticalFacPt], RandPos2, Job1, fbTime);
			

		if (max(span1, span2) >= FactorySpan[CriticalFacPt]) //��������Ч
		{
			Counter++;
		}
		else
		{
			Seq[CriticalFacPt][RandPos1] = Job2;
			Seq[Minor_CriticalFacPt][RandPos2] = Job1;

			FactorySpan[CriticalFacPt] = RefreshFBTime_InFactory_WYT(Seq[CriticalFacPt], fbTime, RandPos1, RandPos1);
			FactorySpan[Minor_CriticalFacPt] = RefreshFBTime_InFactory_WYT(Seq[Minor_CriticalFacPt], fbTime, RandPos2, RandPos2);		

			Counter = 0;
		}		

		if (Counter >= Seq[CriticalFacPt].size())
		{
			break;
		}
	}

	//int FinalMakespan = GetFspan_Block(Seq);
	return *max_element(begin(FactorySpan), end(FactorySpan));
}

//strategy5:ִ��2�ν����������ؼ�������ιؼ�����֮�����ѡһ����������
int strategy5(vector<vector<int>>& Seq, vector<int>& FactorySpan)
{
	int Span;
	Span = strategy6(Seq, FactorySpan);
	Span = strategy6(Seq, FactorySpan);

	return Span;
}

int strategy5_WYT(vector<vector<int>>& Seq, vector<int>& FactorySpan, FBTime& fbTime)
{
	int Span;
	Span = strategy6_WYT(Seq, FactorySpan, fbTime);
	Span = strategy6_WYT(Seq, FactorySpan, fbTime);
	return Span;
}

//��û�ã����ѡ������������makespan�����ѡһ������С��
int strategy7(vector<vector<int>>& Seq)
{
	//����ҵ���������
	int MaxFpt, MinFpt;
	do
	{
		MaxFpt =  wyt_rand(Seq.size());
		MinFpt =  wyt_rand(Seq.size());
	}
	while (MaxFpt == MinFpt);

	//ѡ���깤ʱ�������Ǹ�����
	int MaxFactorySpan = GetFspan_BLOCK(Seq[MaxFpt]);
	int MinFactorySpan = GetFspan_BLOCK(Seq[MinFpt]);

	int TempSpan = MaxFactorySpan;
	int TempFpt = MaxFpt;

	if (MaxFactorySpan < MinFactorySpan)
	{
		MaxFactorySpan = MinFactorySpan;
		MaxFpt = MinFpt;
		MinFactorySpan = TempSpan;
		MinFpt = TempFpt;
	}

	//���깤ʱ���Ĺ������ѡ��һ������
	vector<int> MinTempSeq = Seq[MinFpt];
	int pt =  wyt_rand(Seq[MaxFpt].size());
	int Job = Seq[MaxFpt][pt];

	//�����ȡ�õĹ������²��뵽����һ�����������λ��
	int TempBetterSpan = Job_To_SomeFactory_Bestposition_B(Job, Seq[MinFpt]);
	if (TempBetterSpan < MaxFactorySpan)
		Seq[MaxFpt].erase(Seq[MaxFpt].begin() + pt);
	else
		Seq[MinFpt] = MinTempSeq;

	int FinalMakespan = GetFspan_Block(Seq);
	return FinalMakespan;
}

//�ؼ������ڲ���
//��δ�ã��ؼ������� ������
int nei1(vector<vector<int>>& Seq)
{
	//�ҹؼ�����
	vector<int> FactorySpan(Seq.size(), 0);
	for (int f = 0; f < Seq.size(); f++)
		FactorySpan[f] = GetFspan_BLOCK(Seq[f]);

	int CriticalFacPt = -1;
	int TempFacSpan = INT_MIN;
	for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�����
	{
		if (FactorySpan[i] > TempFacSpan)
		{
			TempFacSpan = FactorySpan[i];
			CriticalFacPt = i;
		}
	}


	int Counter = 0;
	vector<int> TempCriticalFacSeq = Seq[CriticalFacPt];
	while (Counter < Seq[CriticalFacPt].size())
	{
		int MakeSpan = *max_element(FactorySpan.begin(), FactorySpan.end());
		vector<int> TempSeq = Seq[CriticalFacPt];

		int i = 0;
		int j = TempSeq.size() - 1;
		while (i < j)
		{
			if (i < j)
			{
				swap(TempSeq[i], TempSeq[j]);
				if (GetFspan_BLOCK(TempSeq) < GetFspan_BLOCK(Seq[CriticalFacPt]))
				{
					Seq[CriticalFacPt] = TempSeq;
				}
				else
				{
					TempSeq = Seq[CriticalFacPt];
				}
				j--;
				i++;
			}
		}

		int TempMakespan = 0;
		TempMakespan = GetFspan_Block(Seq);

		if (TempMakespan >= MakeSpan) //��������Ч,��ȡ���ϴεĽ���
		{
			Seq[CriticalFacPt] = TempSeq;
			Counter++;
		}
		else //����Ч
		{
			//����FactorySpan
			FactorySpan[CriticalFacPt] = GetFspan_BLOCK(Seq[CriticalFacPt]);
			TempFacSpan = INT_MIN;
			//Ѱ���µĹؼ�����
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

//�ؼ��������ȡһ�����������ڹؼ����������λ��
int nei2(vector<vector<int>>& Seq, vector<int>& FactorySpan)
{
	int Counter = 0;
	int CriticalFacPt = -1;
	while (true)
	{
		if (Counter == 0)
		{
			int TempFacSpan = INT_MIN;
			for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�����
			{
				if (FactorySpan[i] > TempFacSpan)
				{
					TempFacSpan = FactorySpan[i];
					CriticalFacPt = i;
				}
			}
		}
		
		vector<vector<int>> TempSeq = Seq;

		int RandPos = wyt_rand(Seq[CriticalFacPt].size());
		int Job = Seq[CriticalFacPt][RandPos];
		Seq[CriticalFacPt].erase(begin(Seq[CriticalFacPt]) + RandPos);
		
		//int bestPos = -1;

		int TempMakespan = 0;
		TempMakespan = Job_To_KeyFactory_Bestposition_B(Job, Seq[CriticalFacPt]);
		
		if (TempMakespan < FactorySpan[CriticalFacPt])//����Ч
		{
			//����FactorySpan
			FactorySpan[CriticalFacPt] = TempMakespan;
			//Seq[CriticalFacPt].insert(Seq[CriticalFacPt].begin() + bestPos, Job);
			Counter = 0;
		}
		else 
		{
			Seq = TempSeq;
			++Counter;
		}
		if (Counter >= Seq[CriticalFacPt].size())
		{
			break;
		}

	}
	return *max_element(begin(FactorySpan), end(FactorySpan));
}

int nei2_WYT(vector<vector<int>>& Seq, vector<int>& FactorySpan, FBTime& fbTime)
{
	int Counter = 0;
	int CriticalFacPt = -1;

	while (true)
	{
		if (Counter == 0)
		{
			int TempFacSpan = INT_MIN;
			for (int i = 0; i < FactorySpan.size(); i++) //�ҵ��ؼ�����
			{
				if (FactorySpan[i] > TempFacSpan)
				{
					TempFacSpan = FactorySpan[i];
					CriticalFacPt = i;
				}
			}
		}

		int RandPos =  wyt_rand(Seq[CriticalFacPt].size());
		int Job = Seq[CriticalFacPt][RandPos];
		Seq[CriticalFacPt].erase(begin(Seq[CriticalFacPt]) + RandPos);

		RefreshFBTime_InFactory_WYT(Seq[CriticalFacPt], fbTime, RandPos, RandPos - 1);
		int bestPos = -1;
		int temSpan = FindBestInsertionPositon_B_WYT(bestPos, Job, Seq[CriticalFacPt], fbTime);
		
		if (temSpan < FactorySpan[CriticalFacPt]) //����Ч
		{
			//����FactorySpan
			FactorySpan[CriticalFacPt] = temSpan;
			Seq[CriticalFacPt].insert(Seq[CriticalFacPt].begin() + bestPos, Job);
			RefreshFBTime_InFactory_WYT(Seq[CriticalFacPt], fbTime, bestPos, bestPos);
			Counter = 0;
		}
		else
		{
			Seq[CriticalFacPt].insert(begin(Seq[CriticalFacPt]) + RandPos, Job);
			RefreshFBTime_InFactory_WYT(Seq[CriticalFacPt], fbTime, RandPos, RandPos);
			++Counter;
		}
		if (Counter >= Seq[CriticalFacPt].size())
		{
			break;
		}
	}
	//int FinalMakespan = GetFspan_Block(Seq);
	return *max_element(begin(FactorySpan), end(FactorySpan));
}

//�ؼ������ڲ�����

int nei3(vector<vector<int>>& Seq, vector<int>& FactorySpan)
{
	//�ҵ��ؼ�����
	int TempSpan = INT_MIN;
	int CriticalFactory = -1;
	for (int f = 0; f < Seq.size(); f++)
	{
		if (TempSpan < FactorySpan[f])
		{
			TempSpan = FactorySpan[f];
			CriticalFactory = f;
		}
	}

	vector<int> TempSeq = Seq[CriticalFactory];

	//�ڹؼ����������ѡȡ������ͬ�Ĺ���
	int Jobpt1, Jobpt2;
	do
	{
		Jobpt1 =  wyt_rand(Seq[CriticalFactory].size());
		Jobpt2 =  wyt_rand(Seq[CriticalFactory].size());
	} while (Jobpt1 == Jobpt2);
	if (Jobpt1 > Jobpt2)
	{
		swap(Jobpt1, Jobpt2);
	}

	//��������������λ��
	int TempJob = Seq[CriticalFactory][Jobpt1];
	Seq[CriticalFactory][Jobpt1] = Seq[CriticalFactory][Jobpt2];
	Seq[CriticalFactory][Jobpt2] = TempJob;

	//�ж��Ƿ�����µĽ�
	int TempSpan1 = GetFspan_BLOCK(Seq[CriticalFactory]);
	if (TempSpan1 < TempSpan)
	{
		TempSpan = TempSpan1;
		TempSeq = Seq[CriticalFactory];
	}
	Seq[CriticalFactory] = TempSeq;

	return *max_element(begin(FactorySpan), end(FactorySpan));
}

int nei3_WYT(vector<vector<int>>& Seq, vector<int>& FactorySpan, FBTime& fbTime)
{
	//�ҵ��ؼ�����
	int TempSpan = INT_MIN;
	int CriticalFactory = -1;
	for (int f = 0; f < Seq.size(); f++)
	{
		if (TempSpan < FactorySpan[f])
		{
			TempSpan = FactorySpan[f];
			CriticalFactory = f;
		}
	}

	vector<int> TempSeq = Seq[CriticalFactory];

	//�ڹؼ����������ѡȡ������ͬ�Ĺ���
	int Jobpt1, Jobpt2;
	do
	{
		Jobpt1 =  wyt_rand(Seq[CriticalFactory].size());
		Jobpt2 =  wyt_rand(Seq[CriticalFactory].size());
	}
	while (Jobpt1 == Jobpt2);

	if(Jobpt1 > Jobpt2)
	{
		swap(Jobpt1, Jobpt2);
	}

	int span = GetFSpan_BLOCK_After_Swap_Two_Job_WYT(Seq[CriticalFactory], Jobpt1, Jobpt2, fbTime);		

	//vector<int> sss = Seq[CriticalFactory];
	//swap(sss[Jobpt1], sss[Jobpt2]);
	//int aa = GetFspan_BLOCK(sss);
	//assert(aa == span);
	if (span < FactorySpan[CriticalFactory])
	{
		FactorySpan[CriticalFactory] = span;
		swap(Seq[CriticalFactory][Jobpt1], Seq[CriticalFactory][Jobpt2]); //��������������λ��
		int span1 = RefreshFBTime_InFactory_WYT(Seq[CriticalFactory], fbTime, Jobpt1, Jobpt2);
		assert(span1 == span);
	}	

	//int FinalMakespan = GetFspan_Block(Seq);
	return *max_element(begin(FactorySpan), end(FactorySpan));
}

//(û��)������Թؼ������ڲ���
int VNS1(vector<vector<int>>& Seq, int& Span, vector<int> DesJobSeq, int d, vector<int>& FactorySpan)
{
	int FlagMax = 3;
	int Flag = 1;
	do
	{
		vector<vector<int>> TempSeq = Seq;
		int TempSpan = Span;
		if (Flag == 2)
			TempSpan = strategy6(TempSeq, FactorySpan);
		else if (Flag == 1)
			TempSpan = strategy1(TempSeq, DesJobSeq, d, FactorySpan);
		else if (Flag == 3)
			TempSpan = nei3(TempSeq, FactorySpan);


		if (TempSpan < Span)
		{
			Flag = 1;
			Seq = TempSeq;
			Span = TempSpan;
		}
		else
			Flag = Flag + 1;
	}
	while (Flag <= FlagMax);
	return Span;
}

//����NEH��
int VNS2(vector<vector<int>>& Seq, int& Span, vector<int>& FactorySpan)
{
	int FlagMax = 2;
	int Flag = 1;
	do
	{
		vector<vector<int>> TempSeq = Seq;
		int TempSpan = Span;

		if (Flag == 1)
		{
			TempSpan = nei2(TempSeq, FactorySpan);
		}
		else if (Flag == 2)
		{
			TempSpan = strategy6(TempSeq, FactorySpan);
		}
		

		if (TempSpan < Span)
		{
			Flag = 1;
			Seq = TempSeq;
			Span = TempSpan;
		}
		else
			Flag = Flag + 1;
	}while (Flag <= FlagMax);

	return Span;
}

int VNS2_WYT(vector<vector<int>>& Seq, int& Span, vector<int>& FactorySpan, FBTime& fbTime)
{
	int count = 1;
	do
	{
		int TempSpan = Span;
		if (count == 1)
		{
			TempSpan = nei2_WYT(Seq, FactorySpan, fbTime);
		}
		else if (count == 2)
		{
			TempSpan = strategy6_WYT(Seq, FactorySpan, fbTime);
		}

		if (TempSpan < Span)
		{
			count = 1;
			Span = TempSpan;
		}
		else
		{
			count = count + 1;
		}
	}
	while (count <= 2);
	return Span;
}


int IG_ZCY(long TimeLimit, int d, double Tem, int KLen)
{
	int table_len = 60; //��񳤶ȡ���������
	long InitTime = GetElapsedProcessTime();

	vector<vector<int>> Seq;
	int Span;
	vector<int> FactorySpan(gFactory, 0);

	//���ɳ�ʼ��
    Span = NEH2_en_B_ZCY(Seq,FactorySpan);
	
	Span = VNS2(Seq, Span, FactorySpan);
	

	vector<vector<int>> BestSeqSofar = Seq;  //��ǰ�������
	int BestValueSofar = Span; //��ǰ���makspan
	vector<int> BestFactorySpanSofar = FactorySpan; //��ǰ���й�����makespan

	vector<vector<int>> TempSeq = Seq;
	int TempSpan = Span;
	vector<int> TempFactorySpan = FactorySpan;

	vector<int> DesJobSeq;

	double Temperature = GetTemperature(Tem);

	vector<int> List1(table_len);
	for (int i = 0; i < table_len; i++)
	{
		List1[i] = wyt_rand(1, 4);
	}

	vector<int> List2; //good list �õĲ��Ա���
	int iteratorCount = 0;

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		int num = wyt_rand(10);
		if (num < 1)
		{
			List2.clear();
			//Stage one ������
			for (int c = 0; c < table_len; c++)
			{
				switch (List1[c])
				{
				case 1:
					TempSpan = strategy1(TempSeq, DesJobSeq, d, TempFactorySpan);
					break;
				case 2:
					TempSpan = strategy2(TempSeq, TempFactorySpan); //���					
					break;
				case 3:
					TempSpan = strategy5(TempSeq, TempFactorySpan); //���
					break;                                 
				case 4:
					TempSpan = strategy6(TempSeq, TempFactorySpan); //���
					break;
				}

				//�ж��Ƿ��иĽ�
				if (TempSpan < Span)
				{
					Span = TempSpan;
					Seq = TempSeq;
					FactorySpan = TempFactorySpan;
					if (Span < BestValueSofar)
					{
						BestValueSofar = Span;
						BestSeqSofar = Seq;
						BestFactorySpanSofar = FactorySpan;
					}
					List2.push_back(List1[c]);
				}
				else
				{
					TempSeq = Seq;
					TempSpan = Span;
					TempFactorySpan = FactorySpan;
				}
			}
			for (int i = 0; i < KLen; i++)
			{
				List1[i] = i < List2.size() ? List2[i] : wyt_rand(1, 4);
			}

			for (int i = KLen; i < List1.size(); i++)
			{
				List1[i] = wyt_rand(1, 4);
			}

			//Stage two ��Թؼ�������
			for (int i = 0; i < gJobs / 2; i++)
			{
				TempSpan = nei3(TempSeq, TempFactorySpan); //���				
			}
		}
		else
		{
			TempSpan = strategy1(TempSeq, DesJobSeq, d, TempFactorySpan);
			for (int i = 0; i < gJobs / 2 ; i++)
			{
				TempSpan = strategy6(TempSeq, TempFactorySpan); //���				
			}
		}

		//Acceptance
		if (TempSpan < Span)
		{

			Seq = TempSeq;
			Span = TempSpan;
			FactorySpan = TempFactorySpan;
			if (Span < BestValueSofar)
			{
				BestValueSofar = Span;
				BestSeqSofar = Seq;
				BestFactorySpanSofar = FactorySpan;
			}
		}
		else
		{
			double t = exp((Span - TempSpan) / Temperature); //�Ĺ���ģ���˻�
			if (wyt_rand(0, RAND_MAX) < int(RAND_MAX * t)) //if (rand() < int(RAND_MAX * t))
			{
				Seq = TempSeq;
				Span = TempSpan;
				FactorySpan = TempFactorySpan;
			}
			else
			{
				TempSeq = Seq;
				TempSpan = Span;
				TempFactorySpan = FactorySpan;
			}
		}
		++iteratorCount;
	}
	CheckChrom1(BestSeqSofar, BestValueSofar);
	cout << "(" << setw(6) << iteratorCount << ")";
	return BestValueSofar;
}

int IG_ZCY_WYT(long TimeLimit, int d, double Tem, int KLen)
{
	int table_len = 60; //��񳤶ȡ���������
	long InitTime = GetElapsedProcessTime();

	vector<vector<int>> Seq;
	int Span;
	vector<int> FactorySpan(gFactory, 0);
	FBTime FB_Time(gJobs, gMachine);

	//���ɳ�ʼ��
	Span = NEH2_en_B_WYT(Seq, FactorySpan, FB_Time);
	Span = VNS2_WYT(Seq, Span, FactorySpan, FB_Time);
	
	vector<vector<int>> BestSeqSofar = Seq;
	int BestValueSofar = Span;
	vector<int> BestFactorySpanSofar = FactorySpan;
	
	vector<vector<int>> TempSeq = Seq;
	int TempSpan = Span;
	vector<int> TempFactorySpan = FactorySpan;
	FBTime TempFB_Time = FB_Time;

	vector<int> DesJobSeq;

	double Temperature = GetTemperature(Tem);

	vector<int> List1(table_len);

	for (int i = 0; i < table_len; i++)
	{
		List1[i] = wyt_rand(1,4);
	}
	vector<int> List2; //good list �õĲ��Ա���
	int iteratorCount = 0; 
	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		FBTime fb_time(gJobs, gMachine);
		int num = wyt_rand(10);

		if (num < 1 )
		{
			List2.clear();
			//Stage one ������
			for (int c = 0; c < table_len; c++)
			{
				switch (List1[c])
				{
				case 1:
					TempSpan = strategy1_WYT(TempSeq, DesJobSeq, d, TempFactorySpan, TempFB_Time);					
					break;
				case 2:					
					TempSpan = strategy2_WYT(TempSeq, TempFactorySpan, TempFB_Time); //���					
					break;
				case 3:
					TempSpan = strategy5_WYT(TempSeq, TempFactorySpan, TempFB_Time); //���
					break;
				case 4:
					TempSpan = strategy6_WYT(TempSeq, TempFactorySpan, TempFB_Time); //���
					break;
				}

				//�ж��Ƿ��иĽ�
				if (TempSpan < Span)
				{
					Span = TempSpan;
					Seq = TempSeq;
					FactorySpan = TempFactorySpan;
					FB_Time = TempFB_Time;
					if (Span < BestValueSofar)
					{
						BestValueSofar = Span;
						BestSeqSofar = Seq;
						
					}
					List2.push_back(List1[c]);
				}
				else
				{
					TempSeq = Seq;
					TempSpan = Span;
					TempFactorySpan = FactorySpan;
					TempFB_Time = FB_Time;
				}			
			}

			for (int i = 0; i < KLen; i++)
			{
				List1[i] = i < List2.size() ? List2[i]: wyt_rand(1,4);
			}

			for (int i = KLen; i < List1.size(); i++)
			{
				List1[i] = wyt_rand(1, 4);
			}
			
			//Stage two ��Թؼ�������
			for (int i = 0; i < gJobs / 2; i++)
			{
				TempSpan = nei3_WYT(TempSeq, TempFactorySpan, TempFB_Time); //���				
			}
		}
		else
		{
			TempSpan = strategy1_WYT(TempSeq, DesJobSeq, d, TempFactorySpan, TempFB_Time);			
			for (int i = 0; i < gJobs / 2; i++)
			{
				TempSpan = strategy6_WYT(TempSeq, TempFactorySpan, TempFB_Time); //���				
			}
		}
		
		//Acceptance
		if (TempSpan < Span)
		{

			Seq = TempSeq;
			Span = TempSpan;
			FactorySpan = TempFactorySpan;
			FB_Time = TempFB_Time;
			if (Span < BestValueSofar)
			{
				BestValueSofar = Span;
				BestSeqSofar = Seq;
			}
		}
		else
		{
			double t = exp((Span - TempSpan) / Temperature); //�Ĺ���ģ���˻�
			if (wyt_rand(0, RAND_MAX) < int(RAND_MAX * t)) //if (rand() < int(RAND_MAX * t))
			{
				Seq = TempSeq;
				Span = TempSpan;
				FactorySpan = TempFactorySpan;
				FB_Time = TempFB_Time;
			}
			else
			{
				TempSeq = Seq;
				TempSpan = Span;
				TempFactorySpan = FactorySpan;
				TempFB_Time = FB_Time;
			}
		}
		++iteratorCount;
	}
	CheckChrom1(BestSeqSofar, BestValueSofar);
	//cout << "(" << setw(6) << iteratorCount << ")";
	return BestValueSofar;
}

int IGZCY_WYT_Curve(long TimeLimit, int d, double Tem, int KLen, int No)
{
	int table_len = 60; //��񳤶ȡ���������
	long InitTime = GetElapsedProcessTime();

	vector<vector<int>> Seq;
	int Span;
	vector<int> FactorySpan(gFactory, 0);
	FBTime FB_Time(gJobs, gMachine);

	//���ɳ�ʼ��
	Span = NEH2_en_B_WYT(Seq, FactorySpan, FB_Time);
	Span = VNS2_WYT(Seq, Span, FactorySpan, FB_Time);

	vector<vector<int>> BestSeqSofar = Seq;
	int BestValueSofar = Span;
	vector<int> BestFactorySpanSofar = FactorySpan;

	vector<vector<int>> TempSeq = Seq;
	int TempSpan = Span;
	vector<int> TempFactorySpan = FactorySpan;
	FBTime TempFB_Time = FB_Time;

	vector<int> DesJobSeq;

	double Temperature = GetTemperature(Tem);

	vector<int> List1(table_len);

	for (int i = 0; i < table_len; i++)
	{
		List1[i] = wyt_rand(1, 4);
	}
	vector<int> List2; //good list �õĲ��Ա���
	int iteratorCount = 0;

	//����һ��txt�ļ�
	string FileDirectory = "Result\\";

	ofstream ofile;
	ofile.open(FileDirectory + "IGZCY_WYT_Curve"+ ".txt"); //��ͬ���㷨
	//ostringstream str;
	//str << "IGZCY_WYT_Curve" << No << ".txt";                //
	//ofstream ofile;
	//ofile.open(str.str());
	int LocalValue; long LocalTime;
	//�����ʼ���Լ���ʼʱ��
	LocalValue = BestValueSofar;                             //
	LocalTime = GetElapsedProcessTime() - InitTime;         //
	ofile << LocalTime << "\t" << LocalValue << "\t" << endl;

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		FBTime fb_time(gJobs, gMachine);
		int num = wyt_rand(10);

		if (num < 1)
		{
			List2.clear();
			//Stage one ������
			for (int c = 0; c < table_len; c++)
			{
				switch (List1[c])
				{
				case 1:
					TempSpan = strategy1_WYT(TempSeq, DesJobSeq, d, TempFactorySpan, TempFB_Time);
					break;
				case 2:
					TempSpan = strategy2_WYT(TempSeq, TempFactorySpan, TempFB_Time); //���					
					break;
				case 3:
					TempSpan = strategy5_WYT(TempSeq, TempFactorySpan, TempFB_Time); //���
					break;
				case 4:
					TempSpan = strategy6_WYT(TempSeq, TempFactorySpan, TempFB_Time); //���
					break;
				}

				//�ж��Ƿ��иĽ�
				if (TempSpan < Span)
				{
					Span = TempSpan;
					Seq = TempSeq;
					FactorySpan = TempFactorySpan;
					FB_Time = TempFB_Time;
					if (Span < BestValueSofar)
					{
						BestValueSofar = Span;
						BestSeqSofar = Seq;

					}
					List2.push_back(List1[c]);
				}
				else
				{
					TempSeq = Seq;
					TempSpan = Span;
					TempFactorySpan = FactorySpan;
					TempFB_Time = FB_Time;
				}
			}

			for (int i = 0; i < KLen; i++)
			{
				List1[i] = i < List2.size() ? List2[i] : wyt_rand(1, 4);
			}

			for (int i = KLen; i < List1.size(); i++)
			{
				List1[i] = wyt_rand(1, 4);
			}

			//Stage two ��Թؼ�������
			for (int i = 0; i < gJobs / 2; i++)
			{
				TempSpan = nei3_WYT(TempSeq, TempFactorySpan, TempFB_Time); //���				
			}
		}
		else
		{
			TempSpan = strategy1_WYT(TempSeq, DesJobSeq, d, TempFactorySpan, TempFB_Time);
			for (int i = 0; i < gJobs / 2; i++)
			{
				TempSpan = strategy6_WYT(TempSeq, TempFactorySpan, TempFB_Time); //���				
			}
		}

		//Acceptance
		if (TempSpan < Span)
		{

			Seq = TempSeq;
			Span = TempSpan;
			FactorySpan = TempFactorySpan;
			FB_Time = TempFB_Time;
			if (Span < BestValueSofar)
			{
				BestValueSofar = Span;
				BestSeqSofar = Seq;
			}
		}
		else
		{
			double t = exp((Span - TempSpan) / Temperature); //�Ĺ���ģ���˻�
			if (wyt_rand(0, RAND_MAX) < int(RAND_MAX * t)) //if (rand() < int(RAND_MAX * t))
			{
				Seq = TempSeq;
				Span = TempSpan;
				FactorySpan = TempFactorySpan;
				FB_Time = TempFB_Time;
			}
			else
			{
				TempSeq = Seq;
				TempSpan = Span;
				TempFactorySpan = FactorySpan;
				TempFB_Time = FB_Time;
			}
		}
		++iteratorCount;

		LocalValue = BestValueSofar;                             //
		LocalTime = GetElapsedProcessTime() - InitTime;         //

		//���õ���LocalValue�Լ�LocalTimeд���ļ�����

		ofile << LocalTime << "\t" << LocalValue << "\t" << endl;
	}
	ofile.close();
	CheckChrom1(BestSeqSofar, BestValueSofar);
	//cout << "(" << setw(6) << iteratorCount << ")";
	return BestValueSofar;
}
