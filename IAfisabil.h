#ifndef IAFISABIL_H
#define IAFISABIL_H

#include <iostream>


class IAfisabil {
public:
    virtual ~IAfisabil() {}


    virtual void afisare(std::ostream& os) const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const IAfisabil& obj) {
    obj.afisare(os);
    return os;
}

#endif // IAFISABIL_H