#pragma once
#include "Reading_order.h"
#include <vector>
#include <iostream>

class System {
public:
    void add(Reading_order ro) { //agguingo gli ordini dell'ultimo mese
        v.push_back(ro);
    };

    void check_situation() { //incrementa il mese e printa
        month++;
        if (ordine_evaso())
            print(); //FUNZIONE RICHIESTA: printa componenti in arrivo, ordini evasi, situazione magazzino
    };
    friend std::ostream& operator<< (std::ostream& os, System& s); //soluzione alternativa al friend?

private:
    int month = -1; //parto da -1 o da 0? secondo me da -1 dovrebbe funzionare
    std::vector<Reading_order> v;
    //Magazzino m;

    void print() { //funzione importante
        //std::cout << "\nmonth: " << month << "\n";
    };

    bool ordine_evaso() {return true;}; //solo per capire se printare

};


std::ostream& operator<< (std::ostream& os, System& s) {
    for (Reading_order ro : s.v)
        os << ro;
    return os;
};
