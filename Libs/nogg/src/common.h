/*
 * libnogg: a decoder library for Ogg Vorbis streams
 * Copyright (c) 2014-2016 Andrew Church <achurch@achurch.org>
 *
 * This software may be copied and redistributed under certain conditions;
 * see the file "COPYING" in the source code distribution for details.
 * NO WARRANTY is provided with this software.
 */

#ifndef NOGG_SRC_COMMON_H
#define NOGG_SRC_COMMON_H

#include <stdbool.h>

struct stb_vorbis;

/*************************************************************************/
/***************************** Helper macros *****************************/
/*************************************************************************/

/* Convenience macros for testing compiler versions.  major and minor must
 * be literal integers. */
#define IS_CLANG(major,minor)   \
    defined(__clang__)          \
    && (__clang_major__ > major \
        || (__clang_major__ == major && __clang_minor__ >= minor))
#define IS_GCC(major,minor)     \
    defined(__GNUC__)           \
    && (__GNUC__ > major        \
        || (__GNUC__ == major && __GNUC_MINOR__ >= minor))

/**
 * ALIGN:  Attribute indicating that the object to which it is attached
 * should be aligned to a multiple of the given number of bytes, which
 * must be a power of two.
 */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
# define ALIGN(alignment)  _Alignas(alignment)
#elif IS_GCC(2,95) || IS_CLANG(1,0)
# define ALIGN(alignment)  __attribute__((aligned(alignment)))
#else
# define ALIGN(alignment)  /*nothing*/
#endif

/**
 * ASSERT:  Verify that the given condition is true, and abort the program
 * if it is not.  If ENABLE_ASSERT is not defined, the expression is
 * evaluated and its result is discarded; if supported by the compiler, a
 * hint is provided that the expression is always true.
 */
#ifdef ENABLE_ASSERT
# include <assert.h>
# define ASSERT  assert
#else
# define ASSERT(expr)  do {if (UNLIKELY(!(expr))) {UNREACHABLE;}} while (0)
#endif

/**
 * COLD_FUNCTION:  Function attribute indicating that the given function
 * is not expected to be called often.
 */
#if IS_GCC(4,3) || IS_CLANG(3,2)
# define COLD_FUNCTION  __attribute__((cold))
#else
# define COLD_FUNCTION  /*nothing*/
#endif

/**
 * CONST_FUNCTION:  Function attribute indicating that the function's
 * behavior depends only on its arguments and the function has no side
 * effects.
 */
#if IS_GCC(2,95) || IS_CLANG(1,0)
# define CONST_FUNCTION  __attribute__((const))
#else
# define CONST_FUNCTION  /*nothing*/
#endif

/**
 * PURE_FUNCTION:  Function attribute indicating that the function's
 * behavior depends only on its arguments and global state, and the
 * function has no side effects.
 */
#if IS_GCC(3,0) || IS_CLANG(1,0)
# define PURE_FUNCTION  __attribute__((pure))
#else
# define PURE_FUNCTION  /*nothing*/
#endif

/**
 * LIKELY, UNLIKELY:  Construct which indicates to the compiler that the
 * given expression is likely or unlikely to evaluate to true.
 */
#if IS_GCC(3,0) || IS_CLANG(1,0)
# define LIKELY(expr)    (__builtin_expect(!!(expr), 1))
# define UNLIKELY(expr)  (__builtin_expect(!!(expr), 0))
#else
# define LIKELY(expr)    (expr)
# define UNLIKELY(expr)  (expr)
#endif

/**
 * UNREACHABLE:  Compiler intrinsic indicating that the current code
 * location can never be reached.
 */
#if IS_GCC(4,5) || IS_CLANG(2,7)
# define UNREACHABLE  __builtin_unreachable()
#else
# define UNREACHABLE  /*nothing*/
#endif

/**
 * UNUSED:  Attribute indicating that a definition is intentionally unused.
 */
#if IS_GCC(2,95) || IS_CLANG(1,0)
# define UNUSED  __attribute__((unused))
#else
# define UNUSED  /*nothing*/
#endif

/**
 * min, max:  Return the minimum or maximum of two values.  The returned
 * value will be evaluated twice.
 */
#define min(a,b)  ((a) < (b) ? (a) : (b))
#define max(a,b)  ((a) > (b) ? (a) : (b))

/**
 * lenof:  Return the length of (number of elements in) the given array.
 */
#define lenof(array)  ((int)(sizeof((array)) / sizeof(*(array))))

/*-----------------------------------------------------------------------*/

/**
 * INTERNAL:  Prepend "_libnogg_" to the given symbol name.  Used to avoid
 * clashes between internal libnogg functions shared between multiple
 * source files and symbols in client code.
 *
 * This symbol renaming can be disabled by compiling with "-DINTERNAL(x)=x",
 * which may make debugging easier.
 */
#ifndef INTERNAL
# define INTERNAL(name)  _libnogg_##name
#endif

/*************************************************************************/
/*********************** Data types and constants ************************/
/*************************************************************************/

