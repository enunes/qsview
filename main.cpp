
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <QApplication>

#include "MyWindow.h"
#include "Node.h"
#include "Net.h"
#include "Segment.h"
#include "utils.h"
#include "Database.h"
#include "Vec3f.h"

void help () {
	std::cerr << std::endl;
	std::cerr << "Erico Nunes [nunes dot erico at gmail dot com] @ 2010" << std::endl;
	std::cerr << "Qsview - Simple 3D symbolic routing viewer" << std::endl;
	std::cerr << "QT version" << std::endl;
	std::cerr << std::endl;
	std::cerr << "qsview [filename]" << std::endl;
}


Database _database;

bool parseSru (const std::string& filename) {
	std::ifstream file (filename.c_str());
	if (!file) return false;
	file.exceptions (std::ifstream::eofbit);

	std::string readBuffer;
	int trash;
	while (true) {
		try {
			file >> readBuffer;
			file >> trash >> trash >> trash; // I don't really use the coordinate values yet;
			file >> trash >> trash >> trash;
			file >> trash >> trash >> trash;
		}
		catch (std::exception e) {
			break;
		}
		_database.unroutedList.push_back (_database.namesMap[readBuffer]);
	/*	unsigned int t = _database.namesMap[readBuffer];
		std::cout << "name = " << readBuffer << std::endl;
		std::cout << "index = " << t << std::endl;
		std::cout << "backtest = " << _database.netNames[t] << std::endl;*/
	}
/*	for (unsigned int i=0; i<_database.unroutedList.size(); ++i) {
		std::cout << "unrouted = " << _database.netNames[_database.unroutedList[i]] << std::endl;
	}*/
	file.close();
	return true;
}

bool parseSro (const std::string& filename, MatrixCoord3D& max) {
	MatrixCoord3D xyz;
	MatrixCoord3D end;
	max = MatrixCoord3D (0, 0, 0);
	std::ifstream file (filename.c_str());
	unsigned int x, y, z, a, m;
	if (!file) return false;


	file.exceptions (std::ifstream::eofbit);

	while (true) {
		std::string name;
		std::string readBuffer;

		try{
			file >> readBuffer;
		}
		catch (std::exception e){
			break;
		}
		// readBuffer has the name of the net


		name = readBuffer;

		file >> readBuffer;
		while (readBuffer != ".") {
			try{
				x = std::atoi (readBuffer.c_str());
				file >> y;
				file >> z;
				file >> a;
				file >> m;
			}
			catch (std::exception e){
				break;
			}
			xyz = MatrixCoord3D (x, y, z);
			end = xyz;
			end[a] += m;

//			std::cout << xyz << std::endl;

			for (unsigned int i=0; i<3; ++i) {
				if (end[i] > max[i]) {
					max[i] = end[i];
				}
			}
			_database.segmentList.push_back (Segment(xyz, a, m, _database.namesMap[name]));

			file >> readBuffer;
		}
	}
	file.close();

//	_database.matrix = Matrix3D<Node> (max + MatrixCoord3D(1, 1, 1));


	//	std::cout << matrix << std::endl;

	return true;
}

bool parseSri (const std::string& filename, MatrixCoord3D& max) {
	std::string readBuffer;
	max = MatrixCoord3D (0, 0, 0);
	unsigned int netTerminals = 0;

	std::ifstream file (filename.c_str());
	if (!file) {
		return false;
	}

	file >> readBuffer;
	while ((readBuffer != "end") && (!file.eof())) {
		if (readBuffer == "grid") {
			MatrixCoord3D readMatrixSize;
			file >> readMatrixSize;
		}
		else if (readBuffer == "ref") {
			MatrixCoord3D readCoord;
			file >> readCoord;
		}
		else if (readBuffer == "netlist") {
			Net tNet;
			unsigned int readX, readY, readZ;
			MatrixCoord3D readCoord;

			file >> readBuffer;
			while (readBuffer != "end") { // This will make through all the nets
				// If it was not end, readBuffer contains the label of the net

				_database.netNames.push_back (readBuffer);
				_database.netList.push_back (Net());
				netTerminals = 0;

				file >> readBuffer;
				while (readBuffer != ";") { // This will handle each net separately
					// If it didn't read ";", it read the x coord of a terminal

					readX = std::atoi(readBuffer.c_str());
					file >> readY;
					file >> readZ;

					readCoord.set (readX, readY, readZ);

					unsigned int i;
					bool skip = false;
					for (i=0; i<_database.terminalList.size(); ++i) {
						if (_database.terminalList[i].coord == readCoord) {
							std::cerr << "Double definition of terminal in different nets!" << std::endl;
							std::cerr << "Terminal: " << _database.terminalList[i] << std::endl;
							std::cerr << "Ignoring terminal on net " << _database.netNames.back()  << std::endl;
							skip = true;
							break;
						}
					}
					if ((!skip) && (i == _database.terminalList.size())) {
						_database.netList.back().terminals.push_back (_database.terminalList.size());
						_database.terminalList.push_back (Terminal(readCoord, _database.netList.size()-1));

						std::stringstream tName;
						tName << _database.netNames.back() << ":" << netTerminals;
						_database.terminalLabels.push_back (tName.str());

						for (unsigned int i=0; i<3; ++i) {
							if (readCoord[i] > max[i]) {
								max[i] = readCoord[i];
							}
						}
						++netTerminals;
					}

					file >> readBuffer;
				}
				file >> readBuffer;
			}
			//			netConflicts = std::vector< std::set<unsigned int> > (_numberOfNets); // Allocate it
		}
		else {
			std::cerr << "Parse: unexpected '" << readBuffer << "'" << std::endl;
		}
		file >> readBuffer;
	}
	file.close();


	return true;
}

