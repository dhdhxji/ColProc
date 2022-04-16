#ifndef ERROR_H
#define ERROR_H

#include <string>

#define ERR_CHECK_NOT_NULL(arg, message) {if(arg==nullptr){spawnError(message);}}
#define ERR_ASSERT_TRUE(cond, message) {if( (cond) != true ){spawnError(message);}}
#define ERR_ASSERT_FALSE(cond, message) ERR_ASSERT_TRUE( !(cond), message )

void spawnError(const std::string& error_msg);

#endif // ERROR_H
