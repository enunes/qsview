
#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <sstream>
#include "Database.h"
#include "GLWidget.h"
#include "Node.h"
#include "Segment.h"

class MyWindow : public QWidget
{
	Q_OBJECT

	public:
	Database& _database;
	GLWidget* gl;
	QLineEdit* searchField;
	QLabel* mousePosition;
	QLabel* selectedObject;
	QLabel* message;

	MyWindow (Database& database, QWidget *parent = 0);

	public slots:
	void requestSearch ();
	void updatePosition ();
	void updateSelected ();
	void updateMessage ();
};

#endif

