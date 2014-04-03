# Project: libcopypasta
include $(TOPDIR)/config.common.mk

OUTLIB		=	../bin/libcopypasta_s.a

ifeq ($(strip $(OS)), Windows_NT)
	DEPENDS	+=	copypasta.res
endif

SRCFILES	=	$(wildcard *.c)
OBJFILES	=	$(SRCFILES:.c=.o)
.PHONY: all clean

all: $(OBJFILES) $(DEPENDS)
	@echo " [ LD ] $(LIB)"
	@$(CC) $(CFLAGS) $(OBJFILES) -o $(LIB) $(LDFLAGS)
	@echo " [ AR ] $(OUTLIB)"
	@$(AR) -cr $(OUTLIB) *.o
	@echo "Done."
	@echo
	
clean:
	@echo
	@echo " [ RM ] $(OBJFILES)"
	@$(RM) $(OBJFILES)
	@$(RM) copypasta.res
	@echo "Done."
	@echo 

%.o: %.c %.h
	@echo " [ CC ] src/$<"
	@$(CC) $(CFLAGS) -c -o $@ $<
	
darnit.res:
	@windres copypasta.rc -O coff -o copypasta.res

