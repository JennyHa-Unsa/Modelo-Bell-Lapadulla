#include "object.h"

Object::Object() : value(0) {}

Object::Object(const std::string& name, SecurityLevel level) : name(name), lvl(level), value(0) {}

std::string Object::getName() const {
    return name;
}

SecurityLevel Object::getSecurityLevel() const {
    return lvl;
}

void Object::setValue(int value) {
    this->value = value;
}

int Object::getValue() const {
    return value;
}

Object::~Object() = default;
