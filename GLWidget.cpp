
#include "GLWidget.h"

GLWidget::GLWidget (Database& database, QWidget *parent)
: QGLWidget (parent), _database(database)
{
	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking (true);

	_font = new QFont ("Monospace", 8);

	_font->setStyleHint (QFont::Monospace);
	_font->setStyleStrategy (QFont::NoAntialias);

	_pitch = 0.5;
	_height = 0.5;
	_segmentThickness = 0.05;

	_pitch = 0.5;
	_height = 0.5;
	_terminalThickness = 0.08;

	_planeDegAngle = 135;
	_upDegAngle = 270;
	_startingPosition = Vec3f (-3.0f, 3.0f, 3.0f);

	_viaColor = Vec3f (0.4f, 0.4f, 0.0f);
	_terminalColor = Vec3f (0.4f, 0.4f, 0.4f);
	_webColor = Vec3f (0.0f, 1.0f-0.2f, 1.0f-0.2f);

	_segmentColors.push_back(Vec3f (0.8f, 0.0f, 0.0f));
	_segmentColors.push_back(Vec3f (0.0f, 0.8f, 0.0f));
	_segmentColors.push_back(Vec3f (0.0f, 0.0f, 0.8f));
	_segmentColors.push_back(Vec3f (0.5f, 0.0f, 0.0f));
	_segmentColors.push_back(Vec3f (0.0f, 0.5f, 0.0f));
	_segmentColors.push_back(Vec3f (0.0f, 0.0f, 0.5f));

//	_glSegmentList = std::vector<GLSegment> (_database.segmentList.size());

	_terminalBoxes = std::vector<AABB> (_database.terminalList.size());
	_segmentBoxes = std::vector<AABB> (_database.segmentList.size());

	_segmentVertexArray = new float[24*_database.segmentList.size()]; // 8 vertices with 3 floats each = 24, thats for each segment
	_segmentColorArray = new float[24*_database.segmentList.size()]; // same as _segmentVertexArray
	_segmentIndexArray = new unsigned int[36*_database.segmentList.size()]; // each segment will have 12 triangles, and each triangle has 3 indices

	_terminalVertexArray = new float[24*_database.terminalList.size()];
	_terminalColorArray = new float[24*_database.terminalList.size()];
	_terminalIndexArray = new unsigned int[36*_database.terminalList.size()];

	unsigned int indexOffset = 0;
	unsigned int arrayOffset = 0;


	// build____Vertices() functions below takes these arrays as references and stores the result onto them
	unsigned int tempIndexArray[36]; // They are only used for temporary storage and are fully rewritten so they can be reused for every iteration
	float tempVertexArray[24];
	float tempColorArray[24];

	for (unsigned int i=0; i<_database.segmentList.size(); ++i) {
		Vec3f color;


		if (_database.segmentList[i].axis == 2) color = _viaColor;
		else color = _segmentColors[_database.segmentList[i].start[2] % _segmentColors.size()];

		buildSegmentVertices (_database.segmentList[i], color, _pitch, _height, _segmentThickness, indexOffset, tempVertexArray, tempColorArray, tempIndexArray);


		// put their result onto the big vertex array
		std::memcpy (&_segmentVertexArray[24*i], tempVertexArray, 24*sizeof(float));
		std::memcpy (&_segmentColorArray[24*i], tempColorArray, 24*sizeof(float));
		std::memcpy (&_segmentIndexArray[36*i], tempIndexArray, 36*sizeof(unsigned int));

		// increase the positions so that the next one doesn't overwrite
		arrayOffset += 24; // arrayOffset gets 24 because thats 8 vertices with 3 floats each
		indexOffset += 8; // indexOffset gets 8 because every tempVertexArray will return with 8 more vertices, so the next has to index the next 8!

		_segmentBoxes[i] = buildBox (_database.segmentList[i], _pitch, _height, _segmentThickness);
		// maybe use getBorders on the vertex array?
	}

	// These will be reused, reset them
	indexOffset = 0;
	arrayOffset = 0;

	// Build the terminalList vertices
	for (unsigned int i=0; i<_database.terminalList.size(); ++i) {

		buildTerminalVertices (_database.terminalList[i].coord, _terminalColor, _pitch, _height, _terminalThickness, indexOffset, tempVertexArray, tempColorArray, tempIndexArray);

		// put their result onto the big vertex array
		std::memcpy (&_terminalVertexArray[24*i], tempVertexArray, 24*sizeof(float));
		std::memcpy (&_terminalColorArray[24*i], tempColorArray, 24*sizeof(float));
		std::memcpy (&_terminalIndexArray[36*i], tempIndexArray, 36*sizeof(unsigned int));

		// increase the positions so that the next one doesn't overwrite
		arrayOffset += 24; // arrayOffset gets 24 because thats 8 vertices with 3 floats each
		indexOffset += 8; // indexOffset gets 8 because every tempVertexArray will return with 8 more vertices, so the next has to index the next 8!

		_terminalBoxes[i] = buildBox (_database.terminalList[i].coord, _pitch, _height, _terminalThickness);
	}

	// Build the webs, from using the netlist database
	_glWebList = std::vector<GLWeb> (_database.netList.size()); // Allocate
	for (unsigned int i=0; i<_database.netList.size(); ++i) {
		_glWebList[i].build (_database.netList[i], _database.terminalList, _pitch, _height); // each _glWebList[i] will have a vertex array
		_glWebList[i].setWidth (1);
		_glWebList[i].setColor (_webColor);
	}

/*	_glTerminalList = std::vector<GLTerminal> (_database.terminalList.size());
	for (unsigned int i=0; i<_database.terminalList.size(); ++i) {
		const Terminal& theTerminal = _database.terminalList[i];
		const unsigned int& netIndex = theTerminal.net;
		const std::string& netName = _database.netNames[netIndex];
		const Net& theNet = _database.netList[netIndex];
		unsigned int j=0;
		for (j=0; j<theNet.terminals.size(); ++j) { // search for the index of the terminal on the list of terminals of the net
			if (_database.terminalList[theNet.terminals[j]].coord == theTerminal.coord) {
				break;
			}
		}
		std::stringstream tName;
		tName << netName << ":" << j;
		_glTerminalList[i].buildText (tName.str(), _database.terminalList[i].coord, _pitch, _height);
		_glTerminalList[i].setTextColor (Vec3f (0.8f, 0.3f, 0.0f));
	}*/




	


	_speed = 1.0f;
	_showAxis = true;
	_showNames = false;
	_showSegments = true;
	_showTerminals = true;
	_showWebs = false;
	_showGrid = true;

	_camera = Frame();
	_camera.position = _startingPosition;
	_camera.orientation = computeSpheric (degToRad(_planeDegAngle), degToRad(_upDegAngle));
	_camera.up = computeSpheric (degToRad(_planeDegAngle), degToRad(_upDegAngle+90));

//	_mouseRay = Ray  (Vec3f (0.0f, 0.0f, 0.0f), Vec3f (1.0f, 1.0f, 1.0f));

	//buildLists();
	buildGrid();

}

