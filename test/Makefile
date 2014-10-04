# $Id: prog.tmpl,v 1.3 2008/11/04 17:00:50 tho Exp $

include common.mk
include ../Makefile.conf

PROG = test
SRCS = main.c

LDADD   += ../librack/librack.a
LDADD   += ../libhobbit/libhobbit.a
LDADD   += $(LIBR3_LDADD)
LDFLAGS += -L/usr/local/lib -lpcre

include prog.mk
