#include <vector>
#include <fstream>
#include <iostream>
#include "System.h"
#include "Order.h"

using namespace std;
namespace System {

	class Invalid {};
	class TargetNotFound {};

	Warehouse::Warehouse() :
		month { 0 }, cash_desk { 0 } {}

	Warehouse::Warehouse(double initCash_desk) :
		month { 0 }, cash_desk { initCash_desk } {
		fill_data();
	}

	//Inizializzo un nuovo ordine
	void Warehouse::addOrder(orderInit fMain) {
		Order newOrder(fMain, models_infos, components_infos); //Costruttore a cui passo i vettori con i dati dei file
		orderList.push_back(newOrder); //Aggiungo alla lista di ordini il nuovo ordine
		//newOrder.PrintOrder();
	}

	//Scorro i vari ordini e aggiorno la situzione del magazzino
	void Warehouse::check_situation() {
		Order tmp;
		vector<priceAssociation> ComponentTopay; //tiene conto di tutti gli ordini che si vogliono effettuare per valutare il prezzo e aggiornare la cassa
		for (auto p : orderList) {    //Stampo la situzione per debug
			//p.PrintOrder();
			//cout << "\n" << endl;
		}
		int size = orderList.size(); // uso questa variabile temporanea perch� togliendo elementi da OrdeList la dimensione diminuisce
		for (int i = 0; i < size; i++) {

			//POTREBBE ANDARE A PUTTANE
			orderList[i].order_components(ComponentTopay);
			//Ordino i componenti necessari e mi ritorna quello che ho ordinato
			if (orderList[i].updates()) { //Aggiorno le tempistiche e tolgo elettrodomestici completi

				//aggiorno la casssa
				if (!(orderList[i].Ready())) {
					orderList[i].setReady();
				}else {
					//cout << "\n" << orderList[i].modelName() << " e' pronta \n" << endl;
					cash_desk = cash_desk + orderList[i].modelPrice();
					orderReady.push_back(orderList[i]); //Inserisco l'elemento ultimato nella lista degli ordini finiti
					orderList.erase(orderList.begin() + i); //Rimuovo elemento ultimato dalla lista degli ordini in costruzione
					i--;
					size--; //Avendo tolto un elemento da un array che sto scorrendo (Gli elementi riempiono il buco)
					//devo aggiornare di conseguenza indice e dimensione dell'array
				}
			}

		}
		//Funzione che aggiorna e stampa la cassa
		DecreaseMoney(ComponentTopay);

		if (dim_orderReady != orderReady.size())
			printAll();

		dim_orderReady = orderReady.size();

		/*/////////////////////////////////////////STAMPE DI DEBUG//////////////////////////////////////////////
		   cout << "Order List " << endl;
		   for (auto p : orderList) {
		    cout << "-" << p.modelName() << endl;
		   }

		   cout << "\nOrderReady  " << endl;
		   for (auto p : orderReady) {
		    cout << "-" << p.modelName() << endl;
		   }
		 */
	}

	//Stampo situazione del magazzino (da definire)
	void Warehouse::printAll() {
		//cout << "La cassa iniziale e': " << cash_desk << "\n" << endl;

		//ordini evasi li trovo in orderReady
		cout << "\n*** Ordini Evasi:" << endl;
		for (Order p : orderReady) {
			cout << "- " << p.quantityOrdered() << " " << p.modelName() << " del mese " << p.timeStamp() << endl;
		}

		//componenti in arrivo
		cout << "\n*** Componenti in arrivo:" << endl;

		//riempio un vettore con tutte le componenti in arrivo
		std::vector<components> comps;
		for (Order p: orderList) {
			std::vector<components> order_comps = p.componentArriving();
			for (components c : order_comps)
				comps.push_back(c);
		} //questo vettore non puo' ancora essere stampato perche' contiene molteplicita' che ora sistemo

		for (int i = 0; i < comps.size(); i++) { 							// per tutte le componenti
			if (comps[i].id != -10) { 										// controllo se l'ho già considerata
				for (int j = i + 1; j < comps.size(); j++) {				// verifico tutte le componenti successive
					if (comps[j].id != -10 && comps[j].id == comps[i].id) { // se e' dello stesso tipo e non ancora considerata
						comps[i].quantity += comps[j].quantity;				// conteggio la quantita'
						comps[j].id = -10;									// e segnalo che l'ho già considerata
					}
				}
			}
		} //ora so cosa devo stampare e in che quantita'!

		for (components cc : comps) {
			if (cc.id != -10)
				cout << "- " << cc.quantity << " " << cc.name << endl;
		}


		//componenti in magazzino
		cout << "\n\n*** Componenti in magazzino:" << endl;

		std::vector<components> comps_arrived;
		for (Order p: orderList) {
			std::vector<components> order_comps = p.componentArrived();
			for (components c : order_comps)
				comps_arrived.push_back(c);
		}

		for (int i = 0; i < comps_arrived.size(); i++) {
			if (comps_arrived[i].id != -10) {
				for (int j = i + 1; j < comps_arrived.size(); j++) {
					if (comps_arrived[j].id != -10 && comps_arrived[j].id == comps_arrived[i].id) {
						comps_arrived[i].quantity += comps_arrived[j].quantity;
						comps_arrived[j].id = -10;
					}
				}
			}
		} //ora so cosa devo stampare e in che quantita'!

		for (components cc : comps_arrived) {
			if (cc.id != -10)
				cout << "- " << cc.quantity << " " << cc.name << endl;
		}

		//cout << "Cassa attualmente con: " << cash_desk << "$" << endl;
	}

