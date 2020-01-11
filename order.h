#pragma once
#include <iostream>

class order {   // per leggere gli ordini su orders.dat
public:
    order(int t, int m, int q) : time_stamp{t}, model_id{m}, quantity_ordered{q} {}

    int time_stamp;
    int model_id;
    int quantity_ordered;

};


//HELPER FUNCTION
std::ostream& operator<< (std::ostream& os, order& o) {
    os << "--  " << o.time_stamp << ", " << o.model_id << ", " << o.quantity_ordered << ".\n";
    return os;
};
