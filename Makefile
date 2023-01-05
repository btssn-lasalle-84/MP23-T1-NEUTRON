DEBUG = oui
TARGET = neutron.out
MAIN = main
IHM = Ihm
PLATEAU = Plateau
JEUNEWTON = JeuNewton
SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.h)

CFLAGS = -std=c++11 -Wall -I.
ifeq ($(DEBUG),oui)
	CXX = g++ $(CFLAGS) -c -DDEBUG
else
	CXX = g++ $(CFLAGS) -c
endif
DEBUG = g++ $(CFLAGS) -c -DDEBUG
LD = g++ -o
RM = rm -f

all: $(TARGET)

$(TARGET): $(MAIN).o $(IHM).o $(PLATEAU).o $(JEUNEWTON).o
	$(LD) $(TARGET) $^ $(CFLAGS)

$(MAIN).o: $(MAIN).cpp
	$(CXX) $^

$(IHM).o: $(IHM).cpp
	$(CXX) $^

$(PLATEAU).o: $(PLATEAU).cpp
	$(CXX) $^

$(JEUNEWTON).o: $(JEUNEWTON).cpp
	$(CXX) $^

.PHONY: check cppcheck format clean cleanall

check:
	clang-tidy $(SOURCES) --quiet -header-filter='.*' -checks=-*,boost-*,bugprone-*,performance-*,readability-*,portability-*,modernize-use-nullptr,clang-analyzer-*,cppcoreguidelines-* --format-style=none -- -std=c++11

cppcheck:
	cppcheck --enable=all --std=c++11 --platform=unix64 --suppress=missingIncludeSystem --quiet $(SOURCES)

format:
	find . -regex '.*\.\(cpp\|h\)' -exec clang-format -i --style=file {} \;

clean:
	$(RM) *.o

cleanall:
	$(RM) *.o* *.*~ $(TARGET)
