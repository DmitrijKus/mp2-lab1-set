// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

typedef TELEM type;
#define sz  sizeof(type)*8

int TBitField::GetMemIndex(const int n) const
{
	return n / sz;
}

type TBitField::GetMemMask(const int n) const
{
	return 1 << (n % sz);
}

TBitField::TBitField()
{
	BitLen = 1;
	MemLen = 1;
	pMem = new type[1];
	pMem[0] = 0;
}

TBitField::TBitField(int len)
{
	if (len <= 0) {
		throw "error";
	}
	if (len > 0) {
		MemLen = GetMemIndex(len - 1) + 1;
		BitLen = len;
		pMem = new type[MemLen];
		for (int i = 0; i < BitLen; i++) ClrBit(i);
	}
}

TBitField::TBitField(const TBitField& bf)
{
	if (bf.BitLen)
	{
		BitLen = bf.BitLen;
		MemLen = GetMemIndex(BitLen - 1) + 1;
		pMem = new type[MemLen];
		for (int i = 0; i < BitLen; i++) {
			if (bf.GetBit(i) == 1) {
				SetBit(i);
			}
			else {
				ClrBit(i);
			}
		}
	}
	else {
		BitLen = 1;
		MemLen = 1;
		pMem = new type[1];
		pMem[0] = 0;
	}
}

TBitField::~TBitField()
{
	delete pMem;
}

int TBitField::GetLength() const
{
	return BitLen;
}

void TBitField::SetBit(const int n)
{
	if (n < 0 || n >= BitLen) {
		throw "error";
	}
	else pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n)
{
	if (n < 0 || n >= BitLen) {
		throw "error";
	}
	else pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const
{
	if (n < 0 || n >= BitLen) {
		throw "error";
	}
	else return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

int TBitField::operator==(const TBitField& bf) const
{
	if (bf.BitLen == BitLen) {
		for (int i = 0; i < BitLen; i++) {
			if (GetBit(i) != bf.GetBit(i)) {
				return 0;
			}
		}
		return 1;
	}
	else {
		return 0;
	}
}

int TBitField::operator!=(const TBitField& bf) const
{
	if (BitLen == bf.BitLen) {
		for (int i = 0; i < BitLen; i++) {
			if (GetBit(i) != bf.GetBit(i)) {
				return 1;
			}
		}
		return 0;
	}
	else {
		return 1;
	}
}

TBitField& TBitField::operator=(const TBitField& bf)
{
	if (*this != bf)
	{
		~TBitField();
		BitLen = bf.BitLen;
		MemLen = GetMemIndex(BitLen - 1) + 1;
		pMem = new type[MemLen];
		for (int i = 0; i < BitLen; i++) {
			if (bf.GetBit(i) == 1) {
				SetBit(i);
			}
			else {
				ClrBit(i);
			}
		}
	}
	return *this;
}

TBitField TBitField::operator|(const TBitField& bf)
{

	int max_ = max(bf.BitLen, BitLen);
	TBitField ans(max_);
	for (int i = 0; i < max_; i++) {
		if (i < BitLen) {
			if (GetBit(i) == 1) ans.SetBit(i);
		}
		if (i < bf.BitLen) {
			if (bf.GetBit(i) == 1) ans.SetBit(i);
		}
	}
	return ans;
}

TBitField  TBitField::operator&(const TBitField& bf)
{

	TBitField ans(max(bf.BitLen, BitLen));
	int min_ = min(bf.BitLen, BitLen);
	for (int i = 0; i < min_; i++) {
		if (bf.GetBit(i) == 1 && GetBit(i) == 1) {
			ans.SetBit(i);
		}
	}
	return ans;
}

TBitField TBitField::operator~()
{
	TBitField ans(BitLen);
	for (int i = 0; i < BitLen; i++) {
		if (GetBit(i) == 0) {
			ans.SetBit(i);
		}
	}
	return ans;
}

istream& operator>> (istream& istr, TBitField& bf)
{
	for (int i = 0; i < bf.BitLen; i++) {
		int id;
		cin >> id;
		if (id == 1) bf.SetBit(i);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf)
{
	for (int i = 0; i < bf.BitLen; i++) {
		if (bf.GetBit(i) == 1) {
			cout << 1;
		}
		else {
			cout << 0;
		}
	}
	return ostr;
}
