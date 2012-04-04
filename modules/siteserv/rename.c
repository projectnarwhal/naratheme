/*
 * Copyright (c) 2012 Phos <phosphos0@gmail.com>
 * Rights to this code are documented in doc/LICENSE.
 *
 * This file contains the rename() routine.
 *
 */

#include "atheme.h"

DECLARE_MODULE_V1
(
  "siteserv/rename", false, _modinit, _moddeinit,
  PACKAGE_STRING,
  "Phos <phosphos0@gmail.com>"
);

static void siteserv_cmd_rename(sourceinfo_t *si, const int parc, char *parv[]);

command_t siteserv_rename = {
  "RENAME",
  N_(N_("Renames users.")),
  PRIV_SITE_INT,
  3,
  siteserv_cmd_rename,
  { .path = "rename" }
};

/* RENAME <user> <newaccname> */
void siteserv_cmd_rename(sourceinfo_t *si, int parc, char *parv[])
{
  char *username;
  char *newaccname;
  myuser_t *mu;

  username = parv[0], newaccname = parv[1];

  if (!username || !newaccname)
  {
    command_fail(si, fault_needmoreparams, STR_INSUFFICIENT_PARAMS, "RENAME");
    command_fail(si, fault_needmoreparams, "Syntax: RENAME <user> <newaccname>");
    return;
  }

  if (!(mu = myuser_find(username))) {
    command_fail(si, fault_nosuch_target, _("Account \2%s\2 does not exist."), username);
    return;
  }

  command_success_nodata(si, _("User renamed!"));
  myuser_rename(mu, newaccname);
}

void _modinit(module_t *m)
{
  service_named_bind_command("siteserv", &siteserv_rename);
}

void _moddeinit(module_unload_intent_t intent)
{
  service_named_unbind_command("siteserv", &siteserv_rename);
}

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */
