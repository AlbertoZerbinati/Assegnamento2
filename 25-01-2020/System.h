#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <iostream>
#include "Structure.h"
#include "Order.h"

namespace System {

	class Warehouse {

	public:

		class Invalid {};
		// per lanciare eccezioni
		Warehouse();
		Warehouse(double initCash_desk);
		void addOrder(orderInit fromMain);
		void check_situation();

		//Funzioni per la stampa
		double cashDesk();

	private:
		int month;
		double cash_desk; //1 cassa contabile //2 cassa disponibile //3 disponibile + futuri incassi
		std::vector<Order> orderList;
		std::vector<Order> orderReady;

		//vettori di dati salvati dal file ai quali accedo per inizializzare
		std::vector<model> model_types;         // vettore con model_id, model_name
		std::vector<std::vector<components> > models_infos; // vettori con component_id, component_name, quantity dentro un vettore
		std::vector<component_info> components_infos; // vettore con component_id, component_name, delivery_time

		void fill_data();       //Riempie i vettori con le informazioni dei file
		void DecreaseMoney(vector<priceAssociation>& Ordered);     //aggiorna la cassa

		int dim_orderReady = 0;
		void printAll();
	};

}
#endif
