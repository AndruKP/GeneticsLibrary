// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>

#include "sequence.h"
#include "gtest/gtest.h"

using namespace ::testing;

//sequence.h
TEST(TestSequence, TestClassicConstructors) {
  const std::string stringSeq = "ACTG";
  Sequence emptySeq;
  Sequence seq(stringSeq);
  ASSERT_EQ(stringSeq, seq.getSequence());
  ASSERT_EQ("", emptySeq.getSequence());
}

/// todo consider deletion
TEST(TestSequence, SetSequence) {
  const std::string stringSeq = "ACTG";
  Sequence seq(stringSeq);
  ASSERT_EQ(stringSeq, seq.getSequence());
  const std::string stringSeq2 = "AAAA";

  seq.setSequence(stringSeq2);
  ASSERT_EQ(stringSeq2, seq.getSequence());

  seq.setSequence(stringSeq2);
  ASSERT_EQ(stringSeq2, seq.getSequence());

  seq.setSequence("");
  ASSERT_EQ("", seq.getSequence());
}

TEST(TestSequence, TestCopyConstructor) {
  std::string stringSeq = "ACTG";
  Sequence seq1(stringSeq);
  Sequence seq2(seq1);

  ASSERT_EQ(stringSeq, seq1.getSequence());
  ASSERT_EQ(stringSeq, seq2.getSequence());

  stringSeq = "";
  Sequence seq3(stringSeq);
  Sequence seq4(seq3);

  ASSERT_EQ(stringSeq, seq3.getSequence());
  ASSERT_EQ(stringSeq, seq4.getSequence());
}

TEST(TestSequence, TestMoveConstructor) {
  std::string stringSeq = "MerryChristmas";
  Sequence seq1(stringSeq);
  ASSERT_EQ(stringSeq, seq1.getSequence());

  Sequence seq2{std::move(seq1)};
  ASSERT_EQ(stringSeq, seq2.getSequence());
  ASSERT_EQ("", seq1.getSequence());
}

TEST(TestSequence, TestCopyOperator) {
  std::string stringSeq = "MerryChristmas";
  Sequence seq1(stringSeq);
  ASSERT_EQ(stringSeq, seq1.getSequence());

  Sequence seq2("ACGT");

  seq2 = seq1;
  ASSERT_EQ(stringSeq, seq2.getSequence());
  ASSERT_EQ(stringSeq, seq1.getSequence());
}

TEST(TestSequence, TestMoveOperator) {
  std::string stringSeq = "MerryChristmas";
  Sequence seq1(stringSeq);
  ASSERT_EQ(stringSeq, seq1.getSequence());

  Sequence seq2("ACGT");

  seq2 = std::move(seq1);
  ASSERT_EQ(stringSeq, seq2.getSequence());
  ASSERT_EQ("", seq1.getSequence());
}

TEST(TestSequence, TestReverse) {
  std::string stringSeq = "MerryChristmas";
  Sequence seq1(stringSeq);
  ASSERT_EQ(stringSeq, seq1.getSequence());

  seq1.reverse();
  ASSERT_EQ("samtsirhCyrreM", seq1.getSequence());
}

TEST(TestSequence, TestReplaceCharacters) {
  std::string stringSeq = "MerryChristmas";
  const std::map<char, char> charMap{
    {'r', 'x'},
    {'e', 'a'},
    {'m', 'M'},
    {'s', 's'}
  };
  Sequence seq1(stringSeq);
  ASSERT_EQ(stringSeq, seq1.getSequence());

  seq1.replaceChars(charMap);
  ASSERT_EQ("MaxxyChxistMas", seq1.getSequence());
}

TEST(TestSequence, TestTranslate) {
  const std::string stringSeq = "MerryChristmas";
  const std::map<char, char> charMap{
    {'r', 'x'},
    {'e', 'a'},
    {'m', 'M'},
    {'s', 's'}
  };
  Sequence seq1(stringSeq);
  ASSERT_EQ(stringSeq, seq1.getSequence());

  auto seq2 = seq1.translate(charMap);
  ASSERT_EQ("MaxxyChxistMas", seq2.getSequence());
}

TEST(TestSequence, TestLevenshteinDistance) {
  const std::string s1 = "taller";
  const std::string s2 = "falling";
  //dist = 4
  Sequence seq1(s1);
  Sequence seq2(s2);
  ASSERT_EQ(seq1.levenshteinDistance(seq2), 4);
  ASSERT_EQ(seq2.levenshteinDistance(seq1), 4);
  ASSERT_EQ(seq1.levenshteinDistance(seq1), 0);

  Sequence seq3("to maintain");
  Sequence seq4("mountain");

  // 3 additions or insertions : to mountain + 2 substitutions -- to maintain

  ASSERT_EQ(seq3.levenshteinDistance(seq4), 5);
  ASSERT_EQ(seq4.levenshteinDistance(seq3), 5);
}

TEST(TestSequence, TestLevDistTime) {
  std::ostringstream oss1;
  // algo is NM, so try
  int N = 10000;
  for (auto i = 0; i < N; ++i) {
    oss1 << i;
  }

  std::ostringstream oss2;

  for (auto i = N - 1; i > 0; --i) {
    oss2 << i;
  }

  Sequence seq1(oss1.str());
  Sequence seq2(oss2.str());

  ASSERT_NE(seq1.levenshteinDistance(seq2), 0);
}
