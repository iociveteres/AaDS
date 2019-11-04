#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <windows.h>

class Set
{
private: // закрытая часть класса - данные 
	static const int N = 32; // мощность универсума 
	int n; // мощность множества
	char S, * A; // тег и память для множества
public: // открытая часть - функции для работы с множеством

	int power()
	{
		return n;
	} // получение мощности

	~Set()
	{
		delete[] A;
	} // деструктор

	Set& operator &= (const Set& B)
	{
		Set C(*this);
		n = 0;
		for (int i = 0; i < C.n; ++i)
		{
			for (int j = 0; j < B.n; j++)
				if (C.A[i] == B.A[j])
					A[n++] = C.A[i];
		}
		A[n] = 0; // ограничитель строки
		return *this;
	}

	Set operator & (const Set& B) const
	{
		Set C(*this);
		return (C &= B);
	}

	Set& operator |= (const Set& B)
	{
		for (int i = 0; i < B.n; ++i)
		{
			bool f = true;
			for (int j = 0; j < n; ++j)
				if (B.A[i] == A[j]) f = false;
			if (f) A[n++] = B.A[i];
		}
		A[n] = 0;
		return *this;
	}

	Set operator | (const Set& B)
	{
		Set C(*this);
		return (C |= B);
	}

	Set& operator ^= (const Set& B)
	{
		Set C(*this);
		int a = 0;
		for (int i = 0; i < C.n; ++i)
		{
			for (int j = 0; j < B.n; j++)
				if (C.A[i] == B.A[j])
				{
					for (int b = i - a; b + 1 < C.n; b++)
					{
						A[b] = C.A[b + 1 + a];

					}
					a++;
					i++;
					A[n - a] = '\0';
				}
		}
		//A[n] = 0; // ограничитель строки
		return *this;
	}

	Set operator ^ (const Set& B) const
	{
		Set C(*this);
		return (C ^= B);
	}

	Set operator ~ () const
	{
		Set C;
		for (char c = 'а'; c <= 'я'; ++c)
		{
			bool f = true;
			for (int j = 0; j < n; ++j)
				if (c == A[j])
				{
					f = false;
					break;
				}
			if (f)
				C.A[C.n++] = c;
		}
		C.A[C.n] = 0;
		return C;
	}

	void Show()
	{
		std::cout << '\n' << S << " = [" << A << "]";
	}

	Set() : n(0), S('0'), A(new char[N + 1])
	{
		A[0] = 0;
	}

	Set(char s) : S(s), n(0), A(new char[N + 1])
	{
		for (int i = 0; i < N; i++)
		{
			if (rand() % 2) A[n++] = i + 'а';
		}
		A[n] = 0;
		std::cout << '\n' << S << "= [" << A << "]";
	}

	Set(const Set& B) : S(B.S), n(B.n), A(new char[N + 1]) //конструктор копирования
	{
		char* s(B.A), * t(A);
		while (*t++ = *s++);
	}

	Set operator = (const Set& B)
	{
		if (this != &B)
		{
			char* s(B.A), * t(A); n = B.n; S = 'R';
			while (*t++ = *s++);
		}
		return *this;
	}

	Set operator = (Set&& B)
	{
		if (this != &B)
		{
			n = B.n; A = B.A; S = 'R'; B.A = nullptr;
		}
		return *this;
	}

	Set(Set&& B) : S(B.S), n(B.n), A(B.A)
	{
		B.A = nullptr;
	}
};

const long q0 = 100000; // количество повторений цикла времени

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//srand(time(nullptr));
	Set A('A'), B('B'), C('C'), D('D'), E, V, N, M;
	clock_t _begin = clock();
	//for (long q = 0; q < q0; ++q)
	//{
	V = A | B;
	N = C & D;
	M = V ^ N;
	E = (A | B) ^ (C & D);
	//}
	clock_t _end = clock();
	V.Show();
	N.Show();
	M.Show();
	E.Show();

	std::cout << std::endl << "Middle power = " <<
		(A.power() + B.power() + C.power() + D.power() + E.power()) / 5 <<
		", Time = " << _end - _begin << "/" << q0 << std::endl;
	system("pause");

	return 0;
}