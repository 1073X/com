
#include "meta/info.hpp"

#include "com/strcat.hpp"

namespace miu::meta {

std::string info() {
    return com::strcat { "miu", category(), type(), name() }.str();
}

}    // namespace miu::meta
