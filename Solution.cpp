#include <iostream>
#include <windows.h>

using std::cin;
using std::cout;

volatile std::pair<int, int> mm;

DWORD WINAPI min_max(LPVOID arr)
{
	int n = *(int*)(arr);
	int* a = (int*)arr;

	mm.first = a[1];
	mm.second = a[1];
	for (int i = 2; i <= n; i++)
	{
		mm.first = min(mm.first, a[i]);
		Sleep(7);
		mm.second = max(mm.second, a[i]);
		Sleep(7);
	}

	cout << "Minimum: " << mm.first <<'\n';
	cout << "Maximum: " << mm.second << '\n';

	return 0;
}

volatile int avrg;

DWORD WINAPI average(LPVOID arr)
{
	int n = *(int*)(arr);
	int* a = (int*)arr;

	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += a[i];
		Sleep(12);
	}

	avrg = sum / n;
	cout << "Average: " << avrg << '\n';
	return 0;
}

int main()
{
	int n;
	cout << "Enter array dimensity\n";
	cin >> n;

	if (n <= 0)
	{
		cout << "illegal dimensity\n";
		return 0;
	}

	cout << "Enter Array: \n";
	int* numbers = new int[n + 1];
	numbers[0] = n;
	for (int i = 1; i <= n; i++)
	{
		cin >> numbers[i];
	}

	DWORD min_maxID;
	HANDLE hMin_Max = CreateThread(NULL, 0, min_max, numbers, NULL, &min_maxID);
	if (!hMin_Max)
	{
		return GetLastError();
	}

	DWORD averageID;
	HANDLE hAverage = CreateThread(NULL, 0, average, numbers, NULL, &averageID);
	if (!hAverage)
	{
		return GetLastError();
	}

	WaitForSingleObject(hMin_Max, INFINITE);
	CloseHandle(hMin_Max);
	WaitForSingleObject(hAverage, INFINITE);
	CloseHandle(hAverage);

	cout << "Final array: \n";
	for (int i = 1; i <= n; i++)
	{
		if (numbers[i] == mm.first || numbers[i] == mm.second)
		{
			numbers[i] = avrg;
		}

		cout << numbers[i] << ' ';
	}

	cout << '\n';
	system("pause");
	return 0;
}