/*
 * Definition of the vorbis_t stream handle structure.
 */

struct vorbis_t {

    /******** Decode options for this handle. ********/

    /* Decode directly to int16 buffers? (VORBIS_OPTION_READ_INT16_ONLY) */
    bool read_int16_only;

    /******** Stream callbacks and related data. ********/

    /* Callbacks used to access the stream data. */
    vorbis_callbacks_t callbacks;
    /* Opaque data pointer for callbacks. */
    void *callback_data;
    /* Data buffer and current read position.  These are used by the
     * open_from_buffer() callbacks to allow the current buffer state to
     * be stored within the stream handle, avoiding the need to inject a
     * malloc() failure to achieve full test coverage at the cost of an
     * extra 12-16 bytes per handle (which we assume is not significant). */
    const char *buffer_data;
    int64_t buffer_read_pos;
    /* Length of stream data in bytes, or -1 if not a seekable stream. */
    int64_t data_length;
    /* Flag: has an I/O error occurred on the stream? */
    unsigned char read_error_flag;

    /******** Decoder handle and related data. ********/

    /* stb_vorbis decode handle. */
    struct stb_vorbis *decoder;

    /******** Audio parameters. ********/

    /* Number of channels. */
    int channels;
    /* Audio sampling rate, in Hz. */
    uint32_t rate;

    /******** Decoding state. ********/

    /* Flag: have we hit the end of the stream? */
    unsigned char eos_flag;
    /* Sample offset of the beginning of the current frame from the
     * beginning of the stream. */
    uint64_t frame_pos;
    /* Buffer holding decoded audio data for the current frame.  The actual
     * type is "int16_t *" if the read_int16_only option is set, "float *"
     * otherwise. */
    void *decode_buf;
    /* Number of samples (per channel) of valid data in decode_buf. */
    int decode_buf_len;
    /* Index of next sample (per channel) in decode_buf to consume. */
    int decode_buf_pos;

};  /* struct vorbis_t */


/* Individual bit flag and value extraction macro for the FAST_HUFFMAN_LENGTH
 * option. */
#define VORBIS_OPTION_FAST_HUFFMAN_LENGTH_FLAG \
    VORBIS_OPTION_FAST_HUFFMAN_LENGTH(0)
#define VORBIS_OPTION_FAST_HUFFMAN_LENGTH_MASK \
    (VORBIS_OPTION_FAST_HUFFMAN_LENGTH(~0U) \
     & ~VORBIS_OPTION_FAST_HUFFMAN_LENGTH_FLAG)
#define VORBIS_OPTION_FAST_HUFFMAN_LENGTH_VALUE(options) \
    ((options) & VORBIS_OPTION_FAST_HUFFMAN_LENGTH_MASK)

/*************************************************************************/
/********************** Internal decoder interface ***********************/
/*************************************************************************/

typedef struct stb_vorbis stb_vorbis;

typedef struct stb_vorbis_info {
    uint32_t sample_rate;
    int32_t nominal_bitrate;
    int32_t min_bitrate;
    int32_t max_bitrate;
    int channels;
    int max_frame_size;
} stb_vorbis_info;

typedef enum STBVorbisError
{
    VORBIS__no_error = 0,

    VORBIS_outofmem,

    VORBIS_unexpected_eof = 10,    // EOF in the middle of stream decoding.
    VORBIS_reached_eof,            // EOF at an Ogg page boundary.

    VORBIS_invalid_setup = 20,     // Invalid data in the stream header.
    VORBIS_invalid_stream,         // Other invalid stream data.
    VORBIS_invalid_packet,         // Invalid packet found (subsequent reads might succeed).

    VORBIS_missing_capture_pattern = 30,
    VORBIS_invalid_stream_structure_version,
    VORBIS_continued_packet_flag_invalid,
    VORBIS_invalid_first_page,
    VORBIS_cant_find_last_page,
    VORBIS_seek_failed,
    VORBIS_wrong_page_number,      // Ogg page number was out of sequence.
} STBVorbisError;

/**
 * stb_vorbis_open_callbacks:  Open a new decoder handle using the given
 * callbacks to read from the stream.
 *
 * [Parameters]
 *     read_callback: Function to call to read data from the stream.
 *     seek_callback: Function to call to seek to an absolute byte
 *         offset in the stream.
 *     tell_callback: Function to call to retrieve the current byte
 *         offset in the stream.
 *     opaque: Opaque parameter passed to all callback functions.
 *     length: Length of stream data in bytes, or -1 if not known.
 *     options: Option flags (VORBIS_OPTION_*).
 *     error_ret: Pointer to variable to receive the error status of
 *         the operation on failure.
 */
#define stb_vorbis_open_callbacks INTERNAL(stb_vorbis_open_callbacks)
extern stb_vorbis * stb_vorbis_open_callbacks(
   int32_t (*read_callback)(void *opaque, void *buf, int32_t len),
   void (*seek_callback)(void *opaque, int64_t offset),
   int64_t (*tell_callback)(void *opaque),
   void *opaque, int64_t length, unsigned int options, int *error_ret);

