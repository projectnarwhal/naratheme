/*
 * Copyright (c) 2012 Phos <phosphos0@gmail.com>
 * Copyright (c) 2005-2007 William Pitcock, et al.
 * Rights to this code are as documented in doc/LICENSE.
 *
 * This file contains code for the NickServ FREGISTER function.
 *
 * Remember to give the user:fregister priv to any soper you want
 * to be able to use this command.
 *
 */

#include "atheme.h"

DECLARE_MODULE_V1
(
  "siteserv/setpass", false, _modinit, _moddeinit,
  PACKAGE_STRING,
  "Phos <phosphos0@gmail.com>"
);

static void siteserv_cmd_setpass(sourceinfo_t *si, int parc, char *parv[]);

command_t siteserv_setpass = {
  "SETPASS",
  "Sets the password of another user.",
  PRIV_SITE_INT,
  20,
  siteserv_cmd_setpass,
  { .path = "siteserv/setpass" }
};

void _modinit(module_t *m)
{
  service_named_bind_command("siteserv", &siteserv_setpass);
}

void _moddeinit(module_unload_intent_t intent)
{
  service_named_unbind_command("siteserv", &siteserv_setpass);
}

static void siteserv_cmd_setpass(sourceinfo_t *si, int parc, char *parv[])
{
  myuser_t *mu;
  char *account;
  char *pass;
  hook_user_req_t req;

  account = parv[0], pass = parv[1];

  if (!account || !pass)
  {
    command_fail(si, fault_needmoreparams, STR_INSUFFICIENT_PARAMS, "SETPASS");
    command_fail(si, fault_needmoreparams, "Syntax: SETPASS <account> <new password>");
    return;
  }

  if (strlen(pass) > 32)
  {
    command_fail(si, fault_badparams, STR_INVALID_PARAMS, "SETPASS");
    return;
  }

  if (strchr(account, ' ') || strchr(account, '\n') || strchr(account, '\r') || account[0] == '=' || account[0] == '#' || account[0] == '@' || account[0] == '+' || account[0] == '%' || account[0] == '!' || strchr(account, ','))
  {
    command_fail(si, fault_badparams, "The account name \2%s\2 is invalid.", account);
    return;
  }

  if (!(mu = myuser_find(account)))
  {
    command_fail(si, fault_nosuch_target, _("\2%s\2 is not registered."), account);
    return;
  }

  logcommand(si, CMDLOG_SET, "SETPASS");

  set_password(mu, pass);

  command_success_nodata(si, _("The password for \2%s\2 has been changed to \2%s\2."), entity(mu)->name, pass);
}

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */