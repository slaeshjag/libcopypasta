#ifndef __COPYPASTA_DYNALLOC_H__
#define	__COPYPASTA_DYNALLOC_H__

typedef void C_DYNALLOC;

C_DYNALLOC *c_dynalloc_init(C_DYNALLOC_SIZE_TYPE alloc_step, C_DYNALLOC_SIZE_TYPE element_sz);
C_DYNALLOC_SIZE_TYPE c_dynalloc_alloc(struct dynalloc *da);
void c_dynalloc_release(struct dynalloc *da, C_DYNALLOC_SIZE_TYPE id);
void *c_dynalloc_get(struct dynalloc *da, C_DYNALLOC_SIZE_TYPE id);


#endif
