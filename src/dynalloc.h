#ifndef __DYNALLOC_H__
#define	__DYNALLOC_H__


#ifndef DYNALLOC_SIZE_TYPE
	#define	DYNALLOC_SIZE_TYPE	int
#endif

#ifdef USE_ANSIC
	#define	DYNALLOC_DATA_TYPE	unsigned char
#else
	#define	DYNALLOC_DATA_TYPE	void
#endif

struct dynalloc {
	DYNALLOC_DATA_TYPE		*data;

	DYNALLOC_SIZE_TYPE		*used;
	DYNALLOC_SIZE_TYPE		*avail;
	DYNALLOC_SIZE_TYPE		*upos;

	DYNALLOC_SIZE_TYPE		total;
	DYNALLOC_SIZE_TYPE		left;

	DYNALLOC_SIZE_TYPE		alloc_step;
	DYNALLOC_SIZE_TYPE		element_sz;
};


#endif
