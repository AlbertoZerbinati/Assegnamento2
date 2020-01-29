// Zerbinati Alberto

#include <vector>
#include <iostream>
#include "System.h"
#include "Order.h"

void System::Warehouse::printAll() {
	//ordini evasi, li trovo in orderReady
	std::cout << "\n*** Ordini Evasi:" << std::endl;
	for (Order p : orderReady) {
		std::cout << "- " << p.quantityOrdered() << " " << p.modelName()
		     << " del mese " << p.timeStamp() << std::endl;
	}

	//componenti in arrivo
	std::cout << "\n*** Componenti in arrivo:" << std::endl;

	//riempio un vettore con tutte le componenti in arrivo
	std::vector<components> comps;
	for (Order p : orderList) {
		std::vector<components> order_comps = p.componentArriving();
		for (components c : order_comps)
			comps.push_back(c);
	} //questo vettore non puo' ancora essere stampato perche' contiene molteplicita' che ora sistemo

	for (unsigned int i = 0; i < comps.size(); i++) { // per tutte le componenti
		if (comps[i].id != -10) {          // controllo se l'ho già considerata
			for (unsigned int j = i + 1; j < comps.size(); j++) { // verifico tutte le componenti successive
				if (comps[j].id != -10 && comps[j].id == comps[i].id) { // se e' dello stesso tipo e non ancora considerata
					comps[i].quantity += comps[j].quantity; // conteggio la quantita'
					comps[j].id = -10;    // e segnalo che l'ho già considerata
				}
			}
		}
	} //ora so cosa devo stampare e in che quantita'!

	for (components cc : comps) {
		if (cc.id != -10)
			std::cout << "- " << cc.quantity << " " << cc.name << std::endl;
	}

	//componenti in magazzino
	std::cout << "\n\n*** Componenti in magazzino:" << std::endl;

	std::vector<components> comps_arrived;
	for (Order p : orderList) {
		std::vector<components> order_comps = p.componentArrived();
		for (components c : order_comps)
			comps_arrived.push_back(c);
	}

	for (unsigned int i = 0; i < comps_arrived.size(); i++) {
		if (comps_arrived[i].id != -10) {
			for (unsigned int j = i + 1; j < comps_arrived.size(); j++) {
				if (comps_arrived[j].id != -10
				    && comps_arrived[j].id == comps_arrived[i].id) {
					comps_arrived[i].quantity += comps_arrived[j].quantity;
					comps_arrived[j].id = -10;
				}
			}
		}
	} //ora so cosa devo stampare e in che quantita'!

	for (components cc : comps_arrived) {
		if (cc.id != -10)
			std::cout << "- " << cc.quantity << " " << cc.name << std::endl;
	}

}
