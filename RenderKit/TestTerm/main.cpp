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
    
    printf("TEST RENDER \n");
    assert(renderer.render( &parser));

    return 0;
}

