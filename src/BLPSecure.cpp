#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "instruction.h"
#include "referencemonitor.h"

void printUsage(const char* programName) {
    std::cout << "USO: ./" << programName << " FILENAME\n";
}

void handleFileError(const char* filename) {
    std::cerr << "No se pudo abrir el archivo: " << filename << ". Terminando.\n";
    std::exit(EXIT_FAILURE);
}

void processInstructions(std::ifstream& inputFile, ReferenceMonitor& refMon) {
    int instructionCount = 0;
    std::string line;
    while (std::getline(inputFile, line)) {
        if (instructionCount && instructionCount % 10 == 0) {
            refMon.printState();
        }

        Instruction instruction(line);
        if (instruction.isInvalid() || !refMon.executeInstruction(instruction)) {
            std::cout << std::left << std::setw(16) << "Instrucción Incorrecta";
            std::cout << ": " << line << std::endl;
        }

        instructionCount++;
    }
    refMon.printState();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    ReferenceMonitor refMon;
    const char* filename = argv[1];
    std::ifstream inputFile(filename);

    if (!inputFile.good()) {
        handleFileError(filename);
    }

    processInstructions(inputFile, refMon);

    return EXIT_SUCCESS;
}
