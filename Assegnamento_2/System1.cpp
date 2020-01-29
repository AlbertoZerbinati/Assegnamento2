// Spinato Matteo

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
		cash_desk { 0 }, cash_available { 0 } {}

	Warehouse::Warehouse(double initCash_desk) :
		cash_desk { initCash_desk }, cash_available { initCash_desk } {
		fill_data();
	}

	//Inizializzo un nuovo ordine
	void Warehouse::addOrder(orderInit fMain) {
		Order newOrder(fMain, models_infos, components_infos); //Costruttore a cui passo i vettori con i dati dei file
		orderTemp.push_back(newOrder); //Aggiungo questo ordine in un vettore di ordini temporaneo, del tipo: "Ok, considero l'ordine"
		                               //in check_situa poi mi preoccuperò di aggiungerli al vettore orderList
		//newOrder.PrintOrder();
	}

	//accept_order mi dice se ho soldi a sufficienza per effettuare l'ordine
	bool Warehouse::accept_order(Order ord) {
		if (ord.orderValue() <= cash_available)
			return true;
		return false;
	}

	//Scorro i vari ordini e aggiorno la situzione del magazzino
	void Warehouse::check_situation() {
		//if (orderTemp.size() > 0) {
		while (orderTemp.size() > 0 && accept_order(orderTemp[0])) {
			orderList.push_back(orderTemp[0]); //Se ho soldi a sufficienza, metto l'ordine nel vettore orderList
			orderTemp.erase(orderTemp.begin());
			cash_available -= orderTemp[0].orderValue();
			//e lo tolgo dal vettore temporaneo con gli ordini considerati
			//bisogna che in quel momento si riferisca a quello giusto
		}
		//}
		//Infine capisco se lanciare
		Order tmp;
		vector<priceAssociation> ComponentTopay; //tiene conto di tutti gli ordini che si vogliono effettuare per valutare il prezzo e aggiornare la cassa
		for (auto p : orderList) {    //Stampo la situzione per debug
			p.PrintOrder();
			cout << "\n" << endl;
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
					cout << "Sono arrivati tutti i componenti di "
					     << orderList[i].quantityOrdered() << " "
					     << orderList[i].modelName() << "\nma non ancora pronto!"
					     << endl;
				} else {
					cout << "\n" << orderList[i].modelName() << " e' pronta \n"
					     << endl;
					cash_desk = cash_desk + orderList[i].modelPrice();
					cash_available = cash_available + orderList[i].modelPrice();
					orderReady.push_back(orderList[i]); //Inserisco l'elemento ultimato nella lista degli ordini finiti
					orderList.erase(orderList.begin() + i); //Rimuovo elemento ultimato dalla lista degli ordini in costruzione
					i--;
					size--;

					cout << "\nChiamo printAll:" << endl;
					cout << "***************************************************"
					     << endl;
					printAll();
					cout << "***************************************************"
					     << endl;

					//Avendo tolto un elemento da un array che sto scorrendo (Gli elementi riempiono il buco)
					//devo aggiornare di conseguenza indice e dimensione dell'array
				}
			}
		}
		//Funzione che aggiorna e stampa la cassa
		decrease_money(ComponentTopay);

		//if (dim_orderReady != orderReady.size())
		//

		//dim_orderReady = orderReady.size();

		/////////////////////////////////////////STAMPE DI DEBUG//////////////////////////////////////////////
		cout << "\norderTemp " << endl;
		for (auto p : orderTemp) {
			cout << "-" << p.modelName() << endl;
		}

		cout << "\nOrder List " << endl;
		for (auto p : orderList) {
			cout << "-" << p.modelName() << endl;
		}

		cout << "\nOrderReady  " << endl;
		for (auto p : orderReady) {
			cout << "-" << p.modelName() << endl;
		}

	}

	//decide il prezzo in base a quanti componenti bisogna comprare e aggiorna la cassa
	// In pratica ho un array temporaneo che mi serve a contare per ogni tipo di componente
	//quanti ne vengono ordinati in totale
	void Warehouse::decrease_money(vector<priceAssociation> &Ordered) {
		for (auto component : Ordered) {
			component.finalPrice = component.price[0];
			if (component.quantity > 10) {
				component.finalPrice = component.price[1];
				if (component.quantity > 50)
					component.finalPrice = component.price[2];
			}
			cout << component.quantity << " componente C.ID(" << component.id
			     << "): " << " Al prezzo di : " << component.finalPrice
			     << " l'uno\n" << endl;
			cash_desk = cash_desk - (component.quantity * component.finalPrice);
		}
		cout << "Cassa attualmente con: " << cash_desk << "$" << endl;
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

		ist.close();

		// store model_id, model_name, component_id, component_name, quantity
		for (unsigned int i = 0; i < model_files.size(); ++i) {
			// input [model1.dat] (esempio)
			std::string input_name = model_files[i];
			std::ifstream ist2 { input_name };
			if (!ist2)
				throw Invalid();

			int id = 0;
			std::string name;
			int quantity = 0;
			std::vector<double> model_price = { 0, 0, 0 };

			ist2 >> id >> name >> model_price[0];

			std::vector<components> tmp;
			//per riconoscere

			tmp.push_back(components { id, name, quantity, model_price });

			////////////////////////////
			while (ist2 >> id >> name >> quantity)
				tmp.push_back(components { id, name, quantity }); // store tutto il resto
			models_infos.push_back(tmp);
		}

		// print model_id e model_name

		//(2) riempio components_infos
		std::ifstream ist_info { "components_info.dat" };
		if (!ist_info)
			throw Invalid();

		// store component_id, component_name, delivery_time (file components_info.dat)
		int component_id;
		std::string component_name;
		double delivery_time;
		std::vector<double> c_price = { 0, 0, 0 };
		while (ist_info >> component_id >> component_name >> delivery_time
		       >> c_price[0] >> c_price[1] >> c_price[2])
			components_infos.push_back(component_info { component_id,
			                                            component_name, delivery_time, c_price }); // store
		ist_info.close();
	}
}
