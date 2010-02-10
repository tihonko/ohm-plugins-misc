#include <stdlib.h>

#include "backlight-plugin.h"
#include "visibility.h"
#include "mm.h"

#define FALLBACK_DRIVER "null"


/* debug flags */
int DBG_ACTION;

OHM_DEBUG_PLUGIN(backlight,
    OHM_DEBUG_FLAG("action", "policy actions", &DBG_ACTION)
);

OHM_IMPORTABLE(GObject *, signaling_register  , (gchar *uri, gchar **interested));
OHM_IMPORTABLE(gboolean , signaling_unregister, (GObject *ep));

static void select_driver(backlight_context_t *, OhmPlugin *);



/*
 * backlight context
 */

static backlight_context_t context;


/*
 * backlight drivers
 */

backlight_driver_t drivers[] = {
#ifdef HAVE_MCE
    { "mce"  , mce_init  , mce_exit  , mce_enforce   },
#endif
    { "null" , null_init , null_exit , null_enforce  },
    { NULL   , NULL      , NULL      , NULL          }
};



/********************
 * plugin_init
 ********************/
static void
plugin_init(OhmPlugin *plugin)
{
    if (!OHM_DEBUG_INIT(backlight))
        OHM_WARNING("backlight: failed to register for debugging");
    
    if (signaling_register == NULL || signaling_unregister == NULL) {
        OHM_ERROR("backlight: signaling interface not available");
        exit(1);
    }

    select_driver(&context, plugin);
    
    ep_init(&context, signaling_register);
    context.driver->init(&context, plugin);
    
    OHM_INFO("backlight: plugin ready...");
}


/********************
 * plugin_exit
 ********************/
static void
plugin_exit(OhmPlugin *plugin)
{
    (void)plugin;

    FREE(context.action);
    context.action = NULL;

    context.driver->exit(&context);
    ep_exit(&context, signaling_unregister);
}


/********************
 * select_driver
 ********************/
static void
select_driver(backlight_context_t *ctx, OhmPlugin *plugin)
{
    backlight_driver_t *driver;
    char               *cfgdrv;

    cfgdrv = (char *)ohm_plugin_get_param(plugin, "driver");

    if (cfgdrv == NULL)
        cfgdrv = FALLBACK_DRIVER;

    OHM_INFO("backlight: configured driver '%s'", cfgdrv);
    
    for (driver = drivers; driver->name != NULL; driver++) {
        if (!strcmp(driver->name, cfgdrv) ||
            !strcmp(driver->name, FALLBACK_DRIVER))
            break;
    }
    
    if (driver->name == NULL) {
        OHM_ERROR("backlight: failed to find any usable driver");
        exit(1);
    }
    
    ctx->driver = driver;
    
    OHM_INFO("backlight: selected driver '%s'", driver->name);
}


/*****************************************************************************
 *                            *** OHM plugin glue ***                        *
 *****************************************************************************/

EXPORT OHM_PLUGIN_DESCRIPTION(PLUGIN_NAME,
                       PLUGIN_VERSION,
                       "krisztian.litkey@nokia.com",
                       OHM_LICENSE_NON_FREE, /* OHM_LICENSE_LGPL */
                       plugin_init, plugin_exit, NULL);


EXPORT OHM_PLUGIN_REQUIRES_METHODS(PLUGIN_PREFIX, 2, 
    OHM_IMPORT("signaling.register_enforcement_point"  , signaling_register),
    OHM_IMPORT("signaling.unregister_enforcement_point", signaling_unregister));


/* 
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim:set expandtab shiftwidth=4:
 */
