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
#include "edge.h"

namespace PZSculpt
{


Edge::Edge()
{
   m_faces = new Face*[2];
   m_faces[0] = 0;
   m_faces[1] = 0;
}


Edge::Edge ( const Edge & edge )
{
   m_faces = new Face*[2];
   m_faces[0] = edge.getFace ( 0 );
   m_faces[1] = edge.getFace ( 1 );
}


Edge::~Edge()
{
   delete [] m_faces;
}


void Edge::connectFace ( Face * face )
{
   if ( m_faces[0] == 0 )
      m_faces[0] = face;
   else
      m_faces[1] = face;
}


inline Face* Edge::getFace ( int number ) const
{
   return m_faces[number & 1];
}


Face* Edge::getFace ( Face * face ) const
{
   if ( m_faces[0] == face )
      return m_faces[1];

   if ( m_faces[1] == face )
      return m_faces[0];

   return 0;
}


}
