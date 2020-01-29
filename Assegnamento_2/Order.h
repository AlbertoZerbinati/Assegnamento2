// Curculacos Paolo

#ifndef ORDER_H_
#define ORDER_H_

#include <vector>
#include <iostream>
#include "Structure.h"

class Order {

public:

	Order();
	Order(orderInit fMainstd, const std::vector<std::vector<components> > &models_infos,  const std::vector<component_info> &components_infos);
	void PrintOrder();
	bool updates();
	void order_components(std::vector <priceAssociation> &toUpdate);
	void setReady();

	//Funzioni per la stampa
	std::string modelName();
	int timeStamp();
	int modelId();
	int quantityOrdered();
	double modelPrice();
	bool Ready();
	double orderValue(); //serve per determinare il prezzo di un ordine

	std::vector<components> componentArriving();
	std::vector<components> componentArrived();

private:

	void fillComponentToBuy(const components &orderComponents, std::vector <priceAssociation> &toFill);
	int time_stamp;
	int model_id;
	int quantity_ordered;

	bool ready; //serve per aspettare in modo semplice il mese che inpiega ad essere costruito
	double price;
	std::string model_name;
	std::vector<components> orderComponents;

};
#endif
