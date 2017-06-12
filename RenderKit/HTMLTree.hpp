//
//  HTMLParser.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 02/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef HTMLTree_hpp
#define HTMLTree_hpp

#include <string>
#include <iterator>

#include <myhtml/myhtml.h>
#include <mycss/mycss.h>

#include "HTMLTree.hpp"
#include "HTMLAttribute.hpp"

class HTMLNode
{
public:
    
    class Iterator : public std::iterator<std::forward_iterator_tag, HTMLNode>
    {
    public:
        Iterator( myhtml_tree_node_t *node , myhtml_tree_t* tree) :
        _node(node),
        _tree(tree)
        {
        
        }
        
        bool operator!=( const Iterator& rhs)
        {
            return _node != rhs._node;
        }
        
        bool operator==( const Iterator& rhs)
        {
            return _node == rhs._node;
        }
        
        Iterator& operator++()
        {
            _node = _node->next;
            return *this;
        };
        
        HTMLNode operator*()
        {
            return HTMLNode( _node , _tree);
        };
        
        myhtml_tree_node_t *_node;
        myhtml_tree_t* _tree;
    };
    
    HTMLNode(myhtml_tree_node_t* node , myhtml_tree_t* tree):
    _node(node) ,
    _tree(tree)
    {}

    std::string getTagName() const noexcept;
    
    bool hasText() const noexcept;
    std::string getText() const noexcept;
    
    
    
    const mycss_declaration_entry_t * parseDeclaration(myencoding_t encoding , mycss_declaration_t* declaration, const myhtml_tree_attr_t * attribute) const noexcept;
    
    
    const Iterator begin() const
    {
        return Iterator( _node->child , _tree );
    }
    
    const Iterator end() const
    {
        return Iterator( nullptr , _tree);
    }
    
    HTMLAttribute getAttributeByName( const std::string &name) const noexcept;
    HTMLAttribute getAttribute( const std::string &key) const noexcept;
    
    myhtml_tree_node_t* _node;
    myhtml_tree_t* _tree;
};
class HTMLTree
{
public:
    HTMLTree();
    ~HTMLTree();
    
    bool parseContent( const char* buf , size_t len);
    
    myhtml_tree_t *_tree;
    myhtml_t* _html;
private:
    
    
    
};

#endif /* HTMLTree_hpp */
