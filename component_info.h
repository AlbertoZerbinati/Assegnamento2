#ifndef COMPONENTINFO_H
#define COMPONENTINFO_H

#include <iostream>

struct component_info
{   // per leggere le informazioni sui componenti su components_info.dat
    int component_id;                               // components_info.dat
    std::string component_name;
    double delivery_time;    // mi tocca mettere double per non avere conflitti con component_id
};


inline std::ostream& operator<< (std::ostream& os, const component_info& ci) {
    os << "--  " << ci.component_id << ", " << ci.component_name << ", " << ci.delivery_time << ".\n";
    return os;
};

#endif
