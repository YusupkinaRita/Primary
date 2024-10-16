#include "BitField.h"

BitField::BitField(size_t len) {
    _sizeBit = len;
    _memSize = (len / (8 * sizeof(uint16_t))) + (len % (8 * sizeof(uint16_t)) != 0);
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = 0;
}

BitField::BitField(const BitField& tmp) {
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
}

BitField& BitField::operator=(const BitField& tmp){
    if (_sizeBit != tmp._sizeBit){
        delete [] _mem;
        _sizeBit = tmp._sizeBit;
        _memSize = tmp._memSize;
        _mem = new uint16_t[_memSize];
    }
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
    return *this;
}

uint16_t BitField::GetMask(size_t n) const {
    return 1 << (n % 16);
}

void BitField::ClrBit(size_t n){
    _mem[GetMemIndex(n)]&=(~GetMask(n));
}

void BitField::SetBit(size_t n) {
    if (n >= _sizeBit)
        throw "Bit out of range!";
    _mem[GetMemIndex(n)] |= GetMask(n);
}

size_t BitField::GetMemIndex(size_t n) const {
    if (n >= _sizeBit)
        throw "Bit out of range!";
    return n/(sizeof(uint16_t)*8);
}

uint8_t BitField::GetBit(size_t n) const {
    if(n>=_sizeBit)
            throw "Bit out of range";
            return ((GetMask(n)&_mem[GetMemIndex(n)])!=0);

}
BitField BitField::operator|(const BitField& tmp){
    BitField b=BitField(_sizeBit);
    for(size_t i=0; i<_memSize;i++ ){
        b._mem[i]=_mem[i]|tmp._mem[i];
    }
    return b;
}

BitField BitField::operator&(const BitField& tmp){
    BitField b=BitField(*this);
    for(size_t i=0; i<_memSize;i++ ){
        b._mem[i]&=tmp._mem[i];
    }
    return b;
}
BitField BitField::operator^(const BitField& tmp){
    BitField b=BitField(*this);
    for(size_t i=0; i<_memSize;i++ ){
        b._mem[i]^=tmp._mem[i];
    }
    return b;
}
BitField BitField::operator~(){
    BitField b=BitField(*this);
    for(size_t i=0; i<_memSize;i++ ){
        b._mem[i]=~_mem[i];
    }
    return b;

}
bool BitField::operator==(const BitField& tmp){
    if(_sizeBit!=tmp._sizeBit)
        return false;
    for(size_t i=0; i<_memSize;i++){
        if(_mem[i]!=tmp._mem[i])
        return false;
    }
    return true;

}


BitField::~BitField(){
            delete[] _mem;
            _mem=nullptr;
}

