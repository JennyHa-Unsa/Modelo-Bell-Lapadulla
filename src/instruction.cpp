#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "instruction.h"


Instruction::Instruction(const std::string& command)
    : valid(false), type(CmdType::CMD_ERROR), value(0), instruction(command)
{
    // Convertir la cadena de comando a minúsculas
    std::string lowerCmd(command.size(), ' ');
    std::transform(command.begin(), command.end(), lowerCmd.begin(), ::tolower);

    // Obtener la primera palabra del comando
    std::string cmd = lowerCmd.substr(0, lowerCmd.find(' '));
    for (int i = 0; i < Instruction::NUM_CMD_TYPES; ++i) {
        if (cmd == TypeStrings[i]) {
            type = static_cast<CmdType>(i);
            break;
        }
    }

    // Si el tipo sigue siendo CMD_ERROR, la instrucción es inválida
    if (type == CmdType::CMD_ERROR) {
        return;
    }

    parseInstruction(lowerCmd);
}


void Instruction::parseInstruction(const std::string& cmd)
{
    std::vector<std::string> words;
    std::string buffer;
    std::stringstream stream(cmd);

    while (stream >> buffer) {
        words.push_back(buffer);
    }

    int numWords = words.size();

    switch (type) {
        case CmdType::ADD_SUB:
            if (numWords != 3) return;
            subName = words[1];
            lvl = getLevelFromString(words[2]);
            if (lvl == SecurityLevel::LVL_ERROR) return;
            break;

        case CmdType::ADD_OBJ:
            if (numWords != 3) return;
            objName = words[1];
            lvl = getLevelFromString(words[2]);
            if (lvl == SecurityLevel::LVL_ERROR) return;
            break;

        case CmdType::READ:
            if (numWords != 3) return;
            subName = words[1];
            objName = words[2];
            break;

        case CmdType::WRITE:
            if (numWords != 4) return;
            subName = words[1];
            objName = words[2];
            try {
                value = std::stoi(words[3]);
            } catch (const std::invalid_argument&) {
                return;
            }
            break;

        default:
            return;
    }

    valid = true;
}

SecurityLevel Instruction::getLevelFromString(const std::string& str) const {
    for (int i = 0; i < NUM_SEC_LVLS; ++i) {
        if (LevelStrings[i] == str) {
            return static_cast<SecurityLevel>(i);
        }
    }
    return SecurityLevel::LVL_ERROR;
}

bool Instruction::isValid() const {
    return valid;
}

bool Instruction::isInvalid() const {
    return !valid;
}


std::string Instruction::getSubjectName() const {
    return subName;
}

std::string Instruction::getObjectName() const {
    return objName;
}

SecurityLevel Instruction::getSecurityLevel() const {
    return lvl;
}


int Instruction::getValue() const {
    return value;
}


CmdType Instruction::getType() const {
    return type;
}


std::string Instruction::getInstruction() const {
    return instruction;
}

// Destructor
Instruction::~Instruction() = default;
