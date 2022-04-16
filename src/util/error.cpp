#include "colproc/util/error.hpp"
#include <stdexcept>


void spawnError(const std::string& error_msg)
{
    throw std::runtime_error(error_msg);
}