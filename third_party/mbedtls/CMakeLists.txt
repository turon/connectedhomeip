#
#
#    Copyright (c) 2020 Project CHIP Authors
#
#    Licensed under the Apache License, Version 2.0 (the License);
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an AS IS BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

#
#    Description:
#      This file is the CMake template for the mbedtls library.
#

add_library(mbedtls)

set(COMMON_INCLUDES
    ${PROJECT_SOURCE_DIR}/third_party/mbedtls/repo/include
)

set(COMMON_SOURCES
    repo/library/aes.c
    repo/library/aesni.c
    repo/library/arc4.c
    repo/library/aria.c
    repo/library/asn1parse.c
    repo/library/asn1write.c
    repo/library/base64.c
    repo/library/bignum.c
    repo/library/blowfish.c
    repo/library/camellia.c
    repo/library/ccm.c
    repo/library/certs.c
    repo/library/chacha20.c
    repo/library/chachapoly.c
    repo/library/cipher.c
    repo/library/cipher_wrap.c
    repo/library/cmac.c
    repo/library/ctr_drbg.c
    repo/library/debug.c
    repo/library/des.c
    repo/library/dhm.c
    repo/library/ecdh.c
    repo/library/ecdsa.c
    repo/library/ecjpake.c
    repo/library/ecp.c
    repo/library/ecp_curves.c
    repo/library/entropy.c
    repo/library/entropy_poll.c
    repo/library/error.c
    repo/library/gcm.c
    repo/library/havege.c
    repo/library/hkdf.c
    repo/library/hmac_drbg.c
    repo/library/md.c
    repo/library/md2.c
    repo/library/md4.c
    repo/library/md5.c
    repo/library/memory_buffer_alloc.c
    repo/library/net_sockets.c
    repo/library/nist_kw.c
    repo/library/oid.c
    repo/library/padlock.c
    repo/library/pem.c
    repo/library/pk.c
    repo/library/pk_wrap.c
    repo/library/pkcs11.c
    repo/library/pkcs12.c
    repo/library/pkcs5.c
    repo/library/pkparse.c
    repo/library/pkwrite.c
    repo/library/platform.c
    repo/library/platform_util.c
    repo/library/poly1305.c
    repo/library/psa_crypto.c
    repo/library/psa_crypto_driver_wrappers.c
    repo/library/psa_crypto_se.c
    repo/library/psa_crypto_slot_management.c
    repo/library/psa_crypto_storage.c
    repo/library/psa_its_file.c
    repo/library/ripemd160.c
    repo/library/rsa.c
    repo/library/rsa_internal.c
    repo/library/sha1.c
    repo/library/sha256.c
    repo/library/sha512.c
    repo/library/ssl_cache.c
    repo/library/ssl_ciphersuites.c
    repo/library/ssl_cli.c
    repo/library/ssl_cookie.c
    repo/library/ssl_msg.c
    repo/library/ssl_srv.c
    repo/library/ssl_ticket.c
    repo/library/ssl_tls.c
    repo/library/ssl_tls13_keys.c
    repo/library/threading.c
    repo/library/timing.c
    repo/library/version.c
    repo/library/version_features.c
    repo/library/x509.c
    repo/library/x509_create.c
    repo/library/x509_crl.c
    repo/library/x509_crt.c
    repo/library/x509_csr.c
    repo/library/x509write_crt.c
    repo/library/x509write_csr.c
    repo/library/xtea.c
)

if (CHIP_TARGET_STYLE_UNIX)
set(COMMON_SOURCES
    ${COMMON_SOURCES}
    repo/library/timing.c
)
endif ()

target_compile_definitions(mbedtls PRIVATE)
target_include_directories(mbedtls PUBLIC ${COMMON_INCLUDES})
target_sources(mbedtls PRIVATE ${COMMON_SOURCES})

target_link_libraries(mbedtls PUBLIC chip-config)
