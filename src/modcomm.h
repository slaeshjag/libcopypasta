#ifndef __MODCOMM_H__
#define	__MODCOMM_H__

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


enum modcomm_msg_e {
	MODCOMM_MSG_INIT,
	MODCOMM_MSG_LOOP,
	MODCOMM_MSG_KILL,
	MODCOMM_MSG_SEND,
	MODCOMM_MSG_NOAI,
	MODCOMM_MSG_END
};


struct modcomm_h_s {
	void			*libhandle;
	struct modcomm_e_s	*entry;
	int			max_entries;
	int			*available;
	int			num_available;
};


struct modcomm_msg_s {
	enum modcomm_msg_e	msg;
	int			from;
	int			error;
	int			to;
	int			arg[8];
	void			*argp;

	struct modcomm_msg_s	(*callback)(struct modcomm_msg_s msg);
	struct modcomm_h_s	*mch;
};


struct modcomm_e_s {
	struct modcomm_msg_s	(*func)(struct modcomm_msg_s msg, void *data);
	void			*data;
};


#endif
