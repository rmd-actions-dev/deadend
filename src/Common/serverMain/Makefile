# Wildcards to compile any .cc files against boost
SOURCES := $(wildcard *.cc)
OBJECTS := $(patsubst %.cc,%.o,$(SOURCES))
SRC = ${DEADEND_SRC}
CXX := g++ -std=c++11 -Wall -g -I $(SRC)/3rdParty/boost/boost_1_61_0 \
   $(SRC)/libs/libboost_system.so 

.cc.o:
	@${CXX} -c $<

default: $(OBJECTS)
	@$(CXX) -o serverMain $(OBJECTS)
clean :
	@$(RM) serverMain $(OBJECTS)

