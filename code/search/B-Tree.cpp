#include<cstdlib>
#include<iostream>
#include<stdio.h>
using namespace std;

#define m 3

struct Record{
	//empty.
};

typedef int KeyType;

typedef struct BMTNode{
	int keynum;
	BMTNode * parent;

	KeyType   key[m+1];
	BMTNode * ptr[m+1];

	BMTNode(): keynum(0), parent(NULL) {
		for(int i = 0; i <= m; ++i) {
			key[i] = 0;
			ptr[i] = NULL;
		}//endfor
	}//endctor
}*BMT;

bool BMTSearchKey(BMT & T, KeyType K, BMTNode*& recNode, int &recIdx);
bool BMTInsertKey(BMT & T, KeyType K);
bool BMTDeleteKey(BMT & T, KeyType K);
void BMTDestroy(BMT & T);
void BMTWalkThrough(BMT & T);


int BMTSearch(BMT & T, KeyType K)
{
	int i = 0;
	for(int j = 1; j <= T->keynum; ++j)
		if(T->key[j] <= K) i = j;
	return i;
}

bool BMTSearchKey(BMT & T, KeyType K, BMTNode*& recNode, int &recIdx)
{
	recIdx = 0;
	recNode = NULL;

	BMTNode * curNode = T;
	while(curNode) {
		// search
		recIdx = BMTSearch(curNode, K);

		if (recIdx > 0 && curNode->key[recIdx] == K) {
			recNode = curNode;
			return true; //found
		} else {
			recNode = curNode;         // q: the parent of p
			curNode = curNode->ptr[recIdx]; // p->key[i]: the last key lt K
		} //endif
	} // endw
	return false;
}

void BMTInsert(BMT & T, int i, KeyType K, BMTNode* rhs)
{
	// T: current Tree Node;
	// i: points to the last elem that's le K;
	// K: the key to insert.
	// insert K to T->key[i+1] and rhs to T->ptr[i+1],

	// move backward
	for(int j = T->keynum; j >= i+1; --j) {
		T->key[j+1] = T->key[j];
		T->ptr[j+1] = T->ptr[j];
	}//endfor j

	T->key[i+1] = K;
	T->ptr[i+1] = rhs;
	++T->keynum;
}

bool BMTSplit(BMT & T, int s, BMT& rhs, KeyType& midK)
{
	// split T at s, with the right hand side stored in rhs
	// return key[s] by K.
	rhs = new BMTNode;
	if(!rhs) return false;
	rhs->parent = T->parent;

	// take out the mid node.
	midK = T->key[s];
	T->key[s] = 0;

	// T->key[s+1..m] T->ptr[s..m] T->recptr[s+1..m] => *ap
	rhs->ptr[0] = T->ptr[s];
	if ( rhs->ptr[0] )
		rhs->ptr[0]->parent = rhs;
	T->ptr[s] = NULL;
	for (int i = 1; i <= m-s; ++i) {
		// move key
		rhs->key[i] = T->key[s+i]; T->key[s+i] = 0;
		// move ptr
		rhs->ptr[i] = T->ptr[s+i]; T->ptr[s+i] = NULL;
		if ( rhs->ptr[i] )
			rhs->ptr[i]->parent = rhs;
	} //end for

	rhs->keynum = m - s;
	 T->keynum = s - 1;

	return true;
}

bool BMTNewRoot(BMT & T, BMT & lhs, KeyType midK, BMT & rhs)
{
	BMT temp = new BMTNode;
	if(!temp) return false;
	//temp->parent = NULL

	temp->keynum = 1;
	temp->key[1] = midK;

	temp->ptr[0] = lhs;
	if(lhs) lhs->parent = temp;
	temp->ptr[1] = rhs;
	if(rhs) rhs->parent = temp;

	T = temp;
	return true;
}

bool BMTInsertKey(BMT & T, KeyType K)
{
	BMTNode * curNode = NULL;
	int preIdx = 0;

	if (BMTSearchKey(T, K, curNode, preIdx))
		// check repetition and find pos
		return false;
	else {
		// key not found.
		// q = node to insert key; i: pre pos to insert key
		KeyType curK = K;
		BMTNode * rhs = NULL;
		bool finished = false;

		while( curNode && !finished ) {
			// curK: current key to insert.
			//  rhs: current right hand side.
			BMTInsert(curNode, preIdx, curK, rhs);

			// check violation.
			if (curNode->keynum < m)
				finished = true;
			    // exit loop
			else {
				// violated, maintain structure.
				int s = (m + 1)/2;    // ceil(m/2)
				if(!BMTSplit(curNode, s, rhs, curK))
					return false;

				if(curNode->parent == NULL)
					// need to create new node.
					break;
				    //exit loop
				else {
					curNode = curNode->parent;
					preIdx = BMTSearch(curNode, curK);
				}//endelse
			}//endif
		}//endw

		if( !finished && !BMTNewRoot(T, curNode, curK, rhs) ) {
			cerr << "failed to create new root" << endl;
			exit(EXIT_FAILURE);
		}//endif
		return true;
	} //endif not found
	return true;
}

