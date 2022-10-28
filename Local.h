#pragma once
int Swap(vector<int>& Seq)
{
	int Energy = GetFEnergy_BLOCK(Seq);
	vector<int> TempSeq = Seq;
	//srand(100);
	int Job_1 = 0, Job_2 = 0;
	while (Job_1 == Job_2)
	{
		Job_1 =  wyt_rand(Seq.size());
		Job_2 =  wyt_rand(Seq.size());
	}
	//交换两个工件
	int Job = Job_1;
	TempSeq[Job_1] = Job_2;
	TempSeq[Job_2] = Job;

	int TempEnergy = GetFEnergy_BLOCK(Seq);

	if (Energy >= TempEnergy)
	{
		Energy = TempEnergy;
		Seq = TempSeq;
	}
	else
	{
		TempEnergy = Energy;
		TempSeq = Seq;
	}
	
	return TempEnergy;

}

int swap_block_1(vector<int>& Seq1,int d)
{
	int TempEnergy = 0;
	int Energy = GetFEnergy_BLOCK(Seq1);
	vector<int> Seq = Seq1;
	if (Seq.size() <= d+d)
		TempEnergy = Swap(Seq);
	else
	{
		//srand(time(0));
		//随机选择作业块
		int Job_1 = -1, Job_2 = -1;
		vector<int> block_1(d, 0);
		vector<int> block_2(d, 0);
		vector<int> sign(Seq.size(), 0);//标记已选择的作业块
		//确定作业块1
		Job_1 =  wyt_rand(Seq.size());
		if (Job_1 > Seq.size() - d)
		{
			for (int i = 0; i < d; i++)
			{
				block_1[i] = Seq[Seq.size() - d + i];
				sign[Seq.size() - d + i] = 1;
			}
		}


		else
		{
			for (int i = 0; i < d; i++)
			{
				block_1[i] = Seq[Job_1 + i];
				sign[Job_1 + i] = 1;
			}
		}


		//根据作业块一确定作业块2
		int Count = 0;
		Job_2 =  wyt_rand(Seq.size());
		if (sign[Job_2] == 1)
			Job_2 =  wyt_rand(Seq.size());

		while (Count = 0 || sign[Job_2] != 1)
		{


			if (Job_2 > Seq.size() - d)
			{
				if (sign[Seq.size() - d] == 1)
					Count = 0;
				else
					for (int i = 0; i < d; i++)
					{
						block_2[i] = Seq[Seq.size() - d + i];
						Count++;
					}
				sign[Job_2] = 1;
			}
			else
			{
				if (sign[Job_2 + d] == 1)
					Count = 0;
				else
					for (int i = 0; i < d; i++)
					{
						block_2[i] = Seq[Job_2 + i];
						Count++;
					}
				sign[Job_2] = 1;
			}

		}
		//交换两个作业块
		vector<int> block = block_1;

		if (Job_1 > Seq.size() - d)
			for (int i = 0; i < d; i++)
				Seq[Seq.size() - d + i] = block_2[i];
		else
			for (int i = 0; i < d; i++)
				Seq[Job_1 + i] = block_2[i];

		if (Job_2 > Seq.size() - d)
			for (int i = 0; i < d; i++)
				Seq[Seq.size() - d + i] = block[i];
		else
			for (int i = 0; i < d; i++)
				Seq[Job_2 + i] = block[i];


		TempEnergy = GetFEnergy_BLOCK(Seq);

		if (Energy >= TempEnergy)
		{
			Seq1 = Seq;
			Energy = TempEnergy;

		}
		else
		{
			Seq = Seq1;
			TempEnergy = Energy;
		}

	}
	return TempEnergy;
}

