// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0)
		throw "len <= 0 (in Constructor)";
	else
	{
		BitLen = len;
		MemLen = (BitLen - 1) / (8 * sizeof(TELEM)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; ++i)
		{
			pMem[i] = 0;
		}
	}
}


TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}


int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n >= BitLen)
		throw ("  n >= BitLen or n < 0 ");
	else
		return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen)
		throw (" n >= BitLen or n < 0");
	int k;
	k = n % (8 * sizeof(TELEM));
	return 1 << k;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen)
		throw ("n >= BitLen or n < 0");
	else
	{
		pMem[GetMemIndex(n)] |= (GetMemMask(n));
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen)
		throw ("n >= BitLen (in ClrBit) or n < 0 ");
	else
	{
		pMem[GetMemIndex(n)] &= (~(GetMemMask(n)));
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) || (n < BitLen))
		return (pMem[GetMemIndex(n)] & GetMemMask(n)) == 0 ? 0 : 1;
	else throw ("The number is out of the bit field");
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (*this == bf)
	{
		return *this;
	}
	if (MemLen != bf.MemLen)
	{
		delete[] pMem;
		pMem = new TELEM[bf.MemLen];
	}
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	for (int i = 0; i < MemLen; ++i)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.GetLength())
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < MemLen;++i) // i < BitLen не проходит тест
		{
			if (pMem[i] != bf.pMem[i])
				return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	return !(*this == bf);
}
TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int cor_len = BitLen;
	if (bf.BitLen > BitLen)
	{
		cor_len = bf.BitLen;
	}
	TBitField result(cor_len);
	for (int i = 0; i < MemLen; i++)
	{
		result.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return result;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int cor_len = BitLen;
	if (bf.BitLen > BitLen)
	{
		cor_len = bf.BitLen;
	}
	TBitField result(cor_len);
	for (int i = 0; i < MemLen; i++)
	{
		result.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return result;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(*this);
	for (int i = 0; i < BitLen; ++i)
	{

		if (GetBit(i) == 0)
		{
			tmp.SetBit(i); //меняем на 1
		}
		else
		{
			tmp.ClrBit(i); //если =1, очищаем (меняем на 0)
		}
	}
	return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	for (int i = 0; i < bf.GetLength(); ++i)
	{
		int input;
		istr >> input;
		if (input) bf.SetBit(i);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); ++i)
	{
		ostr << bf.GetBit(i) << " ";
	}
	ostr << "\n";
	return ostr;
}
