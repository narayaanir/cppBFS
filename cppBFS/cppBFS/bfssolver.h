/*
 * bfssolver.h
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



#ifndef BFSSOLVER_H_
#define BFSSOLVER_H_

#include <deque>
#include <map>
#include <vector>
#include <iostream>
#include <utility>

template <class T>
class solver {
public:
	solver (T init) : initial_cfg(init) {
		queue_cfg.push_back(initial_cfg);
		map_cfg.insert(std::make_pair(initial_cfg, initial_cfg));
	}

	virtual std::vector<T> get_next_cfg(T)=0;
	virtual void print_cfg(T)=0;
	virtual bool goal_cfg(T)=0;

	void process() {
		while (!queue_cfg.empty() && !goal_cfg(queue_cfg.front())) {
			T parent_cfg=queue_cfg.front();
			queue_cfg.pop_front();
			std::vector<T> vec_cfg=get_next_cfg(parent_cfg);
			while (!vec_cfg.empty()) {
				T child_cfg=vec_cfg.back();
//				typedef typename std::map<T, T>::iterator it_map;
				if (map_cfg.count(child_cfg)==0) {	//&& it->second!=final_cfg -- placed for my reference
					queue_cfg.push_back(child_cfg);
					map_cfg.insert(std::make_pair(child_cfg, parent_cfg));
				}
				vec_cfg.pop_back();
			}
		}
		if (!queue_cfg.empty() && goal_cfg(queue_cfg.front())) {
			print_target=queue_cfg.front();
			vec_print.push_back(print_target);
		}
		else {
			std::cout<<"Unable to find solution.\n";
			return;
		}
		typedef typename std::map<T, T>::iterator it_map;
		it_map it_begin=map_cfg.begin();
		it_map it_end=map_cfg.end();
		while (it_begin!=it_end && print_target!=initial_cfg) {
			print_target=map_cfg.find(print_target)->second;
			vec_print.push_back(print_target);
			--it_end;
		}
		for (typename std::vector<T>::reverse_iterator t=vec_print.rbegin(); t!=vec_print.rend(); t++)
			print_cfg(*t);
		std::cout<<"\n";
	}

	virtual ~solver(){}

private:
	T initial_cfg, print_target;
	std::map<T, T> map_cfg;
	std::deque<T> queue_cfg;
	std::vector<T> vec_print;
};



#endif /* BFSSOLVER_H_ */
