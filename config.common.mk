# Project: libcopypasta
# Makefile configurations

LIBNAME		=	libcopypasta.so
LIB		=	$(TOPDIR)/bin/$(LIBNAME)

VERSION		=	v.0.1
#DBGFLAGS	=	-O0 -g -D__DEBUG__
DBGFLAGS	=	-O3
#General flags
CFLAGS		+=	-Wall -Wextra -shared -fPIC $(DBGFLAGS)
LDFLAGS		+=	-Wl,-soname,$(LIBNAME)
PREFIX		=	/usr/local

#Extra install targets
INSTARG		=	

#Makefile tools
RM		=	rm -Rf
MKDIR		=	mkdir -p

include		$(TOPDIR)/config.mk


ifneq (,$(findstring -DDYNALLOC_LARGE, $(CFLAGS)))
CFLAGS		+=	-DDYNALLOC_DATA_TYPE="long long int"
CONFIG_HEADER	=	config_large.h
else
CONFIG_HEADER	=	config.h
endif
