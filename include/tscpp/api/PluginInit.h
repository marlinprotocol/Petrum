#pragma once
#include <ts/apidefs.h>
#include "tscpp/api/utils.h"
extern "C" {

/**
 * Invoked for "general" plugins - listed in plugin.config. The arguments in the
 * plugin.config line are provided in this invocation.
 *
 * @param argc Count of arguments
 * @param argv Array of pointers pointing to arguments
 */
void TSPluginInit(int argc, const char *argv[]);
/**
 * Invoked for remap plugins - listed in remap.config. The arguments provided as @pparam
 * in the remap.config line are provided in this invocation.
 *
 * @param argc Count of arguments
 * @param argv Array of pointers pointing to arguments
 * @param instance_handle Should be passed to the RemapPlugin constructor
 * @param errbuf Not used
 * @param errbuf_size Not used
 */
TSReturnCode TSRemapNewInstance(int argc, char *argv[], void **instance_handle, char *errbuf, int errbuf_size);
}
