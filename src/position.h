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
#ifndef PZSCULPTPOSITION_H
#define PZSCULPTPOSITION_H

#include <QSet>
#include <QList>
#include <cordinate.h>

namespace PZSculpt
{

/**
 @author Petras Zdanavičius <petraszd@gmail.com>
*/
class Position : public Cordinate
{
   public:
      enum {P_NO_NUMBER = -1, };

   protected:
      QList<Position*> m_neighbors;
      int m_number;

   public:
      Position ( GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f,
                 int level = 0 );
      Position ( const Position & pos );
      Position ( const Cordinate & cord );
      Position ( const Vector3f & vector, int level );

      virtual ~Position();

      bool isNeighborsSameLevel() const;

   public:
      void setNeighbors ( const QSet<Position*> & set ) {
         m_neighbors = QList<Position*>::fromSet ( set );
      }


      int getNeighborsSize() const {
         return m_neighbors.size();
      }


      Position* getNeighbor ( int number ) const {
         return m_neighbors[number];
      }

      void setNumber ( int number ) {
         m_number = number;
      }


      int getNumber () const {
         return m_number;
      }
};

}

#endif
