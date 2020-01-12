#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>


struct component
{   // per leggere le informazioni sui componenti nei file dei modelli
    int component_id;                               // [model1.dat] (esempio)
    std::string component_name;
    int quantity;    // mi tocca mettere double per non avere conflitti con component_id
};

inline std::ostream& operator<< (std::ostream& os, const component& c) {
    os << "--  " << c.component_id << ", " << c.component_name << ", " << c.quantity <<".\n";
    return os;
};

#endif