void BMTRotateLeft(BMT parent, int idx, BMT cur, BMT rsilb)
{
	// from parent and rsilb to cur.
	cur->key[cur->keynum + 1] = parent->key[idx + 1];
	cur->ptr[cur->keynum + 1] = rsilb->ptr[0];
	if (cur->ptr[cur->keynum + 1])
		cur->ptr[cur->keynum + 1]->parent = cur;
	rsilb->ptr[0] = NULL;
	++cur->keynum;

	// from rsilb to parent.
	parent->key[idx + 1] = rsilb->key[1];
	rsilb->key[idx] = 0;

	// restructure rsilb.
	for (int i = 0; i <= rsilb->keynum; ++i) {
		rsilb->key[i] = rsilb->key[i + 1];
		rsilb->ptr[i] = rsilb->ptr[i + 1];
	}//end for
	rsilb->key[0] = 0;
	--rsilb->keynum;
}

void BMTRotateRight(BMT parent, int idx, BMT cur, BMT lsilb)
{
	// from parent and lsilb to cur.
	for (int i = cur->keynum; i >= 0; --i) {
		cur->key[i + 1] = cur->key[i];
		cur->ptr[i + 1] = cur->ptr[i];
	}//end for.
	cur->key[1] = parent->key[idx];
	cur->ptr[0] = lsilb->ptr[lsilb->keynum];
	if (cur->ptr[0])
		cur->ptr[0]->parent = cur;
	lsilb->ptr[lsilb->keynum] = NULL;
	++cur->keynum;

	// from lsilb to parent.
	parent->key[idx] = lsilb->key[lsilb->keynum];
	lsilb->key[lsilb->keynum] = 0;

	--lsilb->keynum;
}

void BMTMerge(BMT parent, int idx, BMT lsilb, BMT cur) {
	// combine lsilb and cur to lsilb
	for (int i = 0; i <= cur->keynum; ++i) {
		lsilb->key[lsilb->keynum + 1 + i] = cur->key[i];
		lsilb->ptr[lsilb->keynum + 1 + i] = cur->ptr[i];
		if (lsilb->ptr[lsilb->keynum + 1 + i])
			lsilb->ptr[lsilb->keynum + 1 + i] = lsilb;
	}//end for.
	lsilb->key[lsilb->keynum + 1] = parent->key[idx];
	lsilb->keynum = lsilb->keynum + cur->keynum + 1;

	delete cur;
	for (i = idx; i <= parent->keynum; ++i) {
		parent->key[i] = parent->key[i + 1];
		parent->ptr[i] = parent->ptr[i + 1];
	}//end for.
	--parent->keynum;
}

void BMTDeleteBalance(BMT & T, BMT curNode)
{
	int lb = (int)m / 2;

	BMT parent = curNode->parent;
	while (parent && curNode->keynum < lb) {
		//need to balance.
		int idx = 0;
		for (int i = 0; i <= parent->keynum; ++i) {
			if (parent->ptr[i] == curNode) {
				idx = i; break;
			}
		}//end for

		// locate lsilb and rsilb
		BMT lsilb = NULL, rsilb = NULL;
		if (idx - 1 >= 0)
			lsilb = parent->ptr[idx - 1];
		if (idx + 1 <= parent->keynum)
			rsilb = parent->ptr[idx + 1];

		// adjust
		if (rsilb && rsilb->keynum > lb) {
			BMTRotateLeft(parent, idx, curNode, rsilb);
			break;
		}
		else if (lsilb && lsilb->keynum > lb) {
			BMTRotateRight(parent, idx, curNode, lsilb);
			break;
		}
		else {
			if (lsilb)
				BMTMerge(parent, idx, lsilb, curNode);
			else
				BMTMerge(parent, idx + 1, curNode, rsilb);
			// potentially causing deficiency of parent.
			curNode = parent;
			parent = curNode->parent;
		}//end else
	} //endw

	if (curNode->keynum == 0) {
		// root is empty.
		T = curNode->ptr[0];
		delete curNode;
	}//endif
}

