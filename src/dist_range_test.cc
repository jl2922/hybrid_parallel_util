#include "dist_range.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "reducer.h"

TEST(DistRangeTest, MapReduceTest) {
  const int N_KEYS = 1000;
  hpmr::DistRange<int> range(0, N_KEYS);
  auto mapper = [](const int id, const std::function<void(const int, const bool)>& emit) {
    EXPECT_THAT(id, testing::Ge(0));
    EXPECT_THAT(id, testing::Lt(N_KEYS));
    emit(id, false);
  };
  range.mapreduce<int, bool>(mapper, hpmr::Reducer<bool>::keep, true);
  // auto dist_map = range.mapreduce<int, bool>(mapper, hpmr::Reducer<bool>::keep, true);
  // EXPECT_EQ(dist_map.get_n_keys(), N_KEYS);
}