Vec3f GLWidget::getMousePosition () const {
	return _mousePosition;
}

std::string GLWidget::getMessage () const {
	return _message;
}

std::string GLWidget::getHighlighted () const {
	std::ostringstream o;
	for (std::set<unsigned int>::const_iterator it = _highlightList.begin(); it != _highlightList.end(); ++it) {
		o << _database.netNames[*it] << " ";
	}
	return o.str();
}

GLWidget::~GLWidget () {
	delete [] _segmentVertexArray;
	delete [] _segmentColorArray;
	delete [] _segmentIndexArray;

	delete [] _terminalVertexArray;
	delete [] _terminalColorArray;
	delete [] _terminalIndexArray;
}

void GLWidget::initializeGL() {

	glClearColor (1.0, 1.0, 1.0, 0.0);

	glEnable (GL_DEPTH_TEST);
	//glEnable (GL_CULL_FACE);


}

void GLWidget::resizeGL(int w, int h) {
	_windowWidth = w;
	_windowHeight = h;
	glViewport (0, 0, w, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (45.0, (float)_windowWidth/(float)_windowHeight, 1.0, 1000.0);
	glMatrixMode (GL_MODELVIEW);
}

void GLWidget::buildGrid () {
	_glGrid = GLGrid ();
	//_glGrid.build (MatrixCoord3D (0, 0, 0), _database.matrix.getSize(), -0.3*_height, _pitch, _height);
	_glGrid.build (MatrixCoord3D (0, 0, 0), _database.matrixSize, 0.0f, _pitch, _height);
	_glGrid.setColor (Vec3f (1.0f-0.15f, 1.0f-0.15f, 1.0f-0.15f)); // Magic color, took via trying until like...
}

/*void GLWidget::buildLists() {
	MatrixCoord3D size = _database.matrix.getSize();
	for (int i=0; i<size[0]; ++i) {
		for (int j=0; j<size[1]; ++j) {
			for (int k=0; k<size[2]; ++k) {
				const Node& node = _database.matrix.at(i, j, k);
				if (node.t != -1) {
					_drawTerminalList.push_back (node.t);
				}
			//	for (unsigned int s=0; s<node.s.size(); ++s) {
			//		_drawSegmentList.push_back (node.s[s]);
			//	}
			}
		}
	}
//	_drawTerminalList.sort();
//	_drawTerminalList.
//	std::sort(_drawSegmentList.begin(), _drawSegmentList.end());
//	std::unique(_drawSegmentList.begin(), _drawSegmentList.end());
}*/

void GLWidget::drawAxis () {
	float mv[16];
	int v[4];
	glGetFloatv (GL_MODELVIEW_MATRIX, mv);
	glGetIntegerv(GL_VIEWPORT, v);

	glPushAttrib (GL_VIEWPORT_BIT);
	const int viewportSize = 50;
	glViewport (0, v[3]-viewportSize, viewportSize, viewportSize);

	glMatrixMode (GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho (-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode (GL_MODELVIEW);
	glPushMatrix(); // Pushing modelview
	glLoadIdentity();
	glTranslatef (0.0f, 0.0f, -0.5f);

	glLineWidth (4);

	glBegin (GL_LINES);
	glColor3f (1.0f, 0.6f, 0.6f);
	glVertex3f (0.0f, 0.0f, 0.0f);
	glVertex3f (mv[0], mv[1], mv[2]);
	glColor3f (0.6f, 1.0f, 0.6f);
	glVertex3f (0.0f, 0.0f, 0.0f);
	glVertex3f (mv[4], mv[5], mv[6]);
	glColor3f (0.6f, 0.6f, 1.0f);
	glVertex3f (0.0f, 0.0f, 0.0f);
	glVertex3f (-mv[8], -mv[9], -mv[10]);
	glEnd();
	glPopAttrib ();

	glLineWidth (1);

	glMatrixMode (GL_PROJECTION);
	glPopMatrix();
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix();
}

void GLWidget::drawLists() {
	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_COLOR_ARRAY);
	//	if (_showSegments) {
	//		for (unsigned int i=0; i<_drawSegmentList.size(); ++i) {
	//			const GLSegment& gls = _glSegmentList[_drawSegmentList[i]];
	//			glColor3fv (gls.color);
	//			glVertexPointer (3, GL_FLOAT, 0, gls.vertexArray);
	//			glDrawArrays (GL_TRIANGLES, 0, 36); // 36 is the exact number of indexes
	//		}
	//	}


	if (_showSegments) {
		glVertexPointer (3, GL_FLOAT, 0, _segmentVertexArray);
		glColorPointer (3, GL_FLOAT, 0, _segmentColorArray);
		glDrawElements (GL_TRIANGLES, 36*_database.segmentList.size(), GL_UNSIGNED_INT, _segmentIndexArray);
	}

	if (_showTerminals) {
		glVertexPointer (3, GL_FLOAT, 0, _terminalVertexArray);
		glColorPointer (3, GL_FLOAT, 0, _terminalColorArray);
		glDrawElements (GL_TRIANGLES, 36*_database.terminalList.size(), GL_UNSIGNED_INT, _terminalIndexArray);
	}

	glDisableClientState (GL_COLOR_ARRAY);

	if (_showGrid) {
		glColor3fv (_glGrid.color);
		glLineWidth (1);
		glVertexPointer (3, GL_FLOAT, 0, _glGrid.vertexArray);
		glDrawArrays (GL_LINES, 0, _glGrid.vertexNumber);
	}

	if (_showWebs) {
		for (unsigned int i=0; i<_glWebList.size(); ++i) {
			const GLWeb& glw = _glWebList[i];
			glColor3fv (glw.color);
			glLineWidth (glw.width);
			glVertexPointer (3, GL_FLOAT, 0, glw.vertexArray);
			glDrawArrays (GL_LINES, 0, glw.vertexNumber); // 36 is the exact number of indexes
		}
	}

	/*	if (_showTerminals) {
		for (unsigned int i=0; i<_drawTerminalList.size(); ++i) {
		const GLTerminal& glt = _glTerminalList[_drawTerminalList[i]];
		glColor3fv (glt.color);
		glVertexPointer (3, GL_FLOAT, 0, glt.vertexArray);
		glDrawArrays (GL_TRIANGLES, 0, 36); // 36 is the exact number of indexes
		}
		}*/
	glDisableClientState (GL_VERTEX_ARRAY);

	if (_showNames) {
		glDisable (GL_DEPTH_TEST);
		glColor3f (0.8f, 0.3f, 0.0f);
		for (unsigned int i=0; i<_database.terminalList.size(); ++i) {
			const Terminal& t = _database.terminalList[i];
			const Vec3f textPosition = Vec3f (static_cast<float>(t.coord[0])*_pitch, static_cast<float>(t.coord[2])*_height, -static_cast<float>(t.coord[1])*_pitch);
			renderText (textPosition[0], textPosition[1], textPosition[2], QString(_database.terminalLabels[i].c_str()), *_font);
		}
		glEnable (GL_DEPTH_TEST);
	}


	glLineWidth (8);
	glColor3f (0.0f, 0.0f, 0.0f);
	for (unsigned int i=0; i < _segmentBoxes.size(); ++i) {
		if (_highlightList.find(_database.segmentList[i].net) != _highlightList.end()) {
			drawGeometry (_segmentBoxes[i]);
		}
	}

	for (unsigned int i=0; i < _terminalBoxes.size(); ++i) {
		if (_highlightList.find(_database.terminalList[i].net) != _highlightList.end()) {
			drawGeometry (_terminalBoxes[i]);
		}
	}

//	drawGeometry (_mouseRay);

	if (_showAxis) {
		drawAxis();
	}

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << "opengl error = " << error << std::endl;
	}
}

void GLWidget::clearLists() {
//	_drawSegmentList.clear();
//	_drawTerminalList.clear();
}

void GLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt (_camera.position[0], _camera.position[1], _camera.position[2], _camera.position[0] + _camera.orientation[0], _camera.position[1] + _camera.orientation[1], _camera.position[2] + _camera.orientation[2], _camera.up[0], _camera.up[1], _camera.up[2]);


	//buildLists();
	drawLists();
	//clearLists();

	GLenum glerror = glGetError ();
	if (glerror != 0) {
		std::cout << "OpenGL error = " << glerror << std::endl;
	}
}