void BMTDelete(BMT & T, BMT curNode, int curIdx)
{
	// after deleted curNode points to one leaf.
	if (curIdx < 0 || curIdx > curNode->keynum) return;

	while (true) 
	{
		if (curNode->ptr[curIdx - 1] && curNode->ptr[curIdx])
		{	// non leaf
			if (curNode->ptr[curIdx - 1]->keynum > curNode->ptr[curIdx]->keynum)
			{
				BMT lhs = curNode->ptr[curIdx - 1];
				// take the last key from lhs.
				curNode->key[curIdx] = lhs->key[lhs->keynum];
				// delete the last key of lhs.
				curNode = lhs; curIdx = lhs->keynum;
			} else {
				BMT rhs = curNode->ptr[curIdx];
				// take the first key from rhs
				curNode->key[curIdx] = rhs->key[1];
				// delete the first key of rhs
				curNode = rhs; curIdx = 1;
			}//endif
		}//endif non leaf
		else if (!curNode->ptr[curIdx - 1] && !curNode->ptr[curIdx])
		{	// is leaf
			for (int i = curIdx; i <= curNode->keynum; ++i) {
				curNode->key[i] = curNode->key[i + 1];
				// all ptr are NULL , no need to move.
			}//end for.
			--curNode->keynum;

			BMTDeleteBalance(T, curNode);
			break;
		} else { //debug
			cerr << "Error" << endl;
		}
	}//endw
}

bool BMTDeleteKey(BMT & T, KeyType K)
{
	BMTNode* curNode = NULL;
	int	curIdx = 0;

	if (BMTSearchKey(T, K, curNode, curIdx)) {
		// curNode: node that K is in. curIdx: index of K in curNode.
		BMTDelete(T, curNode, curIdx);
		return true;
	} //endif
	else return false;
}

void BMTDestroy(BMT & T)
{
	if(!T) return;
	for(int i = 0; i <= T->keynum; ++i)
		BMTDestroy(T->ptr[i]);
	delete T;
	T = NULL;
	return;
}

void BMTWalkThrough(BMT & T)
{
	if(!T) return;
	static int depth = 0;
	++depth;

	int index = 0;
	bool running = true;
	while(running) {
		cout << "Cur depth: " << depth << endl;
		cout << "Cur Pos: " << (void*)T << ";  "
			<< "Keynum: " << T->keynum << "; " << endl;
		cout << "Index: " << index << ";  Key: " << T->key[index] << endl;

		int ans = 0;
		do{
			cout << "1.Prev Key; 2.Next Key; 3.Deepen Left; 4.Deepen Right; 5.Backup" << endl;
			cin >> ans;
			if(1 <= ans && ans <= 5)
				break;
		}while(true);

		switch(ans) {
		case 1:
			if(index == 0)
				cout << "Failed." << endl;
			else
				--index;
			break;
		case 2:
			if(index == T->keynum)
				cout << "Failed" << endl;
			else
				++index;
			break;
		case 4:
			if(index > 0 && T->ptr[index])
				BMTWalkThrough(T->ptr[index]);
			else
				cout << "Failed" << endl;
			break;
		case 3:
			if(index > 0 && T->ptr[index-1])
				BMTWalkThrough(T->ptr[index-1]);
			else
				cout << "Failed" << endl;
			break;
		case 5:
			running = false;
			break;
		}//endsw
	}//endw

	--depth;
}



//BMT: 10 45 24 53 90 3 37 50 61 70 100
int main(void)
{
	BMT T = NULL;

	int n;
	//cout << "Enter the number of keys: "; cout.flush();
	//cin >> n;

	//cout << "keys: "; cout.flush();
	//for(int i = 0; i < n; ++i) {
	//	int key;
	//	cin >> key;
	//	BMTInsertKey(T, key);
	//}//endfor

	BMTInsertKey(T, 45);
	BMTInsertKey(T, 24);
	BMTInsertKey(T, 53);
	BMTInsertKey(T, 90);
	BMTInsertKey(T, 3);
	BMTInsertKey(T, 37);
	BMTInsertKey(T, 50);
	BMTInsertKey(T, 61);
	BMTInsertKey(T, 70);
	BMTInsertKey(T, 100);

	cout << "number of keys to delete: ";
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int key;
		cin >> key;
		BMTDeleteKey(T, key);
	} //end for.

	BMTWalkThrough(T);
	BMTDestroy(T);
	return 0;
}