#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <iostream>
#include "order.h"
#include "component.h"
#include "model.h" //mi serve per sapere come si chiamerà il file corrispondente ad un certo model_id
#include "component_info.h"

class System {
public:
	void add(order ro) {
		month_orders.push_back(ro);
	};//agguingo gli ordini dell'ultimo mese
	void check_situation(); //incrementa il mese (invocata una volta al mese), chiama la funz
	                        //che ordina componenti per quel mese e print() nel caso in cui un
	                        //ordine sia evaso

	inline friend std::ostream& operator<< (std::ostream& os, const System& s); //soluzione alternativa al friend?

	class Invalid {};

private:
	int month = -1; //parto da -1 o da 0? secondo me da -1 dovrebbe funzionare
	std::vector<order> month_orders;  //all'indice i gli ordini del mese i <- nella produzione constrollo
	//gli ED che riesco a consegnare a partire dai primi richiesti

	std::vector<model> model_types; //vettore che associa model_id a model_name (indice I -> modelI.dat)
	std::vector<std::vector<component> > models_infos; //per ogni modello dice le componenti per produrlo
	std::vector<component_info> components_infos; //info delle componenti

	//Magazzino m;
	// nota: le merci nel magazzino deovono sapere se sono impegnate (cioè se stanno aspettando altre merci
	// per un certo ED) o meno

	void print(); //FUNZIONE RICHIESTA: printa componenti in arrivo, ordini evasi, situazione magazzino
	void order_components(); //filla components_needed leggendo i vari file modelX.dat e models.dat
	bool ordine_evaso() {return true;}; //solo per capire se printare, è da cambiare ovviamente
	void fill_data();
	std::vector<component> fill_components_month();
};


//comodo in fase di testing, non richiesto
//uso inline per evitare problemi di double definition
inline std::ostream& operator<< (std::ostream& os, const System& s) {
	// for (order or : s.month_orders)
	// 	os << or;

	std::cout << "model_types & infos:\n";
	for (int i = 0; i < s.model_types.size(); i++) {
		os << s.model_types[i];

		std::cout << "\n";

		for (int j = 0; j < s.models_infos[i].size(); j++)
			os << s.models_infos[i][j];

		std::cout << "\n\n\n";
	}

	std::cout << "\ncomponents_infos\n";
	for (component_info coi : s.components_infos)
		os << coi;

	return os;
};

#endif
