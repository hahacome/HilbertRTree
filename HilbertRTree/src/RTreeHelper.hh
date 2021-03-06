#ifndef HRTREE_SRC_RTREEHELPER_HH
#define HRTREE_SRC_RTREEHELPER_HH

#include <list>
#include <boost/shared_ptr.hpp>

#include "Node.hh"
#include "HilbertValue.hh"
#include "Common.hh"

class RTreeHelper
{
public:

    /**
     * @brief search Search the subtree rooted at the given node and return all the leaf entries
     * in the subtree that intersect the query rectangle.
     * @param subtreeRoot Root of the subtree
     * @param query Query rectangle
     * @return A list of leaf entries whose mbrs intersect the query rectangle
     */
    static std::list<boost::shared_ptr<NodeEntry> > search(Node* subtreeRoot, const boost::shared_ptr<Rectangle>& query);

    /**
     * @brief chooseLeaf Choose a leaf for the hilbert value starting from the node N
     * @param N Node to start the search from
     * @param h Hilbert value of the item we want to insert
     * @return Pointer to a leaf node in which the given hilbert value can be inserted.
     */
    static Node* chooseLeaf(Node* N, const boost::shared_ptr<HilbertValue>& h);

    /**
     * @brief exactSearch Perform an exact search for the leaf node containing an exact
     * match for the rectangle. If no leaf is found, NULL is returned.
     * @param subtreeRoot
     * @param rect
     * @return
     */
    static Node* exactSearch(Node* subtreeRoot, boost::shared_ptr<Rectangle> rect);

    /**
     * @brief redistributeEntries Redistribute the given set of NodeEntries which are assumed to be sorted
     * according to their hilbert value over the given list of nodes which are assumed to be in the correct
     * sibling order i.e. the next node in the list is also the next sibling of the previous node in the list.
     * Each node in the siblings list must not have any entries.
     * N and NN have their LHV and MBR adjusted as well as all the nodes in the siblings list;
     * @param entries
     * @param siblings
     */
    static void redistributeEntries(EntryMultiSet& entries, std::list<Node*> siblings);

    /**
     * @brief handleOverflow
     * @param target
     * @param entry
     * @param out_siblings Will contain the target node, its siblings, and the new node if one was created
     * @return
     */
    static Node* handleOverflow(Node* target, const boost::shared_ptr<NodeEntry>& entry, std::list<Node*>& out_siblings);

    static Node* handleUnderflow(Node* target, std::list<Node*>& out_siblings);
    /**
     * @brief adjustTree Adjust the tree following an insertion or a deletion.
     * @param root The current root of the tree.
     * @param N The node that has been directly modified.
     * @param NN The node that was created if there was no room for insertion in N.
     * This is NULL if no node was created.
     * @param overflowed True if N reached capacity.
     * @return The new root of the tree.
     */
    static Node* adjustTreeForInsert(Node* root, Node*N, Node* NN,std::list<Node*>siblings);

    /**
     * @brief adjustTreeForRemove Adjust the tree after the removal of an entry.
     * @param N Node that was the target of the removal
     * @param DN Node that was deleted if an underflow occured, NULL otherwise
     * @param siblings List of the siblings affected by the removal.
     */
    static void adjustTreeForRemove(Node*N, Node* DN, std::list<Node*> siblings);

};

#endif // HRTREE_SRC_RTREEHELPER_HH
