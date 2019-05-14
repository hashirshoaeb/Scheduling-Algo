#include <iostream>
#include<math.h>
#include<list>

using namespace std;

//schedulling algorithms
//FCFS
void FCFS(const int process[], const int burst_time[], const int priority[])
{
	// variables decelaration
	const int size = 4;
	int w_time[size]; w_time[0] = 0; int T_time[size]; T_time[0] = 0;
	float avg_w_time = 0.0, avg_T_time = 0.0;

	// calculating avg waiting time
	for (int i = 1; i < size; i++)
	{
		w_time[i] = burst_time[i - 1] + w_time[i - 1];
		avg_w_time = avg_w_time + w_time[i];
	}
	//calculating avg turn around time
	for (int i = 0; i < size; i++)
	{
		T_time[i] = w_time[i] + burst_time[i];
		avg_T_time = avg_T_time + T_time[i];
	}
	//display 
	for (int i = 0; i < size; i++)
	{
		cout << "process " << process[i] << " burst time " << burst_time[i] << " waiting time " << w_time[i] << " turn around time " << T_time[i] << " priority " << priority[i] << endl;
	}
	cout << "AVERAGE WAITING TIME is = " << avg_w_time / 4.0 << endl;
	cout << "AVERAGE TURN AROUND TIME is = " << avg_T_time / 4.0 << endl;
}

//SJF non premptive
void sorting(int process[], int burst_time[])
{
	const int size = 4;
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (burst_time[i] > burst_time[j])
			{
				//swap burst time;
				int temp = burst_time[i];
				burst_time[i] = burst_time[j];
				burst_time[j] = temp;
				//swap processes
				temp = process[i];
				process[i] = process[j];
				process[j] = temp;
			}
		}
	}
}
void SJF(const int process[], const int burst_time[], const int priority[])
{
	int sjfpro[4], sjfburst[4];
	for (int i = 0; i < 4; i++)
	{
		sjfpro[i] = process[i];
		sjfburst[i] = burst_time[i];
	}
	sorting(sjfpro, sjfburst);
	FCFS(sjfpro, sjfburst, priority);
}

//Priority Scheduling
void sorting(int process[], int burst_time[], int priority[])
{
	const int size = 4;
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (priority[i] > priority[j])
			{
				//swap burst time;
				int temp = burst_time[i];
				burst_time[i] = burst_time[j];
				burst_time[j] = temp;
				//swap processes
				temp = process[i];
				process[i] = process[j];
				process[j] = temp;
				//swap priority
				temp = priority[i];
				priority[i] = priority[j];
				priority[j] = temp;
			}
		}
	}
}
void PS(const int process[], const int burst_time[], const int priority[])
{
	int rrpro[4], rrburst[4], rrpriority[4];
	for (int i = 0; i < 4; i++)
	{
		rrpro[i] = process[i];
		rrburst[i] = burst_time[i];
		rrpriority[i] = priority[i];
	}
	sorting(rrpro, rrburst, rrpriority);
	FCFS(rrpro, rrburst, rrpriority);
}
//RR
void RR(int TQ, const int BurstTime[])
{
	int BT[4];
	int BuT[4];
	for (int i = 0; i < 4; i++)
	{
		BuT[i] = BT[i] = BurstTime[i];
	}
	int TAT[4];
	int count = 1;
	while (true)
	{
		for (int i = 0; i<4; i++)
		{
			for (int j = 0; j< TQ; j++)
			{
				if (BuT[i] == 0)
					break;
				else
				{
					BuT[i] = BuT[i] - 1;
					if (BuT[i] == 0)
						TAT[i] = count;
					count++;
				}
			}
		}
		double sum = 0;
		for (int i = 0; i < 4; i++)
		{
			sum = BuT[i] + sum;
		}
		if (sum == 0)
		{
			break;
		}
	}
	int WT[4];
	for (int i = 0; i<4; i++)
	{
		WT[i] = TAT[i] - BT[i];
	}
	for (int i = 0; i < 4; i++)
	{
		cout << "process " << (i + 1) << " burst time " << BT[i] << " waiting time " << WT[i] << " turn around time " << TAT[i] << endl;
	}
	cout << endl;
	double sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum = WT[i] + sum;
	}
	double average = sum / 4;
	double s = 0;
	for (int i = 0; i < 4; i++)
	{
		s = TAT[i] + s;
	}
	double avg = s / 4;
	cout << "AVERAGE WAITING TIME is = " << average << endl;
	cout << "AVERAGE TURN AROUND TIME is = " << avg << endl;
}

int main()
{
	//const int size = 4;
	// process ids
	// let us consider that arrival time is same for all processes
	const int processes[] = { 1, 2, 3, 4 };
	const int  burst_time[] = { 21, 3, 6, 2 }; //21, 3, 6, 2
	const int priority[] = { 2, 1, 4, 3 }; // 2, 1, 4, 3
	int Quantum = 4;
	cout << "FCFS" << endl;
	FCFS(processes, burst_time, priority);
	cout << "SJF" << endl;
	SJF(processes, burst_time, priority);
	cout << "PS" << endl;
	PS(processes, burst_time, priority);
	cout << "RR" << endl;
	RR(Quantum, burst_time);

	system("Pause");
	return 0;
}

