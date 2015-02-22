#pragma once

#include "Node.h"
// Include Container For Objects
#include <vector>
using namespace std;

const int ROWS2 = 6;	// Declare Number Of Rows & Columns For Map Grid
const int COLS2 = 8;
using namespace std;
// Declare Structure Representing Neighborhood Of A Node
const struct {int x,y;} succ[4] = {{0,-1},{0,1},{1,0},{-1,0}};

class Astar
{
	private:
		//varable
		CNode* goal;							// Goal node
		CNode* start;							// Start node
		
	public:
		// Container For Open List ( nodes[list] To Examine When Searching)
		std::vector <CNode *> openList;	
		// Container For Close List (Nodes Already Examined)
		std::vector <CNode *> closeList;				
		//default constructor
		Astar();
		// Constructor For Initialising Start And Goal x,y Nodes
		Astar(int sx,int sy,int gx,int gy);
		//destructor
		~Astar();

		//function
		void AddOpenList(CNode *n);				// Add Node To Open list
		void AddCloseList(CNode *n);				// Add Node To Close List
		void RemoveOpenList(CNode *n);			// Remove Node From Open List
		void RemoveCloseList(CNode *n);			// Remove Node From Close List
		void ShowList(vector<CNode*>list);		// Show List Either Open Or Close
		CNode* GetBest();						// Get Best Node (Minimum f) In Open List
		CNode* GetSuccessor(CNode *current,int i,int (&grid)[ROWS2][COLS2]);// Get Neighborhood Nodes( Empty Space) Of Current Node Given A Neighborhood Index 
		float Compute_g(CNode* n);				// Calculate 'g' Cost
		float Compute_h(CNode* n);				// Calculate 'h' Cost
		bool InList(vector <CNode*> list, CNode *n); // Check If Node 'n' Is In List
		bool Search(int (&grid)[ROWS2][COLS2]);							// Search For Best Path
		void ShowPath(CNode *walker,int (&grid)[ROWS2][COLS2]);			// Show In Text Mode The Map And Best Path (walker=navigating node)

		//getter
		CNode* Astar::getFromOpenList(CNode* succ); // Get From List Item Same As 'succ' Successor
		CNode* Astar::getFromCloseList(CNode* succ);
};
