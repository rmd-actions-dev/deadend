# Default makefile with boost includes and linkers
SRC = ${DEADEND_SRC}
CXX := g++ -std=c++11 -Wall -g -lboost_system -I $(SRC)/3rdParty/boost/boost_1_61_0 -L $(SRC)/3rdParty/boost/boost_1_61_0/stage/lib -pthread
