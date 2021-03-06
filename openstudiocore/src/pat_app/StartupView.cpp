/**********************************************************************
 *  Copyright (c) 2008-2013, Alliance for Sustainable Energy.  
 *  All rights reserved.
 *  
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *  
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#include <pat_app/StartupView.hpp>
#include <QVBoxLayout>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QPixmap>

namespace openstudio{
  
namespace pat {

namespace startupview {

class SubSection : public QWidget 
{ 
  public: 

  SubSection(const QString & title, const QString & description, QLabel * imageLabel) : QWidget() 
  {
    QHBoxLayout * mainHLayout = new QHBoxLayout();
    setLayout(mainHLayout);

    mainHLayout->addWidget(imageLabel);

    QVBoxLayout * mainVLayout = new QVBoxLayout();
    mainHLayout->addLayout(mainVLayout);
    QLabel * titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("QLabel { font-size: 14px; font: bold; color: #242D31; }");
    titleLabel->setWordWrap(true);
    mainVLayout->addWidget(titleLabel);

    QHBoxLayout * descriptionHLayout = new QHBoxLayout();
    mainVLayout->addLayout(descriptionHLayout);
    descriptionHLayout->addSpacing(35);

    QLabel * descriptionLabel = new QLabel(description);
    descriptionLabel->setFixedWidth(700);
    descriptionLabel->setStyleSheet("QLabel { font-size: 14px; color: black; }");
    descriptionLabel->setWordWrap(true);
    descriptionHLayout->addWidget(descriptionLabel);

    mainHLayout->setAlignment(Qt::AlignLeft);
  }
};

class Note : public QWidget
{
  public:

  Note(const QString & text)
    : QWidget()
  {
    setObjectName("Note");

    QString style;
    style.append("QWidget#Note { ");
    style.append("background-color: qlineargradient(x1:0,y1:0,x2:1,y2:0,stop: 0 #FDBC3B, stop: 1 #F47920); ");
    style.append("}");

    setStyleSheet(style);

    setMinimumHeight(40);

    QVBoxLayout * mainVLayout = new QVBoxLayout();
    setLayout(mainVLayout);

    QLabel * noteLabel = new QLabel(text);
    noteLabel->setWordWrap(true);
    noteLabel->setStyleSheet("QLabel { font-size: 14px; font: bold; color: black; }");
    mainVLayout->addWidget(noteLabel);
  }

  protected:

  void paintEvent(QPaintEvent *)
  {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  }
};

} // startupview

StartupView::StartupView(QWidget *parent) : 
  QWidget(parent)
{
  setStyleSheet("openstudio--pat--StartupView { background: #808080; }");

  QVBoxLayout * mainVLayout = new QVBoxLayout();
  mainVLayout->setContentsMargins(0,0,0,0);
  mainVLayout->setSpacing(10);
  mainVLayout->setAlignment(Qt::AlignTop);
  setLayout(mainVLayout);

  QLabel * gettingStartedLabel = new QLabel("Getting Started");
  gettingStartedLabel->setIndent(10);
  gettingStartedLabel->setWordWrap(true);
  gettingStartedLabel->setStyleSheet("QLabel { font-size: 20px; font: bold; color: #242D31; }");
  mainVLayout->addWidget(gettingStartedLabel);

  QLabel * newProjectLabel = new QLabel("Under File Menu Choose New Project or Open Project to Get Started");
  newProjectLabel->setIndent(10);
  newProjectLabel->setWordWrap(true);
  newProjectLabel->setStyleSheet("QLabel { font-size: 14px; font: bold; color: black; }");
  mainVLayout->addWidget(newProjectLabel);

  // Organize
  
  QString organizeDescription;
  organizeDescription.append("Select the baseline model and measures you will use in this project.  ");
  organizeDescription.append("Measures can come from the local Building Component Library (BCL) ");
  organizeDescription.append("or the Online BCL, ");
  organizeDescription.append("or you can create your own, available in My Measures.");
  QLabel * organizeImageLabel = new QLabel();
  organizeImageLabel->setFixedSize(54,65);
  organizeImageLabel->setPixmap(QPixmap(":images/measures_big.png"));
  startupview::SubSection * organizeSection;
  organizeSection = new startupview::SubSection("Organize and Edit Measures for Project",organizeDescription,organizeImageLabel);
  mainVLayout->addWidget(organizeSection);

  // Note 1

  QString note1Text;
  note1Text.append("Note: After completing this first tab, coming back to this tab and making changes ");
  note1Text.append("may result in deletion or other changes to your design alternatives.");
  startupview::Note * note1 = new startupview::Note(note1Text);
  mainVLayout->addWidget(note1);

  // Select

  QString selectDescription;
  selectDescription.append("Create a series of design alternatives that you want to run.  ");
  selectDescription.append("A design alternative is the baseline model with one or more measures applied.  ");
  selectDescription.append("Design alternatives allow you to perform \"what-if\" analyses with ");
  selectDescription.append("different combinations of measures.");
  QLabel * selectImageLabel = new QLabel();
  selectImageLabel->setFixedSize(54,65);
  selectImageLabel->setPixmap(QPixmap(":images/design_alts_big.png"));
  startupview::SubSection * selectSection;
  selectSection = new startupview::SubSection("Select Measures and Create Design Alternatives",selectDescription,selectImageLabel);
  mainVLayout->addWidget(selectSection);

  // Note 2

  QString note2Text;
  note2Text.append("Note: After completing the second tab, coming back to this tab and making changes ");
  note2Text.append("will result in the deletion of simulation results.");
  startupview::Note * note2 = new startupview::Note(note2Text);
  mainVLayout->addWidget(note2);

  // Run

  QString runDescription;
  runDescription.append("Once you've set up your design alternatives, you're ready to run the simulations.  ");
  runDescription.append("The run button will kick off each design alternative simulation process.  ");
  runDescription.append("After the simulations finish, you can dig down into the info messages, warning messages, ");
  runDescription.append("and error messages from each design alternative.");
  QLabel * runImageLabel = new QLabel();
  runImageLabel->setFixedSize(54,65);
  runImageLabel->setPixmap(QPixmap(":images/run_big.png"));
  startupview::SubSection * runSection;
  runSection = new startupview::SubSection("Run Simulations",runDescription,runImageLabel);
  mainVLayout->addWidget(runSection);

  // Create Reports

  QString reportDescription;
  reportDescription.append("Compare results from Design Alternatives.  Currently only one report is available.  ");
  reportDescription.append("More reports are being developed.");
  QLabel * reportImageLabel = new QLabel();
  reportImageLabel->setFixedSize(54,65);
  reportImageLabel->setPixmap(QPixmap(":images/results_big.png"));
  startupview::SubSection * reportSection;
  reportSection = new startupview::SubSection("Create and View Reports",reportDescription,reportImageLabel);
  mainVLayout->addWidget(reportSection);
}

void StartupView::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

} // pat

} // openstudio

