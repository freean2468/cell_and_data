#include "FileLoaderBase.h"

//removes any commenting from a line of text
void RemoveCommentingFromLine(std::string& line){
   //search for any comment and remove
   std::string::size_type idx = line.find('//');

   if (idx != std::string::npos){
     //cut out the comment
     line = line.substr(0, idx);
   }
}

//----------------------- GetNextParameter ------------------------------------
//
//  searches the text file for the next valid parameter. Discards any comments
//  and returns the value as a string
//-----------------------------------------------------------------------------
std::string CFileLoaderBase::GetNextParameter(){ 
  //this will be the string that holds the next parameter
  std::string line;
  
  std::getline(file, line);
   
  RemoveCommentingFromLine(line);

  //if the line is of zero length, get the next line from the file
  if (line.length() == 0){
    return GetNextParameter();
  }

  GetParameterValueAsString(line);  
    
  return line;
}

//-------------------------- GetParameterValueAsString ------------------------
//
// given a line of text this function removes the parameter description
// and returns just the parameter as a std::string
//-----------------------------------------------------------------------------
void CFileLoaderBase::GetParameterValueAsString(std::string& line){
  //find beginning of parameter description
  std::string::size_type begIdx;
  std::string::size_type endIdx;

  //define some delimiters
  const std::string delims(" \;=,");

  begIdx = line.find_first_not_of(delims);

  //find the end of the parameter description
  if (begIdx != std::string::npos){
    endIdx = line.find_first_of(delims, begIdx);

    //end of word is the end of the line
    if (endIdx == std::string::npos){
      endIdx = line.length();
    }
  }   

  //find the beginning of the parameter value
  begIdx = line.find_first_not_of(delims, endIdx);

  //find the end of the parameter value
  if(begIdx != std::string::npos){
    endIdx = line.find_first_of(delims, begIdx);

    //end of word is the end of the line
    if (endIdx == std::string::npos){
      endIdx = line.length();
    }
  }
    
  line = line.substr(begIdx, endIdx);
}

//--------------------------- GetNextToken ------------------------------------
//
//  ignores any commenting and gets the next string
//-----------------------------------------------------------------------------
std::string CFileLoaderBase::GetNextToken(){ 
  //strip the line of any commenting
  while (CurrentLine.length() == 0){
    std::getline(file, CurrentLine);
   
    RemoveCommentingFromLine(CurrentLine);
  }

   //find beginning of parameter description
  std::string::size_type begIdx; 
  std::string::size_type endIdx;

  //define some delimiters
  const std::string delims(" \;=,");

  begIdx = CurrentLine.find_first_not_of(delims);

  //find the end of the parameter description
  if (begIdx != std::string::npos){
    endIdx = CurrentLine.find_first_of(delims, begIdx);

    //end of word is the end of the line
    if (endIdx == std::string::npos){
      endIdx = CurrentLine.length();
    }
  }
    
  std::string s = CurrentLine.substr(begIdx, endIdx);

  if (endIdx != CurrentLine.length()){
    //strip the token from the line
    CurrentLine = CurrentLine.substr(endIdx+1, CurrentLine.length());
  }

  else { CurrentLine = "";}

  return s;  
}

std::string CFileLoaderBase::GetNextScript(){
	//this will be the string that holds the next parameter
  std::string line;
  
  std::getline(file, line);

  //if the line is of zero length, get the next line from the file
  if (line.length() == 0){
    return GetNextScript();
  }

  //find beginning of parameter description
  std::string::size_type begIdx;
  std::string::size_type endIdx;

  //define some delimiters
  const std::string delims("\;=");

  begIdx = line.find_first_not_of(delims);

  //find the end of the parameter description
  if (begIdx != std::string::npos){
    endIdx = line.find_first_of(delims, begIdx);

    //end of word is the end of the line
    if (endIdx == std::string::npos){
      endIdx = line.length();
    }
  }   
    
  line = line.substr(begIdx, endIdx);
    
  return line;
}