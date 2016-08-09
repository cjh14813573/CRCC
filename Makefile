#/*==========================================================================*
# *    Copyright(c) 2001-2004, Emerson Network Power Co., Ltd.
# *                     ALL RIGHTS RESERVED
# *
# *  PRODUCT  : ACU(Advanced Controller Unit)
# *
# *  FILENAME : Makefile
# *  CREATOR  : Frank Mao                DATE: 2004-09-10 19:58
# *  VERSION  : V1.00
# *  PURPOSE  : The make file for main application of ACU.
# *
# *  HISTORY  :
# *
# *==========================================================================*/

include ./config.in
#the target output file
EXEC = rtu

#the head files the object files depend on
INCS =

#the object files to generate the target
OBJS =
#get *.c file in sub dir
SRC = $(shell find ./ -name '*.c')
OBJS = $(SRC:.c=.o)


#private shared libraries
LIBS = 

all: $(EXEC)

$(EXEC): $(OBJS) $(INCS) $(PUBINCS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LIBS) $(PUBLIBS)
	
ifeq ($(MAKE_VERSION), debug)
install: $(EXEC)
	-mkdir -p $(INSTALL_PATH)/
	cp -fr $(EXEC) $(INSTALL_PATH)/$(EXEC)
	chmod +x $(INSTALL_PATH)/$(EXEC)
else
install: $(EXEC)
	-mkdir -p $(INSTALL_PATH)/
	#-cp $(EXEC) $(INSTALL_PATH)/
	$(STRIP) -s -o $(INSTALL_PATH)/$(EXEC) $(EXEC)
	chmod +x $(INSTALL_PATH)/$(EXEC)

endif
			
clean:
	-rm -rf $(EXEC) $(OBJS) *.gdb *.elf *.o
	-rm -f *.map  




