#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

#include <QFont>
#include <QGLWidget>
#include <QWidget>
#include <QMouseEvent>
#include <QApplication>

#include "Node.h"
#include "utils.h"
#include "vecmath.h"
#include "Frame.h"
#include "Vec3f.h"
#include "Node.h"
#include "Segment.h"
#include "Database.h"
//#include "GLTerminal.h"
#include "GLWeb.h"
#include "GLFunctions.h"
#include "GLGrid.h"
#include "glUtils.h"

#include <cstring> // memcpy

//typedef unsigned int GLSegment[12*3];

class MyWindow;

const int QSVIEW_PERSP = 0;
const int QSVIEW_ORTHO = 1;

class GLWidget : public QGLWidget
{
	Q_OBJECT

	private:

	Database& _database;

	unsigned int _windowWidth;
	unsigned int _windowHeight;

	float _segmentThickness;
	float _terminalThickness;
	float _webPattern;

	float _pitch;
	float _height;

	float* _segmentVertexArray;
	float* _segmentColorArray;
	unsigned int* _segmentIndexArray;

	float* _terminalVertexArray;
	float* _terminalColorArray;
	unsigned int* _terminalIndexArray;

	std::vector<Vec3f> _segmentColors;
	Vec3f _viaColor;
	Vec3f _terminalColor;
	Vec3f _webColor;

	Frame _camera;
	Vec3f _startingPosition;

	int _planeDegAngle;
	int _upDegAngle;
	float _speed;

//	std::vector<GLSegment> _glSegmentList;
//	std::vector<GLTerminal> _glTerminalList;
	std::vector<GLWeb> _glWebList;

	GLGrid _glGrid;

//	std::vector<int> _drawSegmentList; // maintained here so that it doesn't get de/allocated often
//	std::vector<int> _drawTerminalList;
	std::vector<int> _drawWebList;

	bool _showAxis;
	bool _showNames;
	bool _showSegments;
	bool _showTerminals;
	bool _showWebs;
	bool _showGrid;
	Vec3f _mousePosition;
	std::string _message;

	QFont* _font;

	std::vector<AABB> _terminalBoxes;
	std::vector<AABB> _segmentBoxes;

	std::set<unsigned int> _highlightList; // set so that I can search faster than vector/list

	public:
	GLWidget (Database& database, QWidget *parent = 0);
	virtual ~GLWidget ();

	void buildGrid ();
//	void buildLists();
	void drawAxis();
	void drawLists();
	void clearLists();

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	Ray buildRay (const unsigned int& eventx, const unsigned int& eventy);
	void keyPressEvent (QKeyEvent *event);
	void mousePressEvent (QMouseEvent *event);
	void mouseMoveEvent (QMouseEvent *event);
	QPoint _clickPos;

	int getSpeed();
	bool getAxis();
	bool getNames();
	bool getTerminals();
	bool getWebs();
	bool getSegments();
	bool getGrid();
	Vec3f getMousePosition() const;
	std::string getHighlighted () const;
	std::string getMessage () const;

	void search (const std::string& s);

public slots:
	void setSpeed (int newSpeed);
	void setAxis (bool value);
	void setNames (bool value);
	void setSegments (bool value);
	void setWebs (bool value);
	void setTerminals (bool value);
	void setGrid (bool value);
	void unhighlightAll ();
	void highlightNet (const unsigned int& index, bool update=true);
	void unhighlightNet (const unsigned int& index, bool update=true);
	void toggleHighlightNet (const unsigned int& index, bool update=true);
	void highlightUnrouted ();

signals:
	void positionChanged ();
	void selectedChanged ();
	void messageChanged ();
};

#endif

