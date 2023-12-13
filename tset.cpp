// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
    BitField = TBitField (s.BitField);
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower= bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw "Element exists";
    }
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw "Element exists";
    }
    return BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw "Element exists";
    }
    return BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int cor_len = MaxPower;
    if (MaxPower > s.MaxPower)
    {
        cor_len = MaxPower;
    }
    cor_len = s.MaxPower;
    TSet tmp(cor_len);
    tmp.BitField = BitField | s.BitField;
    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw "Element exists";
    }
    TSet tmp(BitField);
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw "Element exists";
    }
    TSet tmp(BitField);
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    int cor_len = MaxPower;
    if (MaxPower > s.MaxPower)
    {
        cor_len = MaxPower;
    }
    cor_len = s.MaxPower;
    TSet tmp(cor_len);
    tmp.BitField = BitField & s.BitField;
    return tmp;
}

TSet TSet::operator~(void) // дополнение
{
    return TSet (~BitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    const int mp = s.MaxPower;
    for (int i = 0; i < mp; ++i)
    {
        int val; istr >> val;
        s.InsElem(val);
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    const int mp = s.MaxPower;
    for (size_t i = 0; i < mp; ++i)
    {
        if (s.BitField.GetBit(i))
            ostr << i;
        if (i + 1 < s.MaxPower) 
            ostr << " ";
    }
    return ostr;
}
