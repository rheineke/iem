project(iemlib)

# Ordering may matter
include_directories(json)
add_subdirectory(json)

include_directories(iem)
add_subdirectory(iem)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} iem)
add_library(iemlib
        jsoncpp.cpp
        iem/contract.hpp iem/contract.cpp
        iem/executedorder.hpp iem/executedorder.cpp
        iem/logger.hpp iem/logger.cpp
        iem/order.hpp iem/order.cpp
        iem/orderbook.hpp iem/orderbook.cpp
        iem/price.hpp iem/price.cpp
        iem/pricetimelimit.hpp iem/pricetimelimit.cpp
        iem/session.hpp iem/session.cpp
        iem/side.hpp iem/side.cpp)

# target_include_directories(iemlib PUBLIC ${OPENSSL_INCLUDE_DIRS})
# target_include_directories(iemlib PUBLIC ${Boost_INCLUDE_DIRS})
# target_include_directories(iemlib PUBLIC ${CPPNETLIB_INCLUDE_DIRS})