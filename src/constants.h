#pragma once
#include <map>
#include <string>
#include "ErrorsConstants.h"

/**
 * Directionality of strand - 3' to 5' or 5' to 3'
 */
enum class Directionality { DIR_3_to_5, DIR_5_to_3 };

enum class ReplicationStatus { LEADING, LAGGING };

/**
 * Status of strand -- is it template for RNA, or it's coding strand
 */
enum class TranscriptionStatus { TEMPLATE, CODING };

constexpr auto DEFAULT_DIRECT_STATUS = Directionality::DIR_3_to_5;
constexpr auto DEFAULT_REPL_STATUS = ReplicationStatus::LEADING;
constexpr auto DEFAULT_TRNSCPT_STATUS = TranscriptionStatus::TEMPLATE;


/// adenine (A), cytosine (C), guanine (G), thymine (T)
///
/// @note: currently there are no specific bases like aminoadenine (Z)
/// and no FASTA "combinations" like N (which states for aNy base)
const inline std::string CORRECT_DNA_BASES = {'A', 'C', 'G', 'T'};
constexpr int NUM_OF_CORRECT_DNA_BASES = 4;
/**
 * Complementary bases: see Chargaff's rules and complementarity principe
 */
const std::map<char, char> DNA_COMPLEMENTS{
    {'A', 'T'},
    {'T', 'A'},
    {'C', 'G'},
    {'G', 'C'}
};

///adenine (A), cytosine (C), guanine (G), uracil (U)
const inline std::string CORRECT_RNA_BASES{'A', 'C', 'G', 'U'};
constexpr int NUM_OF_CORRECT_RNA_BASES = 4;
/**
 * Complementary bases for RNA: see Chargaff's rules and complementarity principe
 */
const std::map<char, char> RNA_COMPLEMENTS{
    {'A', 'U'},
    {'U', 'A'},
    {'C', 'G'},
    {'G', 'C'}
};

/// Table for transcription DNA (template strand) into RNA
const std::map<char, char> TRANSCRIPTION_TABLE_FOR_TEMPLATE_STRAND{
    {'T', 'A'},
    {'A', 'U'},
    {'C', 'G'},
    {'G', 'C'}
};

/// Table for transcription DNA (coding strand) into RNA
const std::map<char, char> TRANSCRIPTION_TABLE_FOR_CODING_STRAND{
    {'A', 'A'},
    {'T', 'U'},
    {'C', 'C'},
    {'G', 'G'}
};

/// Table for reverse transcription RNA into DNA (template string)
const std::map<char, char> REVERSE_TRANSCRIPTION_TO_TEMPLATE_STRAND{
    {'U', 'A'},
    {'A', 'T'},
    {'C', 'G'},
    {'G', 'C'}
};

/// Table for reverse transcription RNA into DNA (coding string)
const std::map<char, char> REVERSE_TRANSCRIPTION_TO_CODING_STRAND{
    {'A', 'A'},
    {'U', 'T'},
    {'C', 'C'},
    {'G', 'G'}
};

constexpr int CODON_LENGTH = 3;
/// Table for mapping 3-letter codons to names of aminoacids
/// @note: there is used only classic start codon "AUG"
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

/// Standard cost for insertion of a new symbol (used in Wagner-Fisher algo)
constexpr long long INSERTION_COST = -1;
/// Standard cost for deletion of a symbol (used in Wagner-Fisher algo)
constexpr long long DELETION_COST = -1;
/// Standard cost for a pair of equal symbols (used in Wagner-Fisher algo)
constexpr long long MATCH_COST = 1;
/// Standard cost for a pair of different symbols (used in Wagner-Fisher algo)
constexpr long long MISMATCH_COST = -1;

/// Size of one line of the output in FASTA format
constexpr size_t FASTA_OUTPUT_LINE_SIZE = 80;
