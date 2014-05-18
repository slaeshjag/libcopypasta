#ifndef __COPYPASTA_DYNALLOC_H__
#define	__COPYPASTA_DYNALLOC_H__

typedef void C_DYNALLOC;

C_DYNALLOC *c_dynalloc_init(C_DYNALLOC_SIZE_TYPE alloc_step, C_DYNALLOC_SIZE_TYPE element_sz);
C_DYNALLOC_SIZE_TYPE c_dynalloc_alloc(C_DYNALLOC *da);
void c_dynalloc_release(C_DYNALLOC *da, C_DYNALLOC_SIZE_TYPE id);
void *c_dynalloc_get(C_DYNALLOC *da, C_DYNALLOC_SIZE_TYPE id);
C_DYNALLOC_SIZE_TYPE c_dynalloc_entries(struct dynalloc *da);


#endif
