// Zerbinati Alberto

#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
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
		bool accept_order(Order ord);    //si occupa di accettare o meno un ordine in base a quanta cassa è disponibile

		//Funzioni per la stampa
		double cashDesk();

	private:
		double cash_desk;               //cassa
		double cash_available;          //cassa che tiene conto delle spese appena dovute, a cui sincronizzata poi cash_desk
		std::vector<Order> orderList;   //lista ordini incaricati
		std::vector<Order> orderReady;  //ordini pronti (da stampare)
		std::vector<Order> orderTemp;   //vettore temporaneo per considerare gli ordini da prendere in carico

		//vettori di dati salvati dai file ai quali accedo per inizializzare (vedi fill_data())
		std::vector<std::vector<components> > models_infos; // vettori con component_id, component_name, quantity dentro un vettore
		std::vector<component_info> components_infos;       // vettore con component_id, component_name, delivery_time

		void fill_data();       //riempie i vettori con le informazioni dei file
		void decrease_money(std::vector<priceAssociation>& Ordered);     //aggiorna la cassa

		//per la stampa
		void printAll();
	};

}
#endif
