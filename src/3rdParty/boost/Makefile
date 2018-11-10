# We want to untar the boost directory on install
default :
	$(info Untarring boost 1.61.0 files.) 
	@$(shell tar -zxf boost_1_61_0.tar.gz --skip-old-files)
clean : 
	$(info Removing all untarred boost 1.61.0 files.)
	@$(shell rm -rf boost_1_61_0)
