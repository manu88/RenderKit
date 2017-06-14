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
#include <modest/myosi.h> // modest_t
#include <modest/render/tree_node.h> //  modest_render_tree_node_t
#include "HTMLNodeCollection.hpp"
class Document
{
public:
    Document();
    std::string getTitle() const;
    
    
    HTMLNodeCollection getNodesByTagID(myhtml_tag_id_t tagId) const noexcept;
    
    modest_t *_modest;
    modest_render_tree_node_t * _renderNode;
};

#endif /* Document_hpp */
