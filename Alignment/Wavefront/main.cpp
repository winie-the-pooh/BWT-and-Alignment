#include <iostream>
extern "C"
{
#include <gap_affine/affine_wavefront_align.h>
}


int main() {
    char* pattern = "TCTTTACTCGCGCGTTGGAGAAATACAATAGT";
    char* text    = "TCTATACTGCGCGTTTGGAGAAATAAAATAGT";
    // Allocate MM
    mm_allocator_t* const mm_allocator = mm_allocator_new(BUFFER_SIZE_8M);
    // Set penalties
    affine_penalties_t affine_penalties = {
            .match = 0,
            .mismatch = 4,
            .gap_opening = 6,
            .gap_extension = 2,
    };

    // Init Affine-WFA
    affine_wavefronts_t* affine_wavefronts = affine_wavefronts_new_complete(
            strlen(pattern),strlen(text),&affine_penalties,NULL,mm_allocator);
    // Align
    affine_wavefronts_align(
            affine_wavefronts,pattern,strlen(pattern),text,strlen(text));

    // Display alignment
    const int score = edit_cigar_score_gap_affine(
            &affine_wavefronts->edit_cigar,&affine_penalties);
    fprintf(stderr,"  PATTERN  %s\n",pattern);
    fprintf(stderr,"  TEXT     %s\n",text);
    fprintf(stderr,"  SCORE COMPUTED %d\t",score);
    edit_cigar_print_pretty(stderr,
                            pattern,strlen(pattern),text,strlen(text),
                            &affine_wavefronts->edit_cigar,mm_allocator);
    // Free
    affine_wavefronts_delete(affine_wavefronts);
    mm_allocator_delete(mm_allocator);
}
