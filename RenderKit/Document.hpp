//
//  Document.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef Document_hpp
#define Document_hpp

#include <string>
#include <memory> // shared_ptr

#include <modest/myosi.h> // modest_t
#include <modest/render/tree_node.h> //  modest_render_tree_node_t

#include "HTMLNodeCollection.hpp"
#include "MWrapper.hpp"

class Document
{
public:
    Document( const std::string &content = "");
    ~Document();
    
    Document(Document&);
    Document& operator=( const Document &);
    
    void setContent(const std::string &content)
    {
        _docContent = content;
    }
    
    std::string getTitle() const;
    
    bool isValid() const noexcept;
    
    HTMLNodeCollection getNodesByTagID(myhtml_tag_id_t tagId) const noexcept;
    
    modest_t* getModest() const
    {
        return _modest.get()->_modest;
    }
    

    std::string _docContent;
    std::shared_ptr<MWrapper> _modest;
    
    modest_render_tree_node_t * _renderNode;
};

#endif /* Document_hpp */
