/*
 * Copyright (c) 2018 Zilliqa
 * This source code is being disclosed to you solely for the purpose of your
 * participation in testing Zilliqa. You may view, compile and run the code for
 * that purpose and pursuant to the protocols and algorithms that are programmed
 * into, and intended by, the code. You may not do anything else with the code
 * without express permission from Zilliqa Research Pte. Ltd., including
 * modifying or publishing the code (or any part of it), and developing or
 * forming another public or private blockchain network. This source code is
 * provided 'as is' and no warranties are given as to title or non-infringement,
 * merchantability or fitness for purpose and, to the extent permitted by law,
 * all liability for your use of the code is disclaimed. Some programs in this
 * code are governed by the GNU General Public License v3.0 (available at
 * https://www.gnu.org/licenses/gpl-3.0.en.html) ('GPLv3'). The programs that
 * are governed by GPLv3.0 are those programs that are located in the folders
 * src/depends and tests/depends and which include a reference to GPLv3 in their
 * program files.
 */

#include "TestUtils.h"

using namespace std;
using namespace boost::multiprecision;

namespace TestUtils {
void Initialize() { rng.seed(std::random_device()()); }

uint8_t DistUint8() {
  return RandomIntInRng<uint8_t>(std::numeric_limits<uint8_t>::min(),
                                 std::numeric_limits<uint8_t>::max());
}
uint16_t DistUint16() {
  return RandomIntInRng<uint16_t>(std::numeric_limits<uint16_t>::min(),
                                  std::numeric_limits<uint16_t>::max());
}
uint32_t DistUint32() {
  return RandomIntInRng<uint32_t>(std::numeric_limits<uint32_t>::min(),
                                  std::numeric_limits<uint32_t>::max());
}

uint64_t DistUint64() {
  return RandomIntInRng<uint64_t>(std::numeric_limits<uint64_t>::min(),
                                  std::numeric_limits<uint64_t>::max());
}

uint128_t DistUint128() {
  uint128_t left64Rnd = DistUint64();
  uint128_t righ64tRnd = DistUint64();
  return left64Rnd << 64 | righ64tRnd;
}

uint256_t DistUint256() {
  uint256_t left128Rnd = DistUint128();
  uint256_t righ128tRnd = DistUint128();
  return left128Rnd << 128 | righ128tRnd;
}

uint8_t Dist1to99() { return RandomIntInRng<uint8_t>((uint8_t)1, (uint8_t)99); }

PubKey GenerateRandomPubKey() { return PubKey(PrivKey()); }

Peer GenerateRandomPeer() {
  uint128_t ip_address = DistUint32();
  uint32_t listen_port_host = DistUint32();
  return Peer(ip_address, listen_port_host);
}

Peer GenerateRandomPeer(uint8_t bit_i, bool setreset) {
  uint128_t ip_address = DistUint32();
  uint32_t listen_port_host = DistUint32();
  if (setreset) {
    ip_address |= 1UL << bit_i;
  } else {
    ip_address &= ~(1UL << bit_i);
  }
  return Peer(ip_address, listen_port_host);
}

PubKey GenerateRandomPubKey(PrivKey privK) { return PubKey(privK); }

KeyPair GenerateRandomKeyPair() {
  PrivKey privk;
  return KeyPair(privk, GenerateRandomPubKey(privk));
}

DSBlockHeader GenerateRandomDSBlockHeader() {
  uint8_t dsDifficulty = DistUint8();
  uint8_t difficulty = DistUint8();
  BlockHash prevHash;
  PubKey leaderPubKey = GenerateRandomPubKey();
  uint64_t blockNum = DistUint32();
  uint64_t epochNum = DistUint32();
  uint128_t gasPrice = PRECISION_MIN_VALUE;
  SWInfo swInfo;
  map<PubKey, Peer> powDSWinners;
  DSBlockHashSet hash;
  CommitteeHash committeeHash;

  for (unsigned int i = 0, count = Dist1to99(); i < count; i++) {
    powDSWinners.emplace(GenerateRandomPubKey(), GenerateRandomPeer());
  }

  return DSBlockHeader(dsDifficulty, difficulty, prevHash, leaderPubKey,
                       blockNum, epochNum, gasPrice, swInfo, powDSWinners, hash,
                       committeeHash);
}

MicroBlockHeader GenerateRandomMicroBlockHeader() {
  uint8_t type = DistUint8();
  uint32_t version = DistUint32();
  uint32_t shardId = DistUint32();
  uint64_t gasLimit = DistUint32();
  uint64_t gasUsed = DistUint32();
  uint128_t rewards = DistUint32();
  BlockHash prevHash;
  uint64_t epochNum = DistUint32();
  MicroBlockHashSet hashset;
  uint32_t numTxs = Dist1to99();
  PubKey minerPubKey = GenerateRandomPubKey();
  uint64_t dsBlockNum = DistUint32();
  CommitteeHash committeeHash;

  return MicroBlockHeader(type, version, shardId, gasLimit, gasUsed, rewards,
                          prevHash, epochNum, hashset, numTxs, minerPubKey,
                          dsBlockNum, committeeHash);
}

TxBlockHeader GenerateRandomTxBlockHeader() {
  uint8_t type = DistUint8();
  uint32_t version = DistUint32();
  uint64_t gasLimit = DistUint32();
  uint64_t gasUsed = DistUint32();
  uint128_t rewards = DistUint32();
  BlockHash prevHash;
  uint64_t blockNum = DistUint32();
  TxBlockHashSet blockHashSet;
  uint32_t numTxs = Dist1to99();
  PubKey minerPubKey = GenerateRandomPubKey();
  uint64_t dsBlockNum = DistUint32();
  BlockHash dsBlockHeader;
  CommitteeHash committeeHash;

  return TxBlockHeader(type, version, gasLimit, gasUsed, rewards, prevHash,
                       blockNum, blockHashSet, numTxs, minerPubKey, dsBlockNum,
                       committeeHash);
}

VCBlockHeader GenerateRandomVCBlockHeader() {
  uint64_t vieWChangeDSEpochNo = DistUint32();
  uint64_t viewChangeEpochNo = DistUint32();
  unsigned char viewChangeState = DistUint8();
  Peer candidateLeaderNetworkInfo = GenerateRandomPeer();
  PubKey candidateLeaderPubKey = GenerateRandomPubKey();
  uint32_t vcCounter = DistUint32();
  vector<pair<PubKey, Peer>> faultyLeaders;
  CommitteeHash committeeHash;
  BlockHash prevHash;

  for (unsigned int i = 0, count = Dist1to99(); i < count; i++) {
    faultyLeaders.emplace_back(GenerateRandomPubKey(), GenerateRandomPeer());
  }

  return VCBlockHeader(vieWChangeDSEpochNo, viewChangeEpochNo, viewChangeState,
                       candidateLeaderNetworkInfo, candidateLeaderPubKey,
                       vcCounter, faultyLeaders, committeeHash, prevHash);
}

FallbackBlockHeader GenerateRandomFallbackBlockHeader() {
  uint64_t fallbackDSEpochNo = DistUint32();
  uint64_t fallbackEpochNo = DistUint32();
  unsigned char fallbackState = DistUint8();
  FallbackBlockHashSet hashset;
  uint32_t leaderConsensusId = DistUint32();
  Peer leaderNetworkInfo = GenerateRandomPeer();
  PubKey leaderPubKey = GenerateRandomPubKey();
  uint32_t shardId = DistUint32();
  CommitteeHash committeeHash;
  BlockHash prevHash;

  return FallbackBlockHeader(fallbackDSEpochNo, fallbackEpochNo, fallbackState,
                             hashset, leaderConsensusId, leaderNetworkInfo,
                             leaderPubKey, shardId, committeeHash, prevHash);
}

DS_Comitte_t GenerateRandomDSCommittee(uint32_t size) {
  DS_Comitte_t ds_c;
  for (uint32_t i = 1; i <= size; i++) {
    ds_c.push_front(std::make_pair(GenerateRandomPubKey(), Peer()));
  }
  return ds_c;
}

Shard GenerateRandomShard(size_t size) {
  Shard s;
  for (size_t i = 1; i <= size; i++) {
    s.push_back(std::make_tuple(GenerateRandomPubKey(PrivKey()),
                                GenerateRandomPeer(), DistUint16()));
  }
  return s;
}

DequeOfShard GenerateDequeueOfShard(size_t size) {
  DequeOfShard dos;
  for (size_t i = 1; i <= size; i++) {
    dos.push_front(GenerateRandomShard(i));
  }
  return dos;
}

CoSignatures GenerateRandomCoSignatures() { return CoSignatures(Dist1to99()); }

std::string GenerateRandomString(size_t length) {
  auto randchar = []() -> char {
    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = (sizeof(charset) - 2);
    return charset[RandomIntInRng<uint8_t>((uint8_t)0, (uint8_t)max_index)];
  };
  std::string str(length, 0);
  std::generate_n(str.begin(), length, randchar);
  return str;
}

}  // namespace TestUtils
