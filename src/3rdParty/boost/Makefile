# We want to untar the boost directory on install
default :
	$(info Untarring boost 1.61.0 files.) 
	@tar -zxf boost_1_61_0.tar.gz --skip-old-files
	@cd boost_1_61_0 && ./bootstrap.sh --prefix=${DEADEND_SRC}/install --libdir=${DEADEND_SRC}/libs --includedir=${DEADEND_SRC}/include
	@cd boost_1_61_0 && ./b2 install
clean : 
	$(info Removing all untarred boost 1.61.0 files.)
	@$(shell rm -rf boost_1_61_0)
