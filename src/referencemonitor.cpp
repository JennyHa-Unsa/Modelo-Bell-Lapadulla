#include "referencemonitor.h"
#include <map>
#include <iostream>
#include <iomanip>

#define DEFAULT_NAME_LEN 16

ReferenceMonitor::ReferenceMonitor() = default;

bool ReferenceMonitor::executeInstruction(const Instruction& instruction) {
    switch (instruction.getType()) {
        case CmdType::ADD_SUB:
            return addSubject(instruction);
        case CmdType::ADD_OBJ:
            return addObject(instruction);
        case CmdType::READ:
            return executeRead(instruction);
        case CmdType::WRITE:
            return executeWrite(instruction);
        default:
            return false;
    }
}

bool ReferenceMonitor::addSubject(const Instruction& instruction) {
    std::string subName = instruction.getSubjectName();
    SecurityLevel secLvl = instruction.getSecurityLevel();
    Subject* sub = new Subject(subName, secLvl);

    auto result = subjects.insert({subName, sub});
    if (!result.second) {
        std::cout << "Subject: '" << subName << "' Already exists!\n";
        return false;
    }

    std::cout << std::left << std::setw(DEFAULT_NAME_LEN) << "Subject Added"
              << ": " << instruction.getInstruction() << "\n";
    return true;
}

bool ReferenceMonitor::addObject(const Instruction& instruction) {
    std::string objName = instruction.getObjectName();
    SecurityLevel secLvl = instruction.getSecurityLevel();
    Object* obj = new Object(objName, secLvl);

    auto result = objects.insert({objName, obj});
    if (!result.second) {
        std::cout << "Object: '" << objName << "' Already exists!\n";
        return false;
    }

    std::cout << std::left << std::setw(DEFAULT_NAME_LEN) << "Object Added"
              << ": " << instruction.getInstruction() << "\n";
    return true;
}

bool ReferenceMonitor::executeWrite(const Instruction& instruction) {
    std::string subName = instruction.getSubjectName();
    std::string objName = instruction.getObjectName();

    if (subjects.count(subName) == 0 || objects.count(objName) == 0) {
        return false;
    }

    Subject* sub = subjects.at(subName);
    Object* obj = objects.at(objName);
    int value = instruction.getValue();
    SecurityLevel subLvl = sub->getSecurityLevel();
    SecurityLevel objLvl = obj->getSecurityLevel();

    // Add logic for write operation based on security levels

    if (subLvl <= objLvl) {
        sub->writeToObject(&obj, value);
        std::cout << std::left << std::setw(DEFAULT_NAME_LEN) << "Access Granted"
                  << ": " << sub->getName() << " writes value " << value << " to " << obj->getName() << ".\n";
    } else {
        std::cout << std::left << std::setw(DEFAULT_NAME_LEN) << "Access Denied"
                  << ": " << instruction.getInstruction() << "\n";
    }

    return true;
}

bool ReferenceMonitor::executeRead(const Instruction& instruction) {
    std::string subName = instruction.getSubjectName();
    std::string objName = instruction.getObjectName();

    if (subjects.count(subName) == 0 || objects.count(objName) == 0) {
        return false;
    }

    Subject* sub = subjects.at(subName);
    Object* obj = objects.at(objName);
    SecurityLevel subLvl = sub->getSecurityLevel();
    SecurityLevel objLvl = obj->getSecurityLevel();

    if (subLvl >= objLvl) {
        sub->readFromObject(obj);
        std::cout << std::left << std::setw(DEFAULT_NAME_LEN) << "Access Granted"
                  << ": " << sub->getName() << " reads " << obj->getName() << ".\n";
    } else {
        std::cout << std::left << std::setw(DEFAULT_NAME_LEN) << "Access Denied"
                  << ": " << instruction.getInstruction() << "\n";
    }

    return true;
}

void ReferenceMonitor::printState() const {
    std::cout << "-------------------------\n";
    std::cout << std::left << std::setw(DEFAULT_NAME_LEN) << "Subject:" << "Temp:\n";
    std::cout << "-------------------------\n";
    for (const auto& [name, sub] : subjects) {
        std::cout << std::left << std::setw(DEFAULT_NAME_LEN) << sub->getName() << sub->getTemp() << "\n";
    }
    std::cout << "\n";
    std::cout << std::left << std::setw(DEFAULT_NAME_LEN) << "Object:" << "Value:\n";
    std::cout << "-------------------------\n";
    for (const auto& [name, obj] : objects) {
        std::cout << std::left << std::setw(DEFAULT_NAME_LEN) << obj->getName() << obj->getValue() << "\n";
    }
    std::cout << "-------------------------\n";
}

ReferenceMonitor::~ReferenceMonitor() {
    for (auto& [name, sub] : subjects) {
        delete sub;
    }
    for (auto& [name, obj] : objects) {
        delete obj;
    }
}


