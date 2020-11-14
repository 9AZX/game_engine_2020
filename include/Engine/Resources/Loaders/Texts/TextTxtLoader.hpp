#ifndef ENGINE_RESOURCES_LOADERS_TEXTS_TEXT_TXT_LOADER_HPP_
#define ENGINE_RESOURCES_LOADERS_TEXTS_TEXT_TXT_LOADER_HPP_

#include "Engine/Resources/IResourceLoader.hpp"

namespace Engine {

class TextTxtLoader: public IResourceLoader {
    public:
        std::unique_ptr<Resource> load(
            const ResourceDescriptor & descriptor
        ) noexcept override;
}; /* class TextTxtLoader */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_LOADERS_TEXTS_TEXT_TXT_LOADER_HPP_ */
