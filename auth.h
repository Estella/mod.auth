/**
 * auth.h
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

#ifndef __auth_H
#define __auth_H "$Id$"

#include	<string>

#include	"client.h"
#include	"Network.h"

namespace gnuworld
{

/**
 * A dummy xClient.  This is just a skeleton from which developers
 * may create new services clients.
 */
class auth : public xClient
{

public:
	/**
	 * Constructor receives a configuration file name.
	 */
	auth( const std::string& configFileName ) ;

	/**
	 * Destructor does normal stuff.
	 */
	virtual ~auth() ;

	/**
	 * This method is called when a network client sends
	 * a private message (PRIVMSG or NOTICE) to this xClient.
	 * The first argument is a pointer to the source client,
	 * and the second argument is the actual message (minus
	 * all of the server command stuff).
	 */
	virtual void OnPrivateMessage( iClient*, const std::string&,
		bool secure = false ) ;

	/**
	 * This method is called by the server when a server connection
	 * is established.  The purpose of this method is to inform
	 * the xServer of the channels this client wishes to burst.
	 */
	virtual void BurstChannels();

protected:

        /**
         * Return true if the given string represents a valid
         * account.  This is rather trivial, and probably not
         * entirely correct, but hopefully it will avoid some
         * simple typos and types of abuse.
         */
	bool	validAccount( const std::string& ) const ;

        /**
         * The maximum account length for the network on which this
         * client runs.  This is used in determining if an account
         * is valid.
         */
	size_t		maxAccountLen ;

	/**
	 * Whether or not to restrict the service to opers only.
	 */
	bool		operOnly ;

	/**
	 * Whether or not to require the use of the secure message type.
	 */
	bool		secureOnly ;

} ;

} // namespace gnuworld

#endif // __auth_H
