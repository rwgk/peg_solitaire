#include <array>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

namespace solvethis {

typedef unsigned long uint64;

const unsigned num_bits_2 = 21;
const uint64 situations_2[3] = {1024, 273, 2096127};
const uint64 center_one_situation_2 = 0x1U << 10;

const uint64 group_symmetry_masks_2[] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384,
    32768, 65536, 131072, 262144, 524288, 1048576,
    4, 2, 1, 128, 64, 32, 16, 8, 4096, 2048, 1024, 512, 256, 131072, 65536,
    32768, 16384, 8192, 1048576, 524288, 262144,
    8, 256, 8192, 1, 16, 512, 16384, 262144, 2, 32, 1024, 32768, 524288, 4,
    64, 2048, 65536, 1048576, 128, 4096, 131072,
    8192, 256, 8, 262144, 16384, 512, 16, 1, 524288, 32768, 1024, 32, 2,
    1048576, 65536, 2048, 64, 4, 131072, 4096, 128,
    128, 4096, 131072, 4, 64, 2048, 65536, 1048576, 2, 32, 1024, 32768,
    524288, 1, 16, 512, 16384, 262144, 8, 256, 8192,
    131072, 4096, 128, 1048576, 65536, 2048, 64, 4, 524288, 32768, 1024, 32,
    2, 262144, 16384, 512, 16, 1, 8192, 256, 8,
    262144, 524288, 1048576, 8192, 16384, 32768, 65536, 131072, 256, 512,
    1024, 2048, 4096, 8, 16, 32, 64, 128, 1, 2, 4,
    1048576, 524288, 262144, 131072, 65536, 32768, 16384, 8192, 4096, 2048,
    1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1,
};

const uint64 moves_2[44][3] = {
    {1, 16, 512},
    {1, 2, 4},
    {2, 32, 1024},
    {4, 64, 2048},
    {4, 2, 1},
    {8, 256, 8192},
    {8, 16, 32},
    {16, 512, 16384},
    {16, 32, 64},
    {32, 1024, 32768},
    {32, 16, 8},
    {32, 64, 128},
    {64, 2048, 65536},
    {64, 32, 16},
    {128, 4096, 131072},
    {128, 64, 32},
    {256, 512, 1024},
    {512, 16, 1},
    {512, 16384, 262144},
    {512, 1024, 2048},
    {1024, 32, 2},
    {1024, 32768, 524288},
    {1024, 512, 256},
    {1024, 2048, 4096},
    {2048, 64, 4},
    {2048, 65536, 1048576},
    {2048, 1024, 512},
    {4096, 2048, 1024},
    {8192, 256, 8},
    {8192, 16384, 32768},
    {16384, 512, 16},
    {16384, 32768, 65536},
    {32768, 1024, 32},
    {32768, 16384, 8192},
    {32768, 65536, 131072},
    {65536, 2048, 64},
    {65536, 32768, 16384},
    {131072, 4096, 128},
    {131072, 65536, 32768},
    {262144, 16384, 512},
    {262144, 524288, 1048576},
    {524288, 32768, 1024},
    {1048576, 65536, 2048},
    {1048576, 524288, 262144},
};

const unsigned num_bits_3 = 33;
const uint64 situations_3[3] = {65536, 16648, 8589869055};
const uint64 center_one_situation_3 = 0x1U << 16;

const uint64 group_symmetry_masks_3[] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768,
    65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216,
    33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648,
    4294967296,
    4, 2, 1, 32, 16, 8, 4096, 2048, 1024, 512, 256, 128, 64, 524288, 262144,
    131072, 65536, 32768, 16384, 8192, 67108864, 33554432, 16777216, 8388608,
    4194304, 2097152, 1048576, 536870912, 268435456, 134217728, 4294967296,
    2147483648, 1073741824,
    64, 8192, 1048576, 128, 16384, 2097152, 1, 8, 256, 32768, 4194304,
    134217728, 1073741824, 2, 16, 512, 65536, 8388608, 268435456, 2147483648, 4,
    32, 1024, 131072, 16777216, 536870912, 4294967296, 2048, 262144, 33554432,
    4096, 524288, 67108864,
    1048576, 8192, 64, 2097152, 16384, 128, 1073741824, 134217728, 4194304,
    32768, 256, 8, 1, 2147483648, 268435456, 8388608, 65536, 512, 16, 2,
    4294967296, 536870912, 16777216, 131072, 1024, 32, 4, 33554432, 262144,
    2048, 67108864, 524288, 4096,
    4096, 524288, 67108864, 2048, 262144, 33554432, 4, 32, 1024, 131072,
    16777216, 536870912, 4294967296, 2, 16, 512, 65536, 8388608, 268435456,
    2147483648, 1, 8, 256, 32768, 4194304, 134217728, 1073741824, 128, 16384,
    2097152, 64, 8192, 1048576,
    67108864, 524288, 4096, 33554432, 262144, 2048, 4294967296, 536870912,
    16777216, 131072, 1024, 32, 4, 2147483648, 268435456, 8388608, 65536, 512,
    16, 2, 1073741824, 134217728, 4194304, 32768, 256, 8, 1, 2097152, 16384,
    128, 1048576, 8192, 64,
    1073741824, 2147483648, 4294967296, 134217728, 268435456, 536870912,
    1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 8192,
    16384, 32768, 65536, 131072, 262144, 524288, 64, 128, 256, 512, 1024, 2048,
    4096, 8, 16, 32, 1, 2, 4,
    4294967296, 2147483648, 1073741824, 536870912, 268435456, 134217728,
    67108864, 33554432, 16777216, 8388608, 4194304, 2097152, 1048576, 524288,
    262144, 131072, 65536, 32768, 16384, 8192, 4096, 2048, 1024, 512, 256, 128,
    64, 32, 16, 8, 4, 2, 1,
};

