#include "modcomm.h"

struct c_modcomm_msg_s c_modcomm_mod_msg_cback(struct c_modcomm_msg_s msg);

struct modcomm_h_s *c_modcomm_init(const char *library, int max_entries) {
	struct modcomm_h_s *mch;
	int i;

	if (!(mch = malloc(sizeof(*mch))))
		return NULL;
	#ifdef _WIN32
		#error Windows is not yet supported by modcomm
	#else
		if (!(mch->libhandle = dlopen(library, RTLD_NOW | RTLD_LOCAL))) {
			free(mch);
			return NULL;
		}

	#endif

	mch->max_entries = max_entries;
	mch->entry = calloc(sizeof(*mch->entry), mch->max_entries);

	mch->num_available = max_entries;
	for (i = 0; i < max_entries; mch->available[i] = i, i++);
	
	return mch;
}


struct c_modcomm_msg_s c_modcomm_mod_msg(struct modcomm_h_s *mch, struct c_modcomm_msg_s msg, int iter) {
	int n;

	for (;;) {
		msg.mch = mch;
		msg.callback = c_modcomm_mod_msg_cback;
		if (msg.to < 0 || msg.to >= mch->max_entries || !mch->entry[msg.to].func) {
			msg.error = msg.msg;
			msg.msg = COPYPASTA_MODCOMM_MSG_NOAI;
			n = msg.from, msg.from = msg.to, msg.to = n;
			if (msg.from < 0 || msg.from >= mch->max_entries || !mch->entry[msg.from].func) {
				return msg;
			} else {
				continue;
			}
		}

		if (msg.msg == COPYPASTA_MODCOMM_MSG_END)
			return msg;
		msg = mch->entry[msg.to].func(msg, mch->entry[msg.to].data);
		if (!iter)
			return msg;
	}

	return msg;
}


struct c_modcomm_msg_s c_modcomm_mod_msg_cback(struct c_modcomm_msg_s msg) {
	return c_modcomm_mod_msg(msg.mch, msg, 0);
}


int c_modcomm_mod_new_with_func(struct modcomm_h_s *mch, struct c_modcomm_msg_s (*f)(struct c_modcomm_msg_s msg, void *data), void *data) {
	struct modcomm_e_s *mod;
	int id;
	
	if (!mch->num_available)
		return -1;
	mod = &mch->entry[id = --mch->num_available];
	mod->func = f;
	mod->data = data;

	return id;
}


int c_modcomm_mod_new(struct modcomm_h_s *mch, const char *func, void *data) {
	/* C89/Ansi C hack */
	union {
		struct c_modcomm_msg_s (*f)(struct c_modcomm_msg_s msg, void *data);
		void *p;
	} tcast;

	#ifdef _WIN32
		#error Windows is not yet supported by modcomm
	#else
	if (!(tcast.p = dlsym(mch->libhandle, func)))
		return -1;
	#endif
	
	return c_modcomm_mod_new_with_func(mch, tcast.f, data);
}


int c_modcomm_mod_free(struct modcomm_h_s *mch, int id) {
	if (mch->max_entries >= id || !mch->entry[id].func)
		return -1;
	mch->available[mch->num_available++] = id, mch->entry[id].func = NULL;
	return -1;
}


void *c_modcomm_unload(struct modcomm_h_s *mch) {
	#ifdef _WIN32
		#error Windows is not yet supported by modcomm
	#else
		dlclose(mch->libhandle);
		free(mch);
	#endif
	
	return NULL;
}
