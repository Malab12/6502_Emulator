build: src/main.cpp lib/6502_memory.cpp lib/6502_processor.cpp
	gcc -o processor src/main.cpp lib/6502_memory.cpp lib/6502_processor.cpp