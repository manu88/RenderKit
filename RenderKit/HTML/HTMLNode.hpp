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

#include <modest/myosi.h> // modest_t

#include "CSSDeclaration.hpp"
#include "HTMLAttribute.hpp"

struct HTMLNodeBase
{
    modest_t* _modest;
    myhtml_tree_node_t* _node;
};

class HTMLNode : public HTMLNodeBase
{
public:
    typedef myhtml_tags TagID;
    
    /* **** */
    class Iterator : public std::iterator<std::forward_iterator_tag, HTMLNode> , public HTMLNodeBase
    {
        friend class HTMLNode;
    private:
        Iterator( myhtml_tree_node_t *node , modest_t* modest)
        {
            _modest = modest;
            _node = node;
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

    };
    
    /* **** */
    
    HTMLNode(myhtml_tree_node_t* node , modest_t* modest)
    {
        _modest = modest;
        _node = node;
    }

    std::string getTagName() const noexcept;
    
    bool hasText() const noexcept;
    std::string getText() const noexcept;

    const Iterator begin() const
    {
        return Iterator( _node , _modest  );
    }
    
    const Iterator end() const
    {
        return Iterator(  nullptr , _modest );
    }
    
    HTMLNode getChild() const noexcept;
    
    HTMLAttribute getAttributeByName( const std::string &name) const noexcept;
    HTMLAttribute getAttribute( const std::string &key) const noexcept;
    
    bool isValid() const noexcept
    {
        return _modest && _node;
    }
    
    CSSDeclaration getDeclarationByType( mycss_property_type_t type) const noexcept;
    CSSDeclaration parseDeclaration(myencoding_t encoding , const HTMLAttribute&) const noexcept;
    
    
    
    void printCSSProperties() const noexcept;
    CSSDeclaration getSelectorByKey( const std::string &key)const noexcept;
    
    TagID getTagID() const noexcept;
};


#endif /* HTMLNode_hpp */
