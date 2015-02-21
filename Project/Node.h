#pragma once
#include <iostream>
class CNode
{
	public:
		CNode();
		~CNode();
		CNode *parent;	// Link To Previous Node On Best Path
		// x,y Position Of Grid
		int x,y;	
		// Cost Elements : g = Cost From Start To Current Node
		//h = Cost From Current To Goal Node
		//f = Cost From Start To Goal (g+h) Node
		float f,g,h;	
};

