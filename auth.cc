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
{}

auth::~auth()
{
/* No heap space allocated */
}

void auth::OnPrivateMessage( iClient* theClient,
	const std::string& Message, bool secure)
{
if(!theClient->isOper()) {
  //if the client is not oper'd we act as the clientExample ;)
  Notice( theClient, "Howdy :)" ) ;
  return;
}

if(!secure) {
  Notice(theClient, "You must /msg %s@%s", nickName.c_str(), getUplinkName().c_str());
  return ;
}


StringTokenizer st( Message ) ;
if( st.empty() ) {
 return ;
}

string command( string_upper( st[ 0 ] ) ) ;

if(command == "AUTH") {
  if(st.size() < 1) {
    Notice( theClient, "Usage: AUTH <account>" );
    return;
  }

  if(!theClient->isModeR()) {
    theClient->setAccount( st[1] );
  }
}
}

// Burst any channels.
void auth::BurstChannels()
{
xClient::BurstChannels() ;
}

} // namespace gnuworld
