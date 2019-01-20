# Wildcards to compile any .cc files against boost
SOURCES := $(wildcard *.cc)
LIBS    := $(wildcard ${DEADEND_SRC}/lib/*.a)
OBJECTS := $(patsubst %.cc,%.o,$(SOURCES))
DIR = $(shell basename $(CURDIR))

include ${DEADEND_SRC}/default.mk

.cc.o:
	@${CXX} -c $<
.PHONY: all
all : $(OBJECTS)
	@$(CXX) -o $(DIR) $(OBJECTS) $(LIBS)

.PHONY: clean
clean :
	@$(RM) $(DIR) $(OBJECTS)
