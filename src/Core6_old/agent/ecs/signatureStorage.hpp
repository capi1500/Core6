/**
 * Core6
 * Copyright (C) 2020-2021 Kacper Chętkowski (kacper.chetkowski@gmail.com)
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it freely,
 * subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef CORE6_SIGNATURESTORAGE_HPP
#define CORE6_SIGNATURESTORAGE_HPP

#include <MPL/MPL.hpp>
#include <Core6/config.hpp>

namespace c6{
	namespace helper{
		template<concepts::Config TConfig>
		struct SignatureKey{
			using ECSConfig = typename TConfig::ECSConfig;
			using SignatureList = typename ECSConfig::SignatureList;
			using Key = typename ECSConfig::Key;
			
			using KeyStorage = MPL::Tuple<MPL::Repeat<ECSConfig::signatureCount(), Key>>;
			
			template<typename T>
			using IsComponentFilter = std::integral_constant<bool, ECSConfig::template isComponent<T>()>;
			template<typename T>
			using IsTagFilter = std::integral_constant<bool, ECSConfig::template isTag<T>()>;
			
			template<concepts::Signature<typename TConfig::ECSConfig> TSignature>
			using SignatureComponents = MPL::Filter<IsComponentFilter, TSignature>;
			template<concepts::Signature<typename TConfig::ECSConfig> TSignature>
			using SignatureTags = MPL::Filter<IsTagFilter, TSignature>;
		};
	}
	
	template <concepts::Config TConfig>
	class SignatureStorage{
			using Config = TConfig;
			using ECSConfig = typename Config::ECSConfig;
			using SignatureKey = typename helper::SignatureKey<Config>;
			using SignatureList = typename SignatureKey::SignatureList;
			using KeyStorage = typename SignatureKey::KeyStorage;
		private:
			KeyStorage m_storage;
			
			template<concepts::Signature<ECSConfig> T>
			void initializeKey() noexcept{
				auto& key = getSignatureKey<T>();
				
				using SignatureComponents = typename SignatureKey::template SignatureComponents<T>;
				using SignatureTags = typename SignatureKey::template SignatureTags<T>;
				
				MPL::forTypes<SignatureComponents>([this, &key](auto t){
					key[ECSConfig::template componentBit<MPL_TYPE(t)>()] = true;
				});
				
				MPL::forTypes<SignatureTags>([this, &key](auto t){
					key[ECSConfig::template tagBit<MPL_TYPE(t)>()] = true;
				});
			}
		
		public:
			template<concepts::Signature<ECSConfig> T>
			auto& getSignatureKey() noexcept{
				return std::get<ECSConfig::template signatureID<T>()>(m_storage);
			}
			
			template<concepts::Signature<ECSConfig> T>
			const auto& getSignatureKey() const noexcept{
				return std::get<ECSConfig::template signatureID<T>()>(m_storage);
			}
			
			SignatureStorage() noexcept{
				MPL::forTypes<SignatureList>([this](auto t){
					this->initializeKey<MPL_TYPE(t)>();
				});
			}
	};
}

#endif //CORE6_SIGNATURESTORAGE_HPP
