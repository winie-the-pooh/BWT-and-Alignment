#set(SRC utils/commons.c utils/dna_text.c utils/string_padded.c utils/vector.c
#        system/mm_allocator.c system/profiler_counter.c system/profiler_timer.c
#        gap_affine/affine_penalties.c gap_affine/affine_table.c gap_affine/affine_wavefront.c
#        gap_affine/affine_wavefront_align.c gap_affine/affine_wavefront_backtrace.c
#        gap_affine/affine_wavefront_display.c gap_affine/affine_wavefront_extend.c
#        gap_affine/affine_wavefront_penalties.c gap_affine/affine_wavefront_reduction.c
#        gap_affine/affine_wavefront_utils.c gap_affine/swg.c gap_affine/wavefront_stats.c
#        edit/edit_cigar.c edit/edit_dp.c edit/edit_table.c)
file(GLOB SRC system/*.c system/*.h utils/*.c utils/*.h gap_affine/*.c gap_affine/*.h edit/*.c edit/*.h)

add_library(wfa STATIC ${SRC})