const uint64 moves_3[76][3] = {
    {1, 8, 256},
    {1, 2, 4},
    {2, 16, 512},
    {4, 32, 1024},
    {4, 2, 1},
    {8, 256, 32768},
    {8, 16, 32},
    {16, 512, 65536},
    {32, 1024, 131072},
    {32, 16, 8},
    {64, 8192, 1048576},
    {64, 128, 256},
    {128, 16384, 2097152},
    {128, 256, 512},
    {256, 8, 1},
    {256, 32768, 4194304},
    {256, 128, 64},
    {256, 512, 1024},
    {512, 16, 2},
    {512, 65536, 8388608},
    {512, 256, 128},
    {512, 1024, 2048},
    {1024, 32, 4},
    {1024, 131072, 16777216},
    {1024, 512, 256},
    {1024, 2048, 4096},
    {2048, 262144, 33554432},
    {2048, 1024, 512},
    {4096, 524288, 67108864},
    {4096, 2048, 1024},
    {8192, 16384, 32768},
    {16384, 32768, 65536},
    {32768, 256, 8},
    {32768, 4194304, 134217728},
    {32768, 16384, 8192},
    {32768, 65536, 131072},
    {65536, 512, 16},
    {65536, 8388608, 268435456},
    {65536, 32768, 16384},
    {65536, 131072, 262144},
    {131072, 1024, 32},
    {131072, 16777216, 536870912},
    {131072, 65536, 32768},
    {131072, 262144, 524288},
    {262144, 131072, 65536},
    {524288, 262144, 131072},
    {1048576, 8192, 64},
    {1048576, 2097152, 4194304},
    {2097152, 16384, 128},
    {2097152, 4194304, 8388608},
    {4194304, 32768, 256},
    {4194304, 134217728, 1073741824},
    {4194304, 2097152, 1048576},
    {4194304, 8388608, 16777216},
    {8388608, 65536, 512},
    {8388608, 268435456, 2147483648},
    {8388608, 4194304, 2097152},
    {8388608, 16777216, 33554432},
    {16777216, 131072, 1024},
    {16777216, 536870912, 4294967296},
    {16777216, 8388608, 4194304},
    {16777216, 33554432, 67108864},
    {33554432, 262144, 2048},
    {33554432, 16777216, 8388608},
    {67108864, 524288, 4096},
    {67108864, 33554432, 16777216},
    {134217728, 4194304, 32768},
    {134217728, 268435456, 536870912},
    {268435456, 8388608, 65536},
    {536870912, 16777216, 131072},
    {536870912, 268435456, 134217728},
    {1073741824, 134217728, 4194304},
    {1073741824, 2147483648, 4294967296},
    {2147483648, 268435456, 8388608},
    {4294967296, 536870912, 16777216},
    {4294967296, 2147483648, 1073741824},
};

uint64 apply_symmetry_masks(const std::vector<uint64>& symmetry_masks,
                            uint64 situation) {
  uint64 out = 0x0U;
  uint64 bit = 0x1U;
  for (uint64 mask : symmetry_masks) {
    if (situation & mask) out |= bit;
    bit <<= 1;
  }
  return out;
}

uint64 move_apply(const std::array<uint64, 3>& move, uint64 situation) {
  uint64 on1 = move[0];
  uint64 on2 = move[1];
  uint64 off = move[2];
  if (!(situation & on1)) return 0;
  if (!(situation & on2)) return 0;
  if (situation & off) return 0;
  return (situation & ~(on1 | on2)) | off;
}

bool had_symmetry_equivalent_situation(
    unsigned radius,
    const std::vector<std::vector<uint64>>& group_symmetry_masks,
    uint64 situation,
    std::unordered_set<uint64>* lexmins) {
  uint64 lexmin_situation = situation;
  for (const std::vector<uint64>& symmetry_masks : group_symmetry_masks) {
    uint64 equiv_situation = apply_symmetry_masks(symmetry_masks, situation);
    if (lexmin_situation > equiv_situation) {
      lexmin_situation = equiv_situation;
    }
  }
  bool result = (lexmins->find(lexmin_situation) != lexmins->end());
  if (!result) {
    lexmins->insert(lexmin_situation);
  }
  return result;
}

