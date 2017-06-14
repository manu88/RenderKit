//
//  HTMLParser.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef HTMLParser_hpp
#define HTMLParser_hpp

#include <string>
#include <modest/modest.h>

#include <modest/finder/finder.h> // modest_finder_t
#include <modest/finder/myosi.h> // modest_finder_thread_t

#include "HTMLNodeCollection.hpp"

class Document;

class HTMLParser
{
public:
    
    enum{ FinderThreadsNum = 2};
    
    HTMLParser();
    ~HTMLParser();
    
    //std::string getTitle() const;
    
    bool parseContent(Document&, const std::string &buf);
    bool parseContent(Document&, const char* buf , size_t len);
    

    
    
    //HTMLNodeCollection getNodesByTagID(myhtml_tag_id_t tagId) const noexcept;
    
    mycss_t* _cssParser;
    modest_t * X_modest;
    modest_finder_t* _finder;
    modest_finder_thread_t *_finderThread;
    
    
    
private:
    myhtml_tree_t * parse_html(Document&,const char* data, size_t data_size);
    bool parseCSS(Document&);
    mycss_entry_t * parseCSS(const char* data, size_t data_size);
    
    
    void parseHTML();

};

#endif /* HTMLParser_hpp */
