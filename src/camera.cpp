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
#include "camera.h"

namespace PZSculpt
{

Camera::Camera ( GLfloat fov,
                 GLfloat ratio,
                 GLfloat nearPlane,
                 GLfloat farPlane,
                 GLfloat radius )
{
   setFov ( fov );
   setRatio ( ratio );
   setClippingPlanes ( nearPlane, farPlane );

   setRadius ( radius );

   m_starePoint.setPlace( 0.0f, 0.0f, 0.0f );

   m_verticalRotate = 0.0f;
   m_horizontalRotate = 0.0f;
   m_upY = 1.0;
}


Camera::~Camera()
{
}


void Camera::rotateVertical ( GLfloat degree )
{
   //TODO: kiekvienam laipsniu vairnatui sukurti atsikra const.
   m_verticalRotate += degree / DEGREE_TO_RADIAN;

   if ( m_verticalRotate >= 2.0f * PI )
      m_verticalRotate -= 2.0f * PI;
   else if ( m_verticalRotate < 0.0f )
      m_verticalRotate += 2.0f * PI;

   if ( m_verticalRotate > PI / 2.0 && m_verticalRotate < PI * 1.5 )
      m_upY = -1.0f;
   else
      m_upY = 1.0f;

   apply();
}


void Camera::rotateHorizontal ( GLfloat degree )
{
   //On different orientation - different way of rotation.
   m_horizontalRotate += m_upY * degree / DEGREE_TO_RADIAN;

   apply();
}


void Camera::move ( GLfloat horizontal, GLfloat vertical )
{
   Vector3f faceV = facingVector().normalize();

   m_verticalRotate += PI / 2.0f;
   Vector3f vertV = facingVector().normalize();
   m_verticalRotate -= PI / 2.0f;

   Vector3f horiV = vertV.cross ( facingVector() ).normalize();

   vertV *= vertical * m_radius;
   horiV *= -horizontal * m_radius;

   Vector3f res = ( horiV + vertV ) / 2.0f;

   m_starePoint += res;
   apply();
}


void Camera::zoom ( GLfloat ratio )
{
   if ( std::fabs ( ratio ) > 1.0f )
      return;

   setRadius ( m_radius * ( 1.0 + ratio ) );
   apply();
}


void Camera::resizeEvent ( uint width, uint height )
{
   if ( height == 0 )
      height = 1;
   setRatio ( GLfloat ( width ) / height );

   GLint mode;
   //Get current matrix mode
   glGetIntegerv ( GL_MATRIX_MODE, &mode );

   glMatrixMode ( GL_PROJECTION );
   glLoadIdentity();

   gluPerspective ( m_fov, m_ratio, m_nearClippingPlane, m_farClippingPlane );


   glMatrixMode ( GL_MODELVIEW );
   glLoadIdentity();
   glViewport ( 0, 0, width, height );

   //reset matrix mode
   glMatrixMode ( mode );

   apply();
}


Vector3f Camera::facingVector() const
{
   GLfloat y = std::sin ( m_verticalRotate );
   GLfloat r = -std::cos ( m_verticalRotate );

   GLfloat x = std::sin ( m_horizontalRotate ) * r;
   GLfloat z = ( -std::cos ( m_horizontalRotate ) ) * r;

   return Vector3f ( x, y, z );
}


void Camera::apply()
{
   GLint mode;
   //Get current matrix mode
   glGetIntegerv ( GL_MATRIX_MODE, &mode );

   glMatrixMode ( GL_MODELVIEW );
   glLoadIdentity();

   Vector3f v = facingVector();

   gluLookAt ( m_starePoint.getX() + v.getX() * m_radius,
               m_starePoint.getY() + v.getY() * m_radius,
               m_starePoint.getZ() + v.getZ() * m_radius,
               m_starePoint.getX(), m_starePoint.getY(), m_starePoint.getZ(),
               0.0f, m_upY, 0.0f );

   //reset matrix mode
   glMatrixMode ( mode );

   fillGLMatrixes();
}


void Camera::fillGLMatrixes()
{
   glGetDoublev ( GL_MODELVIEW_MATRIX, m_modelviewMatrix );
   glGetDoublev ( GL_PROJECTION_MATRIX, m_projectionMatrix );
   glGetIntegerv ( GL_VIEWPORT, m_viewport );
}


Vector3f Camera::projectOnScreen ( const Vector3f & vector ) const
{
   GLdouble x, y, z;
   gluProject ( vector.getX(), vector.getY(), vector.getZ(),
                m_modelviewMatrix, m_projectionMatrix, m_viewport,
                &x, &y, &z );
   return Vector3f ( GLfloat ( x ), GLfloat ( y ), GLfloat ( z ) );
}


Vector3f Camera::projectOnScreen ( Vector3f * vectorPtr ) const
{
   GLdouble x, y, z;
   gluProject ( vectorPtr->getX(), vectorPtr->getY(), vectorPtr->getZ(),
                m_modelviewMatrix, m_projectionMatrix, m_viewport,
                &x, &y, &z );
   return Vector3f ( GLfloat ( x ), GLfloat ( y ), GLfloat ( z ) );
}


void Camera::projectOnScreen ( const Vector3f & vector,
                               GLdouble & x, GLdouble & y ) const
{
   GLdouble z;
   gluProject ( vector.getX(), vector.getY(), vector.getZ(),
                m_modelviewMatrix, m_projectionMatrix, m_viewport,
                &x, &y, &z );
}


void Camera::projectOnScreen ( Vector3f * vectorPtr,
                               GLdouble & x, GLdouble & y ) const
{
   GLdouble z;
   gluProject ( vectorPtr->getX(), vectorPtr->getY(), vectorPtr->getZ(),
                m_modelviewMatrix, m_projectionMatrix, m_viewport,
                &x, &y, &z );
}


Vector3f Camera::projectInSpace ( const Vector3f & vector ) const
{
   GLdouble x = vector.getX();
   GLdouble y = vector.getY();
   GLdouble z = vector.getZ();

   GLdouble px, py, pz;

   gluUnProject ( x, y, z,
                  m_modelviewMatrix, m_projectionMatrix, m_viewport,
                  &px, &py, &pz );

   return Vector3f ( GLfloat ( px ), GLfloat ( py ), GLfloat ( pz ) );
}


}
