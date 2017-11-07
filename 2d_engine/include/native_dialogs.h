#ifndef __NATIVE_DIALOGS_H__
#define __NATIVE_DIALOGS_H__ 1

#include <stdio.h>
#include <string.h>
#include "tinyfiledialogs.h"

class Native_dialogs{
 public:
  void messageBox(const char *title, const char *message, const char *type, 
    const char *icon, const int defaultButton);
  
  const char *saveFileDialog(const char *title, const char *defaultFile, 
    const int numOfFilterPatterns, const char **filterPatterns, 
    const char *singleFilterDescription);

  const char *openFileDialog(const char *title, const char *defaultFile, 
    const int numOfFilterPatterns, const char **filterPatterns, 
    const char *singleFilterDescription);
  
  const char *selectFolderDialog(const char *title, const char *defaultPath);
};
#endif