
#include <assert.h>
#include <stdio.h>

#include "FileSystem.hpp"
#include "HTMLRenderer.hpp"
#include "HTMLParser.hpp"
#include "Document.hpp"
#include "DocumentParser.hpp"

int main(int argc, const char * argv[])
{
    Document doc;
    DocumentParser p;
    
    const std::string html = FileSystem::getFileText( argv[1]);

    /*
    = "<html><head><style type=\"text/css\">div {padding: 130px 3em; color: rgba(23 10 200 / 0.4) }</style></head><body><div style=\"float:right\"></div>";
    */
    p.load( doc , html.c_str() , html.size() );
    
    HTMLRenderer renderer;
    assert(renderer.prepare(doc));
    
    GXSize viewSize = GXSizeMake(1920, 1080);
    renderer.render(viewSize, doc);
    
    
    return 0;
    /*
    HTMLParser parser;
    
    const std::string html = FileSystem::getFileText( argv[1]);
    
    
    assert(parser.parseContent( doc , html));
    
    printf("Title '%s'\n" , doc.getTitle().c_str());
    
    HTMLRenderer renderer;
    assert(renderer.prepare(doc));
    
    assert(renderer.render( viewSize, doc));
    
    renderer.printBlockTree();

    return 0;
     */
}
