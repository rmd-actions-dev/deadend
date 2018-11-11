# Current DIR
CURDIR = $(shell pwd)
# BOOST config
BOOST_BOOTSTRAP_FLAGS = --prefix=${DEADEND_SRC} --includedir=$(DEADEND_TOP)/include/3rdParty --with-libraries="atomic,date_time,exception,filesystem,iostreams,program_options,random,regex,serialization,system,thread" 
BOOST_BUILD_USER_CONFIG = $(CURDIR)/config.jam
export BOOST_BUILD_USER_CONFIG

# We want to untar the boost directory on install
default :
ifeq ($(wildcard boost_1_61_0/.),)
	$(info Untarring boost 1.61.0 files.) 
	@tar --bzip2  -xf boost_1_61_0.tar.bz2 
	@cd boost_1_61_0 && ./bootstrap.sh $(BOOST_BOOTSTRAP_FLAGS) && ./b2 -d0 -sNO_BZIP2=1
else
	$(info Boost has already been built.)
endif
clean : 
	$(info Removing all untarred boost 1.61.0 files.)
	@$(shell rm -rf boost_1_61_0)
