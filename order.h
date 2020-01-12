#ifndef ORDER_H
#define ORDER_H

#include <iostream>

class order {   // per leggere gli ordini su orders.dat
public:
    order(int t, int m, int q) : time_stamp{t}, model_id{m}, quantity_ordered{q} {}

    int time_stamp;
    int model_id;
    int quantity_ordered;

    //mi servono per sapere quando tutti gli ordini di un mese sono stati evasi per poppare()
    //il relativo ordine da orders in System
    bool completed = false; //da settare a true appena l'odrdine è stato consegnato
    bool preparing = false; //da settare a true nel mese in cui aspetto che venga costruito
};


inline std::ostream& operator<< (std::ostream& os, order& o) {
    os << "--  " << o.time_stamp << ", " << o.model_id << ", " << o.quantity_ordered << ".\n";
    return os;
};

#endif
