// Zerbinati Alberto

#include <iostream>
#include <vector>
#include "Order.h"

//funzioni utili alla printAll()

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
		if (!ready && comp.status == 2)
			ret.push_back(comp);
	}

	return ret;
}
