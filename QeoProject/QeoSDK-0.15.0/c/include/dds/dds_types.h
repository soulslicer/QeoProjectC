#ifndef __dds_types_h_
#define __dds_types_h_

#include <stddef.h>

#include "dds/dds_seq.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define	DDS_DOMAINID		unsigned
#define	DDS_HANDLE		unsigned
#define DDS_HANDLE_NIL		0U
#define	DDS_HANDLE_DEFAULT	1U
#define	DDS_BUILTIN_TOPIC_TYPE	unsigned

typedef unsigned DDS_MemberId;

/* Create a new type as a fixed-size array of the given type: */
#define	DDS_ARRAY(type,nelem,name)		\
typedef type name [nelem]

/* Create a union with the given enumtype as discriminant. */
#define DDS_UNION(type,disctype,name)   	\
typedef struct name ## _st {            	\
    disctype discriminant;              	\
    type     u;                         	\
} name

typedef struct DDS_TypeSupport_st *DDS_TypeSupport;

#ifdef  __cplusplus
}
#endif

#endif /* !__dds_types_h_ */

