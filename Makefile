# Project: libcopypasta
MAKEFLAGS	+=	--no-print-directory

TOPDIR		=	$(shell pwd)
export TOPDIR
include config.common.mk

.PHONY: all lib install strip clean

all:
	@echo " [INIT] bin/"
	@$(MKDIR) bin/
	@echo " [ CD ] src/"
	+@make -C src/
	
	@echo "Build complete."
	@echo 

lib:
	@$(MKDIR) bin/
	@echo " [ CD ] src/"
	+@make -C src/
	
clean:
	@echo " [ RM ] bin/"
	+@$(RM) bin/
	@echo " [ CD ] src/"
	+@make -C src/ clean
	@echo
	@echo "Source tree cleaned."
	@echo

strip:
	@echo " [STRP] bin/"
	@strip $(LIB)
	
install: $(INSTARG)
	@$(MKDIR) $(PREFIX)/include/copypasta
	@$(MKDIR) $(PREFIX)/lib
	@$(MKDIR) $(PREFIX)/bin
# Headers
	@echo " [INST] include/copypasta"
	@install -D -m 0755 include/copypasta/dynalloc.h $(PREFIX)/include/copypasta/dynalloc.h
	@install -D -m 0755 include/copypasta/copypasta.h $(PREFIX)/include/copypasta/copypasta.h
	@install -D -m 0755 include/copypasta/$(CONFIG_HEADER) $(PREFIX)/include/copypasta/config.h
	
	@echo " [INST] $(LIBNAME)"
	@install -D -m 0755 $(LIB) $(PREFIX)/lib
	-@ldconfig
	@echo
	@echo "libcopypasta installed."
	@echo 
