#include <assert.h>
#include <stdio.h>

#include "FileSystem.hpp"
#include "HTMLRenderer.hpp"
#include "HTMLParser.hpp"

int main(int argc, const char * argv[])
{
    
    HTMLParser parser;
    
    const std::string html = FileSystem::getFileText( argv[1]);
    
    assert(parser.parseContent(html));
    assert(parser.render());
    
    
    printf("Title '%s'\n" , parser.getTitle().c_str());
    
    HTMLRenderer renderer;
    
    GXSize viewSize = GXSizeMake(1920, 1080);
    assert(renderer.render( viewSize, &parser));
    
    renderer.printBlockTree();

    return 0;
}

