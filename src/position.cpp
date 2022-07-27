/***************************************************************************
 *   Copyright (C) 2008 by Petras Zdanavičius                              *
 *   petraszd@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "position.h"

namespace PZSculpt
{

Position::Position ( GLfloat x, GLfloat y, GLfloat z, int level )
      : Cordinate ( x, y, z, level )
{
   m_number = P_NO_NUMBER;
}


Position::Position ( const Position & pos ) : Cordinate ( pos )
{
   m_number = pos.getNumber();

   for ( int i = 0; i < pos.getNeighborsSize(); ++i )
      m_neighbors.append ( pos.getNeighbor ( i ) );
}


Position::Position ( const Cordinate & cord ) : Cordinate ( cord )
{
   m_number = P_NO_NUMBER;
}


Position::Position ( const Vector3f & vector, int level )
      : Cordinate ( vector, level )
{
   m_number = P_NO_NUMBER;
}


Position::~Position()
{
}


bool Position::isNeighborsSameLevel() const
{
   for ( int i = 0; i < m_neighbors.size(); ++i ) {
      if ( m_level != m_neighbors[i]->getLevel() )
         return false;
   }
   return true;
}


}
