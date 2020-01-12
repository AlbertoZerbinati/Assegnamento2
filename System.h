#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <iostream>
#include "order.h"
#include "component.h"
#include "model.h" //mi serve per sapere come si chiamerà il file corrispondente ad un certo model_id


class System {
public:
	void add(order ro) { orders.push_back(ro); };//agguingo gli ordini dell'ultimo mese
	void check_situation(); //incrementa il mese (invocata una volta al mese), chiama la funz
	 						//che ordina componenti per quel mese e print() nel caso in cui un
							//ordine sia evaso

	inline friend std::ostream& operator<< (std::ostream& os, const System& s); //soluzione alternativa al friend?


private:
	int month = -1; //parto da -1 o da 0? secondo me da -1 dovrebbe funzionare
	std::vector<order> orders;  //all'indice i gli ordini del mese i <- nella produzione constrollo
	                            //gli ED che riesco a consegnare a partire dai primi richiesti

	std::vector< std::vector<component> > components_needed;
	//contiene all'indice i componenti necessari per la costruzione degli ED ordinati al mese i
	//una volta arrivati posso controllare da orders quali ED riesco a costruire con tali componenti

	//le merci nel magazzino deovono sapere se sono impegnate (aspettano altre merci per un certo ED)
	//o meno

	//Magazzino m;

	void print(); //FUNZIONE RICHIESTA: printa componenti in arrivo, ordini evasi, situazione magazzino
	void order_components(); //filla components_needed leggendo i vari file modelX.dat e models.dat
	bool ordine_evaso() {return true;}; //solo per capire se printare
};


//uso inline per evitare problemi di double definition
inline std::ostream& operator<< (std::ostream& os, const System& s) {
	for (order ro : s.orders)
		os << ro;
	return os;
};

#endif