/*void allocateMatrix (const MatrixCoord3D& max) {
	_database.matrix = Matrix3D<Node> (max + MatrixCoord3D(1, 1, 1));
}*/

/*void loadTerminals () {
	for (unsigned int i=0; i<_database.terminalList.size(); ++i) {
		_database.matrix[_database.terminalList[i].coord].t = i;
	}
}*/

/*void loadSegments () {
	for (unsigned int i=0; i<_database.segmentList.size(); ++i) {
		Segment& segment = _database.segmentList[i];
		//		std::cout << "segment = " << segment << std::endl;
		//		segment.build (0.5f, 0.5f, 0.05f);
		//		if (segment.axis == 2) segment.color = _viaColor;
		//		else segment.color = _colors[segment.start[2] % 3];
		for (MatrixCoord3D m = segment.start; m[segment.axis] <= segment.end[segment.axis]; ++m[segment.axis]) {
			_database.matrix[m].s.push_back(i);
		}
	}
}*/

MatrixCoord3D maxMerge (const MatrixCoord3D& c1, const MatrixCoord3D& c2) {
	MatrixCoord3D r;
	r[0] = (c1[0]>c2[0]) ? c1[0] : c2[0];
	r[1] = (c1[1]>c2[1]) ? c1[1] : c2[1];
	r[2] = (c1[2]>c2[2]) ? c1[2] : c2[2];
	return r;
}

void buildNamesMap () {
	for (unsigned int i=0; i<_database.netNames.size(); ++i) {
		_database.namesMap[_database.netNames[i]] = i;
	}
}

int main (int argc, char** argv) {
	if (argc < 2) {
		help();
		std::exit(1);
	}

	std::string argv1 (argv[1]);

	std::string fileSro = argv1 + std::string (".sro");
	std::string fileSri = argv1 + std::string (".sri");
	std::string fileSru = argv1 + std::string (".sru");

	bool parsedSro;
	bool parsedSri;
	bool parsedSru;

	MatrixCoord3D maxSro;
	MatrixCoord3D maxSri;

	parsedSri = parseSri(fileSri, maxSri);
	if (!parsedSri) {
		std::cerr << "Fail on parsing sri " << fileSri << std::endl;
	}
	else {
		std::cerr << "Success parsing sri " << fileSri << std::endl;
	}

	if (parsedSri) {
		buildNamesMap();
	}

	parsedSro = parseSro (fileSro, maxSro);
	if (!parsedSro) {
		std::cerr << "Fail on parsing sro " << fileSro << std::endl;
		parsedSro = false;
	}
	else {
		std::cerr << "Success parsing sro " << fileSro << std::endl;
		parsedSro = true;
	}

	if ((!parsedSro) && (!parsedSri)) {
		help();
		std::cerr << "Unable to load any " << argv1 << " file." << std::endl;
		std::exit(1);
	}

	MatrixCoord3D max = maxMerge (maxSri, maxSro);
//	allocateMatrix (max);
	_database.matrixSize = max + MatrixCoord3D (1, 1, 1);

//	if (parsedSro) loadSegments();
//	if (parsedSri) loadTerminals();

	parsedSru = parseSru(fileSru);
	if (!parsedSru) {
		std::cerr << "Fail on parsing sru " << fileSru << std::endl;
	}
	else {
		std::cerr << "Success parsing sru " << fileSru << std::endl;
	}



//	std::cout << _database.netNames << std::endl;




	// if parsed both, generate database

	QApplication app (argc, argv);

	MyWindow window (_database);
	window.show();
	std::string title (std::string(argv[1])+" - qsview[*]");
	window.setWindowTitle (title.c_str());
	return app.exec();
}
