/*
 * jump.cpp
 * This file is part of cppBFS
 *
 * Copyright (C) 2014 - ani
 *
 * cppBFS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * cppBFS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cppBFS. If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "../bfssolver.h"

using namespace std;

class jump : public solver<vector<vector<char> > > {
public:
	jump (vector< vector<char> > a, bool l, bool t, bool ld, bool rd) : solver(a), leftRight(l), topDown(t), leftDiag(ld),
																				rightDiag(rd), columnSize(a.at(0).size()) {}

	vector<vector< vector<char> > > get_next_cfg(vector< vector<char> > a) {
		vector<vector< vector<char> > > vector_config;
		for (unsigned int i=0; i<a.size(); ++i) {
			for(unsigned int j=0; j<a.at(i).size(); ++j) {
				if (a.at(i).at(j)=='+') {
					if (j+2<columnSize || j>=2) {
						if (leftRight) {
							if (a[i][j+1]=='+' && a[i][j+2]=='.') {
								vector< vector<char> > x=a;
								x[i][j]='.';
								x[i][j+1]='.';
								x[i][j+2]='+';
//								print_cfg(x);
								vector_config.push_back(x);
							}
							if (a[i][j-1]=='+' && a[i][j-2]=='.') {
								vector< vector<char> > x=a;
								x[i][j]='.';
								x[i][j-1]='.';
								x[i][j-2]='+';
								print_cfg(x);
								vector_config.push_back(x);
							}
						}
						if (leftDiag) {
							if (a[i-1][j-1]=='+' && a[i-2][j-2]=='.') {
								vector< vector<char> > x=a;
								x[i][j]='.';
								x[i-1][j-1]='.';
								x[i-2][j-2]='+';
								vector_config.push_back(x);
							}
							if (a[i+1][j+1]=='+' && a[i+2][j+2]=='.') {
								vector< vector<char> > x=a;
								x[i][j]='.';
								x[i+1][j+1]='.';
								x[i+2][j-2]='+';
								vector_config.push_back(x);
							}
						}
						if (rightDiag) {
							if (a[i-1][j+1]=='+' && a[i-2][j+2]=='.') {
								vector< vector<char> > x=a;
								x[i][j]='.';
								x[i-1][j+1]='.';
								x[i-2][j+2]='+';
								vector_config.push_back(x);
							}
							if (a[i+1][j-1]=='+' && a[i+2][j-2]=='.') {
								vector< vector<char> > x=a;
								x[i][j]='.';
								x[i+1][j-1]='.';
								x[i+2][j-2]='+';
								vector_config.push_back(x);
							}
						}
					}
					if (topDown && (i+2<a.size() || i>=2)) {
						if (a[i+1][j]=='+' && a[i+2][j]=='.') {
							vector< vector<char> > x=a;
							x[i][j]='.';
							x[i+1][j]='.';
							x[i+2][j]='+';
							vector_config.push_back(x);
						}
						if (a[i-1][j]=='+' && a[i-2][j]=='.') {
							vector< vector<char> > x=a;
							x[i][j]='.';
							x[i-1][j]='.';
							x[i-2][j]='+';
							vector_config.push_back(x);
						}
					}
				}
			}
		}
		return vector_config;
	}

	bool goal_cfg(vector< vector<char> > x) {
		for (unsigned int i=0; i<x.size(); ++i) {
			for(unsigned int j=0; j<x.at(i).size(); ++j) {
				if (x.at(i).at(j)=='+') {
					if (leftRight && (j+2<columnSize || j>=2) && ((x[i][j+1]=='+' && x[i][j+2]=='.') || (x[i][j-1]=='+' && x[i][j-2]=='.')))
						return false;
					if (topDown && (i+2<x.size() || i>=2) && ((x[i+1][j]=='+' && x[i+2][j]=='.') || (x[i-1][j]=='+' && x[i-2][j]=='.')))
						return false;
					if (leftDiag && (j+2<columnSize || j>=2) && ((x[i-1][j-1]=='+' && x[i-2][j-2]=='.') || (x[i+1][j+1]=='+' && x[i+2][j+2]=='.')))
						return false;
					if (rightDiag && (j+2<columnSize || j>=2) && ((x[i-1][j+1]=='+' && x[i-2][j+2]=='.') || (x[i+1][j-1]=='+' && x[i+2][j-2]=='.')))
						return false;
				}
			}
		}
		return true;
	}

	void print_cfg(vector< vector<char> > x) {
		for (unsigned int i=0; i<x.size(); ++i) {
			for(unsigned int j=0; j<x.at(i).size(); ++j)
				cout<<x.at(i).at(j);
			cout<<endl;
		}
	}

private:
	bool leftRight, topDown, leftDiag, rightDiag;
	unsigned int columnSize;
};



int main (int argc, char * args[]) {
	if (argc!=3) {
		cerr<<"2 args only."<<endl;
	} else {

		ifstream ifs;
//		ostream *osp;
//		ofstream ofs;

		vector<char> vecstr;

		if (args[1][0]=='-' && args[1][1]=='\0') {
			istream *isp;
			isp=&cin;
		} else {
			istream *isp;
			ifs.open(args[1]);
			isp = &ifs;
			if (ifs.is_open()) {
				char str;
				unsigned int colSize, rowSize;
				bool leftRight=false, topDown=false, rightDiag=false, leftDiag=false;
				while (ifs>>str) {
//					cout<<str;
					vecstr.push_back(str);
				}
				colSize=vecstr.front()-'0';
				vecstr.erase(vecstr.begin());
				rowSize=vecstr.front()-'0';
				vecstr.erase(vecstr.begin());

				for (vector<char>::iterator t=vecstr.begin(); t!=vecstr.begin()+colSize; ++t) {
					if (*t=='-') {
						leftRight=true;
					}
					if (*t=='|') {
						topDown=true;
					}
					if (*t=='/') {
						rightDiag=true;
					}
					if (*t=='\\') {
						leftDiag=true;
					}
				}
				vecstr.erase(vecstr.begin(), vecstr.end()-colSize*rowSize);


				vector< vector<char> > vecConfig;
				vector<char> tmpVec;


				for (vector<char>::iterator t=vecstr.begin(); t!=vecstr.end(); ++t) {
					tmpVec.push_back(*t);
					if (tmpVec.size()==colSize) {
						vecConfig.push_back(tmpVec);
						tmpVec.clear();
					}
				}




/*				for (unsigned int i=0; i<vecConfig.size(); ++i) {
					for(unsigned int j=0; j<vecConfig.at(i).size(); ++j)
						cout<<vecConfig.at(i).at(j);
					cout<<endl;
				}*/
//				cout<<vecConfig.size()<<endl;


/*				for (vector<char>::iterator t=vecstr.begin(); t!=vecstr.end(); ++t)
					cout<<*t;*/

				jump j(vecConfig, leftRight, topDown, leftDiag, rightDiag);
				j.print_cfg(vecConfig);
//				j.process();
//				cout<<endl<<j.goal_cfg(vecConfig);
				cout<<colSize<<"\t"<<rowSize<<"\t"<<leftRight<<"\t"<<topDown<<"\t"<<leftDiag<<"\t"<<rightDiag<<"\t\n";
			} else {
				cout<<"Unable to open file.\n";
			}
			ifs.close();
		}
/*		istream &is=*isp;

		if (args[2][0]=='-' && args[2][1]=='\0') {
			osp = &cout;
		} else {
			ofs.open(args[2]);
			osp=&ofs;
		}*/
	}
	return 0;
}
