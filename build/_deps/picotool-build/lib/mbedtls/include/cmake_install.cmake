# Install script for directory: C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/craig.hemingway/VisualCode_Workspace/NevadaNano_TestBed/build/_deps")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE MESSAGE_NEVER PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/aes.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/aesni.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/arc4.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/aria.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/asn1.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/asn1write.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/base64.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/bignum.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/blowfish.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/bn_mul.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/camellia.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ccm.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/certs.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/chacha20.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/chachapoly.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/check_config.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/cipher.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/cipher_internal.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/cmac.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/compat-1.3.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/config.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/config_psa.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/constant_time.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ctr_drbg.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/debug.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/des.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/dhm.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ecdh.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ecdsa.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ecjpake.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ecp.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ecp_internal.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/entropy.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/entropy_poll.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/error.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/gcm.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/havege.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/hkdf.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/hmac_drbg.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/md.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/md2.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/md4.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/md5.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/md_internal.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/net.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/net_sockets.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/nist_kw.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/oid.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/padlock.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/pem.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/pk.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/pk_internal.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/pkcs11.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/pkcs12.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/pkcs5.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/platform.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/platform_time.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/platform_util.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/poly1305.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/psa_util.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ripemd160.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/rsa.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/rsa_internal.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/sha1.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/sha256.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/sha512.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ssl.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ssl_cache.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ssl_cookie.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ssl_internal.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/ssl_ticket.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/threading.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/timing.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/version.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/x509.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/x509_crl.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/x509_crt.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/x509_csr.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/mbedtls/xtea.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE MESSAGE_NEVER PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_builtin_composites.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_builtin_primitives.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_compat.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_config.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_driver_common.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_extra.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_platform.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_se_driver.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_sizes.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_struct.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_types.h"
    "C:/VSARM/sdk/pico/pico-sdk/lib/mbedtls/include/psa/crypto_values.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/craig.hemingway/VisualCode_Workspace/NevadaNano_TestBed/build/_deps/picotool-build/lib/mbedtls/include/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
