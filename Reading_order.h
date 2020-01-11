#pragma once
#include <iostream>

class Reading_order {   // per leggere gli ordini su orders.dat
public:
    Reading_order(int t, int m, int q) :time_stamp{t}, model_id{m}, quantity_ordered{q} {}
    
    int time_stamp;
    int model_id;
    int quantity_ordered;

};


//HELPER FUNCTION
std::ostream& operator<< (std::ostream& os, Reading_order& ro) {
    os << "--  " << ro.time_stamp << ", " << ro.model_id << ", " << ro.quantity_ordered << ".\n";
    return os;
};
