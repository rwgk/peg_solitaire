import sys

import scitbx_matrix as matrix


def multiply_into_group(group, mx):
  if mx in group:
    return
  group.add(mx)
  mx = matrix.sqr(mx)
  for mg in list(group):
    multiply_into_group(group, (matrix.sqr(mg) * mx).elems)


def get_ipacked_2(i, j):
  i1d = (i + 2) * 5 + (j + 2)
  No = None
  return [
      No,  0,  1,  2, No,
       3,  4,  5,  6,  7,
       8,  9, 10, 11, 12,
      13, 14, 15, 16, 17,
      No, 18, 19, 20, No][i1d]


def get_ipacked_3(i, j):
  i1d = (i + 3) * 7 + (j + 3)
  No = None
  return [
      No, No,  0,  1,  2, No, No,
      No, No,  3,  4,  5, No, No,
       6,  7,  8,  9, 10, 11, 12,
      13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26,
      No, No, 27, 28, 29, No, No,
      No, No, 30, 31, 32, No, No][i1d]


def get_ipacked(radius, i, j):
  if radius == 2:
    return get_ipacked_2(i, j)
  if radius == 3:
    return get_ipacked_3(i, j)
  raise RuntimeError('Invalid radius=%s' % radius)


def get_ipacked_bounds(radius, i, j):
  if (-radius > i or i > radius or
      -radius > j or j > radius):
    return None
  return get_ipacked(radius, i, j)


def build_ij_lookup_table(radius):
  table = []
  for i in xrange(-radius, radius + 1):
    for j in xrange(-radius, radius + 1):
      ipacked = get_ipacked(radius, i, j)
      if ipacked is not None:
        table.append((i, j))
  return tuple(table)


def get_ipacked_from_bit(bits):
  assert bits
  ipacked = 0
  while not bits & 0x1:
    ipacked += 1
    bits >>= 1
  return ipacked


def format_game(radius, bits, prev_bits):
  lines = []
  bit = 1
  for i in xrange(-radius, radius + 1):
    row = []
    for j in xrange(-radius, radius + 1):
      ipacked = get_ipacked(radius, i, j)
      if ipacked is None:
        symbol = ' '
      else:
        if bits & bit:
          if prev_bits is None or prev_bits & bit:
            symbol = 'x'
          else:
            symbol = '*'
        else:
          if prev_bits is not None and prev_bits & bit:
            symbol = 'O'
          else:
            symbol = 'o'
        bit <<= 1
      row.append(symbol)
    lines.append(''.join(row))
  return lines


def show_game(radius, bits):
  lines = format_game(radius, bits, None)
  print '\n'.join([line.rstrip() for line in lines])
  sys.stdout.flush()


def apply_symmetry_masks(symmetry_masks, situation):
  out = 0
  bit = 1
  for mask in symmetry_masks:
    if situation & mask:
      out |= bit
    bit <<= 1
  return out


def show_equiv_games(radius, situation, prev_situation, group_symmetry_masks):
  unique_situations = set()
  boards = []
  for symmetry_masks in group_symmetry_masks:
    equiv_situation = apply_symmetry_masks(symmetry_masks, situation)
    if equiv_situation in unique_situations:
      continue
    unique_situations.add(equiv_situation)
    boards.append(format_game(radius,
                              equiv_situation,
                              prev_situation if not boards else None))
  print 'Order', len(boards)
  for row_of_lines in zip(*boards):
    print '   '.join(row_of_lines).rstrip()
  sys.stdout.flush()


class move(object):

  def __init__(self, fingerprint):
    self.fingerprint = fingerprint

  def __repr__(self):
    return 'move((%d, %d, %d))' % tuple([
        get_ipacked_from_bit(bits) for bits in self.fingerprint])

  def apply(self, situation):
    on1, on2, off = self.fingerprint
    if not situation & on1:
      return None
    if not situation & on2:
      return None
    if situation & off:
      return None
    return (situation & ~(on1 | on2)) | off


def build_moves(radius):
  moves = []
  for ix in xrange(-radius, radius + 1):
    for iy in xrange(-radius, radius + 1):
      ipacked = get_ipacked(radius, ix, iy)
      if ipacked is None:
        continue
      for sx, sy in ((-1, 0), (1, 0), (0, -1), (0, 1)):
        jx = ix + sx
        jy = iy + sy
        jpacked = get_ipacked_bounds(radius, jx, jy)
        if jpacked is None:
          continue
        kx = jx + sx
        ky = jy + sy
        kpacked = get_ipacked_bounds(radius, kx, ky)
        if kpacked is None:
          continue
        moves.append(move((0x1 << ipacked, 0x1 << jpacked, 0x1 << kpacked)))
  return moves


def had_symmetry_equivalent_situation(radius, group_symmetry_masks, situation,
                                      lexmins):
  debug = False
  if debug:
    print 'situation as given'
    show_game(radius, situation)
    print '^' * (2 * radius + 1)
  lexmin_situation = situation
  for symmetry_masks in group_symmetry_masks:
    equiv_situation = apply_symmetry_masks(symmetry_masks, situation)
    if debug:
      show_game(radius, equiv_situation)
      print '~' * (2 * radius + 1)
    if lexmin_situation > equiv_situation:
      lexmin_situation = equiv_situation
  if debug:
    print
    sys.stdout.flush()
  result = lexmin_situation in lexmins
  if not result:
    lexmins.add(lexmin_situation)
  return result


