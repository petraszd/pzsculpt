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
#ifndef PZSCULPTVECTOR3_H
#define PZSCULPTVECTOR3_H

#include <QtOpenGL>
#include <cmath>
#include "config.h"

namespace PZSculpt
{


/**
 @author Petras Zdanavičius <petraszd@gmail.com>
*/
template<class T>
class Vector3
{
   public:
      /**
       * Constructor
       *
       * @param x x cordinate
       * @param y y cordinate
       * @param z z cordinate
       */
      Vector3 ( const T & x = 0, const T & y = 0, const T & z = 0 ) {
         m_x = x;
         m_y = y;
         m_z = z;
      }


      /**
       * Copy constructor
       *
       * @param vector3
       */
      Vector3 ( const Vector3 & vector3 ) {
         m_x = vector3.getX();
         m_y = vector3.getY();
         m_z = vector3.getZ();
      }


      /**
       * Destructor
       */
      virtual ~Vector3() {
      }

   protected:
      T m_x;
      T m_y;
      T m_z;

   public:
      /**
       * Sets member m_x, m_y, m_z. For simplycity.
       *
       * @param x new m_x value
       * @param y new m_y value
       * @param z new m_z value
       */
      void setPlace ( const T & x, const T & y, const T & z ) {
         setX ( x );
         setY ( y );
         setZ ( z );
      }


      /**
       * Copys cordinates from another Vector3
       *
       * @param @param Vector3
       */
      void setPlace ( const Vector3 & vector3 ) {

         setX ( vector3.getX() );
         setY ( vector3.getY() );
         setZ ( vector3.getZ() );
      }


      /**
       * Sets member m_x to new value
       *
       * @param x new value
       */
      void setX ( const T & x ) {
         m_x = x;
      }


      /**
       * @return member m_x
       */
      T getX() const {
         return m_x;
      }


      /**
       * Sets member m_y to new value
       *
       * @param y new value
       */
      void setY ( const T & y ) {
         m_y = y;
      }


      /**
       * @return member m_y
       */
      T getY() const {
         return m_y;
      }


      /**
       * Sets member m_z to new value
       *
       * @param z new value
       */
      void setZ ( const T & z ) {
         m_z = z;
      }


      /**
       * @return member m_z
       */
      T getZ() const {
         return m_z;
      }


      /**
       * Sums two vectors
       *
       * @param arg Vector3
       * @return Vector3
       */
      Vector3 operator+ ( const Vector3 & arg ) {
         return Vector3 ( m_x + arg.getX(), m_y + arg.getY(), m_z + arg.getZ() );
      }


      /**
       * Sums two vectors
       *
       * @param left Vector3
       * @param right Vector3
       * @return Vector3
       */
      friend Vector3 operator+ ( const Vector3 & left, const Vector3 & right ) {
         return Vector3 ( right.getX() + left.getX(),
                          right.getY() + left.getY(),
                          right.getZ() + left.getZ() );
      }


      /**
       * Adds another Vector3
       *
       * @param arg Vector3
       * @return self with new values
       */
      Vector3& operator+= ( const Vector3 & arg ) {
         m_x += arg.getX();
         m_y += arg.getY();
         m_z += arg.getZ();
         return *this;
      }



      /**
       * Subtracts two vectors
       *
       * @param arg Vector3
       * @return Vector3
       */
      Vector3 operator- ( const Vector3 & arg ) {
         return Vector3 ( m_x - arg.getX(), m_y - arg.getY(), m_z - arg.getZ() );
      }


      /**
       * Subtracts two vectors
       *
       * @param left Vector3
       * @param right Vector3
       * @return Vector3
       */
      friend Vector3 operator- ( const Vector3 & left, const Vector3 & right ) {
         return Vector3 ( left.getX() - right.getX(),
                          left.getY() - right.getY(),
                          left.getZ() - right.getZ() );
      }


