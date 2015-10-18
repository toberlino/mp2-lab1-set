#include "tset.h"

TSet::TSet(int mp) : BitField(mp){
	if (mp > 0) MaxPower = mp;
	else throw mp;
}
TSet::~TSet(void) {} 
TSet::TSet(const TSet &s): MaxPower(s.MaxPower) , BitField(s.BitField){} 
TSet::TSet(const TBitField &bf): BitField(bf), MaxPower( bf.GetLength()){} 
TSet::operator TBitField(){
	TBitField Res(this -> BitField);
	return Res;
}
int TSet::GetMaxPower(void) const {
	return MaxPower;
}
int TSet::IsMember(const int Elem) const {
    return BitField.GetBit(Elem);
}
void TSet::InsElem(const int Elem) {
	BitField.SetBit(Elem);
}
void TSet::DelElem(const int Elem) {
	BitField.ClrBit(Elem);
}
TSet& TSet::operator=(const TSet &s) {
	if (this != &s){
		MaxPower = s.MaxPower;
		BitField = s. BitField;
	}
	return *this;
}
int TSet::operator==(const TSet &s) const{
    return ( BitField == s.BitField );
}
int TSet::operator!=(const TSet &s) const {
	return ( BitField != s.BitField );
}
TSet TSet::operator+(const TSet &s) {   
	int power = MaxPower;
	if ( MaxPower < s.GetMaxPower() ) 
		power = s.GetMaxPower();
	TSet Res(power);
	Res.BitField = BitField | s.BitField;
	return Res;
}
TSet TSet::operator+(const int Elem) {
	TSet Res(BitField);
	Res.InsElem(Elem);
	return Res;
}
TSet TSet::operator-(const int Elem) {
	TSet Res(BitField);
	Res.DelElem(Elem);
	return Res;
}
TSet TSet::operator*(const TSet &s) {
	TSet Res(MaxPower);
	Res.BitField = BitField & s.BitField;
	return Res;
}
TSet TSet::operator~(void) {
	TSet Res(MaxPower);
	Res.BitField = ~BitField;
	return Res;
}
/*
TSet& TSet::operator+=(const TSet &s) {
	BitField = BitField | s.BitField;
	return *this;
}
TSet& TSet::operator*=(const TSet &s) {
	BitField = BitField & s.BitField;
	return *this;
}*/
istream &operator>>(istream &istr, TSet &s){
	istr >> s.BitField;
	return istr;}

ostream& operator<<(ostream &ostr, const TSet &s){
	ostr << s.BitField;
	return ostr;
}

