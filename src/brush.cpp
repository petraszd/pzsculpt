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
#include <cmath>
#include "brush.h"
#include "face.h"

namespace PZSculpt
{

Brush::Brush ( bool visible,
               int size,
               int strength,
               int intencity,
               BrushAligment aligment )
{
   m_visible = visible;
   setSize ( size );
   setStrength ( strength );
   setIntencity ( intencity );
   m_x = 0;
   m_y = 0;

   m_aligment = aligment;
}


Brush::~Brush()
{
}


void Brush::drawOnMesh ( VertexDrawer *drawer,
                         Mesh * mesh,
                         Camera * camera,
                         DrawCommand * command )
{
   m_tempMesh = mesh;
   m_tempCamera = camera;
   m_tempEyePos = camera->getLookFrom();
   m_tempCamDir = m_tempEyePos - camera->getLookAt();

   m_tempCentral = findNearestFace ();

   if ( m_tempCentral == 0 )
      return;

   transformBrushTo3D();

   QHash<int, VertexDrawerElem*> elems;
   QSet<Face*> faces;

   parseFaces ( m_tempCentral, faces, elems );

   QList<VertexDrawerElem*> elemsList = elems.values();
   drawer->draw ( elemsList,
                  m_tempMesh->faceMiddle ( m_tempCentral ),
                  m_tempCentral->getFaceNormal(),
                  command );

   for ( int i = 0; i < elemsList.size(); ++i )
      delete elemsList[i];

   QSetIterator<Face*> it ( faces );
   while ( it.hasNext() )
      mesh->recalculateNormal ( it.next() );
}


void Brush::parseFaces ( Face *face,
                         QSet<Face*> & faces,
                         QHash<int, VertexDrawerElem*> & hash )
{
   int nV;
   Position *v;
   bool isGood = false;
   VertexDrawerElem *e;
   GLfloat length;
   for ( int i = 0; i < face->getCount(); ++i ) {
      nV = face->posAt ( i );
      if ( hash.contains ( nV ) ) {
         faces.insert ( face );
         continue;
      }

      v = m_tempMesh->posPtr ( nV );
      length = ( m_tempBrush3DPos - ( *v ) ).length();

      if ( length <= m_temp3DRadius ) {
         faces.insert ( face );
         e = new VertexDrawerElem ( v, calcIntensity ( length ) * m_aligment );
         hash.insert ( nV, e );
         isGood = true;
      }
   }

   if ( ! isGood )
      return;

   Face * nearFace;
   for ( int i = 0; i < face->getCount(); ++i ) {
      nearFace = m_tempMesh->edgePtr ( face->posAt ( i ),
                                       face->posSafe ( i + 1 ) )->getFace ( face );
      if ( nearFace != 0 )
         parseFaces ( nearFace, faces, hash );
   }
}


Face* Brush::findNearestFace ()
{
   Face *f;
   GLfloat angle;

   double * xp;
   double * yp;

   Face * goodFace = 0;
   GLfloat currentLenght = 1e20000f;//TODO Need some different solution

   for ( int i = 0; i < m_tempMesh->getFacesCount(); ++i ) {
      f = m_tempMesh->facePtr ( i );
      angle = f->getFaceNormal().dot ( m_tempCamDir );
      if ( angle <= 1.0f || angle >= 89.0f ) //TODO magic number
         continue;

      xp = new double[ f->getCount() ];
      yp = new double[ f->getCount() ];
      for ( int j = 0; j < f->getCount(); ++j ) {
         m_tempCamera->projectOnScreen ( m_tempMesh->posPtr ( f->posAt ( j ) ),
                                         xp[j], yp[j] );
      }

      if ( isPointInPoly ( f->getCount(), xp, yp, m_x, m_y ) ) {
         GLfloat l = ( m_tempEyePos - m_tempMesh->faceMiddle ( f ) ).length();
         if ( l < currentLenght ) {
            currentLenght = l;
            goodFace = f;
         }
      }

      delete [] xp;
      delete [] yp;
   }

   return goodFace;
}


void Brush::transformBrushTo3D()
{
   Vector3f zDepVector = m_tempCamera->projectOnScreen (
                            m_tempMesh->faceMiddle ( m_tempCentral ) );
   zDepVector.setX ( m_x );
   zDepVector.setY ( m_y );
   Vector3f brush3DPos = m_tempCamera->projectInSpace ( zDepVector );


   m_tempBrush3DPos = brush3DPos;


   zDepVector.setX ( m_x + ( m_size >> 1 ) );
   Vector3f brushCorner3DPos = m_tempCamera->projectInSpace ( zDepVector );

   m_temp3DRadius = ( brush3DPos - brushCorner3DPos ).length();
}


GLfloat Brush::calcIntensity ( GLfloat length )
{
   GLfloat strength = m_strength / 100.0;

   GLfloat bottom = m_temp3DRadius * ( m_intencity / 100.0f );
   if ( length < bottom )
      return strength;
   else
      return strength *
             ( m_temp3DRadius - length ) /
             ( m_temp3DRadius - bottom );
}


int Brush::isPointInPoly ( int npol, double *xp, double *yp,
                           double x, double y )
{
   int i, j, c = 0;
   for ( i = 0, j = npol - 1; i < npol; j = i++ ) {
      //Evil magic.
      if ( ( ( yp[i] <= y && y < yp[j] ) || ( yp[j] <= y && y < yp[i] ) ) &&
            ( x < ( xp[j] - xp[i] ) * ( y - yp[i] ) /
              ( yp[j] - yp[i] ) + xp[i] ) ) {
         c = !c;
      }
   }
   return c;
}


void Brush::drawCursor ( QPainter & painter )
{
   if ( ! m_visible )
      return;

   int x = m_x - m_size / 2;
   int y = m_y - m_size / 2;

   int innerSize = int ( m_size / 100.0f * m_intencity );
   int innerOffset = ( m_size - innerSize ) / 2;

   painter.setPen ( Qt::lightGray );
   painter.drawEllipse ( x + innerOffset, y + innerOffset,
                         innerSize, innerSize );
   painter.setPen ( Qt::white );
   painter.drawEllipse ( x, y, m_size, m_size );
}


bool Brush::isNear ( int x, int y )
{
   x -= m_x;
   y -= m_y;

   int size = m_size >> 1; // m_size / 2

   return x*x + y*y < size * size;
}


}
