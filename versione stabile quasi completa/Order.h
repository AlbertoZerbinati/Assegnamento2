/*
 * Order1.h
 *
 *  Created on: 17 gen 2020
 *      Author: paolo
 */

#ifndef ORDER_H_
#define ORDER_H_

#include <vector>
#include <iostream>
#include "Structures.h"

using namespace std;
class Order {

public:

	Order();
	Order(orderInit fMainstd, const vector<vector<components> > &models_infos,  const vector<component_info> &components_infos);
	void PrintOrder();
	bool updates();
	void order_components(vector <priceAssociation> &toUpdate);
	void setReady();

	//Funzioni per la stampa
	string modelName();
	int timeStamp();
	int modelId();
	int quantityOrdered();
	double modelPrice();
	bool Ready();

	std::vector<components> componentArriving();
	std::vector<components> componentArrived();

private:

	void fillComponentToBuy(components &orderComponents,vector <priceAssociation> &toFill);
	int time_stamp;
	int model_id;
	int quantity_ordered;

	bool ready; //serve per aspettare in modo semplice il mese che inpiega ad essere costruito
	double price;
	string model_name;
	vector<components> orderComponents;

};
#endif
