#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include "instruction.h"
#include "object.h"

class Subject {
public:
    Subject();
    Subject(const std::string& name, SecurityLevel level);

    std::string getName() const;
    SecurityLevel getSecurityLevel() const;
    void readFromObject(const Object* obj);
    void writeToObject(Object* obj, int value);
    int getTemp() const;

    ~Subject() = default;

private:
    std::string name;   // El nombre del sujeto
    int temp;           // El valor temporal del sujeto
    SecurityLevel lvl;  // El nivel de seguridad del sujeto
};

#endif // SUBJECT_H
