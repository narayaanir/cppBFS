/*
 * hanoi.cpp
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


#include <cstdlib>
#include <vector>
#include <iomanip>
#include <exception>
#include "../bfssolver.h"

using namespace std;

class TowOfHanoi : public solver<vector<vector<int> > > {
public:
	TowOfHanoi (int numPegs, int numDisks, vector<vector<int> > a) : solver(a), numPegs(numPegs), numDisks(numDisks) {}

	vector< vector < vector<int> > > get_next_cfg(vector<vector<int> > a) {
		vector< vector< vector<int> > > vector_config;
		for (int i=0; i<numPegs; ++i) {
			for (int j=0; j<numPegs /*&& j!=i*/; ++j) {
				vector<vector<int> > tmp=a;
				if (tmp.at(i).empty())
					continue;
				if ((!tmp.at(j).empty() && tmp.at(i).back()<tmp.at(j).back()) || tmp.at(j).empty()) {
					tmp.at(j).push_back(tmp.at(i).back());
					tmp.at(i).pop_back();
					vector_config.push_back(tmp);
				}
			}
		}
		return vector_config;
	}

	bool goal_cfg(vector<vector<int> > x) {
		vector<vector<int> >  curr(numPegs, vector<int>(0));
		vector<int> tmpVec;
		for (unsigned int i=numDisks; i>=1; --i)
			tmpVec.push_back(i);
		curr.at(numPegs-1)=tmpVec;
		if (curr==x)
			return true;
		return false;
	}

	void print_cfg(vector<vector<int> > x) {
		for (unsigned int i=0; i<x.size(); ++i) {
			cout<<i+1<<"-->";
			for (unsigned int j=0; j<x[i].size(); ++j) {
				cout<<setw(3)<<x[i][j];
			}
			cout<<endl;
		}
		cout<<endl;
	}


private:
	int numPegs, numDisks;
};


int main (int argc, char * args[]) {
	if (argc!=3) {
		cout<<"Usage: ./file <numPegs> <numDisks>"<<endl;
		exit(1);
	}

	int numPegs=atoi(args[1]);
	int numDisks=atoi(args[2]);

	vector<vector<int> >  curr(numPegs, vector<int>(0));

	vector<int> tmpVec;
	for (unsigned int i=numDisks; i>=1; --i)
		tmpVec.push_back(i);

	curr.at(0)=tmpVec;

	TowOfHanoi t(numPegs, numDisks, curr);
	t.process();
	return 0;
}
