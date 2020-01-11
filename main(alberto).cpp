#include <iostream>
#include <fstream>
#include <vector>
#include "System.h"
#include "Reading_order.h"

using namespace std;

class Invalid {};

bool not_finished(int m, const vector<Reading_order>& o); //controlla se il main deve terminare
void fill_orders(vector<Reading_order>& o, istream& i);   //riempre il vector da orders.dat



int main() {
	//variabili
	int month = 0; //tengo traccia del mese corrente
	System syst; //sistema di gestione degli ordini
	vector<Reading_order> orders; //per inserire ordini da orders.dat

	ifstream ist {"orders.txt"};    // input main: orders
	if (!ist)
		throw Invalid();

	//riempio orders dal orders.dat
	fill_orders(orders, ist);

	cout << "*** STAMPA orders <- orders.dat *** \n";
	for (Reading_order ro : orders)
		cout << ro;
	cout << "\n\n";

	//LOOP principale del programma!
	int index = 0;
	for (month = 0; not_finished(month, orders); month++) {
		while(orders[month+index].time_stamp == month) { //passo gli ordini mese per mese al System
			syst.add(orders[month+index]);
			index++;
		}

		index--;
		syst.check_situation(); //invocata una volta per ogni mese -> incrementa il mese del System
	}

	cout << "*** STAMPA System *** \n";
	cout << syst;





	return 0;
}








bool not_finished(int m, const vector<Reading_order>& o) {
	return m < o[o.size() - 1].time_stamp + 12;  //il +12 è per indicare che lasciamo un anno a partire
	                                             //dal time_stamp dell'ULTIMO ORDINE per completarne la
	                                             //consegna, ma si può scegliere un criterio migliore
}

void fill_orders(vector<Reading_order>& o, istream& i) {
	int time_stamp;
	int model_id;
	int quantity_ordered;
	while (i >> time_stamp >> model_id >> quantity_ordered)
		o.push_back(Reading_order{time_stamp, model_id, quantity_ordered});
}