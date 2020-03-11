#pragma once
#include <iostream>
#include <string>
using namespace std;

class BinarySearchTree;


class BinaryNode
{
    int element;
    BinaryNode *left;
    BinaryNode *right;
	string word;
    
    BinaryNode( const int & theElement,const string & str ,BinaryNode *lt, BinaryNode *rt )
    : element( theElement ), left( lt ), right( rt ), word(str) { }
    friend class BinarySearchTree;
};


class BinarySearchTree
{
public:
    explicit BinarySearchTree( const int & notFound );
    BinarySearchTree( const BinarySearchTree & rhs );
    ~BinarySearchTree( );
    
    const int & findMin( ) const;
    const int & findMax( ) const;
    const int & find( const string & s ) const;
    
    void makeEmpty( );
    void insert( const int & x , const string & str);
    
    
private:
    BinaryNode *root;
    const int ITEM_NOT_FOUND;
    
    const int & elementAt( BinaryNode *t ) const;
    
    void insert( const int & x, const string & str ,BinaryNode * & t ) const;
    BinaryNode * findMin( BinaryNode *t ) const;
    BinaryNode * findMax( BinaryNode *t ) const;
    BinaryNode * find( const string & s, BinaryNode *t ) const;
    void makeEmpty( BinaryNode * & t ) const;
};


BinarySearchTree::
BinarySearchTree(const int & notFound ) :
ITEM_NOT_FOUND( notFound ), root( NULL )
{
}



const int & BinarySearchTree::
elementAt( BinaryNode *t ) const
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}



const int & BinarySearchTree::
find( const string &x ) const
{
    return elementAt( find( x, root ) );
}




BinaryNode *
BinarySearchTree::
find( const string &s, BinaryNode *t ) const
{
    while( t != NULL )
        if( s < t->word )
            t = t->left;
        else if( t->word < s )
            t = t->right;
        else
            return t;    // Match
    
    return NULL;   // No match
}



const int & BinarySearchTree::findMin( ) const
{
    return elementAt( findMin( root ) );
}



BinaryNode *
BinarySearchTree::findMin( BinaryNode *t )
const
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}



const int & BinarySearchTree::findMax( ) const
{
    return elementAt( findMax( root ) );
}



BinaryNode *
BinarySearchTree::findMax( BinaryNode *t )
const
{
    if( t == NULL )
        return NULL;
    if( t->right == NULL )
        return t;
    return findMin( t->right );
}



void BinarySearchTree::insert( const int & x, const string & str )
{
    insert( x, str, root );
}



void BinarySearchTree::
insert( const int & x, const string & str, BinaryNode * & t ) const
{
    if( t == NULL ) //  create a new node at the right place
        t = new BinaryNode( x, str,NULL, NULL );
    else if( str < t->word)
        insert( x,str, t->left );  // insert at the left or
    else if( t->word < str)
        insert( x,str, t->right );  // right subtree
    else
        ;  // Duplicate; do nothing
}






void BinarySearchTree::makeEmpty( )
{
    makeEmpty( root );
}



void BinarySearchTree::
makeEmpty( BinaryNode * & t ) const
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}



BinarySearchTree::~BinarySearchTree( )
{
    makeEmpty( );
}









