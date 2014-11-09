#ifndef __MODCOMM_H__
#define	__MODCOMM_H__

#include <stdio.h>
#include <stdlib.h>

#define	COPYPASTA_MODCOMM_INTERNAL
#include <copypasta/modcomm.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

struct modcomm_h_s {
	void			*libhandle;
	struct modcomm_e_s	*entry;
	int			max_entries;
	int			*available;
	int			num_available;
};


struct modcomm_e_s {
	struct c_modcomm_msg_s	(*func)(struct c_modcomm_msg_s msg, void *data);
	void			*data;
};


#endif
