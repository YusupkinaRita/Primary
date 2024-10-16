#include <iostream>
#include "Set.h"
#include <vector>
#include <cstdint>

int main(){
    Set set=Set(14);
    //set.fill_set();
    std::cin>>set;
    std::cout<<set;

    std::vector<uint64_t> vec=set.GetPrimary();
    for (size_t i=0;i<vec.size();i++){
       std::cout<<vec[i]<<" ";
    }

    







    return 0;
}