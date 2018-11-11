# Wildcards to compile any .cc files against boost
SOURCES := $(wildcard *.cc)
OBJECTS := $(patsubst %.cc,%.o,$(SOURCES))
DIR = $(shell basename $(CURDIR))

include ${DEADEND_SRC}/default.mk

.cc.o:
	@${CXX} -c $<
.PHONY: all
all : $(OBJECTS)
	@$(CXX) -o $(DIR) $(OBJECTS)

.PHONY: clean
clean :
	@$(RM) $(DIR) $(OBJECTS)
