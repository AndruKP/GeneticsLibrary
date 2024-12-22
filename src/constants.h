//
// Created by andru_kfgnofp on 12/22/2024.
//

#pragma once
#include <map>

enum class Directionality { DIR_3_to_5, DIR_5_to_3 };

enum class ReplicationStatus { LEADING, LAGGING };

enum class TranscriptionStatus { TEMPLATE, CODING };


/// adenine (A), cytosine (C), guanine (G), thymine (T)
/// NOTE: currently there are no specific bases like aminoadenine (Z)
constexpr char CORRECT_DNA_BASES[] = {'A', 'C', 'G', 'T'};
constexpr int NUM_OF_CORRECT_DNA_BASES = 4;
const std::map<char, char> DNA_COMPLEMENTS{
    {'A', 'T'},
    {'T', 'A'},
    {'C', 'G'},
    {'G', 'C'}
};


const std::string DNA_WRONG_SYMBOL_MESSAGE = "DNA::checkCorrectness() failed: there is a bad symbol in sequence";


///adenine (A), cytosine (C), guanine (G), uracil (U)
constexpr char CORRECT_RNA_BASES[]{'A', 'C', 'G', 'U'};
constexpr int NUM_OF_CORRECT_RNA_BASES = 4;
const std::map<char, char> RNA_COMPLEMENTS{
    {'A', 'U'},
    {'U', 'A'},
    {'C', 'G'},
    {'G', 'C'}
};


const std::map<char, char> TRANSCRIPTION_TABLE{
    {'A', 'A'}
};



