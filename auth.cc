/**
 * auth.cc
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 *
 * $Id$
 */

#include	<string>

#include	"client.h"
#include	"auth.h"
#include	"server.h"
#include	"EConfig.h"
#include        "StringTokenizer.h"

namespace gnuworld
{

/*
 *  Exported function used by moduleLoader to gain an
 *  instance of this module.
 */

extern "C"
{
  xClient* _gnuwinit(const std::string& args)
  { 
    return new auth( args );
  }

} 
 
/**
 * This constructor calls the base class constructor.  The xClient
 * constructor will open the configuration file given and retrieve
 * basic client info (nick/user/host/etc).
 * Any additional processing must be done here.
 */
auth::auth( const std::string& configFileName )
 : xClient( configFileName )
{
/* Load the config file */
EConfig authConfig(configFileName);

/* Load any settings we have */
maxAccountLen = ::atoi(authConfig.Require("maxAccountLen")->second.c_str());
operOnly = ::atoi(authConfig.Require("operOnly")->second.c_str());
secureOnly = ::atoi(authConfig.Require("secureOnly")->second.c_str());
}

auth::~auth()
{
/* No heap space allocated */
}

void auth::OnPrivateMessage( iClient* theClient,
	const std::string& Message, bool secure)
{
if (operOnly && !theClient->isOper()) {
  // if the client is not oper'd we act as the clientExample ;)
  Notice(theClient, "You must be an IRC Operator to use this service.");
  return;
}

if (secureOnly && !secure) {
  Notice(theClient, "You must /msg %s@%s", nickName.c_str(),
	 getUplinkName().c_str());
  return;
}

StringTokenizer st(Message);
if (st.empty())
  return;

std::string account(st[0]);
if (!validAccount(account)) {
  Notice(theClient, "%s is not a valid account name.", account.c_str());
  return;
}
iClient* receiver = NULL;
if (st.size() > 1) {
  if (!(receiver = Network->findNick(st[1]))) {
    Notice(theClient, "Unable to find nickname %s", st[1].c_str());
    return;
  }
}

if (!theClient->isModeR()) {
  if (receiver) {
    MyUplink->UserLogin(receiver, account, this);
    Notice(theClient, "%s is now authenticated as %s.",
	   receiver->getNickName().c_str(), account.c_str());
    Notice(receiver, "You have been authenticated as %s by %s.",
	   account.c_str(), theClient->getNickName().c_str());
  } else {
    MyUplink->UserLogin(theClient, account, this);
    Notice(theClient, "You are now authenticated as %s.",
	   account.c_str());
  }    
} else {
  Notice(theClient, "You are already authenticated as %s!",
	 theClient->getAccount().c_str());
}

}

// Burst any channels.
void auth::BurstChannels()
{
xClient::BurstChannels();
}

bool auth::validAccount(const std::string& account) const
{
if (account.empty() || account.size() > maxAccountLen )
  return false;

/*
 * From IRCu:
 * Nickname characters are in range 'A'..'}', '_', '-', '0'..'9'
 *  anything outside the above set will terminate nickname.
 * In addition, the first character cannot be '-' or a Digit.
 */
if (isdigit(account[0]))
  return false;

for ( std::string::const_iterator sItr = account.begin();
     sItr != account.end() ; ++sItr ) {
  if ( *sItr >= 'A' && *sItr <= '}' )
    // ok
    continue;
  if ( '_' == *sItr || '-' == *sItr )
    // ok
    continue;
  if ( *sItr >= '0' && *sItr <= '9' )
    // ok
    continue;
  // bad char
  return false;
}
return true;
}

} // namespace gnuworld
