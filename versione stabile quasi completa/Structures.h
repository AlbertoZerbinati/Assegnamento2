
#ifndef STRUCTURES_H_
#define STRUCTURES_H_
#include <iostream>
#include <vector>

struct model {   // per leggere il nome del modello e l'id
	int model_id;                                      // [model1.dat] (esempio)
	std::string model_name;
	float price;
};

struct component_info { // per leggere le informazioni dei componenti su components_info.dat
	int component_id;                                   // components_info.dat
	std::string component_name;
	double delivery_time;
	std::vector<double> price;
};

struct components { // per leggere le informazioni sui componenti nei file dei modelli
	int id;                               // [model1.dat] (esempio)
	std::string name;
	int quantity;
	std::vector<double> price; //I 3 prezzi
	int status;                              // 0 da orinare 1 ordinato 2 pronto
	int monthsLeft;

	//std::ostream& os, const components& c
};

struct orderInit {   // per leggere gli ordini su orders.dat
	//order(int t, int m, int q) : time_stamp{t}, model_id{m}, quantity_ordered{q} {}

	int time_stamp;
	int model_id;
	int quantity_ordered;
	std::string model_name;
	std::vector<components> orderComponents;
};

struct priceAssociation {
	int id;
	int quantity;	//quantita componenti
	std::vector<double> price;
	double finalPrice;
};

inline std::ostream& operator<<(std::ostream &os, const orderInit &o) {
	os << " time stamp: " << o.time_stamp << " model_id: " << o.model_id
			<< " quantity: " << o.quantity_ordered << " model_name: "
			<< o.model_name << "\n" << std::endl;
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const components &o) {
	os << "      C.ID(" << o.id << ") C.Name: " << o.name << " Quantita': "
			<< o.quantity << "\n" << "      " << "Status: " << o.status
			<< " Mesi: " << o.monthsLeft << "           $:(" << o.price[0]
			<< "," << o.price[1] << "," << o.price[2] << ")" << std::endl;
	return os;
}

//per il sort nel main
inline bool operator< (const orderInit& left, const orderInit& right) {
	return left.time_stamp < right.time_stamp;
}

#endif /* STRUCTURE_H_ */
