
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


#include "StringOperations.hpp"
#include "FileSystem.hpp"

std::string FileSystem::getPathRelativeTo( const std::string &pathToGet , const std::string &pathRelativeTo)
{
    std::istringstream pa1( pathToGet );
    std::istringstream pa2( pathRelativeTo );
    
    std::vector<std::string> tok1;
    std::vector<std::string> tok2;
    
    std::string s;
    
    while( std::getline(pa1, s, '/') )
        tok1.push_back(s);
    
    while( std::getline(pa2, s, '/') )
        tok2.push_back(s);
    

    const size_t smallSize =  (tok1.size() < tok2.size() ? tok1.size() : tok2.size() );
    
    size_t i =0;
    
    for (; i<smallSize ; ++i)
    {
        if ( tok1.at(i) != tok2.at(i) )
            break;
        
    }
    
    tok1.erase( tok1.begin(), tok1.begin() + static_cast<long>( i ) );
    tok2.erase( tok2.begin(), tok2.begin() + static_cast<long>( i ) );
    
    std::string ret;
    
    for ( size_t j=0; j < tok2.size() ; ++j)
        ret += "../";
    
    for ( size_t j=0; j< tok1.size() ; ++j)
    {
        ret += tok1.at(j);// +  "/";
        if ( j<  tok1.size() - 1  )
            ret += "/";
    }
    
    return ret;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::hasSuffix( const std::string &str, const std::string &suffix )
{
    return str.size() >= suffix.size() &&
    str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

const std::string FileSystem::getFileExtension( const std::string &filePath )
{
    return filePath.substr( filePath.find_last_of(".") + 1);
}

const std::string FileSystem::getFileName( const std::string &filePath )
{
    
    struct MatchPathSeparator
    {
        bool operator()( char ch ) const
        {
            return ch == '\\' || ch == '/';
        }
    };

    return removeExtension( std::string(
                                        std::find_if( filePath.rbegin(), filePath.rend(), MatchPathSeparator() ).base(),
                                        filePath.end()
                                        )
                           );
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

const std::string FileSystem::getPathLocation( const std::string &file)
{
    std::string res = file;
    if (hasSuffix(file, "/"))
    {
        const auto lastindex = file.find_last_of("/");
        res = file.substr(0, lastindex);
    }
        
    size_t found;

    found= res.find_last_of("/\\");


    
    return  correctPathIfNeeded( res.substr(0,found) );
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

const std::string FileSystem::removeExtension( const std::string &file)
{
    std::string::const_reverse_iterator pivot = std::find( file.rbegin(), file.rend(), '.' );

    return pivot == file.rend()? file : std::string( file.begin(), pivot.base() - 1 );
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::fileExists( const std::string &filepath)
{
    struct stat results;
    
    return ( stat( filepath.c_str() , &results) >= 0 && S_ISREG(results.st_mode) );

}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::folderExists( const std::string &path)
{
    struct stat results;

    return ( stat( path.c_str() , &results) >= 0 && S_ISDIR( results.st_mode ) );
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::isFile( const std::string &path)
{
    return fileExists( path );
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::isFolder( const std::string &path)
{
    return folderExists( path );
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::isPipe( const std::string &path)
{
    return path.compare(0, 5, "pipe:") == 0;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::isURL( const std::string &path)
{
    const auto result = path.find("://");
    
    if( result == std::string::npos || result == 0 )
        return false;
    
    for( size_t i = 0; i < result; ++i )
    {
        if( !isalpha( path[i]) )
            return false;
    }
    return true;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::createFile( const std::string &path)
{
    FILE *ifp = nullptr;
    ifp = fopen( path.c_str() , "w");
    
    if (ifp)
    {
        fclose(ifp);
        return true;
    }

    return false;
    
}

bool FileSystem::createDir( const std::string &path)
{
    struct stat st;// = {0 , 0, 0};
    
    if (stat( path.c_str(), &st) == -1)
    {
        return mkdir(path.c_str(), 0700) == 0;

    }
    return false;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::copyFile( const std::string &from , const std::string &to)
{

    int fd_to   = -1;
    int fd_from = -1;
    
    char buf[4096];
    
    ssize_t nread;
    
    int saved_errno = 0;
    
    fd_from = open(from.c_str(), O_RDONLY);
    
    if (fd_from < 0)
        return false;
    
    fd_to = open(to.c_str(), O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (fd_to < 0)
        goto out_error;
    
    while (nread = read(fd_from, buf, sizeof buf), nread > 0)
    {
        char *out_ptr = buf;
        ssize_t nwritten;
        
        do {
            nwritten = write(fd_to, out_ptr, static_cast<size_t>( nread ));
            
            if (nwritten >= 0)
            {
                nread -= nwritten;
                out_ptr += nwritten;
            }
            else if (errno != EINTR)
            {
                goto out_error;
            }
        } while (nread > 0);
    }
    
    if (nread == 0)
    {
        if (close(fd_to) < 0)
        {
            fd_to = -1;
            goto out_error;
        }
        close(fd_from);
        
        /* Success! */
        return true;
    }
    
out_error:
    saved_errno = errno;
    
    close(fd_from);
    if (fd_to >= 0)
        close(fd_to);
    
    errno = saved_errno;
    return false;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::removeFile( const std::string &path)
{
    return remove( path.c_str() ) == 0 ;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::removeDir( const std::string &path)
{
    return rmdir( path.c_str() ) == 0;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

long long FileSystem::getFileSize( const std::string &filepath)
{
    if( !fileExists( filepath ) )
        return -1;
    
    struct stat st;
    stat(filepath.c_str() , &st);
    
    return st.st_size;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

const std::string FileSystem::correctPathIfNeeded( const std::string &path)
{
    if ( !isFolder( path))
        return path;
    
    if (hasSuffix(path, "/"))
        return path;
    
    return path + "/";
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

const std::string FileSystem::locateFileFromFoldersList( const std::string &filename , const std::vector<std::string> &vector)
{
    for (const auto p : vector)
    {
        const std::string fullPath = p + filename;
        
        if ( fileExists( fullPath) )
            return fullPath;
    }
    
    return "";
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

const std::string FileSystem::locateFolderFromFoldersList( const std::string &folder , const std::vector<std::string> &vector)
{
    const std::string fol = correctPathIfNeeded( folder );
    
    for (const auto p : vector)
    {
        const std::string fullPath = p + fol;
        
        if ( folderExists( fullPath) )
            return fullPath;
    }
    
    return "";
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

const std::vector< std::string > FileSystem::getFilesListFromFolder( const std::string &path ,
                                                                     bool  withFullPath,
                                                                     bool  sortABC,
                                                                     const std::string &beginWith ,
                                                                     const std::string withExtention
                                                                    )
{

    std::vector< std::string > ret;
    
    getFilesListFromFolder( ret, path , "" , withFullPath , beginWith , withExtention);
    
    if ( sortABC )
        std::sort(ret.begin(), ret.end() );
    
    return ret;

    
}

const bool FileSystem::getFilesListFromFolder(
                                  std::vector< std::string> &vector,
                                  const std::string &fullPath ,
                                  const std::string &relPath ,
                                  bool  withFullPath,
                                  const std::string &beginWith,
                                  const std::string withExtention
                                  )
{

    DIR * d = nullptr ;
    
    const std::string realPath  = fullPath+relPath;
    
    d = opendir ( realPath.c_str() );
    
    
    if (! d)
    {
        return false;
    }
    
    while (1)
    {
        struct dirent * entry;
        const char * d_name;
        
        entry = readdir (d);
        if (! entry)
            break;

        
        d_name = entry->d_name;
        
        
        if (   ( strcmp( entry->d_name , "."  ) != 0 )
            && ( strcmp( entry->d_name , ".." ) != 0 )
            )
        {
            if (entry->d_type & DT_DIR)
            {
                
                
                int path_length;
                char path[PATH_MAX];
                
                path_length = snprintf (path, PATH_MAX, "%s%s", fullPath.c_str() , d_name);
                
                
                
                if (path_length >= PATH_MAX)
                {
                    fprintf (stderr, "Path length has got too long.\n");
                    
                    return false;
                }
                
                getFilesListFromFolder( vector,
                                       correctPathIfNeeded(fullPath),
                                       ( relPath.empty() ?"" : ( relPath + "/" ) ) + std::string( d_name ),
                                       withFullPath ,
                                       beginWith ,
                                       withExtention
                                       );
            }
            else //if (entry->d_type & DT_REG)
            {
                
                const std::string item = correctPathIfNeeded((withFullPath?fullPath :"") + (relPath.empty()?"":(relPath + "/") )) + std::string( d_name );
            
                if ( (beginWith.empty() ) || StringOperations::beginWith( d_name, beginWith ) )
                {
                    vector.push_back( item );
                }
            }

        
            
            
        }

    } // end of while

    closedir (d);

    return true;

}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

const std::string FileSystem::getFileText( const std::string &fileUrl)
{
    std::ifstream in( fileUrl );
        
    return std::string((std::istreambuf_iterator<char>(in)),
                                std::istreambuf_iterator<char>());
    
}


/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::setFileText(const std::string &file , const std::string &data)
{
    FILE *f = fopen(file.c_str() , "w");
    
    if (f)
    {
        fprintf(f, "%s", data.c_str() );
        
        fclose( f );
        return true;
    }
    
    return false;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool FileSystem::appendTextToFile(const std::string &file , const std::string &data)
{
    FILE *f = fopen(file.c_str() , "a");
    
    if (f)
    {
        fprintf(f, "%s", data.c_str() );
        
        fclose( f );
        return true;
    }
    
    return false;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

const std::string FileSystem::getExtensionWithMIME( const std::string &mime)
{
    if (mime =="image/jpeg" )
        return "jpg";
    
    else if (mime == "video/x-msvideo")
        return "avi";
    
    else if (mime == "image/png")
        return "png";
    
    return "undef";
}

