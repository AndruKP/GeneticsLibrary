#pragma once
#include <map>
#include <string>
#include "ErrorsConstants.h"

enum class Directionality { DIR_3_to_5, DIR_5_to_3 };

enum class ReplicationStatus { LEADING, LAGGING };

enum class TranscriptionStatus { TEMPLATE, CODING };


/// adenine (A), cytosine (C), guanine (G), thymine (T)
/// NOTE: currently there are no specific bases like aminoadenine (Z)
const inline std::string CORRECT_DNA_BASES = {'A', 'C', 'G', 'T'};
constexpr int NUM_OF_CORRECT_DNA_BASES = 4;
const std::map<char, char> DNA_COMPLEMENTS{
    {'A', 'T'},
    {'T', 'A'},
    {'C', 'G'},
    {'G', 'C'}
};

///adenine (A), cytosine (C), guanine (G), uracil (U)
const inline std::string CORRECT_RNA_BASES{'A', 'C', 'G', 'U'};
constexpr int NUM_OF_CORRECT_RNA_BASES = 4;
const std::map<char, char> RNA_COMPLEMENTS{
    {'A', 'U'},
    {'U', 'A'},
    {'C', 'G'},
    {'G', 'C'}
};


const std::map<char, char> TRANSCRIPTION_TABLE{
    {'T', 'A'},
    {'A', 'U'},
    {'C', 'G'},
    {'G', 'C'}
};

const std::map<char, char> REVERSE_TRANSCRIPTION_TABLE{
    {'U', 'A'},
    {'A', 'T'},
    {'C', 'G'},
    {'G', 'C'}
};


/// Note: there is used only classic start codon "AUG"
const std::map<std::string, std::string> TRANSLATION_TABLE{
    {"UUU", "Phe"}, {"UUC", "Phe"}, // Phenylalanine
    {"UUA", "Leu"}, {"UUG", "Leu"}, {"CUU", "Leu"}, {"CUC", "Leu"}, {"CUA", "Leu"}, {"CUG", "Leu"}, // Leucine
    {"AUU", "Ile"}, {"AUC", "Ile"}, {"AUA", "Ile"}, // Isoleucine
    {"AUG", "Met"}, // Methionine (Classic start codon)
    {"GUU", "Val"}, {"GUC", "Val"}, {"GUA", "Val"}, {"GUG", "Val"}, // Valine (GUG is non-classic start codon)
    {"UCU", "Ser"}, {"UCC", "Ser"}, {"UCA", "Ser"}, {"UCG", "Ser"}, // Serine
    {"CCU", "Pro"}, {"CCC", "Pro"}, {"CCA", "Pro"}, {"CCG", "Pro"}, // Proline
    {"ACU", "Thr"}, {"ACC", "Thr"}, {"ACA", "Thr"}, {"ACG", "Thr"}, // Threonine
    {"GCU", "Ala"}, {"GCC", "Ala"}, {"GCA", "Ala"}, {"GCG", "Ala"}, // Alanine
    {"UAU", "Tyr"}, {"UAC", "Tyr"}, // Tyrosine
    {"UAA", "Stop"}, // Stop codon (Ochre)
    {"UAG", "Stop"}, // Stop codon (Amber)
    {"CAU", "His"}, {"CAC", "His"}, // Histidine
    {"CAA", "Gln"}, {"CAG", "Gln"}, // Glutamine
    {"AAU", "Asn"}, {"AAC", "Asn"}, // Asparagine
    {"AAA", "Lys"}, {"AAG", "Lys"}, // Lysine
    {"GAU", "Asp"}, {"GAC", "Asp"}, // Aspartic Acid
    {"GAA", "Glu"}, {"GAG", "Glu"}, // Glutamic Acid
    {"UGU", "Cys"}, {"UGC", "Cys"}, // Cysteine
    {"UGA", "Stop"}, // Stop codon (Opal)
    {"UGG", "Trp"}, // Tryptophan
    {"CGU", "Arg"}, {"CGC", "Arg"}, {"CGA", "Arg"}, {"CGG", "Arg"}, // Arginine
    {"AGU", "Ser"}, {"AGC", "Ser"}, // Serine
    {"AGA", "Arg"}, {"AGG", "Arg"}, // Arginine
    {"GGU", "Gly"}, {"GGC", "Gly"}, {"GGA", "Gly"}, {"GGG", "Gly"} // Glycine
};
