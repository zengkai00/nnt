
# ifndef __WSI_CORE_CHAR_D8E4FE35399742C6BE542AFB4673F0FD_H_INCLUDED
# define __WSI_CORE_CHAR_D8E4FE35399742C6BE542AFB4673F0FD_H_INCLUDED

WSI_BEGIN_HEADER_C

# define CHARHEX_EQUAL 0x3D
# define CHARHEX_REF   0x26
# define CHARHEX_SLASH 0x2F
# define CHARHEX_RSLASH 0x5C
# define CHARHEX_COLON 0x3A
# define CHARHEX_SEMICOLON 0x3B

# define CH2PY_TABLE_SIZE 396

//! global array for convert pinyin to char code.
WSI_EXTERN int __gs_pinyin_code [CH2PY_TABLE_SIZE];

//! global array for convert char code to char.
WSI_EXTERN char const* __gs_pinyin_string [CH2PY_TABLE_SIZE];

//! global array for convert hex-int to hex-char.
WSI_EXTERN char const* __gs_byte_to_hex_str [256];

//! global array for convert hex-char to hex-int.
//! u can use string's MAP_ASCII_BINARY.

WSI_END_HEADER_C

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSI_EXTERN NSString* chinese2pinyin(unichar);
WSI_EXTERN NSArray* chinese2pinyin_stream(void const*, size_t);

WSI_END_HEADER_OBJC

# endif

# endif