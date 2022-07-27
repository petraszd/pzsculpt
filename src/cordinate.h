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
#ifndef PZSCULPTCORDINATE_H
#define PZSCULPTCORDINATE_H

#include <QtOpenGL>
#include "vector3.h"
#include "config.h"

namespace PZSculpt
{

/**
 @author Petras Zdanavičius <petraszd@gmail.com>
*/
class Cordinate : public Vector3f
{
   protected:
      int m_level;

   public:
      Cordinate ( GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f,
                  int level = 0 );
      Cordinate ( const Cordinate & cord );
      Cordinate ( const Vector3f & vector, int level );
      virtual ~Cordinate();

   public:
      int getLevel() const {
         return m_level;
      }


      void setLevel ( int level ) {
         m_level = level;
      }
};

}

#endif
