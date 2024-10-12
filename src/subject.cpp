#include "subject.h"

Subject::Subject() : temp(0) {}

Subject::Subject(const std::string& name, SecurityLevel level) : name(name), lvl(level), temp(0) {}

std::string Subject::getName() const {
    return name;
}

SecurityLevel Subject::getSecurityLevel() const {
    return lvl;
}

void Subject::readFromObject(const Object* obj) {
    temp = obj->getValue();
}

void Subject::writeToObject(Object* obj, int value) {
    obj->setValue(value);
}

int Subject::getTemp() const {
    return temp;
}

Subject::~Subject() = default;
