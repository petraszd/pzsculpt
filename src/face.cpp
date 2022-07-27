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
#include "face.h"

namespace PZSculpt
{

Face::Face ( int count )
{
   m_count = count;
   m_positionList = new QList<int>;
   m_textureList = new QList<int>;
}


Face::Face ( const Face & face )
{
   m_count = face.getCount();
   m_positionList = new QList<int>;
   m_textureList = new QList<int>;
   for ( int i = 0; i < face.getCount(); ++i ) {
      m_positionList->append ( face.posAt ( i ) );
      m_textureList->append ( face.texAt ( i ) );
   }
}


Face::~Face()
{
//   m_positionList->clear();
//   m_textureList->clear();

   delete m_positionList;
   delete m_textureList;
}


}
