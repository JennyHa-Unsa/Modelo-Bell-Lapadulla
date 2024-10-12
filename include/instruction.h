#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <vector>

// Tipos de datos para Instruction y SecurityLevel
enum class CmdType { ADD_SUB, ADD_OBJ, READ, WRITE, CMD_ERROR };
enum class SecurityLevel { LOW, MEDIUM, HIGH, LVL_ERROR };

// Instrucciones para ReferenceMonitor
class Instruction {
public:
    explicit Instruction(const std::string& command);

    // Número de tipos de comandos y niveles de seguridad
    static constexpr int NUM_CMD_TYPES = 4;
    static constexpr int NUM_SEC_LVLS = 3;

    bool isValid() const;
    bool isInvalid() const;
    std::string getSubjectName() const;
    std::string getObjectName() const;
    std::string getInstruction() const;
    SecurityLevel getSecurityLevel() const;
    int getValue() const;
    CmdType getType() const;

    ~Instruction() = default;

private:
    // Las cadenas que representan los niveles de seguridad y los tipos de instrucciones en las cadenas de instrucciones
    const std::vector<std::string> LevelStrings = {"low", "medium", "high"};
    const std::vector<std::string> TypeStrings = {"addsub", "addobj", "read", "write"};

    std::string subName;     // El nombre del sujeto
    std::string objName;     // El nombre del objeto
    std::string instruction; // La cadena de instrucciones
    CmdType type;            // El tipo de comando
    SecurityLevel lvl;       // El nivel de seguridad
    bool valid;              // Es una Instrucción válida
    int value;               // El valor (si se proporciona)

    void parseInstruction(const std::string& command);
    SecurityLevel getLevelFromString(const std::string& str) const;
};

#endif // INSTRUCTION_H
