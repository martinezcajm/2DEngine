#ifndef __NATIVE_DIALOGS_H__
#define __NATIVE_DIALOGS_H__ 1

#include <stdio.h>
#include <string.h>
#include "tinyfiledialogs.h"

class Native_dialogs{
 public:
  /** @Open a message box native
  *
  * Open a mesage box with the introduced message.
  *
  * @return void
  * @param title Title of the message box
  * @param message Message to write in the message box
  * @param type Type of message box, can be: "ok", "okcancel", "yesno" or
  *  "yesnocancel"
  * @param icon Icon to put in the message box, can be: "info" "warning" "error"
  *  or "question"
  * @param defaultButton Default button: 0 for cancel/no, 1 for ok/yes or 
     2 for no in yesnocancel
  */
  void messageBox(const char *title, const char *message, const char *type, 
    const char *icon, const int defaultButton);
  
  /** @Open a save file dialog
  *
  * Open a native dialog for save a file
  *
  * @return void
  * @param title Title of the dialog box. Can be NULL
  * @param defaultFile Put a default path and file to save. Can be NULL.
  * @param numOfFilterPatterns Number of posibles extensions to save. 
     By default 0
  * @param filterPatterns Pattern with the posible extensions to save. 
     i.e: {"*.jpg","*.png"}. Can be NULL
  * @param singleFilterDescription Singl description of the file type
  */
  const char *saveFileDialog(const char *title, const char *defaultFile, 
    const int numOfFilterPatterns, const char **filterPatterns, 
    const char *singleFilterDescription);

  /** @Open a open file dialog
  *
  * Open a native dialog for open a file
  *
  * @return void
  * @param title Title of the dialog box. Can be NULL
  * @param defaultFile Put a default path and file to open. Can be NULL.
  * @param numOfFilterPatterns Number of posibles extensions to open. 
     By default 0
  * @param filterPatterns Pattern with the posible extensions to open. 
     i.e: {"*.jpg","*.png"}. Can be NULL
  * @param singleFilterDescription Singl description of the file type
  */
  const char *openFileDialog(const char *title, const char *defaultFile, 
    const int numOfFilterPatterns, const char **filterPatterns, 
    const char *singleFilterDescription);
  
  /** @Open a select folder dialog
  *
  * Open a native dialog for select a folder
  *
  * @return void
  * @param title Title of the dialog box. Can be NULL
  * @param defaultPath Put a default path to open. Can be NULL.
  */
  const char *selectFolderDialog(const char *title, const char *defaultPath);
 private:
  const char * ret;
};
#endif