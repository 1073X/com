
#include "com/directory.hpp"

namespace fs = std::filesystem;

namespace miu::com {

void
directory::init(std::string_view raw) {
    if (!fs::is_directory(raw)) {
        fs::create_directories(raw);
    }
    _path = fs::canonical(fs::absolute(raw));
}

fs::path
directory::do_make_file(std::string_view filename) const {
    if (filename.empty()) {
        FATAL_ERROR("empty shmem file name");
    }
    return path() / filename;
}

}    // namespace miu::com