int swap_block(vector<int>& Seq1, int d)
{
	int TempEnergy = 0;
	int Energy = GetFEnergy_BLOCK(Seq1);
	vector<int> Seq = Seq1;
	if (Seq.size() <= d + d)
		TempEnergy = Swap(Seq);
	else
	{
		//srand(time(0));
		//随机选择作业块
		int Job_1 = -1, Job_2 = -1;
		vector<int> block_1(d, 0);
		vector<int> block_2(d, 0);
		vector<int> sign(Seq.size(), 0);//标记已选择的作业块
		//确定作业块1
		Job_1 =  wyt_rand(Seq.size());
		if (Job_1 > Seq.size() - d)
		{
			for (int i = 0; i < d; i++)
			{
				block_1[i] = Seq[Seq.size() - d + i];
				sign[Seq.size() - d + i] = 1;
			}
		}


		else
		{
			for (int i = 0; i < d; i++)
			{
				block_1[i] = Seq[Job_1 + i];
				sign[Job_1 + i] = 1;
			}
		}


		//根据作业块一确定作业块2
		int Count = 0;
		//Job_2 =  wyt_rand(Seq.size());
		//if (sign[Job_2] == 1)


		while (Count = 0)
		{
			int J =  wyt_rand(Seq.size());
			while (sign[J] == 1)
			{
				J =  wyt_rand(Seq.size());
			}
			Job_2 = J;

			if (Job_2 > Seq.size() - d)
			{
				if (sign[Seq.size() - d] == 1)
					Count = 0;
				else
					for (int i = 0; i < d; i++)
					{
						block_2[i] = Seq[Seq.size() - d + i];
						Count++;
						//sign[Job_2] = 0;
					}
				//sign[Job_2] = 1;
			}
			else
			{
				if (sign[Job_2 + d] == 1)
					Count = 0;
				else
					for (int i = 0; i < d; i++)
					{
						block_2[i] = Seq[Job_2 + i];
						Count++;
						//sign[Job_2] = -1;
					}
				//sign[Job_2] = 1;
			}

		}
		//交换两个作业块
		vector<int> block = block_1;

		if (Job_1 > Seq.size() - d)
			for (int i = 0; i < d; i++)
				Seq[Seq.size() - d + i] = block_2[i];
		else
			for (int i = 0; i < d; i++)
				Seq[Job_1 + i] = block_2[i];

		if (Job_2 > Seq.size() - d)
			for (int i = 0; i < d; i++)
				Seq[Seq.size() - d + i] = block[i];
		else
			for (int i = 0; i < d; i++)
				Seq[Job_2 + i] = block[i];


		TempEnergy = GetFEnergy_BLOCK(Seq);

		if (Energy >= TempEnergy)
		{
			Seq1 = Seq;
			Energy = TempEnergy;

		}
		else
		{
			Seq = Seq1;
			TempEnergy = Energy;
		}

	}
	return TempEnergy;
}

int Insert(vector<int>& Seq)//insert_f, insert_b
{
	//find two distinct elements randly;
	unsigned short  pt1, pt2, Ward;
	do
	{
		pt1 =  wyt_rand(Seq.size());
		pt2 =  wyt_rand(Seq.size());
	} while (pt1 == pt2);

	if (pt2 < pt1)
	{
		unsigned short  temp = pt2;
		pt2 = pt1;
		pt1 = temp;
	}

	Ward = wyt_rand(2);
	//insert foreword;
	if (Ward)
	{
		unsigned short  temp = Seq[pt2];
		do
		{
			Seq[pt2] = Seq[pt2 - 1];
			pt2 = pt2 - 1;
		} while (pt2 > pt1);
		Seq[pt2] = temp;

	}
	else
	{
		// insert backword;
		unsigned short  temp = Seq[pt1];
		do
		{
			Seq[pt1] = Seq[pt1 + 1];
			pt1 = pt1 + 1;
		} while (pt1 < pt2);
		Seq[pt1] = temp;
	}

	int tempEnergy = GetFEnergy_BLOCK(Seq);
	return tempEnergy;
}