/**
 * stb_vorbis_close:  Close a decoder handle.
 *
 * [Parameters]
 *     handle: Decoder handle to close.
 */
#define stb_vorbis_close INTERNAL(stb_vorbis_close)
extern void stb_vorbis_close(stb_vorbis *handle);

/**
 * stb_vorbis_get_error:  Retrieve and clear the error code of the last
 * failed operation.
 *
 * [Parameters]
 *     handle: Decoder handle.
 * [Return value]
 *     Error code (VORBIS_* in src/decode/common.h).
 */
#define stb_vorbis_get_error INTERNAL(stb_vorbis_get_error)
extern STBVorbisError stb_vorbis_get_error(stb_vorbis *handle);

/**
 * stb_vorbis_get_info:  Return information about the given stream.
 *
 * [Parameters]
 *     handle: Decoder handle.
 * [Return value]
 *     Stream information.
 */
#define stb_vorbis_get_info INTERNAL(stb_vorbis_get_info)
extern stb_vorbis_info stb_vorbis_get_info(stb_vorbis *handle);

/**
 * stb_vorbis_stream_length_in_samples:  Return the length of the stream.
 * This function returns 0 (unknown) on an unseekable stream.
 *
 * Error conditions can be distinguished from a valid, zero-length stream
 * by checking the stream error code:
 *     (void) stb_vorbis_get_error(handle);
 *     length = stb_vorbis_stream_length_in_samples(handle);
 *     if (length == 0 && stb_vorbis_get_error(handle) != VORBIS__no_error) {
 *         // An error occurred.
 *     }
 *
 * [Parameters]
 *     handle: Decoder handle.
 * [Return value]
 *     Number of samples in the stream, or 0 if unknown.
 */
#define stb_vorbis_stream_length_in_samples INTERNAL(stb_vorbis_stream_length_in_samples)
extern uint64_t stb_vorbis_stream_length_in_samples(stb_vorbis *handle);

/**
 * stb_vorbis_seek:  Seek to the given sample in the stream.
 *
 * [Parameters]
 *     handle: Decoder handle.
 *     sample_number: Sample to seek to (0 is the first sample of the stream).
 * [Return value]
 *     Offset of the requested sample in the next frame returned by
 *     stb_vorbis_get_frame_float(), or 0 on error.
 */
#define stb_vorbis_seek INTERNAL(stb_vorbis_seek)
extern int stb_vorbis_seek(stb_vorbis *handle, uint64_t sample_number);

/**
 * stb_vorbis_tell_pcm:  Return the current sample offset, which is the end
 * of the frame most recently returned by stb_vorbis_get_frame_float() (i.e.,
 * one sample past the offset of the last sample returned from that function).
 *
 * [Parameters]
 *     handle: Decoder handle.
 * [Return value]
 *     Sample offset of the end of the last decoded frame.
 */
#define stb_vorbis_tell_pcm INTERNAL(stb_vorbis_tell_pcm)
extern uint64_t stb_vorbis_tell_pcm(stb_vorbis *handle);

/**
 * stb_vorbis_tell_bits:  Return the current read offset in the data stream
 * (the position of the next bit to be read), in bits.  This function is
 * intended as a debugging convenience and is not used in the normal
 * decoding path.
 *
 * [Parameters]
 *     handle: Decoder handle.
 * [Return value]
 *     Bit offset from the beginning of the stream of the next bit to be
 *     read, or 0 if the stream is not seekable.
 */
#define stb_vorbis_tell_bits INTERNAL(stb_vorbis_tell_bits)
extern uint64_t stb_vorbis_tell_bits(stb_vorbis *handle);

/**
 * stb_vorbis_reset_eof:  Clear the given stream's end-of-file status.
 * This can be used to resume decoding with streaming input when new data
 * becomes available after a previous end-of-file result.
 *
 * [Parameters]
 *     handle: Decoder handle.
 */
#define stb_vorbis_reset_eof INTERNAL(stb_vorbis_reset_eof)
extern void stb_vorbis_reset_eof(stb_vorbis *handle);

/**
 * stb_vorbis_get_frame_float:  Decode the next Vorbis frame into
 * floating-point PCM samples.
 *
 * [Parameters]
 *     handle: Decoder handle.
 *     output_ret: Pointer to variable to receive a pointer to the
 *         two-dimensional PCM output array.
 *     len_ret: Pointer to variable to receive the frame length in samples.
 * [Return value]
 *     True if a frame was successfully decoded; false on error or end of
 *     stream.
 */
#define stb_vorbis_get_frame_float INTERNAL(stb_vorbis_get_frame_float)
extern bool stb_vorbis_get_frame_float(stb_vorbis *handle, float ***output_ret,
                                       int *len_ret);

/*************************************************************************/
/*************************************************************************/

#endif  /* NOGG_SRC_COMMON_H */
