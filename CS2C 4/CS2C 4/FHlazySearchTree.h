// Student Name: Lee Rogers
// LAB Assignment 4

// ---------------------------------------------------------------------------------------- Modified FHsearch_tree ----------------------------------------------------------------------------------------

#ifndef FHLAZYSEARCHTREE_H
#define FHLAZYSEARCHTREE_H

// ---------------------- FHs_treeNode Prototype --------------------------
template <class Comparable>
class FHlazySearchTreeNode
{
public:
   FHlazySearchTreeNode( const Comparable & d = Comparable(),
      FHlazySearchTreeNode *lt = NULL,
      FHlazySearchTreeNode *rt = NULL)
      : lftChild(lt), rtChild(rt), data(d)
   { }

   FHlazySearchTreeNode* lftChild, *rtChild;
   Comparable data;
   bool deleted;

   // for use only with AVL Trees
   virtual int getHeight() const { return 0; }
   virtual bool setHeight(int height) { return true; }
}; 

// ---------------------- FHsearch_tree Prototype --------------------------
template <class Comparable>
class FHlazySearchTree
{
protected:
   int mSize;
   int mSizeHard;
   FHlazySearchTreeNode<Comparable> *mRoot;

public:
   FHlazySearchTree() { mSize = 0; mRoot = NULL; }
   FHlazySearchTree(const FHlazySearchTree &rhs)
      { mRoot = NULL; mSize = 0; *this = rhs; }
   ~FHlazySearchTree() { clear(); }

   const Comparable &findMin() const;
   const Comparable &findMax() const;
   const Comparable &find(const Comparable &x) const;

   bool empty() const { return (mSize == 0); }
   int size() const { return mSize; }
   int sizeHard() const { return mSizeHard; }
   void clear() { makeEmpty(mRoot); }
   const FHlazySearchTree& operator=(const FHlazySearchTree &rhs);

   bool insert(const Comparable &x);
   bool remove(const Comparable &x);
   bool contains(const Comparable &x) const { return find(mRoot, x) != NULL; }

   template <class Processor>
   void traverse(Processor func) const { traverse(mRoot, func); }
   int showHeight() const { return findHeight(mRoot); }

   void collectGarbage();

protected:
   FHlazySearchTreeNode<Comparable> *clone(FHlazySearchTreeNode<Comparable> *root) const;
   FHlazySearchTreeNode<Comparable> *findMin(FHlazySearchTreeNode<Comparable> *root) const;
   FHlazySearchTreeNode<Comparable> *findMax(FHlazySearchTreeNode<Comparable> *root) const;
   FHlazySearchTreeNode<Comparable> *find(FHlazySearchTreeNode<Comparable> *root,
      const Comparable &x) const;
   bool insert(FHlazySearchTreeNode<Comparable> * &root,
      const Comparable &x);
   bool remove(FHlazySearchTreeNode<Comparable> * &root, const Comparable &x);
   bool removeHard(FHlazySearchTreeNode<Comparable> * &root, const Comparable& x);
   void makeEmpty(FHlazySearchTreeNode<Comparable> * &subtreeToDelete);
   template <class Processor>
   void traverse(FHlazySearchTreeNode<Comparable> *treeNode,
      Processor func, int level = -1) const;
   int findHeight(FHlazySearchTreeNode<Comparable> *treeNode, int height = -1) const;
   void collectGarbage(FHlazySearchTreeNode<Comparable>* root);
   
public:
   // for exception throwing
   class EmptyTreeException {};
   class NotFoundException {};
};

// FHsearch_tree public method definitions -----------------------------
template <class Comparable>
const Comparable & FHlazySearchTree<Comparable>::findMin() const
{
   if (mRoot == NULL)
      throw EmptyTreeException();
   return findMin(mRoot)->data;
}

template <class Comparable>
const Comparable & FHlazySearchTree<Comparable>::findMax() const
{
   if (mRoot == NULL)
      throw EmptyTreeException();
   return findMax(mRoot)->data;
}

template <class Comparable>
const Comparable &FHlazySearchTree<Comparable>::find(
   const Comparable &x) const
{ 
   FHlazySearchTreeNode<Comparable> *resultNode;
   
   resultNode = find(mRoot, x);
   if (resultNode == NULL)
      throw NotFoundException();
    return resultNode->data;
}

