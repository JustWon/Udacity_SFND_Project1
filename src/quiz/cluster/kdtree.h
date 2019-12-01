/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"


// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	void insertHelper(Node **p_cur, Node *new_node, int depth)
	{
		if (*p_cur == NULL)
			*p_cur = new_node;
		else if (new_node->point[depth%2] < (*p_cur)->point[depth%2])
			insertHelper(&(*p_cur)->left, new_node, depth++);
		else
			insertHelper(&(*p_cur)->right, new_node, depth++);
	}

	void insert(std::vector<float> point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
		Node *new_node = new Node(point, id);

		insertHelper(&root, new_node, 0);
	}

	double distance(std::vector<float> a, std::vector<float> b)
	{
		return sqrt((a[0] - b[0])*(a[0] - b[0]) + (a[1] - b[1])*(a[1] - b[1]));
	}

	void searchHelper(Node *p_cur, std::vector<float> target, float distanceTol, int depth, std::vector<int>& ids) 
	{
		if (p_cur != NULL) 
		{
			if (p_cur->point[0] >=(target[0]-distanceTol) && p_cur->point[0] <=(target[0]+distanceTol) &&
				p_cur->point[1] >=(target[1]-distanceTol) && p_cur->point[1] <=(target[1]+distanceTol)) 
			{
				if (distance(p_cur->point, target) <= distanceTol)
					ids.push_back(p_cur->id);
			}
		
			if (target[depth%2] < p_cur->point[depth%2])
				searchHelper(p_cur->left, target, distanceTol, depth++, ids);
			if (target[depth%2] > p_cur->point[depth%2])
				searchHelper(p_cur->right, target, distanceTol, depth++, ids);

		}
	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;

		searchHelper(root, target, distanceTol, 0, ids);
		return ids;
	}
	

};




