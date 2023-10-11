#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len <= 0)
        throw "less than zero (Constructor)";
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
    MemLen = bf.MemLen;
    BitLen = bf.BitLen;
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
        throw ("n < 0 or n >= BL (GetMemIndex)");
    else
        return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen)
        throw ("n < 0 or n >= BL (GetMemMask)");
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
        throw ("n < 0 or n >= BL (SetBit)");
    else
    {
        pMem[GetMemIndex(n)] |= (GetMemMask(n));
    }
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen)
        throw ("n < 0 or n >= BL (ClrBit)");
    else
    {
        pMem[GetMemIndex(n)] &= (~(GetMemMask(n)));
    }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen)
        throw ("n < 0 or n >= BitLen (GetBit)");
    else
    {
        return pMem[GetMemIndex(n)] & GetMemMask(n);
    }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    delete[] pMem;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; ++i)
    {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.GetLength())
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < MemLen;++i)
        {
            if (pMem[i] != bf.pMem[i])
                return 0;
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}
TBitField TBitField::operator|(const TBitField &bf) // операция "или"
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

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
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
    for (int i = 0; i <BitLen; ++i)
    {

        if (GetBit(i) == 0)
        {
            tmp.SetBit(i);
        }
        else
        {
            tmp.ClrBit(i);
        }
    }
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.GetLength(); ++i)
    {
        int input;
        istr >> input;
        if (input) bf.SetBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); ++i)
    {
        ostr << bf.GetBit(i) << " ";
    }
    ostr << "\n";
    return ostr;
}