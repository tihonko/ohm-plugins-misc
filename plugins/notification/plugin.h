#ifndef __OHM_NOTIFICATION_PLUGIN_H__
#define __OHM_NOTIFICATION_PLUGIN_H__

#include <stdint.h>
#include <glib.h>
#include <glib-object.h>
#include <gmodule.h>
#include <ohm/ohm-plugin.h>
#include <ohm/ohm-plugin-log.h>
#include <ohm/ohm-plugin-debug.h>

#define EXPORT __attribute__ ((visibility ("default")))
#define HIDE   __attribute__ ((visibility ("hidden")))

#ifdef  G_MODULE_EXPORT
#undef  G_MODULE_EXPORT
#define G_MODULE_EXPORT EXPORT
#endif

#define DIM(a)   (sizeof(a) / sizeof(a[0]))

/*
 * FactStore prefix's 
 */
#define FACTSTORE_PREFIX        "com.nokia.policy"
#define FACTSTORE_NOTIFICATION  FACTSTORE_PREFIX ".notification"

/*
 * notification ID's
 */
#define SEQNO_BITS              31
#define TYPE_BITS               1
#define SEQNO_MASK              ((((uint32_t)1) << SEQNO_BITS) - 1)
#define TYPE_MASK               ((((uint32_t)1) << TYPE_BITS)  - 1)
#define NOTIFICATION_TYPE(id)   (((id) >> SEQNO_BITS) & TYPE_MASK)
#define NOTIFICATION_SEQNO(id)  ((id) & SEQNO_MASK)
#define NOTIFICATION_ID(t,s)  \
  ((((uint32_t)(t) & TYPE_MASK) << SEQNO_BITS) | ((uint32_t)(s) & SEQNO_MASK))

#if (SEQNO_BITS + TYPE_BITS) > 32
#error "Notification ID is wider than 32 bit"
#endif

typedef enum {
    unknown_id = -1,

    regular_id = 0,
    longlive_id,

    max_id
} notification_id_type_t;

extern int DBG_PROXY, DBG_LLIV, DBG_SUBSCR, DBG_RESRC, DBG_DBUS, DBG_RULE;


/*
static void plugin_init(OhmPlugin *);
static void plugin_destroy(OhmPlugin *);
*/


#endif /* __OHM_NOTIFICATION_PLUGIN_H__ */

/* 
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim:set expandtab shiftwidth=4:
 */
