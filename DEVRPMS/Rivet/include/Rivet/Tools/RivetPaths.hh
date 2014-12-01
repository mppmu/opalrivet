// -*- C++ -*-
#ifndef RIVET_RivetPaths_HH
#define RIVET_RivetPaths_HH

namespace Rivet {


  /// Convenience function for determining if a filesystem path exists
  inline bool fileexists(const std::string& path) {
    return (access(path.c_str(), R_OK) == 0);
  }


  /// @name Installation directory paths
  //@{

  /// Get library install path
  std::string getLibPath();

  /// Get data install path
  std::string getDataPath();

  /// Get Rivet data install path
  std::string getRivetDataPath();

  //@}


  /// @name Analysis library search paths
  //@{

  /// Get Rivet analysis plugin library search paths
  std::vector<std::string> getAnalysisLibPaths();

  /// Set the Rivet analysis plugin library search paths
  void setAnalysisLibPaths(const std::vector<std::string>& paths);

  /// Set the Rivet analysis plugin library search paths
  void addAnalysisLibPath(const std::string& extrapath);

  /// @brief Find the first file of the given name in the analysis library search dirs
  /// @note If none found, returns an empty string
  std::string findAnalysisLibFile(const std::string& filename);

  //@}


  /// @name Analysis data/metadata paths and search functions
  //@{

  /// Get Rivet analysis reference data search paths
  std::vector<std::string> getAnalysisRefPaths();

  /// Set the Rivet Ref search paths
  void setAnalysisRefPaths(const std::vector<std::string>& paths);

  /// Set the Rivet analysis plugin library search paths
  void addAnalysisRefPath(const std::string& extrapath);

  /// @brief Find the first file of the given name in the ref data file search dirs
  /// @note If none found, returns an empty string
  std::string findAnalysisRefFile(const std::string& filename,
                                  const std::vector<std::string>& pathprepend=std::vector<std::string>(),
                                  const std::vector<std::string>& pathappend=std::vector<std::string>());

  /// Get Rivet analysis info metadata search paths
  std::vector<std::string> getAnalysisInfoPaths();

  /// Set the Rivet info search paths
  void setAnalysisInfoPaths(const std::vector<std::string>& paths);

  /// Set the Rivet analysis plugin library search paths
  void addAnalysisLibPath(const std::string& extrapath);

  /// @brief Find the first file of the given name in the analysis info file search dirs
  /// @note If none found, returns an empty string
  std::string findAnalysisInfoFile(const std::string& filename,
                                   const std::vector<std::string>& pathprepend=std::vector<std::string>(),
                                   const std::vector<std::string>& pathappend=std::vector<std::string>());

  /// Get Rivet analysis plot style search paths
  std::vector<std::string> getAnalysisPlotPaths();

  /// Set the Rivet Ref search paths
  void setAnalysisPlotPaths(const std::vector<std::string>& paths);

  /// Set the Rivet analysis plugin library search paths
  void addAnalysisPlotPath(const std::string& extrapath);

  /// @brief Find the first file of the given name in the analysis plot file search dirs
  /// @note If none found, returns an empty string
  std::string findAnalysisPlotFile(const std::string& filename,
                                   const std::vector<std::string>& pathprepend=std::vector<std::string>(),
                                   const std::vector<std::string>& pathappend=std::vector<std::string>());

  //@}


}

#endif
