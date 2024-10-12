all: blpsecure

blpsecure: build/BlpSecure.o build/ReferenceMonitor.o build/Instruction.o build/Subject.o build/Object.o
	g++ -std=c++11 -o blpsecure build/BlpSecure.o build/ReferenceMonitor.o build/Instruction.o build/Subject.o build/Object.o

build/BlpSecure.o: src/BLPSecure.cpp include/referenceMonitor.h include/instruction.h include/subject.h include/object.h
	g++ -std=c++11 -c -o build/BlpSecure.o src/BLPSecure.cpp -Iinclude

build/ReferenceMonitor.o: src/referenceMonitor.cpp include/referenceMonitor.h
	g++ -std=c++11 -c -o build/ReferenceMonitor.o src/referenceMonitor.cpp -Iinclude

build/Instruction.o: src/instruction.cpp include/instruction.h
	g++ -std=c++11 -c -o build/Instruction.o src/instruction.cpp -Iinclude

build/Subject.o: src/subject.cpp include/subject.h
	g++ -std=c++11 -c -o build/Subject.o src/subject.cpp -Iinclude

build/Object.o: src/object.cpp include/object.h
	g++ -std=c++11 -c -o build/Object.o src/object.cpp -Iinclude

clean:
	rm -f build/*.o blpsecure
