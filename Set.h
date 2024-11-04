#pragma once
#include<iostream>
#include "BitField.h"
#include <vector>
#include <cstdint>

class Set{
private:
    BitField _bitField;
    size_t _maxPower;

public:
    Set(size_t size):_bitField(size){
        _maxPower=size;
    
    }
    Set(const Set& set):_bitField(set._bitField){
        _maxPower=set._maxPower;
    }
    Set(const BitField& bf):_bitField(bf){
        _maxPower=bf.GetLength();
    }
    operator BitField(){
        return _bitField;
    }

    size_t GetMaxPower()const{
        return _maxPower;
    }

    void InsElem(uint64_t elem){
        _bitField.SetBit(elem);

    }
    void DeleteElem(uint64_t elem){
        _bitField.ClrBit(elem);
    }
    bool IsMember(uint64_t elem)const{
        return(_bitField.GetBit(elem));
    }
    Set& operator=(const Set& s){
        _maxPower=s.GetMaxPower();
        _bitField=s._bitField;
    return *this;
    }
    Set operator+(uint64_t elem);
    Set operator+(const Set& s){//обединение
        Set b=Set(s);
        if(_maxPower>s.GetMaxPower()){
            b=Set(*this);
            b._bitField=b._bitField|s._bitField;  
        }
        else 
            b._bitField=b._bitField|_bitField;

        return b;

    }
    Set operator*(const Set& s){
        Set b=Set(s);
        if(_maxPower<s.GetMaxPower()){
            b=Set(*this);
            b._bitField=b._bitField&s._bitField;
        }
        else
            b._bitField=b._bitField&_bitField;
    
        return b;
        }//пересечение
    Set operator-(uint64_t elem);
    Set operator~(){
        Set b=Set(*this);
        b._bitField=~b._bitField;

     return b;
    }
    std::vector<uint64_t> GetPrimary(){
        std::vector<uint64_t> prim_num;
        BitField tmp=_bitField;
        uint64_t current_div=2;
        while(current_div<_maxPower){
            if (IsMember(current_div)){
                for(uint64_t i=current_div+current_div; i<_maxPower;i+=current_div){
                    _bitField.ClrBit(i);
                }
            }
            if (IsMember(current_div))
            prim_num.push_back(current_div);
            current_div++;
                
        }
        _bitField=tmp;
        return prim_num;
    }

    void fill_set(){
        for(size_t i=0;i<_maxPower;i++){
            InsElem(i);
        }
    }


    friend std::istream& operator>>(std::istream& istr, Set& set){
        int64_t current;
        for(int64_t i=0;i<set.GetMaxPower();i++){
            std::cout<<"add elem:";
            istr>>current;
            if(current<0)
            break;
            set.InsElem(current);
        }
        return istr;
    }
    friend std::ostream& operator<<(std::ostream& os, const Set& set){
        for(uint64_t i=0;i<set._maxPower;i++){
            if(set.IsMember(i)==true)
            os<<i<<" ";

        }
        std::cout<<"\n";
        return os;
        
    }
};