unsigned get_num_bits_set(uint64 bits) {
  unsigned result = 0;
  while (bits) {
    if (bits & 0x1U) {
      result++;
    }
    bits >>= 1;
  }
  return result;
}

void continue_play(
    const unsigned radius,
    const unsigned cutoff,
    const std::vector<std::vector<uint64>>& group_symmetry_masks,
    const std::vector<std::array<uint64, 3>>& moves,
    std::vector<std::unordered_set<uint64>>* all_lexmins,
    const uint64 situation,
    std::vector<unsigned>* path,
    std::vector<uint64>* pruning_counts,
    const uint64 center_one_situation)
{
  if (cutoff && path->size() == cutoff) {
    return;
  }
  std::unordered_set<uint64>* lexmins = &((*all_lexmins)[path->size()]);
  unsigned num_moves = 0;
  unsigned num_pruned = 0;
  for (unsigned imove = 0; imove < moves.size(); imove++) {
    uint64 next_situation = move_apply(moves[imove], situation);
    if (next_situation) {
      if (had_symmetry_equivalent_situation(
              radius, group_symmetry_masks, next_situation, lexmins)) {
        num_pruned++;
      } else {
        num_moves++;
        path->push_back(imove);
        continue_play(radius, cutoff, group_symmetry_masks, moves, all_lexmins,
                      next_situation, path, pruning_counts,
                      center_one_situation);
        path->pop_back();
      }
    }
  }
  (*pruning_counts)[path->size()] += num_pruned;
  if (num_moves + num_pruned == 0) {
    unsigned num_bits_set = get_num_bits_set(situation);
    if (num_bits_set == 1) {
      if (situation == center_one_situation) {
        std::cout << "CENTER ONE";
      } else {
        std::cout << "SOME ONE";
      }
      for (unsigned imove : *path) {
        std::cout << " " << imove;
      }
      std::cout << std::endl;
    }
  }
}

void copy_group_symmetry_masks(
    const uint64* source, unsigned size_i, unsigned size_j,
    std::vector<std::vector<uint64>>* target) {
  target->resize(size_i);
  for (unsigned i = 0; i < size_i; i++) {
    (*target)[i].reserve(size_j);
    for (unsigned j = 0; j < size_j; j++) {
      (*target)[i].push_back(source[i * size_j + j]);
    }
  }
}

void copy_moves(
    const uint64 source[][3], unsigned size_i,
    std::vector<std::array<uint64, 3>>* target) {
  target->resize(size_i);
  for (unsigned i = 0; i < size_i; i++) {
    for (unsigned j = 0; j < 3; j++) {
      (*target)[i][j] = source[i][j];
    }
  }
}

void run(unsigned radius, unsigned isituation, unsigned cutoff) {
  unsigned num_bits;
  uint64 situation;
  uint64 center_one_situation;
  std::vector<std::vector<uint64>> group_symmetry_masks;
  std::vector<std::array<uint64, 3>> moves;

  if (radius == 2) {
    num_bits = num_bits_2;
    situation = situations_2[isituation];
    center_one_situation = center_one_situation_2;
    copy_group_symmetry_masks(group_symmetry_masks_2, 8, num_bits,
                              &group_symmetry_masks);
    copy_moves(moves_2, 44, &moves);
  } else {
    num_bits = num_bits_3;
    situation = situations_3[isituation];
    center_one_situation = center_one_situation_3;
    copy_group_symmetry_masks(group_symmetry_masks_3, 8, num_bits,
                              &group_symmetry_masks);
    copy_moves(moves_3, 76, &moves);
  }

  std::vector<std::unordered_set<uint64>> all_lexmins(num_bits - 1);
  std::vector<uint64> pruning_counts(num_bits - 1);
  std::vector<unsigned> path;
  path.reserve(num_bits - 1);
  continue_play(radius, cutoff, group_symmetry_masks, moves, &all_lexmins,
                situation, &path, &pruning_counts, center_one_situation);
  for (unsigned len_path = 0; len_path < num_bits - 1; len_path++) {
    std::cout << len_path << " " << all_lexmins[len_path].size() << " "
        << pruning_counts[len_path] << std::endl;
  }
}

}  // namespace solvethis

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "missing required arguments: radius isituation cutoff"
        << std::endl;
    return 1;
  }
  unsigned radius = std::atoi(argv[1]);
  unsigned isituation = std::atoi(argv[2]);
  unsigned cutoff = std::atoi(argv[3]);
  solvethis::run(radius, isituation, cutoff);
  return 0;
}