	//decide il prezzo in base a quanti componenti bisogna comprare e aggiorna la cassa
	// In pratica ho un array temporaneo che mi serve a contare per ogni tipo di componente
	//quanti ne vengono ordinati in totale
	void Warehouse::DecreaseMoney(vector<priceAssociation> &Ordered) {
		for (auto component : Ordered) {
			component.finalPrice = component.price[0];
			if (component.quantity > 10) {
				component.finalPrice = component.price[1];
				if (component.quantity > 50)
					component.finalPrice = component.price[2];
			}
			//cout << component.quantity << " componente C.ID(" << component.id << "): " << " Al prezzo di : " << component.finalPrice << " l'uno\n" << endl;
			cash_desk = cash_desk - (component.quantity * component.finalPrice);
		}
		//cout << "Cassa attualmente con: " << cash_desk << "$" << endl;

	}

	double Warehouse::cashDesk() {
		return cash_desk;
	}

	void Warehouse::fill_data() {
		//(1) riempio model_types e models_infos
		std::ifstream ist { "models.dat" };
		if (!ist)
			throw Invalid();

		// store models
		std::vector<std::string> model_files; // questo è il mio vettore con i model
		std::string file;

		while (ist >> file)
			model_files.push_back(std::string { file });

		ist.close();    // chiudo ist
		////////////////////////////////////////////
		/* print models
		   std::cout << "Dentro model_files:\n";                                           // ***** debug *****
		   for (int i=0; i < model_files.size(); ++i)                                      // ***** debug *****
		   std::cout << model_files[i] << std::endl;                                   // ***** debug *****
		   std::cout << std::endl;*/// ***** debug *****
		/////////////////////////////////////////
		// store model_id, model_name, component_id, component_name, quantity
		for (unsigned int i = 0; i < model_files.size(); ++i) {
			// input [model1.dat] (esempio)
			std::string input_name = model_files[i];
			std::ifstream ist2 { input_name };
			if (!ist2)
				throw Invalid();
			//CAAAAAAAAAAAAAAAAAAAAZOOOOOOOOOOOOOOOOOOOOOO
			//model_types.push_back(model { model_id, model_name }); // store prima riga

			// store seconda riga di [model1.dat] (esempio)
			// store prima riga di [model1.dat] (esempio)
			int id = 0;
			std::vector<double> c_price = { 0, 0, 0 };
			std::string name;
			int quantity = 0;

			ist2 >> id >> name >> c_price[0];

			std::vector<components> tmp;
			////////////////////////////////////per riconoscere
			//tmp.push_back(components { model_id, model_name, '0', mod el_price});
			tmp.push_back(components { id, name, quantity, c_price });

			////////////////////////////
			while (ist2 >> id >> name >> quantity >> c_price[0] >> c_price[1]
			       >> c_price[2])
				tmp.push_back(components { id, name, quantity, c_price }); // store tutto il resto
			models_infos.push_back(tmp);
		}
		//////////////////////////////////7
		// print model_id e model_name
		/*	std::cout << "Dentro model_types:\n";                                           // ***** debug *****
		   for (int j=0; j < model_types.size(); ++j)                                      // ***** debug *****
		   {                                                                               // ***** debug *****
		   std::cout << model_types[j].model_id << ", "                                // ***** debug *****
		   << model_types[j].model_name                                            // ***** debug *****
		   << std::endl;                                                           // ***** debug *****
		   }                                                                               // ***** debug *****
		   std::cout << std::endl;                                                        // ***** debug *****
		   //////////////////////////////7
		   ///////////////////////////7
		   // print component_id, component_name e quantity
		   std::cout << "Dentro i vettori dentro models_infos:\n";                         // ***** debug *****
		   for (auto vec : models_infos)                                                   // ***** debug *****
		   {
		   // ***** debug *****
		   for (auto v : vec)                                                          // ***** debug *****
		   {                                                                           // ***** debug *****
		   std::cout << v.id << ", "                                     // ***** debug *****
		   << v.name << ", "                                         // ***** debug *****
		   << v.quantity << std::endl;                                         // ***** debug *****
		   }                                                                           // ***** debug *****
		   std::cout << std::endl;                                                     // ***** debug *****
		   }         */// ***** debug *****
		//////////////////////////////////77
		//(2) riempio components_infos
		std::ifstream ist_info { "components_info.dat" };
		if (!ist_info)
			throw Invalid();

		// store component_id, component_name, delivery_time (file components_info.dat)
		int component_id;
		std::string component_name;
		double delivery_time;
		while (ist_info >> component_id >> component_name >> delivery_time)
			components_infos.push_back(component_info { component_id,
			                                            component_name, delivery_time });                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              // store

		ist_info.close();    // chiudo ist_info

		// print component_id, component_name, delivery_time
		/*std::cout << "Dentro components_infos:\n";                                      // ***** debug *****
		   for (auto c : components_infos)                                                 // ***** debug *****
		   {                                                                               // ***** debug *****
		   std::cout << c.component_id << ", "                                         // ***** debug *****
		   << c.component_name << ", "                                             // ***** debug *****
		   << c.delivery_time << std::endl;                                        // ***** debug *****
		   }                                                                               // ***** debug *****
		   std::cout << std::endl;   */// ***** debug *****
	}
}
