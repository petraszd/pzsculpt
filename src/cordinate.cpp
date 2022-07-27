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
#include "cordinate.h"

namespace PZSculpt
{

Cordinate::Cordinate ( GLfloat x, GLfloat y, GLfloat z, int level ) :
      Vector3f ( x, y, z )
{
   m_level = level;
}


Cordinate::Cordinate ( const Cordinate & cord ) : Vector3f ( cord )
{
   m_level = cord.getLevel();
}


Cordinate::Cordinate ( const Vector3f & vector, int level ) : Vector3f ( vector )
{
   m_level = level;
}


Cordinate::~Cordinate()
{
}


}
