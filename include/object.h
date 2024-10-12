#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "instruction.h"

// Representa un objeto BLP
class Object {
public:
    Object();
    Object(const std::string& name, SecurityLevel level);

    std::string getName() const;
    SecurityLevel getSecurityLevel() const;
    void setValue(int value);
    int getValue() const;

    ~Object() = default;

private:
    std::string name;   // El nombre del objeto
    int value;          // El valor del objeto
    SecurityLevel level;  // El nivel de seguridad del objeto
};

#endif // OBJECT_H
