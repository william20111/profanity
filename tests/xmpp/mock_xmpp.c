#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "xmpp/xmpp.h"

static jabber_conn_status_t
_mock_jabber_get_connection_status(void)
{
    return (jabber_conn_status_t)mock();
}

static char *
_mock_jabber_get_account_name(void)
{
    return (char *)mock();
}

static void
_mock_iq_room_list_request(gchar *conf_server)
{
    check_expected(conf_server);
}

static jabber_conn_status_t
_mock_jabber_connect_with_details(const char * const jid,
    const char * const passwd, const char * const altdomain, const int port)
{
    check_expected(jid);
    check_expected(passwd);
    check_expected(altdomain);
    check_expected(port);
    return (jabber_conn_status_t)mock();
}

static jabber_conn_status_t
_mock_jabber_connect_with_account(const ProfAccount * const account)
{
    check_expected(account);
    return (jabber_conn_status_t)mock();
}

static char *
_mock_jabber_get_presence_message(void)
{
    return (char *)mock();
}

static void
_mock_presence_update(resource_presence_t status, const char * const msg, int idle)
{
    check_expected(status);
    check_expected(msg);
    check_expected(idle);
}

static const GList *
_mock_bookmark_get_list(void)
{
    return (GList *)mock();
}

static gboolean
_mock_bookmark_add(const char *jid, const char *nick, gboolean autojoin)
{
    check_expected(jid);
    check_expected(nick);
    check_expected(autojoin);
    return (gboolean)mock();
}

static gboolean
_mock_bookmark_remove(const char *jid, gboolean autojoin)
{
    check_expected(jid);
    check_expected(autojoin);
    return (gboolean)mock();
}

void
mock_jabber_connect_with_details(void)
{
    jabber_connect_with_details = _mock_jabber_connect_with_details;
}

void
mock_jabber_connect_with_account(void)
{
    jabber_connect_with_account = _mock_jabber_connect_with_account;
}

void
mock_presence_update(void)
{
    presence_update = _mock_presence_update;
}

void
mock_connection_status(jabber_conn_status_t status)
{
    jabber_get_connection_status = _mock_jabber_get_connection_status;
    will_return(_mock_jabber_get_connection_status, status);
}

void
mock_bookmark_add(void)
{
    bookmark_add = _mock_bookmark_add;
}

void
mock_bookmark_remove(void)
{
    bookmark_remove = _mock_bookmark_remove;
}

void
bookmark_get_list_returns(GList *bookmarks)
{
    bookmark_get_list = _mock_bookmark_get_list;
    will_return(_mock_bookmark_get_list, bookmarks);
}

void
mock_connection_account_name(char *name)
{
    jabber_get_account_name = _mock_jabber_get_account_name;
    will_return(_mock_jabber_get_account_name, name);
}

void
mock_connection_presence_message(char *message)
{
    jabber_get_presence_message = _mock_jabber_get_presence_message;
    will_return(_mock_jabber_get_presence_message, message);
}

void
expect_room_list_request(char *conf_server)
{
    iq_room_list_request = _mock_iq_room_list_request;
    expect_string(_mock_iq_room_list_request, conf_server, conf_server);
}

void
jabber_connect_with_details_expect_and_return(char *jid,
    char *password, char *altdomain, int port, jabber_conn_status_t result)
{
    expect_string(_mock_jabber_connect_with_details, jid, jid);
    expect_string(_mock_jabber_connect_with_details, passwd, password);
    if (altdomain == NULL) {
        expect_any(_mock_jabber_connect_with_details, altdomain);
    } else {
        expect_string(_mock_jabber_connect_with_details, altdomain, altdomain);
    }
    expect_value(_mock_jabber_connect_with_details, port, port);
    will_return(_mock_jabber_connect_with_details, result);
}

void
jabber_connect_with_details_return(jabber_conn_status_t result)
{
    expect_any(_mock_jabber_connect_with_details, jid);
    expect_any(_mock_jabber_connect_with_details, passwd);
    expect_any(_mock_jabber_connect_with_details, altdomain);
    expect_any(_mock_jabber_connect_with_details, port);
    will_return(_mock_jabber_connect_with_details, result);
}

void
jabber_connect_with_account_expect_and_return(ProfAccount *account,
    jabber_conn_status_t result)
{
    expect_memory(_mock_jabber_connect_with_account, account, account, sizeof(ProfAccount));
    will_return(_mock_jabber_connect_with_account, result);
}

void
jabber_connect_with_account_return(ProfAccount *account,
    jabber_conn_status_t result)
{
    expect_any(_mock_jabber_connect_with_account, account);
    will_return(_mock_jabber_connect_with_account, result);
}

void
presence_update_expect(resource_presence_t presence, char *msg, int idle)
{
    expect_value(_mock_presence_update, status, presence);
    expect_string(_mock_presence_update, msg, msg);
    expect_value(_mock_presence_update, idle, idle);
}

void
expect_and_return_bookmark_add(char *expected_jid, char *expected_nick,
    gboolean expected_autojoin, gboolean added)
{
    expect_string(_mock_bookmark_add, jid, expected_jid);
    if (expected_nick != NULL) {
        expect_string(_mock_bookmark_add, nick, expected_nick);
    } else {
        expect_any(_mock_bookmark_add, nick);
    }
    expect_value(_mock_bookmark_add, autojoin, expected_autojoin);

    will_return(_mock_bookmark_add, added);
}

void
expect_and_return_bookmark_remove(char *expected_jid, gboolean expected_autojoin,
    gboolean removed)
{
    expect_string(_mock_bookmark_remove, jid, expected_jid);
    expect_value(_mock_bookmark_remove, autojoin, expected_autojoin);

    will_return(_mock_bookmark_remove, removed);
}
