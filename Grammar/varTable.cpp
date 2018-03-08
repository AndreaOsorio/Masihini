#include <iostream>
#include <string>
#include <set>
#include "varTable.hpp"

VarTable::VarTable(){

    std::set <int> set;
    std::set <int> ::iterator it;

    set.insert(1);
    set.insert(1);
    set.insert(10);
    set.insert(11);

    for(it = set.begin() ; it != set.end(); it++){
        std::cout << *it << std :: endl;
    }

}