#pragma once

#include "beatsaber-hook/shared/utils/utils.h"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"

namespace BTDownloader {
    ModInfo& getModInfo();
    Logger& getLogger();
}

namespace BTDownloader::literals {
    inline Il2CppString* operator "" _cs(const char *cString, size_t length) {
        return il2cpp_utils::createcsstr(std::basic_string_view<char>(cString, length));
    }

    inline Il2CppString* operator "" _csP(const char *cString, size_t length) {
        return il2cpp_utils::createcsstr(std::basic_string_view<char>(cString, length), il2cpp_utils::StringType::Manual);
    }
}
