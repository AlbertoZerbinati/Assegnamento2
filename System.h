#pragma once
#include <vector>
#include <iostream>
#include "order.h"
#include "component.h"
#include "model.h" //mi serve per sapere come si chiamerà il file corrispondente ad certo model_id

class System {
public:
	void add(order ro) { //agguingo gli ordini dell'ultimo mese
		orders.push_back(ro);
	};

	void check_situation() { //incrementa il mese e printa
		month++;
		order_component();
		if (ordine_evaso())
			print(); //FUNZIONE RICHIESTA: printa componenti in arrivo, ordini evasi, situazione magazzino
	};
	friend std::ostream& operator<< (std::ostream& os, System& s); //soluzione alternativa al friend?

private:
	int month = -1; //parto da -1 o da 0? secondo me da -1 dovrebbe funzionare
	std::vector<order> orders;
	std::vector< std::vector<component> > components_needed; //contiene all'indice i componenti per
                                                             //la costruzione degli ED ordinati al mese i


    //Magazzino m;

	void print() { //funzione importante
		//std::cout << "\nmonth: " << month << "\n";
	};
	void order_component(){}; //filla components_needed leggendo i vari file modelX.dat e models.dat
	bool ordine_evaso() {
		return true;
	}; //solo per capire se printare

};


std::ostream& operator<< (std::ostream& os, System& s) {
	for (order ro : s.orders)
		os << ro;
	return os;
};
