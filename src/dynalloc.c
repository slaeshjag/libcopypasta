#include "dynalloc.h"
#include <stdlib.h>
#include <string.h>


static int dynalloc_expand(struct dynalloc *da) {
	DYNALLOC_SIZE_TYPE i;
	void *used, *avail, *upos, *data;


	used = realloc(da->used, sizeof(*da->used) * (da->total + da->alloc_step));
	avail = realloc(da->avail, sizeof(*da->avail) * (da->total + da->alloc_step));
	upos = realloc(da->upos, sizeof(*da->upos) * (da->total + da->alloc_step));
	data = realloc(da->data, da->element_sz * (da->total + da->alloc_step));

	if (used) da->used = used;
	if (avail) da->avail = avail;
	if (upos) da->upos = upos;
	if (data) da->data = data;

	if (!used || !avail || !upos || !data)
		return 0;

	for (i = 0; i < da->alloc_step; i++) {
		da->used[i + da->total] = -1;
		da->avail[i + da->total] = i + da->total;
		da->upos[i + da->total] = -1;
	}

	da->total += da->alloc_step;
	da->left += da->alloc_step;

	return 1;
}


struct dynalloc *c_dynalloc_init(DYNALLOC_SIZE_TYPE alloc_step, DYNALLOC_SIZE_TYPE element_sz) {
	struct dynalloc *da;

	if (!(da = malloc(sizeof(*da))))
		return NULL;

	da->used = da->avail = da->upos = NULL;
	da->data = NULL;

	da->total = da->left = 0;
	da->element_sz = element_sz;
	da->alloc_step = alloc_step;

	if (!dynalloc_expand(da))
		return free(da->used), free(da->avail), free(da->data), free(da->upos), free(da), NULL;
	
	return da;
}


DYNALLOC_SIZE_TYPE c_dynalloc_alloc(struct dynalloc *da) {
	DYNALLOC_SIZE_TYPE id;

	if (!da)
		return -1;
	if (!da->left)
		if (!dynalloc_expand(da))
			return -1;
	id = da->avail[da->left - 1];
	da->upos[id] = da->avail[da->left - 1];
	da->left--;

	return id;
}


void c_dynalloc_release(struct dynalloc *da, DYNALLOC_SIZE_TYPE id) {
	DYNALLOC_SIZE_TYPE n, used;

	if (!da)
		return;
	if (id < 0 || id >= da->total)
		return;
	if (da->upos[id] == -1)
		return;

	if ((n = da->upos[id]) < 0)
		return;
	
	used = da->total - da->left;
	da->used[n] = da->used[used - 1];
	da->used[used - 1] = -1;
	
	da->upos[da->used[n]] = n;
	da->avail[da->left] = id;
	da->left++;

	return;
}


void *c_dynalloc_get(struct dynalloc *da, DYNALLOC_SIZE_TYPE id) {
	if (!da)
		return NULL;
	if (id < 0 || id >= da->total)
		return NULL;
	if (da->upos[id] == -1)
		return NULL;
	
	return da->data + id * da->element_sz;
}