void GLWidget::mousePressEvent (QMouseEvent *event) {
	std::set<unsigned int> hit; // a set, so that duplicates get excluded..
	// I'm too lazy to implement something to highlight only the first hit
	_clickPos = event->pos();
	if (event->buttons() & Qt::LeftButton) {
		Ray mouseRay = buildRay (event->x(), event->y());
		//unhighlightAll();
		if (_showSegments) {
			for (unsigned int i=0; i<_segmentBoxes.size(); ++i) {
				if (collision (_segmentBoxes[i], mouseRay)) {
					//std::cout << "collided with " << i << "   net=" << _database.segmentList[i].net << std::endl;
					hit.insert (_database.segmentList[i].net);
				}
			}
		}
		if (_showTerminals) {
			for (unsigned int i=0; i<_terminalBoxes.size(); ++i) {
				if (collision (_terminalBoxes[i], mouseRay)) {
					hit.insert (_database.terminalList[i].net);
				}
			}
		}
		for (std::set<unsigned int>::iterator it = hit.begin(); it != hit.end(); ++it) {
			toggleHighlightNet (*it);
		}
		emit selectedChanged();
		updateGL();
	}
}

Ray GLWidget::buildRay (const unsigned int& eventx, const unsigned int& eventy) {

	double modelview[16], projection[16];
	int viewport[4];
	float z = 1;

	//Read the projection, modelview and viewport matrices
	//using the glGet functions.
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetIntegerv( GL_VIEWPORT, viewport );

	//Read the window z value from the z-buffer	
	glReadPixels( eventx, viewport[3]-eventy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z );	

	double fx, fy, fz, sx, sy, sz;
	gluUnProject (eventx, viewport[3]-eventy, 0.0, modelview, projection, viewport, &fx, &fy, &fz);
	gluUnProject (eventx, viewport[3]-eventy, z, modelview, projection, viewport, &sx, &sy, &sz);

	Vec3f start (fx, fy, fz);
	Vec3f end (sx, sy, sz);

	Ray rr = Ray (start, (end-start));
	//std::cout << rr.start << " " << rr.dir << std::endl;

	return rr;

}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() & Qt::RightButton) {
		_planeDegAngle = (_planeDegAngle + (event->x() - _clickPos.x())) % 360;
		_upDegAngle = (_upDegAngle + (_clickPos.y() - event->y()));

		if (_upDegAngle<181) _upDegAngle = 181;
		if (_upDegAngle>359) _upDegAngle = 359; // Avoiding 'bad' look angles and movement mirroring.

		_camera.orientation = computeSpheric (degToRad (_planeDegAngle), degToRad (_upDegAngle));
		_camera.up = computeSpheric (degToRad(_planeDegAngle), degToRad(_upDegAngle+90));

		_clickPos = event->pos();

		updateGL();
	}
	emit positionChanged ();
