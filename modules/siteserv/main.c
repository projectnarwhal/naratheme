/*
 * Copyright (c) 2012 Phos <phosphos0@gmail.com>
 * Rights to this code are documented in doc/LICENSE.
 *
 * This file contains the main() routine.
 *
 */

#include "atheme.h"

DECLARE_MODULE_V1
(
  "siteserv/main", false, _modinit, _moddeinit,
  PACKAGE_STRING,
  "Phos <phosphos0@gmail.com>"
);

service_t *siteserv;

static void siteserv_cmd_help(sourceinfo_t *si, const int parc, char *parv[]);

command_t siteserv_help = {
  "HELP",
  N_(N_("Displays contextual help information.")),
  PRIV_SITE_INT,
  20,
  siteserv_cmd_help,
  { .path = "help" }
};

/* HELP <command> [params] */
void siteserv_cmd_help(sourceinfo_t *si, int parc, char *parv[])
{
  char *command = parv[0];

  if (!command)
  {
    command_success_nodata(si, _("***** \2%s Help\2 *****"), si->service->nick);
    command_success_nodata(si, _("\2%s\2 allows for advanced site-IRC integration."), si->service->nick);
    command_success_nodata(si, " ");
    command_success_nodata(si, _("For more information on a command, type:"));
    command_success_nodata(si, "\2/%s%s help <command>\2", (ircd->uses_rcommand == false) ? "msg " : "", siteserv->disp);
    command_success_nodata(si, " ");

    command_help(si, si->service->commands);

    command_success_nodata(si, _("***** \2End of Help\2 *****"));
    return;
  }

  /* take the command through the hash table */
  help_display(si, si->service, command, si->service->commands);
}

void _modinit(module_t *m)
{
  siteserv = service_add("siteserv", NULL);

  service_bind_command(siteserv, &siteserv_help);
}

void _moddeinit(module_unload_intent_t intent)
{
  service_unbind_command(siteserv, &siteserv_help);

  if (siteserv)
  {
    service_delete(siteserv);
    siteserv = NULL;
  }
}

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */
