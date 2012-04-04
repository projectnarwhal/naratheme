/*
 * Copyright (c) 2012 Phos <phosphos0@gmail.com>
 * Rights to this code are documented in doc/LICENSE.
 *
 * This file contains the notice() routine.
 *
 */

#include "atheme.h"

DECLARE_MODULE_V1
(
  "siteserv/notice", false, _modinit, _moddeinit,
  PACKAGE_STRING,
  "Phos <phosphos0@gmail.com>"
);

static void siteserv_cmd_notice(sourceinfo_t *si, const int parc, char *parv[]);

command_t siteserv_notice = {
  "NOTICE",
  N_(N_("Notices users.")),
  PRIV_SITE_INT,
  2,
  siteserv_cmd_notice,
  { .path = "notice" }
};

/* NOTICE <user> <message> */
void siteserv_cmd_notice(sourceinfo_t *si, int parc, char *parv[])
{
  char *user;
  char *msg;

  user = parv[0], msg = parv[1];

  if (!user || !msg)
  {
    command_fail(si, fault_needmoreparams, STR_INSUFFICIENT_PARAMS, "NOTICE");
    command_fail(si, fault_needmoreparams, "Syntax: NOTICE <user> <message>");
    return;
  }

  command_success_nodata(si, _("Notice sent!"));
  notice(si->service->nick, user, "%s", msg);
}

void _modinit(module_t *m)
{
  service_named_bind_command("siteserv", &siteserv_notice);
}

void _moddeinit(module_unload_intent_t intent)
{
  service_named_unbind_command("siteserv", &siteserv_notice);
}

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */
