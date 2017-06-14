//
//  HTMLParser.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 02/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef HTMLNode_hpp
#define HTMLNode_hpp

#include <string>
#include <iterator>

#include <myhtml/myhtml.h>
#include <mycss/mycss.h>

#include <modest/myosi.h> // modest_t
#include <modest/modest.h> // modest

#include "HTMLAttribute.hpp"

class HTMLNode
{
public:
    
    
    class Iterator : public std::iterator<std::forward_iterator_tag, HTMLNode>
    {
        friend class HTMLNode;
    private:
        Iterator( myhtml_tree_node_t *node , modest_t* modest) :
        _modest(modest),
        _node(node)
        {
            
        }
    public:
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
            return HTMLNode( _node , _modest);
        };
        
        modest_t* _modest;
        myhtml_tree_node_t *_node;
    };
    
    
    HTMLNode(myhtml_tree_node_t* node , modest_t* modest):
    _modest(modest),
    _node(node)
    {}

    std::string getTagName() const noexcept;
    
    bool hasText() const noexcept;
    std::string getText() const noexcept;
    
    
    
    const mycss_declaration_entry_t* parseDeclaration(myencoding_t encoding , mycss_declaration_t* declaration, const HTMLAttribute&) const noexcept;
    
    
    const Iterator begin() const
    {
        return Iterator( _node , _modest  );
    }
    
    const Iterator end() const
    {
        return Iterator(  nullptr , _modest );
    }
    
    HTMLAttribute getAttributeByName( const std::string &name) const noexcept;
    HTMLAttribute getAttribute( const std::string &key) const noexcept;
    
    bool isValid() const noexcept
    {
        return _modest && _node;
    }
    
    
    modest_t* _modest;
    myhtml_tree_node_t* _node;
};


#endif /* HTMLNode_hpp */
