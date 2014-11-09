#ifndef __COPYPASTA_MODCOMM_H__
#define	__COPYPASTA_MODCOMM_H__

#ifndef COPYPASTA_MODCOMM_INTERNAL
	typedef void c_modcomm_handle;
#endif


enum c_modcomm_msg_e {
	COPYPASTA_MODCOMM_MSG_INIT,
	COPYPASTA_MODCOMM_MSG_LOOP,
	COPYPASTA_MODCOMM_MSG_KILL,
	COPYPASTA_MODCOMM_MSG_SEND,
	COPYPASTA_MODCOMM_MSG_NOAI,
	COPYPASTA_MODCOMM_MSG_END
};

struct c_modcomm_msg_s {
	enum c_modcomm_msg_e	msg;
	int			from;
	int			error;
	int			to;
	int			arg[8];
	void			*argp;

	struct c_modcomm_msg_s	(*callback)(struct c_modcomm_msg_s msg);

	#ifdef COPYPASTA_MODCOMM_INTERNAL
	struct modcomm_h_s	*mch;
	#else
	c_modcomm_handle	*mch;
	#endif
};

#ifndef COPYPASTA_MODCOMM_INTERNAL
c_modcomm_handle *c_modcomm_init(const char *library, int max_entries);
struct c_modcomm_msg_s c_modcomm_mod_msg(c_modcomm_handle *h, struct c_modcomm_msg_s msg, int iter);
int c_modcomm_mod_new_with_func(c_modcomm_handle *h, struct c_modcomm_msg_s (*f)(struct c_modcomm_msg_s msg, void *data), void *data);
int c_modcomm_mod_new(c_modcomm_handle *h, const char *func, void *data);
int c_modcomm_mod_free(c_modcomm_handle *h, int id);
void c_modcomm_unload(c_modcomm_handle *h);
#endif

#endif