/*	else {

		Ray mouseRay = buildRay (event->x(), event->y());
		Plane groundPlane = Plane (Vec3f(0.0f, 1.0f, 0.0f), 0); // plane with normal on y+ and at y=0

		float intersectionParameter = rayPlaneIntersection (_mouseRay, groundPlane);
		Vec3f intersectionPoint = solve (mouseRay, intersectionParameter);

		//_mousePosition = Vec3f (event->x(), event->y(), 0);
		Vec3f alligner (_pitch/2.0f, 0.0f, -_pitch/2.0f);

		intersectionPoint += alligner; // compensate the pitch movement so that stuff is in the center of the grid squares, not at the crosses of line grids
		intersectionPoint /= _pitch; // make each grid square = 1

		// make it int so that it gets truncated to the equivalent matrixcoord3D
		Vec3f intUnit = intersectionPoint;

		_mousePosition = intUnit;
		for (unsigned int i=0; i<_segmentBoxes.size(); ++i) {
			if (collision (_segmentBoxes[i], mouseRay)) {
				std::cout << "collided with " << i << "   net=" << _database.segmentList[i].net << std::endl;
			}

		}
		//_mouseRay = buildRay (event->x(), event->y());
//		unhighlightAll();
		updateGL();

	}*/
	//	std::cout << _planeDegAngle << std::endl;
}


