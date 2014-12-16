#ifndef GLOBAL_H
#define GLOBAL_H

//#define QTRC_DEBUG

//Define app name for config files/folders
#define APP_NAME "qtrc"

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

enum RC_POSITION_MODE {
    RC_CURSOR,
    RC_RANDOM,
    RC_CENTER
};

/*TODO:
 * Save configuration in a config file
 * Make phasetimer configurable (?maybe base it on the user's past usage?)
 * Make UI a bit prettier?
*/

#endif // GLOBAL_H
