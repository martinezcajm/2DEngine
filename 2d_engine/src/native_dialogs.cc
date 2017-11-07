#include "native_dialogs.h"

void Native_dialogs::messageBox(const char *title, const char *message, 
  const char *type, const char *icon, const int defaultButton){
      
  tinyfd_messageBox(title, message, type, icon, defaultButton);
}

/*
filterPatterns: NULL or {"*.jpg", "*.txt, "*.scene""}
*/
const char *Native_dialogs::saveFileDialog(const char *title, 
    const char *defaultFile, const int numOfFilterPatterns, 
    const char **filterPatterns, const char *singleFilterDescription){
      
  return tinyfd_saveFileDialog(title, defaultFile, numOfFilterPatterns, 
    filterPatterns, singleFilterDescription);
}

const char *Native_dialogs::openFileDialog(const char *title, 
    const char *defaultFile, const int numOfFilterPatterns, 
    const char **filterPatterns, const char *singleFilterDescription){
      
  return tinyfd_openFileDialog(title, defaultFile, numOfFilterPatterns, 
    filterPatterns, singleFilterDescription, 0);
}

const char *Native_dialogs::selectFolderDialog(const char *title, 
    const char *defaultPath){    
  return tinyfd_selectFolderDialog(title, defaultPath);
}