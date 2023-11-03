// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet()
{
	MaxPower = 1;
}

TSet::TSet(int np)
{
	if (np <= 0) {
		throw "error";
	}
	if (np > 0) {
		MaxPower = np;
		TBitField tmp(np);
		BitField = tmp;
	}
}

TSet::TSet(const TSet& s)
{
	if (s.GetMaxPower()) {
		MaxPower = s.GetMaxPower();
		TBitField tmp(MaxPower);
		BitField = tmp;

		for (int i = 0; i < s.GetMaxPower(); ++i) {
			if (s.IsMember(i)) {
				BitField.SetBit(i);
			}
		}
	}
	else {
		MaxPower = 1;
	}
}

TSet::TSet(const TBitField& bf)
{
	if (bf.GetLength()) {
		MaxPower = bf.GetLength();
		BitField = bf;
	}
	else MaxPower = 0;
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower() const
{
	return MaxPower;
}

void TSet::InsElem(const int Elem)
{
	if (Elem >= GetMaxPower() || Elem < 0) {
		throw "error";
	}
	else {
		BitField.SetBit(Elem);
	}
}

void TSet::DelElem(const int Elem)
{
	if (Elem >= GetMaxPower() || Elem < 0) {
		throw "error";
	}
	else {
		BitField.ClrBit(Elem);
	}
}

int TSet::IsMember(const int Elem) const
{
	if (Elem >= GetMaxPower() || Elem < 0) {
		throw "error";
	}
	else {
		if (BitField.GetBit(Elem) == 1) return 1;
		else return 0;
	}
}

int TSet::operator== (const TSet& s) const
{
	int a = MaxPower == s.GetMaxPower();
	int b = BitField == s.BitField;
	if (a == 1 && b == 1) return 1;
	else return 0;
}

int TSet::operator!= (const TSet& s) const
{
	int a = MaxPower == s.GetMaxPower();
	int b = BitField == s.BitField;
	if (a == 1 && b == 1) return 0;
	else return 1;
}

TSet& TSet::operator=(const TSet& s)
{

	if (*this == s) {
		return *this;
	}
	else {
		MaxPower = s.GetMaxPower();
		BitField = s.BitField;
		return *this;
	}
}

TSet TSet::operator+(const int Elem)
{
	if (Elem >= GetMaxPower() || Elem < 0) {
		throw "error";
	}
	else {
		TSet ans(*this);
		ans.InsElem(Elem);
		return ans;
	}
}

TSet TSet::operator- (const int Elem)
{
	if (Elem >= GetMaxPower() || Elem < 0) {
		throw "error";
	}
	else {
		TSet ans(*this);
		ans.DelElem(Elem);
		return ans;
	}
}

TSet TSet::operator+ (const TSet& s)
{
	TSet ans = s;
	ans.BitField = BitField | s.BitField;
	return ans;
}

TSet TSet::operator* (const TSet& s)
{
	TSet ans = s;
	ans.BitField = BitField & s.BitField;
	return ans;
}

TSet TSet::operator~ (void)
{

	TSet ans(*this);
	ans.BitField = ~ans.BitField;
	return ans;
}

istream& operator>> (istream& istr, TSet& bf)
{
	for (int i = 0; i < bf.MaxPower; ++i)
	{
		int x;
		cin >> x;
		if (x == 1) {
			bf.InsElem(i);
		}
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& bf)
{
	for (int i = 0; i < bf.MaxPower; ++i)
	{
		if (bf.IsMember(i)) {
			cout << 1;
		}
		else {
			cout << 0;
		}
	}
	return ostr;
}