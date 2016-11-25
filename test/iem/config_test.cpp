// Copyright 2016 Reece Heineke<reece.heineke@gmail.com>
#include "iem/config.hpp"

#include "gtest/gtest.h"

namespace iem {

TEST(ConfigTest, ReadJson) {
  EXPECT_NO_THROW(read_markets_json());
}

TEST(ConfigTest, MarketValue) {
  const auto& root = read_markets_json();
  for (const auto& market_name : root.getMemberNames()) {
    EXPECT_FALSE(market_value(root, market_name).isNull());
  }
}

TEST(ConfigTest, BundleValue) {
  const auto& root = read_markets_json();
  for (const auto& market_name : root.getMemberNames()) {
    // Non-const return value will insert a null value for "bundle"
    const auto& bundle_val = root[market_name]["bundle"];
    if (bundle_val["bundle_id"].isNull()) {  // Market has multiple bundles
      for (const auto& bundle_name : bundle_val.getMemberNames()) {
        EXPECT_FALSE(bundle_value(root, market_name, bundle_name).isNull());
      }
    } else {  // Market has one bundle
      EXPECT_FALSE(bundle_value(root, market_name, "").isNull());
    }
  }
}

TEST(ConfigTest, AssetValue) {
  const auto& root = read_markets_json();
  for (const auto& market_name : root.getMemberNames()) {
    // Non-const return value will insert a null value for "bundle"
    const auto& bundles_val = root[market_name]["bundle"];
    if (bundles_val["bundle_id"].isNull()) {  // Market has multiple bundles
      for (const auto& bundle_val : bundles_val) {
        const auto& assets_val = bundle_val["assets"];
        for (const auto& asset_name : assets_val.getMemberNames()) {
          EXPECT_FALSE(asset_value(root, market_name, asset_name).isNull());
        }
      }
    } else {  // Market has one bundle
      const auto& assets_val = bundles_val["assets"];
      for (const auto& asset_name : assets_val.getMemberNames()) {
        EXPECT_FALSE(asset_value(root, market_name, asset_name).isNull());
      }
    }
  }
}

}  // namespace iem