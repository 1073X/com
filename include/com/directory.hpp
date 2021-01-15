#pragma once

#include <filesystem>

#include "fatal_error.hpp"
#include "strcat.hpp"

namespace miu::com {

class directory {
  public:
    template<typename... ARGS>
    directory(ARGS&&... args) {
        init(strcat(std::forward<ARGS>(args)..., strcat::delimiter { "/" }).str());
    }

    auto path() const { return _path; }

    template<typename... ARGS>
    auto make_file(ARGS&&... args) const {
        return do_make_file(com::strcat { std::forward<ARGS>(args)... }.str());
    }

    template<typename... ARGS>
    auto file_size(ARGS&&... args) const {
        auto file = make_file(std::forward<ARGS>(args)...);
        return std::filesystem::file_size(file);
    }

    template<typename... ARGS>
    auto exists(ARGS&&... args) const {
        auto file = make_file(std::forward<ARGS>(args)...);
        return std::filesystem::exists(file);
    }

    template<typename... ARGS>
    auto remove(ARGS&&... args) const {
        auto file = make_file(std::forward<ARGS>(args)...);
        return std::filesystem::remove(file);
    }

  private:
    void init(std::string_view);
    std::filesystem::path do_make_file(std::string_view) const;

  private:
    std::filesystem::path _path;
};

}    // namespace miu::com
