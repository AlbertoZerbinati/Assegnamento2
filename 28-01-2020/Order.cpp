// Paolo

#include <vector>
#include <fstream>
#include <iostream>
#include "Order.h"

using namespace std;

class fileNameNotFound {};
class TargetNotFound {};
class Invalid {};

//Costruttore di default di order
Order::Order() :
	time_stamp { 0 }, model_id { 0 }, quantity_ordered { 0 }, ready {false}, price { 0 } {}

//costruttore di Order: Inizializza un ordine composto da un numero di un certo tipo di modello
//es 4 lavatrici.
//La parte piu' importante e' l'inizializzazione del vettore di componenti al suo interno
Order::Order(orderInit fMain, const vector<vector<components> > &models_infos,
             const vector<component_info> &components_infos) :
	time_stamp { fMain.time_stamp }, model_id { fMain.model_id }, quantity_ordered {fMain.quantity_ordered},ready {false} {
	for (auto mod : models_infos) { //scorro il vettore con le info sui modelli
		if (model_id == mod[0].id) {
			model_name = mod[0].name;
			price = mod[0].prices[0] * quantity_ordered;
			//Trovo il modello che mi serve
			//DEVO SALTARE IL PRIMO che non � un componente vero ma per riconoscere il modello
			for (unsigned int i = 1; i < mod.size(); i++) { //scorro i componenti all'interno del file saltando il primo

				mod[i].quantity = mod[i].quantity * quantity_ordered;

				for (auto info : components_infos) { //scoroo il vettore con le informazioni dei componenti
					//cerco all' interno del vettore con le informazioni dei vari componenti il componente che mi serve (tramite l'id)
					if (mod[i].id == info.component_id)
						mod[i].monthsLeft = info.delivery_time;
				}
				orderComponents.push_back(mod[i]);
			}
			//Metto al primo posto dell'array di componenti del modello il componente che ci mette pi� tempo ad arrivare:
			//questo perche' mi serve come riferimento. Cosi' so dove trovarlo qualunque sia il modello.
			components tmp;
			int indexMax = 0;
			//Trovo quello che ci mette pi� tempo
			for (unsigned int i = 0; i < orderComponents.size(); i++) {
				if (orderComponents[i].monthsLeft
				    > orderComponents[indexMax].monthsLeft)
					indexMax = i;
			}
			//Effettuo lo scambio
			tmp = orderComponents[0];
			orderComponents[0] = orderComponents[indexMax];
			orderComponents[indexMax] = tmp;
		}
	}

}
//Si occupa di aggiornare il tempo di arrivo dei componenti di un modello e il loro stato una volta arrivati.
//Ritorna true quando tutti i componenti del modello sono pronti ormai da un mese.
//Come faccio a capirlo? Vado per esclusione. Se entra in una qualsiasi delle casistiche elencate
//significa che almeno un componente non � pronto e metto "verify" false.
//Tutti pronti: verify true.

bool Order::updates() {
	bool verify = true;
	for (unsigned int i = 0; i < orderComponents.size(); i++) {
		if (orderComponents[i].status == 1) {
			if (orderComponents[i].monthsLeft == 0)
				orderComponents[i].status = 2;
			else {
				orderComponents[i].monthsLeft--;
				verify = false;
			}
		}
		if (orderComponents[i].status == 0)
			verify = false;
	}
	return verify;
}

//Si occupa di ordinare i componenti necessari secondo la politica "scalata"
//ovvero ordino prima i pi� vecchi e poi procedo in modo che tutti i componenti arrivino lo stesso mese
//Questa strategia consente di distibuire le spese nel tempo per mettendo di incassare i soldi dei
//modelli finiti.

void Order::order_components(vector<priceAssociation> &toUpdate) {
	if (orderComponents[0].status == 0) {
		orderComponents[0].status = 1;
		fillComponentToBuy(orderComponents[0], toUpdate);
	}
	for (unsigned int i = 0; i < orderComponents.size(); i++) {
		if (orderComponents[i].monthsLeft == orderComponents[0].monthsLeft) {
			if (orderComponents[i].status == 0) {
				orderComponents[i].status = 1;
				fillComponentToBuy(orderComponents[i], toUpdate);

			}
		}
	}
}

void Order::fillComponentToBuy(components &order, vector<priceAssociation> &toFill) {
	bool findID = false;

	for (unsigned int i = 0; i < toFill.size(); i++) {
		if (order.id == toFill[i].id) {
			findID = true;
			toFill[i].quantity = toFill[i].quantity + order.quantity;
		}
	}
	if (!findID) {
		toFill.push_back(
			priceAssociation { order.id, order.quantity, order.prices });
	}
}

//Stampa le variabili esemplare di un ordine
void Order::PrintOrder() {
	cout << " " << quantity_ordered << " " << model_name << " Al mese "
	     << time_stamp << " (ID: " << model_id << ", $:" << price << ")"
	     << ":\n  Componenti:" << endl;
	for (components ro : orderComponents)
		cout << ro << endl;
}

void Order::setReady(){
	ready = true;
};
//Funzioni che ritornano lo stato delle variabili esemplare
// al di fuori della classe Order.

string Order::modelName() {
	return model_name;
}
int Order::timeStamp() {
	return time_stamp;
}
int Order::modelId() {
	return model_id;
}
int Order::quantityOrdered() {
	return quantity_ordered;
}
double Order::modelPrice() {
	return price;
}
bool Order::Ready() {
	return ready;
}

//ritorna il vettore con le componenti di questo ordine in arrivo
std::vector<components> Order::componentArriving() {
	std::vector<components> ret;
	for (components comp : orderComponents) {
		if (comp.status == 1)
			ret.push_back(comp);
	}

	return ret;
}

//ritorna il vettore con le componenti di questo ordine arrivate
std::vector<components> Order::componentArrived() {
	std::vector<components> ret;
	for (components comp : orderComponents) {
		if (comp.status == 2)
			ret.push_back(comp);
	}

	return ret;
}
