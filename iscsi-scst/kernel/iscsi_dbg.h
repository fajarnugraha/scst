#ifndef ISCSI_DBG_H
#define ISCSI_DBG_H

#include <scst_debug.h>

#define TRACE_D_READ		0x80000000
#define TRACE_D_WRITE		0x40000000
#define TRACE_CONN_OC		0x20000000
#define TRACE_D_IOV		0x10000000
#define TRACE_D_DUMP_PDU	0x08000000

#define TRACE_D_DATA		(TRACE_D_READ | TRACE_D_WRITE)

#define TRACE_ALL_NO_DATA	(TRACE_ALL & ~TRACE_D_IOV & ~TRACE_D_DUMP_PDU & ~TRACE_D_DATA)

#define LOG_PREFIX "iscsi-scst"

#ifdef DEBUG
#define ISCSI_DEFAULT_LOG_FLAGS (TRACE_FUNCTION | TRACE_LINE | TRACE_PID | \
	TRACE_OUT_OF_MEM | TRACE_MGMT | TRACE_MGMT_DEBUG | \
	TRACE_MINOR | TRACE_SPECIAL | TRACE_CONN_OC)
#else
#define ISCSI_DEFAULT_LOG_FLAGS (TRACE_FUNCTION | TRACE_PID | \
	TRACE_OUT_OF_MEM | TRACE_MGMT | \
	TRACE_MINOR | TRACE_SPECIAL)
#endif

#ifdef DEBUG
struct msghdr;
struct iscsi_pdu;
extern void iscsi_dump_iov(struct msghdr *msg);
extern void iscsi_dump_pdu(struct iscsi_pdu *pdu);
#else
#define iscsi_dump_iov(x) do {} while (0)
#define iscsi_dump_pdu(x) do {} while (0)
#endif

#if defined(DEBUG) || defined(TRACING)
extern unsigned long iscsi_trace_flag;
#define trace_flag iscsi_trace_flag

#define TRACE_CONN_CLOSE(format, args...)	                    \
do {                                                                \
  if (trace_flag & TRACE_CONN_OC) 	                            \
  {                                                                 \
    char *__tflag = LOG_FLAG;                                       \
    if (debug_print_prefix(trace_flag, __FUNCTION__, __LINE__) > 0) \
    {                                                               \
      __tflag = NO_FLAG;                                            \
    }                                                               \
    PRINT(NO_FLAG, "%s" format, __tflag, args);                     \
  }                                                                 \
} while(0)

#else /* defined(DEBUG) || defined(TRACING) */
#define TRACE_CONN_CLOSE(format, args...) {}
#endif

#endif
