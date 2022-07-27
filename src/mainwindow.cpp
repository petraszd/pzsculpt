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
#include <QAction>
#include "mainwindow.h"

MainWindow::MainWindow ( QWidget* parent, Qt::WFlags fl )
      : QMainWindow ( parent, fl ), Ui::MainWindow()
{
   setupUi ( this );
   initUiObjects();
}


MainWindow::~MainWindow()
{
}


void MainWindow::initUiObjects()
{
   m_ui_glWidget = qFindChild<PZSculpt::GLWidget*> ( this, "canvas" );

   QAction * ui_actionRedo = qFindChild<QAction*> ( this, "actionRedo" );
   QAction * ui_actionUndo = qFindChild<QAction*> ( this, "actionUndo" );
   connect ( m_ui_glWidget, SIGNAL ( canRedo ( bool ) ),
             ui_actionRedo, SLOT ( setEnabled ( bool ) ) );
   connect ( m_ui_glWidget, SIGNAL ( canUndo ( bool ) ),
             ui_actionUndo, SLOT ( setEnabled ( bool ) ) );

   QTextEdit * ui_text = qFindChild<QTextEdit*> ( this, "textEditMeshInfo" );
   connect ( m_ui_glWidget, SIGNAL ( meshTextChanged ( const QString & ) ),
             ui_text, SLOT ( setText ( const QString & ) ) );
}


void MainWindow::on_actionImport_triggered()
{
   m_ui_glWidget->openFile();
}


void MainWindow::on_actionExport_triggered()
{
   m_ui_glWidget->saveFile();
}


void MainWindow::on_actionUndo_triggered()
{
   m_ui_glWidget->undo();
}


void MainWindow::on_actionRedo_triggered()
{
   m_ui_glWidget->redo();
}


void MainWindow::on_pushButtonDown_clicked()
{
   m_ui_glWidget->stepDown();
}


void MainWindow::on_pushButtonUp_clicked()
{
   m_ui_glWidget->stepUp();
}


void MainWindow::on_pushButtonSubd_clicked()
{
   m_ui_glWidget->subdivide();
}


void MainWindow::on_spinBoxSize_valueChanged ( int value )
{
   m_ui_glWidget->setBrushSize ( value );
}


void MainWindow::on_spinBoxStrength_valueChanged ( int value )
{
   m_ui_glWidget->setBrushStrength ( value );
}


void MainWindow::on_spinBoxIntencity_valueChanged ( int value )
{
   m_ui_glWidget->setBrushIntencity ( value );
}

void MainWindow::on_radioButtonDraw_clicked()
{
   m_ui_glWidget->setDrawToPusher();
}


void MainWindow::on_radioButtonSmooth_clicked()
{
   m_ui_glWidget->setDrawToSmoother();
}


void MainWindow::on_radioButtonPinch_clicked()
{
   m_ui_glWidget->setDrawToPincher();
}
