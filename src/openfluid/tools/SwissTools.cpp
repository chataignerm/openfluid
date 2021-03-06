/*

  This file is part of OpenFLUID software
  Copyright(c) 2007, INRA - Montpellier SupAgro


 == GNU General Public License Usage ==

  OpenFLUID is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenFLUID is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.
  
*/



#include <openfluid/tools/SwissTools.hpp>

#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string.hpp>

#include <openfluid/core/DateTime.hpp>


#if WIN32
#include <windows.h> // for Sleep
#else
#include <time.h>
#endif

namespace openfluid { namespace tools {


void TokenizeString(const std::string& StrToTokenize,
                    std::vector<std::string>& Tokens,
                    const std::string& Delimiters = " ")
{
  Tokens.clear();

  std::string::size_type LastPos = StrToTokenize.find_first_not_of(Delimiters, 0);
  std::string::size_type Pos = StrToTokenize.find_first_of(Delimiters, LastPos);

  while (std::string::npos != Pos || std::string::npos != LastPos)
  {
    // Found a token, add it to the vector.
    Tokens.push_back(StrToTokenize.substr(LastPos, Pos - LastPos));
    // Skip delimiters.  Note the "not_of"
    LastPos = StrToTokenize.find_first_not_of(Delimiters, Pos);
    // Find next "non-delimiter"
    Pos = StrToTokenize.find_first_of(Delimiters, LastPos);
  }
}


// =====================================================================
// =====================================================================


bool WildcardMatching(const std::string Pattern, const std::string Str)
{

  // source : http://www.codeproject.com/KB/string/wildcmp.aspx

  const char *cp = NULL;
  const char *mp = NULL;

  const char *StrToCheck = Str.c_str();
  const char *WildStr = Pattern.c_str();

  while ((*StrToCheck) && (*WildStr != '*'))
  {
    if ((*WildStr != *StrToCheck) && (*WildStr != '?'))
    {
      return false;
    }
    WildStr++;
    StrToCheck++;
  }

  while (*StrToCheck)
  {
    if (*WildStr == '*')
    {
      if (!*++WildStr)
      {
        return true;
      }
      mp = WildStr;
      cp = StrToCheck+1;
    }
    else
    {
      if ((*WildStr == *StrToCheck) || (*WildStr == '?'))
      {
        WildStr++;
        StrToCheck++;
      }
      else
      {
        WildStr = mp;
        StrToCheck = cp++;
      }
    }
  }

  while (*WildStr == '*')
  {
    WildStr++;
  }
  return !*WildStr;
}



// =====================================================================
// =====================================================================


std::vector<std::string> GetFilesByExt(const std::string DirToExplore, const std::string Ext, bool WithPath, bool ExtIncludeDot)
{

  std::vector<std::string> FileList;


  std::string FileExt = Ext;
  if (!ExtIncludeDot) FileExt = "."+Ext;

  boost::filesystem::path PathToExplore(DirToExplore);

  if (boost::filesystem::is_directory(PathToExplore))
  {

    boost::filesystem::directory_iterator it;

    std::string FoundFile;

    for (it = boost::filesystem::directory_iterator(PathToExplore);it != boost::filesystem::directory_iterator(); ++it)
    {

      // lists files with specified extension

      if (boost::filesystem::is_regular(it->status()) && boost::ends_with(it->path().string(),FileExt))
      {
        if (WithPath) FileList.push_back(it->path().string());
        else FileList.push_back(it->path().filename().string());
      }
    }
  }

  return FileList;

}



// =====================================================================
// =====================================================================


std::vector<std::string> GetFilesBySuffixAndExt(const std::string& DirToExplore,
                                                const std::string& Suffix,
                                                const std::string& Ext,
                                                bool WithPath,
                                                bool ExtIncludeDot)

{

  std::vector<std::string> FileList;


  std::string FileEnd = Suffix+Ext;
  if (!ExtIncludeDot) FileEnd = Suffix+"."+Ext;

  boost::filesystem::path PathToExplore(DirToExplore);

  if (boost::filesystem::is_directory(PathToExplore))
  {

    boost::filesystem::directory_iterator it;

    std::string FoundFile;

    for (it = boost::filesystem::directory_iterator(PathToExplore);it != boost::filesystem::directory_iterator(); ++it)
    {

      // lists files with specified extension

      if (boost::filesystem::is_regular(it->status()) && boost::ends_with(it->path().string(),FileEnd))
      {
        if (WithPath) FileList.push_back(it->path().string());
        else FileList.push_back(it->path().filename().string());
      }
    }
  }

  return FileList;
}


// =====================================================================
// =====================================================================


std::vector<std::string> SplitString(const std::string& StrToSplit,
                                     const std::string& Separators,
                                     bool ReturnsEmpty)
{
  std::vector<std::string> SplitParts;

  boost::algorithm::token_compress_mode_type TokCompress = boost::token_compress_on;
  if (ReturnsEmpty) TokCompress = boost::token_compress_off;

  boost::split(SplitParts, StrToSplit, boost::is_any_of(Separators),TokCompress);

  return SplitParts;
}


// =====================================================================
// =====================================================================

// TODO to be fixed: should not delete the given path, may not work on win32
bool EmptyDirectoryRecursively(const std::string DirPath)
{

  boost::filesystem::path PathToEmpty(DirPath);

  boost::filesystem::remove_all(PathToEmpty);

  return boost::filesystem::create_directory(PathToEmpty);

}


// =====================================================================
// =====================================================================


std::vector<std::string> getFilesRecursively(const std::string& DirPath)
{
  std::vector<std::string> FileNames;

  boost::filesystem::directory_iterator It;

  for (It = boost::filesystem::directory_iterator(DirPath); It != boost::filesystem::directory_iterator(); ++It)
  {
    // Regular file
    if (boost::filesystem::is_regular(It->status()))
      FileNames.push_back(DirPath + "/" + It->path().filename().string());

    // Directory
    if (boost::filesystem::is_directory(It->status()))
    {
      std::vector<std::string> SubDirFiles = getFilesRecursively(It->path().string());
      std::vector<std::string>::const_iterator It;

      for (It = SubDirFiles.begin(); It != SubDirFiles.end(); ++It)
        FileNames.push_back(*It);
    }
  }

  return FileNames;
}


// =====================================================================
// =====================================================================

std::string ReplaceEmptyString(std::string SourceStr, const std::string& ReplaceStr)
{
  if (SourceStr.empty()) SourceStr = ReplaceStr;
  return SourceStr;
}


// =====================================================================
// =====================================================================


std::string RemoveTrailingSlashes(std::string Str)
{
  std::string PathSep = "/";

#ifdef BOOST_WINDOWS_PATH
  PathSep = "\\";
#endif


  while (boost::ends_with(Str,PathSep))
  {
    boost::erase_last(Str,PathSep);
  }

  return Str;
}


// =====================================================================
// =====================================================================


void OutputToStream(std::vector<std::string> Strings, std::string Sep, std::ostream& OStream)
{
  for (unsigned int i=0; i< Strings.size(); i++) OStream << Strings[i] << Sep;
  OStream << std::endl;
}


// =====================================================================
// =====================================================================


void CopyDirectoryRecursively(const std::string SourceDir, const std::string IntoDir, const bool DontCopyDotDirs)
{

  boost::filesystem::path SourceDirPath(SourceDir);
  boost::filesystem::path IntoDirPath(IntoDir);
  boost::filesystem::path DestDirPath(IntoDir+"/"+SourceDirPath.filename().string());


  if (boost::filesystem::is_directory(DestDirPath)) boost::filesystem::remove_all(DestDirPath);

  boost::filesystem::create_directory(DestDirPath);

  boost::filesystem::directory_iterator it;

  for (it = boost::filesystem::directory_iterator(SourceDirPath);it != boost::filesystem::directory_iterator(); ++it)
  {

    if (boost::filesystem::is_regular(it->status()))
    {
      boost::filesystem::copy_file(it->path(),boost::filesystem::path(DestDirPath.string()+"/"+it->path().filename().string()));
    }

    if (boost::filesystem::is_directory(it->status()))
    {
      if (!DontCopyDotDirs || (DontCopyDotDirs && !boost::starts_with(it->path().filename().string(),".")))
      {
        CopyDirectoryRecursively(it->path().string(),DestDirPath.string(), DontCopyDotDirs);
      }
    }
  }
}


// =====================================================================
// =====================================================================


void CopyDirectoryContentsRecursively(const std::string SourceDir, const std::string IntoDir, const bool DontCopyDotDirs)
{

  boost::filesystem::path SourceDirPath(SourceDir);
  boost::filesystem::path IntoDirPath(IntoDir);

  if (boost::filesystem::is_directory(IntoDirPath)) boost::filesystem::remove_all(IntoDirPath);

  boost::filesystem::create_directory(IntoDirPath);

  boost::filesystem::directory_iterator it;

  for (it = boost::filesystem::directory_iterator(SourceDirPath);it != boost::filesystem::directory_iterator(); ++it)
  {

    if (boost::filesystem::is_regular(it->status()))
    {
      boost::filesystem::copy_file(it->path(),boost::filesystem::path(IntoDirPath.string()+"/"+it->path().filename().string()));
    }

    if (boost::filesystem::is_directory(it->status()))
    {
      if (!DontCopyDotDirs || (DontCopyDotDirs && !boost::starts_with(it->path().filename().string(),".")))
      {
        CopyDirectoryRecursively(it->path().string(),IntoDirPath.string(), DontCopyDotDirs);
      }
    }
  }
}


// =====================================================================
// =====================================================================


int CompareVersions(const std::string& VersionA, const std::string& VersionB, bool Strict)
{
  std::string LowCaseA(VersionA), LowCaseB(VersionB);

  boost::to_lower(LowCaseA);
  boost::to_lower(LowCaseB);


  if (LowCaseA == LowCaseB) return 0;


  std::vector<std::string> SplittedA, SplittedB;

  SplittedA = SplitString(LowCaseA,".~",false);

  SplittedB = SplitString(LowCaseB,".~",false);

  if ( !(SplittedA.size()==3 || SplittedA.size()==4) || !(SplittedB.size()==3 || SplittedB.size()==4))
    return -2;


  unsigned int MajorA, MinorA, PatchA, MajorB, MinorB, PatchB;
  std::string StatusA(""), StatusB("");

  if (SplittedA.size()==4) StatusA = SplittedA[3];
  if (SplittedB.size()==4) StatusB = SplittedB[3];

  if (ConvertString(SplittedA[0],&MajorA) && ConvertString(SplittedA[1],&MinorA) && ConvertString(SplittedA[2],&PatchA) &&
      ConvertString(SplittedB[0],&MajorB) && ConvertString(SplittedB[1],&MinorB) && ConvertString(SplittedB[2],&PatchB))
  {
    if (MajorA > MajorB) return 1;
    if (MajorA < MajorB) return -1;
    if (MajorA == MajorB)
    {
      if (MinorA > MinorB) return 1;
      if (MinorA < MinorB) return -1;
      if (MinorA == MinorB)
      {
        if (PatchA > PatchB) return 1;
        if (PatchA < PatchB) return -1;
        if (PatchA == PatchB)
        {
          if (!Strict) return 0;
          else
          {

            if (StatusA.empty() && StatusB.empty()) return 0;

            if (StatusA == StatusB) return 0;

            if (StatusA.empty() && !StatusB.empty()) return 1;
            if (!StatusA.empty() && StatusB.empty()) return -1;


            if (StatusA > StatusB) return 1;
            if (StatusA < StatusB) return -1;
          }
        }
      }
    }
  }

  return -2;
}


// =====================================================================
// =====================================================================


void Sleep(const unsigned int MSec)
{
#if WIN32
  Sleep(MSec);
#else
  usleep(MSec);
#endif
}

} } // namespaces
