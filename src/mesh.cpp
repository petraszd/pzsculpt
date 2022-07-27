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
#include "mesh.h"
#include <QGLWidget>
#include <QGLFormat>

namespace PZSculpt
{

Mesh::Mesh () : Drawable()
{
   m_allQuads = false;
   m_shiftAmount = 0;
}


Mesh::Mesh ( Mesh & mesh ) : Drawable()
{
   Face *f;
   for ( int i = 0; i < mesh.getFacesCount(); ++i ) {
      f = new Face ( mesh.face ( i ) );
      m_faceData << f;

      m_faceData[i]->setFaceNormal ( mesh.facePtr ( i )->getFaceNormal() );
   }

   for ( int i = 0; i < mesh.getPosCount(); ++i ) {
      addPos ( new Position ( mesh.pos ( i ) ) );
   }

   for ( int i = 0; i < mesh.getTexCount(); ++i ) {
      m_texData << new Cordinate ( mesh.tex ( i ) );
   }

   //Maybe this is not requared?
   initShiftAmount();
   recalculateFaceNeighbors();
   recalculatePosNeighbors();
}


Mesh::~Mesh()
{
   for ( int i = 0; i < m_posData.size(); ++i )
      delete m_posData[i];

   for ( int i = 0; i < m_texData.size(); ++i )
      delete m_texData[i];

   for ( int i = 0; i < m_faceData.size(); ++i )
      delete m_faceData[i];

   foreach ( Edge* edge, m_edgeData )
   delete edge;
}


void Mesh::draw()
{
   Vector3f v;
   Vector3f *pv;

   if ( m_allQuads ) {
      glBegin ( GL_QUADS );
      for ( int i = 0; i < m_faceData.size(); ++i ) {
         v = m_faceData[i]->getFaceNormal();
         for ( int j = 0; j < m_faceData[i]->getCount(); ++j ) {
            glNormal3f ( v.getX(), v.getY(), v.getZ() );
            pv = posPtr ( m_faceData[i]->posAt ( j ) );
            glVertex3f ( pv->getX(), pv->getY(), pv->getZ() );
         }
      }
      glEnd();
   }
   else {
      bool allQuads = true;
      for ( int i = 0; i < m_faceData.size(); ++i ) {
         if ( m_faceData[i]->getCount() == 4 ) {
            glBegin ( GL_QUADS );
         }
         else if ( m_faceData[i]->getCount() == 3 ) {
            glBegin ( GL_TRIANGLES );
            allQuads = false;
         }
         else {
            glBegin ( GL_POLYGON );
            allQuads = false;
         }

         v = m_faceData[i]->getFaceNormal();
         for ( int j = 0; j < m_faceData[i]->getCount(); ++j ) {
            glNormal3f ( v.getX(), v.getY(), v.getZ() );
            pv = posPtr ( m_faceData[i]->posAt ( j ) );
            glVertex3f ( pv->getX(), pv->getY(), pv->getZ() );
         }
         glEnd();
      }
      m_allQuads = allQuads;
   }
}


void Mesh::finishConstrucion()
{
   recalculateNormalAll();
   initShiftAmount();
   recalculateFaceNeighbors();
   recalculatePosNeighbors();
}


void Mesh::getMetrics ( Vector3f & center, GLfloat & radius )
{
   radius = 0.0f;
   center.setPlace ( 0.0f, 0.0f, 0.0f );

   if ( getPosCount() == 0 )
      return;

   for ( int i = 0; i < m_posData.size(); ++i ) {
      center += pos ( i );
   }
   center /= getPosCount();

   GLfloat r;
   for ( int i = 0; i < m_posData.size(); ++i ) {
      r = ( center - pos ( i ) ).length();
      if ( r > radius )
         radius = r;
   }
}


int Mesh::generateEdgeKey ( int one, int two )
{
   uint max;
   uint min;
   if ( one >= two ) {
      max = one;
      min = two;
   }
   else {
      max = two;
      min = one;
   }

   return ( max << m_shiftAmount ) | min;
}


void Mesh::recalculateFaceNeighbors()
{
   int n = getFacesCount();
   Face *f;
   Edge *e;
   int key;
   for ( int i = 0; i < n; ++i ) {
      f = facePtr ( i );
      for ( int j = 0; j < f->getCount(); ++j ) {
         key = generateEdgeKey ( f->posAt ( j ), f->posSafe ( j + 1 ) );
         if ( !m_edgeData.contains ( key ) ) {
            e = new Edge();
            m_edgeData[key] = e;
         }
         else {
            e = m_edgeData[key];
         }

         e->connectFace ( f );
      }
   }
}


void Mesh::recalculatePosNeighbors()
{
   QSet<Position*> neighboors[ m_posData.size() ];

   Position* onePos;
   Position* twoPos;
   int oneNo;
   int twoNo;
   for ( int i = 0; i < m_faceData.size(); ++i ) {
      for ( int j = 0; j < m_faceData[i]->getCount(); ++j ) {
         oneNo = m_faceData[i]->posAt ( j );
         twoNo = m_faceData[i]->posSafe ( j + 1 );
         onePos = posPtr ( oneNo );
         twoPos = posPtr ( twoNo );

         neighboors[ oneNo ].insert ( twoPos );
         neighboors[ twoNo ].insert ( onePos );
      }
   }

   for ( int i = 0; i < m_posData.size(); ++i )
      m_posData[i]->setNeighbors ( neighboors[i] );
}


void Mesh::recalculateNormalAll()
{
   for ( int i = 0; i < m_faceData.size(); ++i )
      recalculateNormal ( m_faceData[ i ] );
}


void Mesh::recalculateNormal ( Face *face )
{
   Vector3f n ( 0.0f, 0.0f, 0.0f );

   Vector3f * p0;
   Vector3f * p1;
   Vector3f * p2;
   for ( int j = 1; j < face->getCount() - 1; ++j ) {
      p0 = posPtr ( face->posAt ( j - 1 ) );
      p1 = posPtr ( face->posAt ( j ) );
      p2 = posPtr ( face->posAt ( j + 1 ) );

      n += ( *p1 - *p0 ).cross ( ( *p2 - *p0 ) );
   }
   n = ( n / ( face->getCount() - 2 ) ).normalize();
   face->setFaceNormal ( n );
}


void Mesh::initShiftAmount()
{
   uint count = getPosCount();
   m_shiftAmount = 0;

   while ( count != 0 ) {
      count = count >> 1;
      m_shiftAmount++;
   }
}


Vector3f Mesh::faceMiddle ( Face & face )
{
   return faceMiddle ( &face );
}


Vector3f Mesh::faceMiddle ( int face )
{
   return faceMiddle ( facePtr ( face ) );
}


Vector3f Mesh::faceMiddle ( Face *face )
{
   Vector3f middle ( 0.0f, 0.0f, 0.0f );
   for ( int i = 0; i < face->getCount(); ++i )
      middle += pos ( face->posAt ( i ) );

   return middle / face->getCount();
}


QString Mesh::toString() const
{
   return QString ( "Vertex count: %1\nFaces count: %2" )
          .arg ( getPosCount() )
          .arg ( getFacesCount() );
}


}//end of namespace
