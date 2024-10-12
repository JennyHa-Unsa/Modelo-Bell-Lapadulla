#ifndef REFERENCEMONITOR_H
#define REFERENCEMONITOR_H

#include <vector>
#include <string>
#include <map>
#include "instruction.h"
#include "subject.h"
#include "object.h"

class ReferenceMonitor {
public:
    ReferenceMonitor();
    ~ReferenceMonitor();

    bool executeInstruction(const Instruction& instruction);
    void printState() const;

private:
    // Mapa de sujetos: Nombre del sujeto -> Puntero a Subject
    std::map<std::string, Subject*> subjects;
    using SubjectIterator = std::map<std::string, Subject*>::iterator;
    using SubjectPair = std::pair<std::string, Subject*>;

    // Mapa de objetos: Nombre del objeto -> Puntero a Object
    std::map<std::string, Object*> objects;
    using ObjectIterator = std::map<std::string, Object*>::iterator;
    using ObjectPair = std::pair<std::string, Object*>;

    bool addSubject(const Instruction& instruction);
    bool addObject(const Instruction& instruction);
    bool executeWrite(const Instruction& instruction);
    bool executeRead(const Instruction& instruction);
};

#endif // REFERENCEMONITOR_H