def get_num_bits_set(bits):
  result = 0
  while bits:
    if bits & 0x1:
      result += 1
    bits >>= 1
  return result


def continue_play(radius, cutoff, group_symmetry_masks, moves, all_lexmins,
                  situation, path, pruning_counts):
  if cutoff and len(path) == cutoff:
    return
  lexmins = all_lexmins[len(path)]
  num_moves = 0
  num_pruned = 0
  for imove, move in enumerate(moves):
    next_situation = move.apply(situation)
    if next_situation is not None:
      if had_symmetry_equivalent_situation(
          radius, group_symmetry_masks, next_situation, lexmins):
        num_pruned += 1
      else:
        num_moves += 1
        path.append(imove)
        continue_play(radius, cutoff, group_symmetry_masks, moves, all_lexmins,
                      next_situation, path, pruning_counts)
        path.pop()
  pruning_counts[len(path)] += num_pruned
  if num_moves + num_pruned == 0:
    num_bits_set = get_num_bits_set(situation)
    if num_bits_set == 1:
      if situation == 0x1 << get_ipacked(radius, 0, 0):
        print 'CENTER ONE',
      else:
        print 'SOME ONE',
      for imove in path:
        print imove,
      print
      sys.stdout.flush()


def run(args):
  assert len(args) == 3, 'radius isituation cutoff'
  radius = int(args[0])
  isituation = int(args[1])
  cutoff = int(args[2])

  group_symmetry_masks = []
  r90 = (0, -1, 1, 0)
  mx = (-1, 0, 0, 1)
  group = set()
  multiply_into_group(group, r90)
  multiply_into_group(group, mx)
  ij_lookup_table = build_ij_lookup_table(radius)
  num_bits = len(ij_lookup_table)
  for mx in reversed(sorted(group)):
    mx = matrix.sqr(mx)
    symmetry_masks = [None] * num_bits
    a = 0
    for i in xrange(-radius, radius + 1):
      for j in xrange(-radius, radius + 1):
        p = matrix.col((i, j))
        q = mx * p
        b = get_ipacked(radius, *q.elems)
        if b is not None:
          assert ij_lookup_table[a] == p.elems
          assert ij_lookup_table[b] == q.elems
          symmetry_masks[b] = (0x1 << a)
          a += 1
    assert None not in symmetry_masks
    for a in xrange(num_bits):
      p = mx * matrix.col(ij_lookup_table[a])
      b = get_ipacked(radius, *p.elems)
      assert apply_symmetry_masks(symmetry_masks, (0x1 << a)) == (0x1 << b)
    group_symmetry_masks.append(tuple(symmetry_masks))
  group_symmetry_masks = tuple(group_symmetry_masks)
  assert len(group_symmetry_masks) == 8

  for ipacked in xrange(num_bits):
    assert get_ipacked_from_bit(0x1 << ipacked) == ipacked

  moves = build_moves(radius)
  center_bit = 0x1 << get_ipacked(radius, 0, 0)
  situations = (
      center_bit,
      (0x1 << get_ipacked(radius,  0, -2) |
       0x1 << get_ipacked(radius, -2, -1) |
       0x1 << get_ipacked(radius, -1, -1)),
      ~center_bit & ((0x1 << num_bits) - 1),
      (0x1 << get_ipacked(radius, -3, -1) |
       0x1 << get_ipacked(radius,  1, -3) |
       0x1 << get_ipacked(radius,  3,  1) |
       0x1 << get_ipacked(radius, -1,  3)),
  )

  print 'Constants for dfs_core.cc:'
  print num_bits
  print situations
  print get_ipacked(radius, 0, 0);
  for symmetry_mask in group_symmetry_masks:
    print symmetry_mask
  for move in moves:
    print move.fingerprint
  print

  situation = situations[isituation]
  show_game(radius, situation)
  print
  show_equiv_games(radius, situation, None, group_symmetry_masks)

  if cutoff >= 100:
    imoves = (7, 13, 0, 4, 20, 11, 22, 29, 32, 0, 30, 32, 40, 3, 45, 40, 66,
              47, 50, 5, 35, 58, 8, 65, 57, 74, 41, 72, 74, 63, 68)
    if cutoff > 100:
      imoves = imoves[:-1] + (55,)
    print
    for imove in imoves:
      move = moves[imove]
      next_situation = move.apply(situation)
      show_equiv_games(radius, next_situation, situation, group_symmetry_masks)
      print
      situation = next_situation
    sys.stdout.flush()
    return

  all_lexmins = {}
  pruning_counts = []
  for len_path in xrange(num_bits - 1):
    all_lexmins[len_path] = set()
    pruning_counts.append(0)
  path = []
  continue_play(radius, cutoff, group_symmetry_masks, moves, all_lexmins,
                situation, path, pruning_counts)
  for len_path in xrange(num_bits - 1):
    print len_path, len(all_lexmins[len_path]), pruning_counts[len_path]
  print 'Done.'


if __name__ == '__main__':
  run(args=sys.argv[1:])
