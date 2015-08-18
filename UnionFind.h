//Assuming about T: c'tor , d'tor , copy c'tor
//Do we really need generic UnionFind?

#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <assert.h>
#include <exception>

class UnionFind {
	int* elements;
	int* parents;
	int* sizes;
	int ufSize;
	int numOfGroups;

	//check if element already in one of the trees
	bool isExist(const int element) const{
		if (element >= ufSize || element < 0){
			return false;
		}
		return elements[element] == element;
	}

public:

	//Exceptions:
	class InvalidInput : public std::exception {};
	class ElementAlreadyExist : public std::exception {};
	class ElementDoesNotExist : public std::exception {};

	UnionFind(int n);

	~UnionFind();
	//create new singleton == root
	void MakeSet(int element);
	//return the "head group" == root of tree
	int Find(const int element);
	//union between two "head group"
	void Union(const int element1, const int element2);

	//Additional functions:
	//swapRoot(currRoot, newRoot):
	//Params: currRoot - current root in the group
	//		  newRoot - the new candidate root to swap with.
	//summary: swap between 2 vertex in the group tree proactively from the user.
	void swapRoot(int currRoot, int newRoot);		//asume get legal values in the range
};


#endif


