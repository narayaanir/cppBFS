/*
 * clock.cpp
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
#include "../bfssolver.h"

using namespace std;

class Clock1 : public solver<int> {
public:
	Clock1 (int hrs, int a, int final_hrs) : solver(a), hrs(hrs), final_hrs(final_hrs) {}

	vector<int> get_next_cfg(int a) {
		vector<int> vector_config;
		if (a<0) {
			vector_config.push_back(hrs+a);
			vector_config.push_back(hrs+a+1);
		} else if (a==0) {
			vector_config.push_back(hrs-1);
			vector_config.push_back(1);
		}
		else {
			vector_config.push_back((a-1)%hrs);
			vector_config.push_back((a+1)%hrs);
		}
		return vector_config;
	}

	void print_cfg(int x) {
		cout<<x<<"\t";
	}

	bool goal_cfg(int x) {
		return x==final_hrs;
	}

private:
	int hrs, final_hrs;
};


int main (int argc, char * args[]) {
	if (argc!=4) {
		cout<<"Usage: ./file <clock hrs> <current time> <required time>"<<endl;
		exit(1);
	}
	int hrs=atoi(args[1]);
	int curr=atoi(args[2]);
	int req=atoi(args[3]);
	Clock1 c(hrs, curr, req);
	c.process();
//	c.display();
	return 0;
}
