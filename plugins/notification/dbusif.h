#ifndef __OHM_NOTIFICATION_DBUSIF_H__
#define __OHM_NOTIFICATION_DBUSIF_H__

#include <stdint.h>

/* hack to avoid multiple includes */
typedef struct _OhmPlugin OhmPlugin;

/* D-Bus errors */
#define DBUS_NGF_ERROR_PREFIX         "com.nokia.Error"

#define DBUS_NGF_ERROR_FORMAT          DBUS_NGF_ERROR_PREFIX ".MessageFormat"
#define DBUS_NGF_ERROR_INTERNAL        DBUS_NGF_ERROR_PREFIX ".Failed"
#define DBUS_NGF_ERROR_DENIED          DBUS_NGF_ERROR_PREFIX ".RequestDenied"
#define DBUS_NGF_ERROR_NO_BACKEND      DBUS_NGF_ERROR_PREFIX ".ServiceUnknown"
#define DBUS_NGF_ERROR_BACKEND_METHOD  DBUS_NGF_ERROR_PREFIX ".BackendMethod"


/* D-Bus service names */
#define DBUS_ADMIN_SERVICE             "org.freedesktop.DBus"
#define DBUS_NGF_PROXY_SERVICE         "com.nokia.NonGraphicFeedback1"
#define DBUS_NGF_BACKEND_SERVICE       "com.nokia.NonGraphicFeedback1.Backend"

/* D-Bus pathes */
#define DBUS_ADMIN_PATH                "/org/freedesktop/DBus"
#define DBUS_POLICY_DECISION_PATH      "/com/nokia/policy/decision"
#define DBUS_NGF_PATH                  "/com/nokia/NonGraphicFeedback1"

/* D-Bus interface names */
#define DBUS_ADMIN_INTERFACE           "org.freedesktop.DBus"
#define DBUS_POLICY_DECISION_INTERFACE "com.nokia.policy"
#define DBUS_NGF_INTERFACE             "com.nokia.NonGraphicFeedback1"

/* D-Bus signal & method names */
#define DBUS_GET_NAME_OWNER_METHOD     "GetNameOwner"
#define DBUS_PLAY_METHOD               "Play"
#define DBUS_STOP_METHOD               "Stop"
#define DBUS_STATUS_METHOD             "Status"

#define DBUS_NAME_OWNER_CHANGED_SIGNAL "NameOwnerChanged"
#define DBUS_POLICY_NEW_SESSION_SIGNAL "NewSession"

/*
 * error buffer sizes
 */
#define DBUS_ERRBUF_LEN   256
#define DBUS_DESCBUF_LEN  512


/*
 * types shall match the corresponding DBUS_TYPE_xxx definitions
 */
#define DBUSIF_STRING_ARG(n,v)   (char*)n, (int)'s', (char *)(v)
#define DBUSIF_INTEGER_ARG(n,v)  (char*)n, (int)'i', (int32_t)(v)
#define DBUSIF_UNSIGNED_ARG(n,v) (char*)n, (int)'u', (uint32_t)(v)
#define DBUSIF_DOUBLE_ARG(n,v)   (char*)n, (int)'d', (double)(v)
#define DBUSIF_BOOLEAN_ARG(n,v)  (char*)n, (int)'b', (uint32_t)((v)?TRUE:FALSE)
#define DBUSIF_ARGLIST_END       NULL, (int)0, (void *)0 


void dbusif_init(OhmPlugin *);
DBusHandlerResult dbusif_session_notification(DBusConnection *,
                                              DBusMessage *, void *);
void *dbusif_append_to_play_data(void *, ...);
void *dbusif_copy_status_data(const char *, void *);
void *dbusif_create_status_data(char *, uint32_t, uint32_t);
void *dbusif_create_stop_data(uint32_t);
void  dbusif_forward_data(void *);
void  dbusif_free_data(void *);

#endif	/* __OHM_NOTIFICATION_DBUSIF_H__ */

/* 
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim:set expandtab shiftwidth=4:
 */
