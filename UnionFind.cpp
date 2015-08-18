#include "UnionFind.h"

	UnionFind::UnionFind(int n) : ufSize(n), numOfGroups(0) {
		if (n < 0){
			throw InvalidInput();
		}
		elements = new int[n];
		for (int i = 0; i < n; i++){
			elements[i] = -1;		//not initiolized
		}
		parents = new int[n];
		sizes = new int[n];
	}

	UnionFind::~UnionFind(){
		delete[] elements;
		delete[] parents;
		delete[] sizes;
	}
	//create new singleton == root
	void UnionFind::MakeSet(int element){
		if (isExist(element)) {
			throw ElementAlreadyExist();
		}
		if (element > ufSize){
			throw InvalidInput();
		}
		elements[element] = element;
		parents[element] = element;
		sizes[element] = 1;
		numOfGroups++;
	}
	//return the "head group" == root of tree
	int UnionFind::Find(const int element){
		if (!isExist(element)){
			throw ElementDoesNotExist();
		}
		int root = parents[element];
		int curr = element;
		while (root != curr){
			root = parents[root];
			curr = parents[curr];
		}
		curr = element;
		while (curr != root){
			parents[curr] = root;
			curr = parents[curr];
		}
		return root;
	}
	//union between two "head group"
	void UnionFind::Union(const int element1, const int element2){
		int root1 = Find(element1);
		int root2 = Find(element2);
		if (root1 == root2){
			return;
		}
		if (sizes[root1] >= sizes[root2]){
			parents[root2] = root1;
			sizes[root2] += sizes[root1];
			numOfGroups--;
			return;
		}
		parents[root1] = root2;
		sizes[root1] += sizes[root2];
		numOfGroups--;
		return;
	}

	//Additional functions:
	//swapRoot(currRoot, newRoot):
	//Params: currRoot - current root in the group
	//		  newRoot - the new candidate root to swap with.
	//summary: swap between 2 vertex in the group tree proactively from the user.
	void UnionFind::swapRoot(int currRoot, int newRoot){		//asume get legal values in the range
		if (currRoot == newRoot){
			return;
		}
		int v1 = parents[newRoot];
		int v2 = newRoot;
		parents[newRoot] = newRoot;
		sizes[newRoot] = sizes[currRoot];
		do {
			int v3 = parents[v1];
			parents[v1] = v2;
			v2 = v1;
			v1 = v3;
		} while (v2 != currRoot);

	}

