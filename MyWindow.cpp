
#include "MyWindow.h"

MyWindow::MyWindow (Database& database, QWidget *parent)
: QWidget (parent), _database(database)
{

	gl = new GLWidget (_database);
	gl->setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Ignored); // Expand as much as possible

	QLabel* searchLabel = new QLabel ("Search");
	searchLabel->setAlignment(Qt::AlignCenter | Qt::AlignRight);
	searchField = new QLineEdit ("net names or grid positions; examples: 'N16' or '34 55 2'");

	QLabel* speedLabel = new QLabel ("Speed");
	speedLabel->setAlignment(Qt::AlignCenter | Qt::AlignRight);
	QLabel* axisLabel = new QLabel ("Axis");
	axisLabel->setAlignment(Qt::AlignCenter | Qt::AlignRight);
	QLabel* namesLabel = new QLabel ("Names");
	namesLabel->setAlignment(Qt::AlignCenter | Qt::AlignRight);
	QLabel* segmentsLabel = new QLabel ("Segments");
	segmentsLabel->setAlignment(Qt::AlignCenter | Qt::AlignRight);
	QLabel* terminalsLabel = new QLabel ("Terminals");
	terminalsLabel->setAlignment(Qt::AlignCenter | Qt::AlignRight);
	QLabel* websLabel = new QLabel ("Webs");
	websLabel->setAlignment(Qt::AlignCenter | Qt::AlignRight);
	QLabel* gridLabel = new QLabel ("Grid");
	gridLabel->setAlignment(Qt::AlignCenter | Qt::AlignRight);

	mousePosition = new QLabel ("[0, 0]");
	mousePosition->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Maximum);
	mousePosition->setAlignment(Qt::AlignLeft);
	selectedObject = new QLabel ("Selected: (none)");
	selectedObject->setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Maximum);
	selectedObject->setAlignment(Qt::AlignLeft);


	message = new QLabel ("");
	message->setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Maximum);
	message->setAlignment(Qt::AlignLeft);

	QSpinBox* speed = new QSpinBox;
	speed->setRange (1, 20);
	speed->setValue(gl->getSpeed());

	QCheckBox* axis = new QCheckBox;
	axis->setChecked(gl->getAxis());
	QCheckBox* names = new QCheckBox;
	names->setChecked(gl->getNames());
	QCheckBox* segments = new QCheckBox;
	segments->setChecked(gl->getSegments());
	QCheckBox* terminals = new QCheckBox;
	terminals->setChecked(gl->getTerminals());
	QCheckBox* webs = new QCheckBox;
	webs->setChecked(gl->getWebs());
	QCheckBox* grid = new QCheckBox;
	grid->setChecked(gl->getGrid());

	QPushButton* clearButton = new QPushButton ("Clear");
	QPushButton* unroutedButton = new QPushButton ("Unrouted");

	QHBoxLayout *toolbar1 = new QHBoxLayout;
	toolbar1->addWidget (searchLabel);
	toolbar1->addWidget (searchField);
	toolbar1->addWidget (speedLabel);
	toolbar1->addWidget (speed);
	toolbar1->addWidget (axisLabel);
	toolbar1->addWidget (axis);
	toolbar1->addWidget (namesLabel);
	toolbar1->addWidget (names);
	toolbar1->addWidget (segmentsLabel);
	toolbar1->addWidget (segments);
	toolbar1->addWidget (terminalsLabel);
	toolbar1->addWidget (terminals);
	toolbar1->addWidget (websLabel);
	toolbar1->addWidget (webs);
	toolbar1->addWidget (gridLabel);
	toolbar1->addWidget (grid);

	QHBoxLayout *toolbar2 = new QHBoxLayout;
	toolbar2->addWidget (mousePosition);
	toolbar2->addWidget (selectedObject, 1);
	toolbar2->addWidget (message);
	toolbar2->addWidget (clearButton);
	toolbar2->addWidget (unroutedButton);


	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget (gl);
	layout->addLayout (toolbar1);
	layout->addLayout (toolbar2);

	connect (speed, SIGNAL(valueChanged(int)), gl, SLOT(setSpeed(int)));
	connect (axis, SIGNAL(toggled(bool)), gl, SLOT(setAxis(bool)));
	connect (names, SIGNAL(toggled(bool)), gl, SLOT(setNames(bool)));
	connect (segments, SIGNAL(toggled(bool)), gl, SLOT(setSegments(bool)));
	connect (terminals, SIGNAL(toggled(bool)), gl, SLOT(setTerminals(bool)));
	connect (webs, SIGNAL(toggled(bool)), gl, SLOT(setWebs(bool)));
	connect (grid, SIGNAL(toggled(bool)), gl, SLOT(setGrid(bool)));
	connect (clearButton, SIGNAL (clicked()), gl, SLOT (unhighlightAll()));
	connect (unroutedButton, SIGNAL (clicked()), gl, SLOT (highlightUnrouted()));
	connect (searchField, SIGNAL (returnPressed()), this, SLOT (requestSearch()));
	connect (gl, SIGNAL (positionChanged()), this, SLOT (updatePosition()));
	connect (gl, SIGNAL (selectedChanged()), this, SLOT (updateSelected()));
	connect (gl, SIGNAL (messageChanged()), this, SLOT (updateMessage()));

	setLayout (layout);
}

void MyWindow::requestSearch () {
	const std::string& s = searchField->text().toStdString();
	gl->search(s);
}


void MyWindow::updatePosition () {
	const Vec3f pos = gl->getMousePosition();

	std::ostringstream s;
	s << "[" << floor(pos[0]) << ", " << floor(-pos[2]) << "]";

	mousePosition->setText (s.str().c_str());
}

void MyWindow::updateSelected () {
	const std::string highlighted = gl->getHighlighted();
	std::ostringstream s;
	if (highlighted != "") {
		s << "Selected: " << highlighted;
	}
	else {
		s << "Selected: (none)";
	}
	selectedObject->setText (s.str().c_str());
}

void MyWindow::updateMessage () {
	const std::string s = gl->getMessage();
	message->setText (s.c_str());
}
