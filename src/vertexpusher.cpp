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
#include "vertexpusher.h"

namespace PZSculpt
{

VertexPusher::VertexPusher() : VertexDrawer()
{
}


VertexPusher::~VertexPusher()
{
}


void VertexPusher::draw ( QList<VertexDrawerElem*> elems,
                          const Vector3f & place,
                          const Vector3f & direction,
                          DrawCommand * command )
{
   Q_UNUSED ( place );

   Position * vertex;
   Vector3f delta;
   for ( int i = 0; i < elems.size(); ++i ) {
      vertex = elems[i]->getVertexPtr();
      delta = direction * elems[i]->getIntensity() * m_scale;
      vertex->setPlace ( ( *vertex ) + delta );
      command->insert ( vertex, delta );
   }
}


}
