#ifndef KTP_ASSETS_PATH_HPP_
#define KTP_ASSETS_PATH_HPP_

#include <string>

namespace ktp { namespace Assets {

/**
 * @brief Gets the path to the assets directory.
 * @param sub_dir Specify a sub directory, ie. textures.
 * @return The full path to the assets directory (and subdirectory if instructed).
 */
std::string getAssetsPath(const std::string& sub_dir = "");

} /* assets */ } // ktp

#endif
