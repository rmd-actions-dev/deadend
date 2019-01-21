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
	@ar rsv $(DIR).a $(OBJECTS) > /dev/null
	@cp $(DIR).a ${DEADEND_SRC}/lib/$(DIR).a

.PHONY: clean
clean :
	@$(RM) $(DIR) $(OBJECTS)