template <class Comparable>
const FHlazySearchTree<Comparable> &FHlazySearchTree<Comparable>::operator=
   (const FHlazySearchTree &rhs)
{
   if (&rhs != this) 
   {
      clear();
      mRoot = clone(rhs.mRoot);
      mSize = rhs.size();
      mSizeHard = rhs.sizeHard();
   }
   return *this;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(const Comparable &x)
{
   if (insert(mRoot, x))
   {
      mSize++;
      return true;
   }
   return false;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(const Comparable &x)
{
   if (remove(mRoot, x))
   {
      mSize--;
      return true;
   }
   return false;
}

template <class Comparable>
template <class Processor>
void FHlazySearchTree<Comparable>::traverse(FHlazySearchTreeNode<Comparable> *treeNode,
   Processor func, int level) const
{
   if (treeNode == NULL)
      return;

   // we're not doing anything with level but its there in case we want it
   traverse(treeNode->lftChild, func, level + 1);
   if (treeNode->deleted == false)
       func(treeNode->data);
   traverse(treeNode->rtChild, func, level + 1);
}

// collectGarbage definition ----------------------------------------------------------------------------------------------------------------
template <class Comparable>
void FHlazySearchTree<Comparable>::collectGarbage() {

    collectGarbage(mRoot);
    return;
}

// FHsearch_tree private method definitions -----------------------------
template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::clone(
   FHlazySearchTreeNode<Comparable> *root) const
{
   FHlazySearchTreeNode<Comparable> *newNode;
   if (root == NULL)
      return NULL;

   newNode =  new FHlazySearchTreeNode<Comparable>(
      root->data, 
      clone(root->lftChild), clone(root->rtChild));
   return newNode;
}

template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMin(
   FHlazySearchTreeNode<Comparable> *root) const
{
   if (root == NULL)
      return NULL;
   if (root->lftChild == NULL) // did not need to use method in any functions other than removeHard so left as hard findMin
       return root;
   return findMin(root->lftChild);
}

template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMax(
   FHlazySearchTreeNode<Comparable> *root) const
{
   if (root == NULL)
      return NULL;
   if (root->rtChild == NULL) // did not need to use method so left as hard findMax
       return root;
   return findMax(root->rtChild);
}

template <class Comparable>
FHlazySearchTreeNode<Comparable>* FHlazySearchTree<Comparable>::find(
   FHlazySearchTreeNode<Comparable> *root, const Comparable &x) const
{
   if (root == NULL)
      return NULL;

   if (x < root->data)
      return find(root->lftChild, x);
   if (root->data < x)
      return find(root->rtChild, x);
   if (root->deleted == false) // only return if the node is not "deleted"
       return root;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(
   FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{
   if (root == NULL)
   {
      root = new FHlazySearchTreeNode<Comparable>(x, NULL, NULL);
      mSizeHard++;
      return true;
   }
   else if (root->deleted == true && x == root->data) {

       root->deleted = false;
       return true;
   }
   else if (x < root->data)
      return insert(root->lftChild, x);
   else if (root->data < x)
      return insert(root->rtChild, x);

   return false; // duplicate
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(
    FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{
   if (root == NULL)
      return false;

   if (x < root->data)
      return remove(root->lftChild, x);
   if (root->data < x)
      return remove(root->rtChild, x);

   // found the node
   if (root->deleted == true)
       return false;
   // "delete" the node
   root->deleted = true;
   return true;
}

// collectGarbage definition ----------------------------------------------------------------------------------------------------------------

template <class Comparable>
void FHlazySearchTree<Comparable>::collectGarbage(FHlazySearchTreeNode<Comparable>* root) {

    if (root == nullptr)
        return;

    // recurse through the tree
    if (root->lftChild)
        collectGarbage(root->lftChild);

    if (root->rtChild)
        collectGarbage(root->rtChild);

    if (root->deleted)
        removeHard(root, root->data);
}

// removeHard definition ----------------------------------------------------------------------------------------------------------------

template <class Comparable>
bool FHlazySearchTree<Comparable>::removeHard(FHlazySearchTreeNode<Comparable> * &root, const Comparable& x) {

    if (root == NULL)
        return false;

    if (x < root->data)
        return removeHard(root->lftChild, x);
    if (root->data < x)
        return removeHard(root->rtChild, x);
    
    // found the node
    if (root->lftChild != NULL && root->rtChild != NULL)
    {
        FHlazySearchTreeNode<Comparable>* minNode = findMin(root->rtChild);
        root->data = minNode->data;
        root->deleted = minNode->deleted;
        removeHard(root->rtChild, root->data);
    }
    else
    {
        root = (root->lftChild != NULL) ? root->lftChild : root->rtChild;
        mSizeHard--;
    }
    return true;
}

template <class Comparable>
void FHlazySearchTree<Comparable>::makeEmpty(
   FHlazySearchTreeNode<Comparable> * &subtreeToDelete)
{
   if (subtreeToDelete == NULL)
      return;
   if (subtreeToDelete->deleted == true)
       return;

   // remove children
   makeEmpty(subtreeToDelete->lftChild);
   makeEmpty(subtreeToDelete->rtChild);

   // clear client's pointer
   delete subtreeToDelete;
   subtreeToDelete = NULL;
   --mSize;
   --mSizeHard;
}

template <class Comparable>
int FHlazySearchTree<Comparable>::findHeight(FHlazySearchTreeNode<Comparable> *treeNode,
   int height ) const
{
   int leftHeight, rightHeight;

   if (treeNode == NULL)
      return height;
   height++;
   leftHeight = findHeight(treeNode->lftChild, height);
   rightHeight = findHeight(treeNode->rtChild, height);
   return (leftHeight > rightHeight)? leftHeight : rightHeight;
}
#endif

/* Runs ----------------------------------------------------------------------------------------------------------------------------------

Default run:

initial size: 0
After populating -- traversal and sizes:
10 20 30 50 60 70
tree 1 size: 6  Hard size: 6
Collecting garbage on new tree - should be no garbage.
tree 1 size: 6  Hard size: 6


Attempting 1 removal:
removed 20
tree 1 size: 5  Hard size: 6
Collecting Garbage - should clean 1 item.
tree 1 size: 5  Hard size: 5
Collecting Garbage again - no change expected.
tree 1 size: 5  Hard size: 5
Adding 'hard' 22 - should see new sizes.
10 22 30 50 60 70
tree 1 size: 6  Hard size: 6

After soft removal.
10 30 50 60 70
tree 1 size: 5  Hard size: 6
Repeating soft removal. Should see no change.
10 30 50 60 70
tree 1 size: 5  Hard size: 6
Soft insertion. Hard size should not change.
10 22 30 50 60 70
tree 1 size: 6  Hard size: 6


Attempting 100 removals:
removed 70
removed 60
removed 50
removed 30
removed 22
removed 10

searchTree now:

tree 1 size: 0  Hard size: 0

searchTree2:
10 20 30 50 60 70 100 200 300 500 600 700
tree 2 size: 12  Hard size: 12

-------------------------------------------------------------------------------------------------------------------------------------------------

Custom Run 1:

initial size: 0
After populating -- traversal and sizes:
12 40 71 99
tree 1 size: 4  Hard size: 4


Attempting 1 removal:
removed 40
tree 1 size: 3  Hard size: 4
Collecting Garbage - should clean 1 item.
tree 1 size: 3  Hard size: 3
Adding 'hard' 87 - should see new sizes.
12 71 87 99
tree 1 size: 4  Hard size: 4

After soft removal.
12 71 99
tree 1 size: 3  Hard size: 4

Soft insertion. Hard size should not change.
12 71 87 99
tree 1 size: 4  Hard size: 4


Attempting 100 removals:
removed 99
removed 87
removed 71
removed 12

searchTree now:

tree 1 size: 0  Hard size: 0

-------------------------------------------------------------------------------------------------------------------------------------------------

Custom run 2:

initial size: 0

After populating -- traversal and sizes:
15 30 45 60 75 90 105 120 135 150 165 180 195 210
tree 1 size: 14  Hard size: 14

Attempting 1 removal:
removed 30
tree 1 size: 13  Hard size: 14

Attempting 1 removal:
removed 120
tree 1 size: 12  Hard size: 14

Attempting 1 removal:
removed 75
tree 1 size: 11  Hard size: 14

Soft insertion. Hard size should not change.
15 45 60 75 90 105 135 150 165 180 195 210
tree 1 size: 12  Hard size: 14

Collecting Garbage - should clean 2 items.
tree 1 size: 12  Hard size: 12

Adding 'hard' 225 - should see new sizes.
15 45 60 75 90 105 135 150 165 180 195 210 225
tree 1 size: 13  Hard size: 13


Attempting 200 soft removals:
removed 195
removed 180
removed 165
removed 150
removed 135
removed 105
removed 90
removed 75
removed 60
removed 45
removed 15

searchTree now:
210 225
tree 1 size: 2  Hard size: 13

Attempting 1 removal:
removed 210
tree 1 size: 1  Hard size: 13

Attempting 1 removal:
removed 225
tree 1 size: 0  Hard size: 13

-------------------------------------------------------------------------------------------------------------------------------------------------
*/