void GLWidget::keyPressEvent (QKeyEvent *event) {
	switch (event->key()) {
		case Qt::Key_W:
			_camera.moveFront(_speed);
			break;
		case Qt::Key_S:
			_camera.moveBack(_speed);
			break;
		case Qt::Key_D:
			_camera.moveRight(_speed);
			break;
		case Qt::Key_A:
			_camera.moveLeft(_speed);
			break;
		case Qt::Key_Q:
			_camera.moveDown(_speed);
			break;
		case Qt::Key_E:
			_camera.moveUp(_speed);
			break;
		case Qt::Key_Escape:
			QApplication::exit();
			break;
	}
	updateGL();
}


int GLWidget::getSpeed () {
	float s = 10.0f*_speed;
	return static_cast<int>(s);
}

bool GLWidget::getAxis () {
	return _showAxis;
}

bool GLWidget::getNames () {
	return _showNames;
}

bool GLWidget::getSegments () {
	return _showSegments;
}

bool GLWidget::getTerminals () {
	return _showTerminals;
}

bool GLWidget::getWebs () {
	return _showWebs;
}

bool GLWidget::getGrid () {
	return _showGrid;
}

void GLWidget::setSpeed (int newSpeed) {
	_speed = static_cast<float>(newSpeed)/10.0f;
}

