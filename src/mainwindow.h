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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"
#include <QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
      Q_OBJECT

   public:
      MainWindow ( QWidget* parent = 0, Qt::WFlags fl = 0 );
      ~MainWindow();

   protected:
      PZSculpt::GLWidget * m_ui_glWidget;

   protected:
      void initUiObjects();

   public slots:
      /*$PUBLIC_SLOTS$*/

   protected slots:
      void on_actionImport_triggered();
      void on_actionExport_triggered();
      void on_actionUndo_triggered();
      void on_actionRedo_triggered();
      void on_pushButtonDown_clicked();
      void on_pushButtonUp_clicked();
      void on_pushButtonSubd_clicked();
      void on_spinBoxSize_valueChanged ( int value );
      void on_spinBoxStrength_valueChanged ( int value );
      void on_spinBoxIntencity_valueChanged ( int value );
      void on_radioButtonDraw_clicked();
      void on_radioButtonSmooth_clicked();
      void on_radioButtonPinch_clicked();

};

#endif

