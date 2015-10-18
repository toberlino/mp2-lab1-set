
#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if(len > 0){
		BitLen = len;
		MemLen = (BitLen + (sizeof(TELEM) * 8 - 1)) / (sizeof(TELEM) * 8);
		pMem = new TELEM [MemLen];
		for( int i = 0; i < MemLen; ++i)
			pMem[i] = 0;
	}
	else throw len;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem=new TELEM[MemLen];
	if ( pMem != NULL )
		for (int i=0; i<MemLen;i++) 
			pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return ( n / ( sizeof(TELEM) * 8 ) );
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int k = n % ( sizeof(TELEM)*8 ); 
	return ( 1 << k);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ( (-1 < n) && (n < BitLen) ){  
		int i = GetMemIndex(n); 
		TELEM mask = GetMemMask(n); 
		pMem[i] = pMem[i] | mask;
	}
	else throw n;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ( (-1 < n) && (n < BitLen) ){
		int i = GetMemIndex(n);
		TELEM mask = GetMemMask(n);
		pMem[i] = pMem[i] & (~mask);
	}
	else throw n;
}

int TBitField::GetBit(const int n) const // получить значение бита
{ 
	if ( (-1 < n) && (n < BitLen) ) {
		int i = GetMemIndex(n);
		TELEM mask = GetMemMask(n) ;
		return ( mask == ( pMem[i] & GetMemMask(n)) );
	}
	else throw n;
}


// битовые операции


TBitField& TBitField::operator=(const TBitField &bf) {
	if ( this != &bf ) { 
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete [] pMem;
		pMem = new TELEM [MemLen];
		for (int i = 0; i < MemLen; ++i)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const{
	int Res = 1;
	if ( BitLen != bf.BitLen)
		Res = 0;
	else
		for( int i = 0; i < BitLen; ++i )
			if ( GetBit(i) != bf.GetBit(i) ){
				Res = 0;
				break;
			}
			return Res;
}

int TBitField::operator!=(const TBitField &bf) const {
	int Res = 0;
	if ( BitLen != bf.BitLen)
		Res = 1;
	else
		for( int i = 0; i < BitLen; ++i )
			if ( GetBit(i) != bf.GetBit(i) )
			{
				Res = 1;
				break;
			}
			return Res;
}

TBitField TBitField::operator|(const TBitField &bf){
	int Len = BitLen; 
	if (BitLen < bf.BitLen) 
		Len = bf.BitLen;
	TBitField Res(Len);
	for(int i = 0; i < MemLen; ++i) 
		Res.pMem[i] = pMem[i];
	for(int i = 0; i < bf.MemLen; ++i)
		Res.pMem[i] |= bf.pMem[i];
	return Res;
}

TBitField TBitField::operator&(const TBitField &bf) {
	int Len = BitLen;
	if (BitLen < bf.BitLen) 
		Len = bf.BitLen;
	TBitField Res(Len);
	for(int i = 0; i < MemLen; ++i)
		Res.pMem[i] = pMem[i];
	for(int i = 0; i < bf.MemLen; ++i)
		Res.pMem[i] &= bf.pMem[i];
	return Res;
}

TBitField TBitField::operator~(void){
	TBitField Res(BitLen);
	for(int i = 0; i < Res.MemLen; ++i)
		Res.pMem[i] = ~pMem[i];
	return Res;
}


// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char c;
	int len = bf.GetLength();
	for (int i = 0; i < len; ++i)
	{
		istr >> c;
		if (c == '1') bf.SetBit(i);
		else
			if (c == '0') bf.ClrBit(i);
			else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	for ( int i = 0; i < len; ++i )
		ostr << bf.GetBit(i) << ' ' ;
	ostr << endl;
	return ostr;
}
