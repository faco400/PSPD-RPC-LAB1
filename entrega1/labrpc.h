/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _LABRPC_H_RPCGEN
#define _LABRPC_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct vetor {
	float v[500000];
};
typedef struct vetor vetor;

#define ENTREGA1 88888
#define VERSAO 100

#if defined(__STDC__) || defined(__cplusplus)
#define max 1
extern  float * max_100(vetor *, CLIENT *);
extern  float * max_100_svc(vetor *, struct svc_req *);
#define min 2
extern  float * min_100(vetor *, CLIENT *);
extern  float * min_100_svc(vetor *, struct svc_req *);
extern int entrega1_100_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define max 1
extern  float * max_100();
extern  float * max_100_svc();
#define min 2
extern  float * min_100();
extern  float * min_100_svc();
extern int entrega1_100_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_vetor (XDR *, vetor*);

#else /* K&R C */
extern bool_t xdr_vetor ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_LABRPC_H_RPCGEN */
