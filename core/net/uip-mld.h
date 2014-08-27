#ifndef __MLD_H__
#define __MLD_H__

#include "contiki-conf.h"

#if UIP_CONF_MLD

#include <stdbool.h>

#include "net/uip.h"
#include "net/uip-ds6.h"

/** \name MLDv1 message processing and multicast listener reporting */
/** @{ */
/** \brief Report timeout for multicast adresses, in seconds.
 */
#define UIP_IP6_MLD_REPORT_INTERVAL 10

/**
 */
void
uip_icmp6_mldv1_schedule_report(uip_ds6_maddr_t *addr);

/**
 * \brief Send an MLDv1 listener report for the specified maddr
 * \param addr Address to send a report for
 */
void
uip_icmp6_mldv1_report(uip_ip6addr_t *addr);

/**
 * \brief Send an MLDv1 listener done for the specified maddr
 * \param addr Address to send a "done" for
 */
void
uip_icmp6_mldv1_done(uip_ip6addr_t *addr);

/** \brief Process an MLDv1 query and send multicast listener reports for
 * suitable addresses.
 */
void
uip_icmp6_ml_query_input(void);

/** \brief Process an MLDv1 report and suppress listener reports for
 * suitable addresses.
 */
void
uip_icmp6_ml_report_input(void);

/**
 * \brief Checks whether MLD works has to be done, and if so, does it.
 */
void
uip_mld_periodic(void);

extern struct etimer uip_mld_timer_periodic;

/** @} */

#endif

#endif /*__MLD_H__*/