int LS_N_NIG(vector<vector<int>>& Seq)//只对关键工厂进行局部搜索
{
	vector<int>FactorySpan(Seq.size(), 0);
	for (int f = 0; f < Seq.size(); f++)
		FactorySpan[f] = GetFspan_BLOCK(Seq[f]);

	int CriticalFacPt = -1;
	int TempFacSpan = INT_MIN;
	for (int i = 0; i < FactorySpan.size(); i++)//找到关键工厂
	{
		if (FactorySpan[i] > TempFacSpan)
		{
			TempFacSpan = FactorySpan[i];
			CriticalFacPt = i;
		}
	}
	int Minor_CriticalFacPt = -1;//找到次要的工厂
	int Minor_TempFacSpan = INT_MIN;
	for (int i = 0; i < CriticalFacPt; i++)
	{
		if (FactorySpan[i] > Minor_TempFacSpan)
		{
			Minor_TempFacSpan = FactorySpan[i];
			Minor_CriticalFacPt = i;
		}
	}

	for (int i = CriticalFacPt + 1; i < FactorySpan.size(); i++)
	{
		if (FactorySpan[i] > Minor_TempFacSpan)
		{
			Minor_TempFacSpan = FactorySpan[i];
			Minor_CriticalFacPt = i;
		}
	}

	int Counter = 0;
	vector<int>TempCriticalFacSeq = Seq[CriticalFacPt];
	vector<int>Minor_TempCriticalFacSeq = Seq[Minor_CriticalFacPt];
	while (Counter < Seq[CriticalFacPt].size())
	{
		//随机选择一个工件
		int MakeSpan = *max_element(FactorySpan.begin(), FactorySpan.end());
		int RandNum_1 =  wyt_rand(TempCriticalFacSeq.size());
		int Job_1 = TempCriticalFacSeq[RandNum_1];

		int RandNum_2 =  wyt_rand(Minor_TempCriticalFacSeq.size());
		int Job_2 = Minor_TempCriticalFacSeq[RandNum_2];

		//TempCriticalFacSeq.erase(TempCriticalFacSeq.begin() + RandNum);
		vector<vector<int>>TempSeq = Seq;

		int TempMakespan = 0;
		Seq[CriticalFacPt][RandNum_1] = Job_2;
		Seq[Minor_CriticalFacPt][RandNum_2] = Job_1;

		// ector<int> TempFactoryspan(Seq.size(), 0);
		TempMakespan = GetFspan_Block(Seq);
		if (TempMakespan >= MakeSpan)//若交换无效,则取消上次的交换
		{
			Seq = TempSeq;
			Counter++;
		}
		else//若有效
		{
			//更新FactorySpan
			FactorySpan[CriticalFacPt] = GetFspan_BLOCK(Seq[CriticalFacPt]);
			FactorySpan[Minor_CriticalFacPt] = GetFspan_BLOCK(Seq[Minor_CriticalFacPt]);
			TempFacSpan = INT_MIN;
			//寻找新的关键工厂
			for (int i = 0; i < FactorySpan.size(); i++)
			{
				if (FactorySpan[i] > TempFacSpan)
				{
					TempFacSpan = FactorySpan[i];
					CriticalFacPt = i;
				}
			}
			int Minor_TempFacSpan = INT_MIN;
			for (int i = 0; i < CriticalFacPt; i++)
			{
				if (FactorySpan[i] > Minor_TempFacSpan)
				{
					Minor_TempFacSpan = FactorySpan[i];
					Minor_CriticalFacPt = i;
				}
			}

			for (int i = CriticalFacPt + 1; i < FactorySpan.size(); i++)
			{
				if (FactorySpan[i] > Minor_TempFacSpan)
				{
					Minor_TempFacSpan = FactorySpan[i];
					Minor_CriticalFacPt = i;
				}
			}
			TempCriticalFacSeq = Seq[CriticalFacPt];
			Minor_TempCriticalFacSeq = Seq[Minor_CriticalFacPt];
			Counter = 0;

		}

	}
	int FinalMakespan = GetFspan_Block(Seq);
	return FinalMakespan;
}


//接受准则