      /**
       * Subtract another Vector3
       *
       * @param arg Vector3
       * @return self with new values
       */
      Vector3& operator-= ( const Vector3 & arg ) {
         m_x -= arg.getX();
         m_y -= arg.getY();
         m_z -= arg.getZ();
         return *this;
      }


      /**
       * Multiple with simple value
       *
       * @param arg T
       * @return Vector3
       */
      Vector3 operator* ( const T & arg ) {
         return Vector3 ( m_x * arg, m_y * arg, m_z * arg );
      }


      /**
       * Multiple vector with simple value
       *
       * @param value T
       * @param vector Vector3
       * @return Vector3
       */
      friend Vector3 operator* ( const T & value, const Vector3<T> & vector ) {
         return Vector3 ( vector.getX() * value,
                          vector.getY() * value,
                          vector.getZ() * value );
      }


      /**
       * Multiple vector with simple value
       *
       * @param vector Vector3
       * @param value T
       * @return Vector3
       */
      friend Vector3 operator* ( const Vector3<T> & vector, const T & value ) {
         return Vector3 ( vector.getX() * value,
                          vector.getY() * value,
                          vector.getZ() * value );
      }


      /**
       * Multiple self with simple value
       *
       * @param arg
       * @return self with new values
       */
      Vector3& operator*= ( const T & arg ) {
         m_x *= arg;
         m_y *= arg;
         m_z *= arg;
         return *this;
      }


      /**
       * Divides vectors with simple value
       *
       * @param arg
       * @return Vector3
       */
      Vector3 operator/ ( const T & arg ) {
         return Vector3 ( m_x / arg, m_y / arg, m_z / arg );
      }


      /**
       * Divides vectors with simple value
       *
       * @param vector Vector3
       * @param arg T
       * @return Vector3
       */
      friend Vector3 operator/ ( const Vector3 & vector, const T & value ) {
         return Vector3 ( vector.getX() / value,
                          vector.getY() / value,
                          vector.getZ() / value );
      }



      /**
       * Divides self with simple value
       *
       * @param arg
       * @return self with new values
       */
      Vector3& operator/= ( const T & arg ) {
         m_x /= arg;
         m_y /= arg;
         m_z /= arg;
         return *this;
      }



      /**
       * Compares two vectors
       *
       * @param arg
       * @return is equal
       */
      int operator== ( const Vector3 & arg ) {
         return m_x == arg.getX() &&
                m_y == arg.getY() &&
                m_z == arg.getZ();
      }


      /**
       * Compares two vectors
       *
       * @param arg
       * @return is not equal
       */
      int operator!= ( const Vector3 & arg ) {
         return ! ( m_x == arg.getX() &&
                    m_y == arg.getY() &&
                    m_z == arg.getZ() );
      }



      /**
       * Calculate dot product
       *
       * @param arg Vector3
       * @return dot product (simple value)
       */
      T dot ( const Vector3 &arg ) const {
         return m_x * arg.getX() + m_y * arg.getY() + m_z * arg.getZ();
      }


      /**
       * Calculate cross product
       *
       * @param arg Vector3
       * @return cross product (Vector3)
       */
      Vector3 cross ( const Vector3 &arg ) const {
         return Vector3 ( m_y * arg.getZ() - m_z * arg.getY(),
                          m_z * arg.getX() - m_x * arg.getZ(),
                          m_x * arg.getY() - m_y * arg.getX() );
      }


      /**
       * Calculates lenght of Vector3
       *
       * @return lenght
       */
      T length() const {
         return std::sqrt ( m_x * m_x + m_y * m_y + m_z * m_z );
      }


      /**
       * normalized copy version of self
       *
       * @return nomalized self
       */
      Vector3 normalize() const {
         T len = length();
         return Vector3 ( m_x / len, m_y / len, m_z / len );
      }
};

typedef Vector3<GLfloat> Vector3f;


}//end of namespace PZ

#endif
