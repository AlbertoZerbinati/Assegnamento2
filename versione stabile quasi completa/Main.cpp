// Zerbinati Alberto

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "System.h"

using namespace std;

class Invalid {};

bool finished(int m, const vector<orderInit>& o);       //controlla se il main deve terminare
double fill_orders(vector<orderInit>& o, istream& i);   //riempre il vector da orders.dat


int main() {

	int month = 0;                  //tengo traccia del mese corrente
	vector<orderInit> orders;       //per inserire ordini da orders.dat

	ifstream ist {"orders.dat"};    // input main: orders
	if (!ist)
		throw Invalid();


	//sistema di gestione degli ordini:
	//riempio orders da orders.dat e ritorno il valore iniziale della cassa per inizializzare il magazzino
	System::Warehouse syst(fill_orders(orders, ist));

	//ordino gli ordini secondo time_stamp come definito da operator< tra orderInit
	sort(orders.begin(), orders.end());

	ist.close();

	int index = 0;

	//LOOP principale del programma!
	for (month = 0; !finished(month, orders); month++) {
		cout << "\nMese " << month << "----------------------------------------\n" << endl;

		while(orders[month + index].time_stamp == month) {
			syst.addOrder(orders[month + index]);       //il magazzino riceve di volta in volta gli ordini del solo mese corrente
			index++;
		}

		syst.check_situation(); //invocata una volta per ogni mese
		index--;
	}

	return 0;
}


bool finished(int m, const vector<orderInit>& o) {
	return m > o[o.size() - 1].time_stamp + 12;  // lasciamo trascorrere un anno a partire dal time_stamp
	                                             // dell'ULTIMO ORDINE per completarne la consegna
}

double fill_orders(vector<orderInit>& o, istream& i) {
	int time_stamp;
	int model_id;
	int quantity_ordered;
	double cash_desk;

	i >> cash_desk;

	while (i >> time_stamp >> model_id >> quantity_ordered)
		o.push_back(orderInit{time_stamp, model_id, quantity_ordered});

	return cash_desk;
}
