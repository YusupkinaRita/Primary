#pragma once
#include<iostream>
#include "BitField.h"
#include <vector>

class Set{
private:
    BitField _bitField;
    size_t _maxPower;

public:
    Set(size_t size):_bitField(size){
        _maxPower=size;
        _bitField=BitField(_maxPower);
    }
    Set(const Set& set):_bitField(set._maxPower){
        _maxPower=set._maxPower;
        _bitField=set._bitField;
    }
    Set(const BitField& bf):_bitField(bf.GetLength()){
        _maxPower=bf.GetLength();
        _bitField=bf;
    }
    operator BitField(){
        return _bitField;
    }

    size_t GetMaxPower(){
        return _maxPower;
    }

    void InsertElem(uint64_t elem){
        _bitField.SetBit(elem);

    }
    void DeleteElem(uint64_t elem){
        _bitField.ClrBit(elem);
    }
    bool IsMember(uint64_t elem)const{
        return(_bitField.GetBit(elem));
        
    }
    Set& operator=(const Set& tmp);
    Set operator+(uint64_t elem);
    Set operator+(const Set& tmp);//обединение
    Set operator*(const Set& tmp);//пересечение
    Set operator-(uint64_t elem);
    Set operator~();
    std::vector<uint64_t> GetPrimary(){
        std::vector<uint64_t> prim_num;
        uint64_t current_div=2;
        while(current_div<_maxPower-1){
            if (IsMember(current_div)){
                for(uint64_t i=current_div+current_div; i<_maxPower;i+=current_div){
                    _bitField.ClrBit(i);
                }
            }
            if (IsMember(current_div))
            prim_num.push_back(current_div);
            current_div++;
                
        }
        return prim_num;
    }

    void fill_set(){
        for(size_t i=0;i<_maxPower;i++){
            InsertElem(i);
        }
    }


    friend std::istream& operator>>(std::istream& istr, Set& set){
        int64_t current;
        for(int64_t i=0;i<set.GetMaxPower();i++){
            std::cout<<"add elem:";
            istr>>current;
            if(current<0)
            break;
            set.InsertElem(current);
        }
        return istr;
    }
    friend std::ostream& operator<<(std::ostream& os, const Set& set){
        for(uint64_t i=0;i<set._maxPower;i++){
            if(set.IsMember(i)==true)
            os<<i;

        }
        std::cout<<"\n";
        return os;
        
    }
};