void GLWidget::setAxis (bool value) {
	_showAxis = value;
	updateGL();
}

void GLWidget::setNames (bool value) {
	_showNames = value;
	updateGL();
}

void GLWidget::setSegments (bool value) {
	_showSegments = value;
	updateGL();
}

void GLWidget::setTerminals (bool value) {
	_showTerminals = value;
	updateGL();
}

void GLWidget::setWebs (bool value) {
	_showWebs = value;
	updateGL();
}

void GLWidget::setGrid (bool value) {
	_showGrid = value;
	updateGL();
}

void GLWidget::highlightNet (const unsigned int& netIndex, bool update) {

	_glWebList[netIndex].setWidth (3);
	_glWebList[netIndex].setColor (_webColor - Vec3f (0.2f, 0.2f, 0.2f));
/*	const Net& net = _database.netList[netIndex];
	for (unsigned int i=0; i<net.terminals.size(); ++i) {
		_glTerminalList[net.terminals[i]].build (_database.terminalList[net.terminals[i]].coord, _pitch, _height, _terminalThickness+0.05);
	}*/

	if (update) {
		_highlightList.insert (netIndex);
		emit selectedChanged();
		updateGL();
	}
}

void GLWidget::unhighlightNet (const unsigned int& netIndex, bool update) {
	_glWebList[netIndex].setWidth (1);
	_glWebList[netIndex].setColor (_webColor);
/*	const Net& net = _database.netList[netIndex];
	for (unsigned int i=0; i<net.terminals.size(); ++i) {
		_glTerminalList[net.terminals[i]].build (_database.terminalList[net.terminals[i]].coord, _pitch, _height, _terminalThickness);
	}*/

	if (update) {
		_highlightList.erase (netIndex);
		emit selectedChanged();
		updateGL();
	}
}


void GLWidget::unhighlightAll () {
	for (std::set<unsigned int>::iterator it = _highlightList.begin(); it != _highlightList.end(); ++it) {
		unhighlightNet (*it, false);
	}
	_highlightList.clear();
	emit selectedChanged();
	updateGL();
}

void GLWidget::highlightUnrouted () {
	for (unsigned int i=0; i<_database.unroutedList.size(); ++i) {
		highlightNet (_database.unroutedList[i], false);
		_highlightList.insert (_database.unroutedList[i]);
	}
	emit selectedChanged();
	updateGL();
}

void GLWidget::toggleHighlightNet (const unsigned int& index, bool update) {
	std::set<unsigned int>::iterator it = _highlightList.find (index);
	if (it != _highlightList.end()) { // found!
		unhighlightNet(index, update);
	}
	else {
		if (index < _database.netList.size()) {
			highlightNet(index, update);
		}
	}
}


void GLWidget::search (const std::string& s) {
	// First, check if its a terminal or a net
	// If it has 3 int-convertable, its a terminal
	std::istringstream input (s);
	input.exceptions (std::istringstream::failbit);
	bool terminal = false;
	int x, y, z;
	MatrixCoord3D coord;
	try {
		input >> x;
		input >> y;
		input >> z;
		terminal = true;
		coord = MatrixCoord3D (x, y, z);
	}
	catch (std::exception e) {
	}

	if (!terminal) {
		std::map<std::string, unsigned int>::const_iterator result = _database.namesMap.find (s); // not using operator[] so that it doesnt add stuff
		if (result != _database.namesMap.end()) {
			const unsigned int& index = result->second;
			if (_highlightList.find (index) == _highlightList.end()) {
				highlightNet (index);
			}
			else {
				unhighlightNet (index);
			}
		}
		else {
			unhighlightAll();
		}
	}
	else {
		_camera.position[0] = _pitch*static_cast<float> (coord[0]);
		_camera.position[1] = _height*static_cast<float> (coord[2]); // swapped
		_camera.position[2] = -_pitch*static_cast<float> (coord[1]);
		std::cout << _camera.position << std::endl;
		updateGL();	
	}
}





