# deadend
Basic server library. Uses boost 1.61.0.

At the present moment these environment variables must be set:

export DEADEND_TOP=/home/{user.name}/deadend

export DEADEND_SRC=$DEADEND_TOP/src

export LD_LIBRARY_PATH=$DEADEND_SRC/3rdParty/boost/boost_1_61_0/stage/lib:$LD_LIBRARY_PATH

TODOs
Client side connections
Cleaner interface for creating server dialogs
Logging
Integrate with Apache
Better way to manage include paths (I.E not relative)
A way to rebuild boost if changes should occur
Configuration Files
UDP Server/Client
SSL (Eventually)
HTTP Document Retrieval
Actually using signals
Stop applications without coring

Apparently this is also now for marketplace testing
