//
//  FileSystem.h
//  Broadway_core
//
//  Created by Manuel Deneu on 30/11/14.
//  Copyright (c) 2014 Manuel Deneu. All rights reserved.
//

#ifndef __Broadway_core__FileSystem__
#define __Broadway_core__FileSystem__

#include <vector>
#include <iostream>

/*
 
 General rules:
 
 Paths have to end with a '/' : most of the methods here (if not all) will correct the path to do so.
 
 */


namespace FileSystem
{
    // return pathToGet relative to PathRelativeTo,
    // ie the relative path to go from pathRelativeTo to pathToGet
    std::string getPathRelativeTo( const std::string &pathToGet , const std::string &pathRelativeTo);
    
    bool hasSuffix(const std::string &str, const std::string &suffix);
    
    const std::string getFileExtension( const std::string &filePath );
    const std::string getFileName( const std::string &filePath );
    const std::string getPathLocation( const std::string &file);
    const std::string removeExtension( const std::string &file);
    
    bool fileExists( const std::string &filepath);
    bool folderExists( const std::string &path);
    
    bool isFile( const std::string &path);
    bool isFolder( const std::string &path);
    bool isPipe( const std::string &path);
    bool isURL( const std::string &path);
    
    bool createFile( const std::string &path);
    bool createDir( const std::string &path);
    
    bool copyFile( const std::string &from , const std::string &to);
    
    bool removeFile( const std::string &path);
    bool removeDir( const std::string &path);

    
    // will return -1 if invalid (?)
    long long getFileSize( const std::string &filepath);
    
    const std::string correctPathIfNeeded( const std::string &path);
    
    // will return an empty string if nothing found;
    const std::string locateFileFromFoldersList( const std::string &filename , const std::vector<std::string> &vector);
    /*
    inline const std::string locateFileFromFoldersList( const std::string &filename , const VariantList &vector)
    {
        std::vector<std::string> l;
        
        if (vector.empty() )
            return "";
        
        for ( const auto &f : vector)
            l.push_back(f.getString() );
        
        return locateFileFromFoldersList( filename, l);
    }
    */
    
    // will return an empty string if nothing found;
    const std::string locateFolderFromFoldersList( const std::string &folder , const std::vector<std::string> &vector);
    
    
    const std::vector< std::string > getFilesListFromFolder( const std::string &path ,
                                                             bool  withFullPath,
                                                             bool  sortABC = true,
                                                             const std::string &beginWith = "" ,
                                                             const std::string withExtention = "*"
                                                            );
    
    const bool getFilesListFromFolder(
                                      std::vector< std::string> &vector,
                                       const std::string &fullPath ,
                                       const std::string &relPath,
                                       bool  withFullPath,
                                       const std::string &beginWith = "" ,
                                       const std::string withExtention = "*"
                                       );
    
    const std::string getFileText( const std::string &fileUrl);
    
    bool setFileText(const std::string &file , const std::string &data);
    bool appendTextToFile(const std::string &file , const std::string &data);
    
    
    const std::string getExtensionWithMIME( const std::string &mime);
    
} /*namespace FileSystem*/

#endif /* defined(__Broadway_core__FileSystem__) */
