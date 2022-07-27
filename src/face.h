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
#ifndef PZSCULPTFACE_H
#define PZSCULPTFACE_H

#include "config.h"
#include <QList>
#include <cordinate.h>

namespace PZSculpt
{

/**
 @author Petras Zdanavičius <petraszd@gmail.com>
*/
class Face
{
   public:
      Face ( int count );
      Face ( const Face& face );
      virtual ~Face();

   protected:
      QList<int> * m_positionList;
      QList<int> * m_textureList;
      Vector3f m_faceNormal;
      int m_count;

   public:
      int getCount() const {
         return m_count;
      }

      void setFaceNormal ( Vector3f faceNormal ) {
         m_faceNormal = faceNormal;
      }

      Vector3f getFaceNormal () const {
         return m_faceNormal;
      }

      void addPoint ( int position, int texture ) {
         m_positionList->append ( position );
         m_textureList->append ( texture );
      }

      int posAt ( int i ) const {
         return m_positionList->at ( i );
      }

      int posSafe ( int i ) const {
         return m_positionList->at ( qAbs ( i % m_count ) );
      }

      int texAt ( int i ) const {
         return m_textureList->at ( i );
      }

      int texSafe ( int i ) const {
         return m_textureList->at ( qAbs ( i % m_count ) );
      }
};

}

#endif
